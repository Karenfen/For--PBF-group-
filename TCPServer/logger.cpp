#include "logger.h"

std::mutex Logger::mtx;


Logger::Logger()
{
    file.open("log.txt", std::ios::out | std::ios::app);
    if (!file.is_open())
    {
        throw std::ios_base::failure("Failed to open file");
    }
}

void Logger::WriteToLog(const std::string &str)
{
    if (file.is_open())
    {
        file << str << std::endl;
    }
}

Logger::~Logger()
{
    if (file.is_open()) {
        file.close();
    }
}
Logger &Logger::GetInstance()
{
    std::lock_guard<std::mutex> lock(mtx);
    static Logger instance;
    return instance;
}
