#include <iostream>
#include "tcpclient.h"



int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " <name> <port> <interval (ms)>" << std::endl;
        return 1;
    }

    int server_port = std::stoi(argv[2]);

    if(server_port <0 || server_port > 65535)
    {
        std::cerr << "Invalid server port: " << server_port << std::endl;
        return 1;
    }

    int interval = std::stoi(argv[3]);

    if(interval <= 0)
    {
        std::cerr << "Invalid interval: " << interval << std::endl;
        return 1;
    }

    std::string server_ip = "127.0.0.1";
    TCPClient client(std::string(argv[1]), server_ip, server_port, interval);

    std::cout << "Client is running..." << std::endl;

    client.Run();

    return 0;
}
