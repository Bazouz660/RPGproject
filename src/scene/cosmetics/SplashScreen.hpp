/*
 *  Author: Clément Thomas
 *  Create Time: 2023-07-07 01:04:46
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-07 02:14:15
 *  Description:
 */

#pragma once

#include "AScene.hpp"

namespace bya {
    class SplashScreen : public AScene {
        public:
            SplashScreen();
            ~SplashScreen();
            void init() override;
            void update(float) override;
            void render(sf::RenderTarget&) override;

        private:
            sf::Sprite m_splashIcon;
    };
}
