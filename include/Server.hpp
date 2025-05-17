#pragma once
#include <string>
#include "ThreadPool.hpp"

class Server {
public:
    Server(int port, const std::string& root_dir);
    void run();

private:
    int port;
    int listen_fd;
    std::string root_dir;
    ThreadPool thread_pool;

    void setup_socket();
    void handle_connections();
};
