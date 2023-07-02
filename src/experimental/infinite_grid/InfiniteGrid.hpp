/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** InfiniteGrid
*/

#pragma once

#include "common.hpp"
#include "info.hpp"

namespace bya {

    class InfiniteGrid {
        public:
            InfiniteGrid(const sf::Vector2u& cellSize);
            ~InfiniteGrid();

            void update(float dt);
            void render(sf::RenderTarget& target) const;

            bool isCellVisible(const sf::Vector2f& cellPos) const;
            bool isCellVisible(const sf::Vector2i& cellIndex) const;

            void setCellSize(const sf::Vector2u& cellSize);
            sf::Vector2u getCellSize() const;

            void setCellColor(const sf::Vector2i& cellIndex, const sf::Color& color);

            sf::Vector2i getCellFromPos(const sf::Vector2f& position) const;

            sf::Vector2f getPosFromCell(const sf::Vector2i& cellIndex) const;

            sf::Vector2u getSize() const;

        private:
            sf::Vector2u m_cellSize;
            sf::VertexArray m_vertices;
            sf::Vector2f m_positionOffset = {0, 0};
            sf::Vector2f m_lastViewCenter = {0, 0};
            sf::Vector2f m_lastViewSize = {0, 0};
    };

}