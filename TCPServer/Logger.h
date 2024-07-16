#pragma once

#include <string>
#include <fstream>
#include <mutex>



class Logger
{
public:
    Logger& GetInstance()
    {

    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    Logger()
    {
        file.open("log.txt", std::ios::out | std::ios::app);
        if (!file.is_open())
        {
            throw std::ios_base::failure("Failed to open file");
        }
    }

    ~Logger()
    {
        if (file.is_open()) {
            file.close();
        }
    }

private:
    std::ofstream file;
    static std::mutex mtx;
};
