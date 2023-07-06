/*
** EPITECH PROJECT, 2023
** RPGproject
** File description:
** OrientedBoundingBox
*/

#pragma once

#include "common.hpp"
#include <array>

namespace bya::gameObj
{
    class OrientedBoundingBox
    {
        public:
            OrientedBoundingBox();
            OrientedBoundingBox(sf::Vector2f position, sf::Vector2f size, float rotation);
            ~OrientedBoundingBox() = default;

            bool intersects(OrientedBoundingBox &other) const;
            bool intersects(sf::FloatRect &other) const;
            bool contains(const sf::Vector2f& point) const;

            void setRotation(float rotation) { m_rotation = rotation; }
            void setPosition(sf::Vector2f position) { m_position = position; }
            void setSize(sf::Vector2f size);
            void setOrigin(sf::Vector2f origin);
            void setColor(sf::Color color) { m_color = color; }
            void setScale(sf::Vector2f scale) { m_scale = scale; }
            void setTexture(sf::Texture &texture);
            void setTextureRect(sf::IntRect textureRect);

            sf::Vector2f getPosition() const { return m_position; }
            sf::Vector2f getSize() const { return m_size; }
            float getRotation() const { return m_rotation; }
            sf::Vector2f getOrigin() const { return m_origin; }
            sf::Color getColor() const { return m_color; }
            sf::Vector2f getScale() const { return m_scale; }
            std::array<sf::Vector2f, 4> getCorners() const;
            sf::Vector2f getCenter() const;
            sf::FloatRect getGlobalBounds() const;
            sf::Texture* getTexture() const { return m_texture; }
            sf::IntRect getTextureRect() const { return m_textureRect; }

            void render(sf::RenderTarget &target);

        private:
            void updateTexCoords();

        private:
            sf::Vector2f m_position = {0, 0};
            sf::Vector2f m_size = {0, 0};
            sf::Vector2f m_origin = {0, 0};
            sf::Vector2f m_scale = {1, 1};
            sf::Color m_color = sf::Color(255, 0, 0, 100);
            float m_rotation = 0;
            std::array<sf::Vector2f, 4> m_corners = {};
            sf::Vertex m_vertices[5] = {};
            sf::VertexBuffer m_vertexBuffer;
            sf::CircleShape m_originShape;
            sf::CircleShape m_pivotShape;
            sf::Texture *m_texture = nullptr;
            sf::IntRect m_textureRect = {0, 0, 0, 0};
            sf::RenderStates m_renderStates = sf::RenderStates::Default;
    };
}