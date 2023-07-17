/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** main
*/

#include "Engine.hpp"
#include "logger.hpp"

int main(int argc, char **argv)
{
    bya::Engine& engine = bya::Engine::getInstance();

    try {
        engine.preProcessor();
        engine.run();
    } catch (std::exception &e) {
        logger::error(e.what());
        return 84;
    }
    return 0;
}