#pragma once

#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>


// Maximum connection requests will be queued before further requests are refused.
#define MAX_CONNECTION_REQUESTS 100
#define BUFFER_SIZE 1024

class Socket
{
public:
    Socket() : sock_fd(-1) {}

    Socket(int __domain, int __type, int __protocol)
    {
        sock_fd = socket(__domain, __type, __protocol);
    }

    Socket(int socket) : sock_fd(socket) {}

    ~Socket()
    {
        if (sock_fd != -1)
        {
            close(sock_fd);
        }
    }

    int operator*() const { return sock_fd; }

    Socket& operator=(int socket)
    {
        if (sock_fd != -1)
        {
            close(sock_fd);
        }

        sock_fd = socket;

        return *this;
    }

    bool operator==(int socket) { return sock_fd == socket; }

private:
    int sock_fd;
};


class TCPServer
{
public:
    TCPServer(int port);
    void Run();

private:
    void handle_connection(int socket);

private:
    Socket socket_listener;
    struct sockaddr_in addr;
};
