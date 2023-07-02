/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** AObject
*/

#pragma once

#include "IObject.hpp"

namespace bya {

    namespace gameObj {

        class AObject : public IObject {
            public:
                virtual ~AObject() = default;

                virtual sf::FloatRect getBounds() const override;
                virtual sf::Vector2f getCenter() const override;
                virtual sf::Vector2f getHalfSize() const override;

                virtual sf::Vector2f getTopLeft() const override;
                virtual sf::Vector2f getTopRight() const override;
                virtual sf::Vector2f getBottomLeft() const override;
                virtual sf::Vector2f getBottomRight() const override;

                virtual void draw(sf::RenderTarget &window, sf::RenderStates states = sf::RenderStates::Default) = 0;

            protected:
                sf::FloatRect m_bounds;
        };

    }

}