#include "tcpserver.h"
#include <iostream>
#include <thread>
#include <cstring>
#include "logger.h"


TCPServer::TCPServer(int port)
{
    socket_listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
}

void TCPServer::Run()
{
    if(socket_listener == -1)
    {
        std::cerr << "Socket creation failed!" << std::endl;
        return;
    }

    if (bind(*socket_listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        std::cerr << "Socket binding failed!" << std::endl;
        return;
    }

    if (listen(*socket_listener, MAX_CONNECTION_REQUESTS) == -1)
    {
        std::cerr << "Socket listening failed!" << std::endl;
        return;
    }

    while (true)
    {
        int sock = accept(*socket_listener, NULL, NULL);

        if (sock == -1)
        {
            std::cerr << "Connection accept failed!" << std::endl;
            continue;
        }

        std::thread(&TCPServer::handle_connection, this, sock).detach();
    }

}

void TCPServer::handle_connection(int socket)
{
    Socket client_socket(socket);
    char buffer[BUFFER_SIZE];
    int bytes_received;

    bytes_received = recv(*client_socket, buffer, BUFFER_SIZE - 1, 0);
    buffer[bytes_received] = '\0';

    if (bytes_received == -1)
    {
        std::cerr << "Reading failed!" << std::endl;
    }

    Logger::GetInstance().WriteToLog(std::string(buffer));
}
