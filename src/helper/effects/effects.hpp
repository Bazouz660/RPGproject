/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** effects
*/

#pragma once

#include "common.hpp"

namespace bya {
    namespace effects {

        static sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight)
        {
            float windowRatio = windowWidth / (float)windowHeight;
            float viewRatio = view.getSize().x / (float)view.getSize().y;
            float sizeX = 1;
            float sizeY = 1;
            float posX = 0;
            float posY = 0;
            bool horizontalSpacing = true;

            if (windowRatio < viewRatio)
                horizontalSpacing = false;
            if (horizontalSpacing) {
                sizeX = viewRatio / windowRatio;
                posX = (1 - sizeX) / 2.f;
            } else {
                sizeY = windowRatio / viewRatio;
                posY = (1 - sizeY) / 2.f;
            }
            view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
            return view;
        }

    }
}