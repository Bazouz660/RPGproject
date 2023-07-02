/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** Widget
*/

#pragma once

#include "common.hpp"

namespace bya::ui {

    class IUIelement {
        public:
            virtual ~IUIelement() = default;

            virtual void handleEvent(sf::Event event, const sf::RenderWindow &window) = 0;

            virtual void setPosition(const sf::Vector2f &pos) = 0;
            virtual sf::FloatRect getBounds() const = 0;

            virtual void render(sf::RenderTarget &target) = 0;
    };

}
