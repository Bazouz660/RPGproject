/*
 *  Author: Clément Thomas
 *  Create Time: 2023-07-07 02:58:14
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-07 03:12:10
 *  Description:
 */

#pragma once

#include "common.hpp"

namespace logger {
    static void logCurrentDate()
    {
        time_t t = time(NULL);
        std::string now = asctime(localtime(&t));
        now[now.size() - 1] = '\0';
        std::cout << "\033[90m" << now << " ";
    }

    static void log(const std::string message)
    {
        logCurrentDate();
        std::cout << "\033[37m\e[1m[LOG]\033[0m\e[0m ";
        std::cout << message << std::endl;
    }

    static void debug(const std::string message)
    {
        logCurrentDate();
        std::cout << "\033[36m\e[1m[DEBUG]\033[0m\e[0m ";
        std::cout << message << std::endl;
    }

    static void warn(const std::string message)
    {
        logCurrentDate();
        std::cout << "\033[33m\e[1m[WARN]\033[0m\e[0m ";
        std::cout << message << std::endl;
    }

    static void error(const std::string message)
    {
        logCurrentDate();
        std::cerr << "\033[31m\e[1m[ERROR]\033[0m\e[0m ";
        std::cerr << message << std::endl;
    }
}
