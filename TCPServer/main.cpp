#include <iostream>
#include "tcpserver.h"

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return 1;
    }

    int listen_port = std::stoi(argv[1]);

    if(listen_port <0 || listen_port > 65535)
    {
        std::cerr << "Invalid listen port: " << listen_port << std::endl;
        return 1;
    }

    TCPServer server(listen_port);

    std::cout << "Server is running..." << std::endl;

    server.Run();

    return 0;
}
