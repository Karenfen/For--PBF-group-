#pragma once

#include <string>
#include <fstream>
#include <mutex>



class Logger
{
public:
    static Logger& GetInstance();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void WriteToLog(const std::string& str);

private:
    Logger();
    ~Logger();

private:
    std::ofstream file;
    static std::mutex mtx;
};
