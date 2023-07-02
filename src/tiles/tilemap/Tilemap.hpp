/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** Tilemap
*/

#pragma once

#include "common.hpp"
#include "InfiniteGrid.hpp"
#include "Tileset.hpp"

namespace bya {
    class Tilemap {
        public:
            Tilemap(const sf::Vector2u &tileSize);
            ~Tilemap();
            void loadTileset(sf::Texture &texture);
            void update(float dt);
            void render(sf::RenderTarget &target) const;

        private:
            struct Cell
            {
                int id;
                bool isCollidable;
                int left;
                int right;
                int top;
                int bottom;
                sf::Vertex vertices[4];
            };

            void updateCells();

            sf::VertexArray m_vertices;
            std::vector<std::unique_ptr<Cell>> m_cells;
            sf::Vector2u m_tileSize;
            std::unique_ptr<Tileset> m_tileset;
            InfiniteGrid m_grid;
            sf::Vector2u m_gridSize;
            sf::Vector2u m_lastGridSize;
    };
}