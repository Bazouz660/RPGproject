/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** info
*/

#include "context.hpp"
#include "logger.hpp"
#include "parsing.hpp"

namespace bya {
    namespace context {

        static sf::RenderWindow *windowInstance = nullptr;
        static sf::View *staticView = nullptr;
        static sf::Vector2u resolution;
        static bool shouldclose = false;

        sf::Vector2f getMousePosition()
        {
            if (context::windowInstance == nullptr)
                return sf::Vector2f(0, 0);
            sf::Vector2i mouse_pos0 = sf::Mouse::getPosition(*context::windowInstance);
            return context::windowInstance->mapPixelToCoords(mouse_pos0, windowInstance->getView());
        }

        sf::Vector2u getWindowSize()
        {
            return context::resolution;
        }

        void setContext(const sf::RenderWindow &window, sf::Vector2u resolution)
        {
            context::windowInstance = const_cast<sf::RenderWindow *>(&window);
            context::resolution = resolution;
        }

        bool shouldClose()
        {
            return context::shouldclose;
        }

        void closeWindow()
        {
            context::shouldclose = true;
        }

        sf::RenderWindow *getWindowInstance()
        {
            return context::windowInstance;
        }

        void setStaticView(const sf::View &view)
        {
            context::staticView = const_cast<sf::View *>(&view);
        }

        sf::View &getStaticView()
        {
            return *context::staticView;
        }
    }
}
