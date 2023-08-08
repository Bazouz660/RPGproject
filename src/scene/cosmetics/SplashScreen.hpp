/*
 *  Author: Clément Thomas
 *  Create Time: 2023-07-07 01:04:46
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-09 01:48:11
 *  Description:
 */

#pragma once

#include "AScene.hpp"
#include "FadeIn.hpp"

namespace bya {
    class SplashScreen : public AScene {
        public:
            SplashScreen();
            ~SplashScreen();
            void load() override;
            void update(float) override;
            void render(sf::RenderTarget&) override;

        private:
            Animation::FadeIn fadeIn;
            sf::Sprite m_splashIcon;
            sf::Sprite m_loading;
    };
}
