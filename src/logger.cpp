#include <iostream>
#include "windows.h"
#include <fcntl.h>
#include "logger.h"


Logger::Logger()
{
    #ifdef _DEBUG
    AllocConsole();

    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    int hCrt = _open_osfhandle((intptr_t) handle_out, _O_TEXT);
    FILE* hf_out = _fdopen(hCrt, "w");
    setvbuf(hf_out, NULL, _IONBF, 1);
    *stdout = *hf_out;

    HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
    hCrt = _open_osfhandle((intptr_t) handle_in, _O_TEXT);
    FILE* hf_in = _fdopen(hCrt, "r");
    setvbuf(hf_in, NULL, _IONBF, 128);
    *stdin = *hf_in;

    HANDLE handle_err = GetStdHandle(STD_ERROR_HANDLE);
    hCrt = _open_osfhandle((intptr_t) handle_err, _O_TEXT);
    FILE* hf_err = _fdopen(hCrt, "w");
    setvbuf( stderr, NULL, _IONBF, 0);
    *stderr = *hf_err;
    #endif
}

Logger::~Logger()
{
    bool result = true;
    FILE* fp;

    if (freopen_s(&fp, "NUL:", "r", stdin) == 0)
        setvbuf(stdin, NULL, _IONBF, 0);

    if (freopen_s(&fp, "NUL:", "w", stdout) == 0)
        setvbuf(stdout, NULL, _IONBF, 0);

    if (freopen_s(&fp, "NUL:", "w", stderr) == 0)
        setvbuf(stderr, NULL, _IONBF, 0);

    FreeConsole();
}

void Logger::log(LogLevel level, const std::string& message)
{
    #ifdef _DEBUG
    std::cout << "[" << getCurrentTime() << "] " << levelToString(level) << ": " << message << std::endl;
    #endif
}

void Logger::debug(const std::string& message)
{
    #ifdef _DEBUG
    std::cout << "[" << getCurrentTime() << "] DEBUG: " << message << std::endl;
    #endif
}

void Logger::info(const std::string& message)
{
    #ifdef _DEBUG
    std::cout << "[" << getCurrentTime() << "] INFO: " << message << std::endl;
    #endif
}

void Logger::warn(const std::string& message)
{
    #ifdef _DEBUG
    std::cout << "[" << getCurrentTime() << "] WARNING: " << message << std::endl;
    #endif
}

void Logger::error(const std::string& message)
{
    #ifdef _DEBUG
    std::cout << "[" << getCurrentTime() << "] ERROR: " << message << std::endl;
    #endif
}

std::string Logger::levelToString(LogLevel level)
{
    switch (level) {
    case L_DEBUG:
        return "DEBUG";
    case L_INFO:
        return "INFO";
    case L_WARNING:
        return "WARNING";
    case L_ERROR:
        return "ERROR"; 
    default:
        return "LOG";
    }
}

char Logger::getCurrentTime()
{
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    return *timestamp;
}