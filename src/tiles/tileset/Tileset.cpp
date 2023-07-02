/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** Tileset
*/

#include "Tileset.hpp"

namespace bya {

    Tileset::Tileset(const sf::Vector2u &tileSize, sf::Texture &texture)
    {
        m_tileSize = tileSize;
        m_texture = &texture;
        divideTexture();
    }

    Tileset::~Tileset()
    {
    }

    void Tileset::divideTexture()
    {
        for (unsigned int y = 0; y < m_texture->getSize().y / m_tileSize.y; y++) {
            for (unsigned int x = 0; x < m_texture->getSize().x / m_tileSize.x; x++) {
                m_tiles.push_back(sf::IntRect(x * m_tileSize.x, y * m_tileSize.y, m_tileSize.x, m_tileSize.y));
            }
        }
        removeEmptyTiles();
    }

    void Tileset::removeEmptyTiles()
    {
        // checks if the rect of the texture is composed of only transparent pixels
        bool isTransparent = true;
        for (unsigned int i = 0; i < m_tiles.size(); i++) {
            sf::Image image = m_texture->copyToImage();
            for (unsigned int y = m_tiles[i].top; y < m_tiles[i].top + m_tiles[i].height; y++) {
                for (unsigned int x = m_tiles[i].left; x < m_tiles[i].left + m_tiles[i].width; x++) {
                    if (image.getPixel(x, y).a != 0) {
                        isTransparent = false;
                        break;
                    }
                }
            }
            if (isTransparent) {
                m_tiles.erase(m_tiles.begin() + i);
                i--;
            }
            isTransparent = true;
        }
    }

    sf::Texture *Tileset::getTexture() const
    {
        return m_texture;
    }

    sf::IntRect Tileset::getTile(unsigned int id) const
    {
        if (id >= m_tiles.size())
            return sf::IntRect(0, 0, 0, 0);
        return m_tiles[id];
    }

}
