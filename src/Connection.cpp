// Connection.cpp
#include "Connection.hpp"
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <iostream>

Connection::Connection(int client_fd, const std::string& root_dir)
    : client_fd(client_fd), root_dir(root_dir) {}

void Connection::process() {
    char buffer[4096];
    int bytes = read(client_fd, buffer, sizeof(buffer) - 1);
    if (bytes <= 0) {
        close(client_fd);
        return;
    }
    buffer[bytes] = '\0';
    std::istringstream request(buffer);
    std::string method, path, version;
    request >> method >> path >> version;

    std::string file_path = root_dir + path;
    if (file_path.back() == '/') file_path += "index.html";

    std::ifstream file(file_path);
    std::string response;
    if (file) {
        std::ostringstream ss;
        ss << file.rdbuf();
        std::string body = ss.str();
        response = "HTTP/1.1 200 OK\r\nContent-Length: " + std::to_string(body.size()) +
                   "\r\nContent-Type: text/html\r\n\r\n" + body;
    } else {
        std::string body = "<h1>404 Not Found</h1>";
        response = "HTTP/1.1 404 Not Found\r\nContent-Length: " + std::to_string(body.size()) +
                   "\r\nContent-Type: text/html\r\n\r\n" + body;
    }
    write(client_fd, response.c_str(), response.size());
    close(client_fd);
}
