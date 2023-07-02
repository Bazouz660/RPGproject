/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** windowInfo
*/

#ifndef WINDOWINFO_HPP_
    #define WINDOWINFO_HPP_

    #include "common.hpp"

    namespace bya {
        namespace info {
            extern sf::Vector2f getMousePosition();
            extern sf::Vector2u getWindowSize();
            extern sf::RenderWindow *getWindowInstance();
            extern sf::View &getStaticView();
            extern void setContext(const sf::RenderWindow& window);
            extern void setStaticView(const sf::View& view);
        }
    }

#endif /* !WINDOWINFO_HPP_ */
