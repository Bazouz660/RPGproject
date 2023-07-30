/*
** EPITECH PROJECT, 2023
** RPGproject
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-11 17:45:33
*/

#pragma once

#include "common.hpp"
#include <array>

namespace bya::gameObj
{
    class OrientedBoundingBox : public sf::Transformable
    {
        public:
            OrientedBoundingBox();
            OrientedBoundingBox(const sf::Vector2f& position, const sf::Vector2f& size, float rotation);
            ~OrientedBoundingBox() = default;

            bool intersects(const OrientedBoundingBox& other) const;
            bool intersects(const sf::FloatRect& other) const;
            bool contains(const sf::Vector2f& point) const;

            void setOutlineColor(const sf::Color& color) { m_outlineColor = color;}
            void showOutline(bool show) { m_showOutline = show;}

            void setSize(const sf::Vector2f& size);
            void setColor(const sf::Color& color) { m_color = color; }

            void setOrigin(const sf::Vector2f& pivotPoint);
            void setScale(const sf::Vector2f& scale);
            void setRotation(float rotation);
            void setPosition(const sf::Vector2f& position);

            void setTexture(sf::Texture &texture);
            void setTextureRect(const sf::IntRect& textureRect);
            sf::Texture* getTexture() const { return m_texture; }
            sf::IntRect getTextureRect() const { return m_textureRect; }

            sf::Vector2f getSize() const { return m_size; }
            sf::Color getColor() const { return m_color; }
            void updateTransform();
            const std::array<sf::Vector2f, 4>& getGlobalCorners() const { return m_transformedCorners; }
            const std::array<sf::Vector2f, 4>& getLocalCorners() const { return m_corners; }
            sf::Vector2f transformPoint(const sf::Vector2f& point) const;

            sf::Vector2f getGlobalCenter() const;
            sf::Vector2f getLocalCenter() const;
            virtual sf::FloatRect getBounds() const;

            virtual void render(sf::RenderTarget &target);

        private:
            void updateTexCoords();

        private:
            sf::Vector2f m_size = {0, 0};
            sf::Color m_color = sf::Color(255, 0, 0, 100);
            std::array<sf::Vector2f, 4> m_corners = {};
            std::array<sf::Vector2f, 4> m_transformedCorners = {};
            sf::Vertex m_vertices[5] = {};
            sf::VertexBuffer m_vertexBuffer;
            sf::CircleShape m_originShape;
            sf::CircleShape m_pivotShape;
            sf::Texture *m_texture = nullptr;
            sf::IntRect m_textureRect = {0, 0, 0, 0};
            sf::RenderStates m_renderStates = sf::RenderStates::Default;

            bool m_showOutline = false;
            sf::Color m_outlineColor = sf::Color::Transparent;

            bool m_needTransformUpdate = true;
    };
}