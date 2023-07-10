/*
** EPITECH PROJECT, 2023
** RPG3
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-10 03:24:20
*/

#pragma once

#include "common.hpp"

namespace bya
{
    namespace context
    {
        extern sf::Vector2f getMousePosition();
        extern sf::Vector2u getWindowSize();
        extern sf::RenderWindow *getWindowInstance();
        extern sf::View &getStaticView();
        extern bool shouldClose();
        extern void closeWindow();
        extern void setContext(const sf::RenderWindow &window, sf::Vector2u resolution);
        extern void setStaticView(const sf::View &view);
    }
}
