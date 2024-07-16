#pragma once

#include <string>
#include <chrono>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>




class TCPClient {
public:
    TCPClient(const std::string& name, const std::string& ip, int port, int interval);
    ~TCPClient();
    void Run();

private:

    bool connectToServer(int socket);
    bool sendData(int socket, const std::string& data);
    std::string generate_data();

private:
    const std::string client_name;
    const std::string server_ip;
    const int server_port;
    const int interval_ms;
    sockaddr_in server_addr;

};

class Socket
{
public:
    Socket(int __domain, int __type, int __protocol)
    {
        sock_fd = socket(__domain, __type, __protocol);
    }

    ~Socket()
    {
        if (sock_fd != -1)
        {
            close(sock_fd);
        }
    }

    int operator*() const { return sock_fd; }

private:
    int sock_fd;
};
