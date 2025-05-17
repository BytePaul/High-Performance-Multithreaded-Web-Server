// Server.cpp
#include "Server.hpp"
#include "Connection.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <poll.h>

Server::Server(int port, const std::string& root_dir)
    : port(port), root_dir(root_dir), thread_pool(4) {}

void Server::setup_socket() {
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    bind(listen_fd, (sockaddr*)&addr, sizeof(addr));
    listen(listen_fd, SOMAXCONN);

    fcntl(listen_fd, F_SETFL, O_NONBLOCK);
}

void Server::run() {
    setup_socket();
    std::cout << "Server running on port " << port << std::endl;
    handle_connections();
}

void Server::handle_connections() {
    pollfd fds[1024];
    fds[0].fd = listen_fd;
    fds[0].events = POLLIN;
    int nfds = 1;

    while (true) {
        int ret = poll(fds, nfds, -1);
        if (ret < 0) continue;

        for (int i = 0; i < nfds; ++i) {
            if (fds[i].revents & POLLIN) {
                if (fds[i].fd == listen_fd) {
                    int client_fd = accept(listen_fd, nullptr, nullptr);
                    fcntl(client_fd, F_SETFL, O_NONBLOCK);
                    fds[nfds].fd = client_fd;
                    fds[nfds].events = POLLIN;
                    nfds++;
                } else {
                    int client_fd = fds[i].fd;
                    thread_pool.enqueue([this, client_fd]() {
                        Connection conn(client_fd, root_dir);
                        conn.process();
                    });
                    fds[i] = fds[nfds - 1];
                    nfds--;
                }
            }
        }
    }
}
