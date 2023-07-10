/*
 *  Author: Clément Thomas
 *  Create Time: 2023-07-09 20:21:17
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-10 03:22:14
 *  Description:
 */

#include "AScene.hpp"
#include "MainMenuButton.hpp"

namespace bya
{
    class MainMenu : public AScene {
        public:
            MainMenu();
            ~MainMenu();
            void init() override;
            void handleEvent(sf::Event &event, sf::RenderWindow &window) override;
            void update(float dt) override;
            void render(sf::RenderTarget &target) override;
        private:
            sf::Sprite m_gameLogo;
    };
}
