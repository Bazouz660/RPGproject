/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** main
*/

#include "Engine.hpp"

int main(int argc, char **argv)
{
    bya::Engine engine;

    try {
        engine.init();
        engine.setIcon("steel_helm");
        engine.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}