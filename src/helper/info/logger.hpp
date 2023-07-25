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
#include <mutex>
#include <queue>
#include <thread>
#include <atomic>

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

        std::mutex pushMtx;
        std::mutex dateMtx;
        std::mutex logMtx;
        std::queue<std::string> logQueue;
        std::thread loggerThread;
        std::atomic<bool> stopFlag;

        logger() : stopFlag(false) {
            loggerThread = std::thread(&logger::logMessages, this);
            loggerThread.detach();
        }

        logger(const logger&) = delete; // Disable copy constructor
        logger& operator=(const logger&) = delete; // Disable assignment operator

        void logImpl(const std::string& message) {
            logCurrentDate();
            std::lock_guard<std::mutex> lock(pushMtx);
            logQueue.push(message);
        }

        void logCurrentDate() {
            time_t t = time(NULL);
            std::string now = asctime(localtime(&t));
            now[now.size() - 1] = '\0';
            std::lock_guard<std::mutex> lock(dateMtx);
            std::cout << "\033[90m" << now << " ";
        }

        void logMessages() {
            while (!stopFlag) {
                std::lock_guard<std::mutex> lock(logMtx);
                if (!logQueue.empty()) {
                    std::cout << logQueue.front() << std::endl;
                    logQueue.pop();
                }
                else {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Sleep to avoid busy waiting
                }
            }
        }

    };
}
