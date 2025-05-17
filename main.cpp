#include "Server.hpp"

int main() {
    Server server(8080, "./public");
    server.run();
    return 0;
}
