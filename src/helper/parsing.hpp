/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** parsing
*/

#pragma once

#include "common.hpp"
#include <fstream>

namespace bya {
    namespace parsing {
        static std::string removeExtension(const std::string& filename) {
            size_t lastdot = filename.find_last_of(".");
            if (lastdot == std::string::npos) return filename;
            return filename.substr(0, lastdot);
        }

        static std::string getFileContent(const std::string& path) {
            std::ifstream file(path);
            std::string content;
            std::string line;
            if (!file.is_open())
                throw std::runtime_error("Failed to open file: " + path);
            while (std::getline(file, line)) {
                content += line;
                content.push_back('\n');
            }
            return content;
        }
    }
}


