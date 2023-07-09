/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** info
*/

#include "info.hpp"
#include "logger.hpp"
#include "parsing.hpp"

namespace bya {
    namespace info {

        static sf::RenderWindow *windowInstance = nullptr;
        static sf::View *staticView = nullptr;
        static sf::Vector2u resolution;

        sf::Vector2f getMousePosition()
        {
            if (info::windowInstance == nullptr)
                return sf::Vector2f(0, 0);
            sf::Vector2i mouse_pos0 = sf::Mouse::getPosition(*info::windowInstance);
            return info::windowInstance->mapPixelToCoords(mouse_pos0, windowInstance->getView());
        }

        sf::Vector2u getWindowSize()
        {
            return info::resolution;
        }

        void setContext(const sf::RenderWindow &window, sf::Vector2u resolution)
        {
            info::windowInstance = const_cast<sf::RenderWindow *>(&window);
            info::resolution = resolution;
        }

        sf::RenderWindow *getWindowInstance()
        {
            return info::windowInstance;
        }

        void setStaticView(const sf::View &view)
        {
            info::staticView = const_cast<sf::View *>(&view);
        }

        sf::View &getStaticView()
        {
            return *info::staticView;
        }
    }
}
