/*
 *  Author: Clément Thomas
 *  Create Time: 2023-07-07 02:58:14
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-07 03:12:10
 *  Description:
 */

#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <queue>
#include <thread>
#include <atomic>
#include <mutex>

namespace bya {

    class logger {
    public:
        static void log(const std::string& message) {
            getInstance().logImpl("\033[37m\e[1m[LOG]\033[0m\e[0m " + message);
        }

        static void debug(const std::string& message) {
            getInstance().logImpl("\033[36m\e[1m[DEBUG]\033[0m\e[0m " + message);
        }

        static void warn(const std::string& message) {
            getInstance().logImpl("\033[33m\e[1m[WARN]\033[0m\e[0m " + message);
        }

        static void error(const std::string& message) {
            getInstance().logImpl("\033[31m\e[1m[ERROR]\033[0m\e[0m " + message);
        }

    private:
        static logger& getInstance() {
            static logger instance;
            return instance;
        }

        std::mutex logMtx;
        std::queue<std::string> logQueue;
        std::thread loggerThread;
        std::atomic<bool> stopFlag;

        logger() : stopFlag(false) {
            loggerThread = std::thread(&logger::logMessages, this);
        }

        ~logger() {
            {
                std::lock_guard<std::mutex> lock(logMtx);
                stopFlag = true;
            }
            loggerThread.join(); // Wait for loggerThread to finish
        }

        logger(const logger&) = delete; // Disable copy constructor
        logger& operator=(const logger&) = delete; // Disable assignment operator

        void logImpl(const std::string& message) {
            std::lock_guard<std::mutex> lock(logMtx);
            logQueue.push(logCurrentDate() + message);
        }

        std::string logCurrentDate() {
            time_t t = time(NULL);
            std::string now = asctime(localtime(&t));
            now[now.size() - 1] = '\0';
            return now;
        }

        void logMessages() {
            while (true) {
                std::string logEntry;
                {
                    std::lock_guard<std::mutex> lock(logMtx);
                    if (!logQueue.empty()) {
                        logEntry = logQueue.front();
                        logQueue.pop();
                    }
                }
                if (!logEntry.empty()) {
                    std::cout << logEntry << std::endl;
                }
                if (stopFlag && logQueue.empty()) { // Break the loop if stopFlag is true and the logQueue is empty
                    break;
                }
            }
        }

    };
}
