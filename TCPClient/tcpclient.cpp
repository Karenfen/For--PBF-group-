#include "tcpclient.h"
#include <iostream>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <thread>


TCPClient::TCPClient(const std::string& name, const std::string& ip, int port, int interval)
    : client_name(name), server_ip(ip), server_port(port), interval_ms(interval)
{
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
}

TCPClient::~TCPClient()
{

}

void TCPClient::Run()
{
    while (true)
    {
        Socket socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if (connectToServer(*socket))
        {
            std::cout << "Connected to server!" << std::endl;

            if (sendData(*socket, generate_data()))
            {
                std::cout << "Data sent!" << std::endl;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
    }
}

bool TCPClient::connectToServer(int socket)
{   
    if (socket == -1)
    {
        std::cerr << "Socket creation failed!" << std::endl;
        return false;
    }

    if (inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr) <= 0)
    {
        std::cerr << "Invalid address!" << std::endl;
        return false;
    }

    if (connect(socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        std::cerr << "Connection failed!" << std::endl;
        return false;
    }

    return true;
}

bool TCPClient::sendData(int socket, const std::string &data)
{
    if (socket == -1)
    {
        std::cerr << "Socket not connected!" << std::endl;
        return false;
    }

    if (send(socket, data.c_str(), data.length(), 0) < 0)
    {
        std::cerr << "Send failed!" << std::endl;
        return false;
    }

    return true;
}

std::string TCPClient::generate_data()
{
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    std::tm now_tm;
    localtime_r(&now_time_t, &now_tm);

    std::ostringstream oss;
    oss << '[' << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
    oss << '.' << std::setfill('0') << std::setw(3) << now_ms.count() << "] " << client_name;

    return oss.str();
}
