/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** Tileset
*/

#pragma once

#include "common.hpp"

namespace bya {
    class Tileset {
        public:
            Tileset(const sf::Vector2u &tileSize, sf::Texture &texture);
            ~Tileset();

            sf::Texture* getTexture() const;
            sf::IntRect getTile(unsigned int id) const;

        private:
            void divideTexture();
            void removeEmptyTiles();

        private:
            sf::Vector2u m_tileSize;
            sf::Texture* m_texture;
            std::vector<sf::IntRect> m_tiles;
    };
}