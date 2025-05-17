// Connection.hpp
#pragma once
#include <string>

class Connection {
public:
    Connection(int client_fd, const std::string& root_dir);
    void process();

private:
    int client_fd;
    std::string root_dir;
};
