/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** Box
*/

#pragma once

#include "AObject.hpp"

namespace bya {

    namespace gameObj {

        class Box : public AObject, public sf::RectangleShape {
            public:
                Box();
                Box(sf::Vector2f pos, sf::Vector2f size);
                virtual ~Box() override = default;

                virtual sf::FloatRect getBounds() const override;
                virtual sf::Vector2f getCenter() const override;
                virtual sf::Vector2f getHalfSize() const override;
                virtual sf::Vector2f getTopLeft() const override;
                virtual sf::Vector2f getTopRight() const override;
                virtual sf::Vector2f getBottomLeft() const override;
                virtual sf::Vector2f getBottomRight() const override;

                virtual bool isHovered();
                virtual bool isClicked();

                virtual void draw(sf::RenderTarget &window, sf::RenderStates states = sf::RenderStates::Default) override;
        };

    }

}