/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** Tilemap
*/

#include "Tilemap.hpp"
#include "ResourceManager.hpp"
#include "numberGenerator.hpp"

namespace bya {
    Tilemap::Tilemap(const sf::Vector2u &tileSize)
    : m_grid(tileSize)
    {
        m_tileset = nullptr;
        m_tileSize = tileSize;
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(0);
        m_grid = InfiniteGrid(m_tileSize);
        m_gridSize = m_grid.getSize();
        m_lastGridSize = m_gridSize;
        m_tileset = std::make_unique<Tileset>(m_tileSize, getResource().getTexture("tileset"));

        updateCells();
    }

    void Tilemap::updateCells()
    {
        m_cells.clear();
        m_vertices.clear();
        m_vertices.resize(0);
        for (int i = -1; i < (int)m_gridSize.x; i++) {
            for (int j = -1; j < (int)m_gridSize.y; j++) {
                m_cells.push_back(std::make_unique<Cell>());
                m_cells.back()->id = 0;
                m_cells.back()->isCollidable = false;
                m_cells.back()->left = 0;
                m_cells.back()->right = 0;
                m_cells.back()->top = 0;
                m_cells.back()->bottom = 0;
                m_cells.back()->vertices[0].position = sf::Vector2f(i * (int)m_tileSize.x, j * (int)m_tileSize.y);
                m_cells.back()->vertices[1].position = sf::Vector2f((i + 1) * (int)m_tileSize.x, j * (int)m_tileSize.y);
                m_cells.back()->vertices[2].position = sf::Vector2f((i + 1) * (int)m_tileSize.x, (j + 1) * (int)m_tileSize.y);
                m_cells.back()->vertices[3].position = sf::Vector2f(i * (int)m_tileSize.x, (j + 1) * (int)m_tileSize.y);
                sf::IntRect tile = m_tileset->getTile(nbgen::between(0, 20));
                m_cells.back()->vertices[0].texCoords = sf::Vector2f(tile.left, tile.top);
                m_cells.back()->vertices[1].texCoords = sf::Vector2f(tile.left + tile.width, tile.top);
                m_cells.back()->vertices[2].texCoords = sf::Vector2f(tile.left + tile.width, tile.top + tile.height);
                m_cells.back()->vertices[3].texCoords = sf::Vector2f(tile.left, tile.top + tile.height);
            }
        }

        sf::Vector2f pos = m_grid.getPosFromCell(sf::Vector2i(0, 0));

        int i = -1;
        int j = -1;
        for (auto &cell : m_cells) {
            // translate the grid to the top left corner
            cell->vertices[0].position = sf::Vector2f(i * (int)m_tileSize.x + pos.x, j * (int)m_tileSize.y + pos.y);
            cell->vertices[1].position = sf::Vector2f((i + 1) * (int)m_tileSize.x + pos.x, j * (int)m_tileSize.y + pos.y);
            cell->vertices[2].position = sf::Vector2f((i + 1) * (int)m_tileSize.x + pos.x, (j + 1) * (int)m_tileSize.y + pos.y);
            cell->vertices[3].position = sf::Vector2f(i * (int)m_tileSize.x + pos.x, (j + 1) * (int)m_tileSize.y + pos.y);

            if (m_grid.isCellVisible(cell->vertices[0].position)) {
                m_vertices.append(cell->vertices[0]);
                m_vertices.append(cell->vertices[1]);
                m_vertices.append(cell->vertices[2]);
                m_vertices.append(cell->vertices[3]);
            }

            i++;
            if (i >= m_gridSize.x) {
                i = -1;
                j++;
            }
        }
    }

    void Tilemap::loadTileset(sf::Texture &texture)
    {
        if (m_tileset)
            m_tileset = std::make_unique<Tileset>(m_tileSize, texture);
    }

    Tilemap::~Tilemap()
    {
    }

    void Tilemap::update(float dt)
    {
        m_grid.update(dt);
        m_gridSize = m_grid.getSize();

        if (m_gridSize != m_lastGridSize) {
            updateCells();
        }

        m_lastGridSize = m_gridSize;
    }

    void Tilemap::render(sf::RenderTarget &target) const
    {
        m_grid.render(target);

        target.draw(m_vertices, m_tileset->getTexture());
    }
}