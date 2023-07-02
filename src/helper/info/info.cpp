/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** info
*/

#include "info.hpp"

namespace bya {
    namespace info {

        static sf::RenderWindow *windowInstance = nullptr;
        static sf::View *staticView = nullptr;

        sf::Vector2f getMousePosition()
        {
            if (info::windowInstance == nullptr)
                return sf::Vector2f(0, 0);
            sf::Vector2i mouse_pos0 = sf::Mouse::getPosition(*info::windowInstance);
            return info::windowInstance->mapPixelToCoords(mouse_pos0, windowInstance->getView());
        }

        sf::Vector2u getWindowSize()
        {
            if (info::windowInstance == nullptr)
                return sf::Vector2u(0, 0);
            return info::windowInstance->getSize();
        }

        void setContext(const sf::RenderWindow &window)
        {
            info::windowInstance = const_cast<sf::RenderWindow *>(&window);
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
