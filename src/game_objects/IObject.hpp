/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** IObject
*/

#pragma once

#include "common.hpp"

namespace bya {

    namespace gameObj {

        class IObject {
            public:
                virtual ~IObject() = default;

                virtual sf::FloatRect getBounds() const = 0;
                virtual sf::Vector2f getCenter() const = 0;
                virtual sf::Vector2f getHalfSize() const = 0;

                virtual sf::Vector2f getTopLeft() const = 0;
                virtual sf::Vector2f getTopRight() const = 0;
                virtual sf::Vector2f getBottomLeft() const = 0;
                virtual sf::Vector2f getBottomRight() const = 0;

                virtual void draw(sf::RenderTarget &window, sf::RenderStates states = sf::RenderStates::Default) = 0;
        };

    }

}