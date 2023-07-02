/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** Renderer
*/

#pragma once

#include "common.hpp"

namespace bya {

    class Renderer {
        public:
            Renderer();
            ~Renderer();

            void init(sf::Vector2u size, const std::string& title, sf::Uint32 style = sf::Style::Default);
            void init(int width, int height, const std::string& title, sf::Uint32 style = sf::Style::Default);
            void close();
            sf::RenderWindow& getWindow();
            sf::View& getView();

            bool isOpen() const;

        private:
            sf::RenderWindow m_window;
            sf::View m_staticView;
    };

}