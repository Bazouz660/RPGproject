/*
 *  Author: Clément Thomas
 *  Create Time: 2023-07-09 20:21:12
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-10 01:52:46
 *  Description:
 */

#include "MainMenu.hpp"
#include "ResourceManager.hpp"
#include "info.hpp"

namespace bya
{
    MainMenu::MainMenu()
    {
    }

    MainMenu::~MainMenu()
    {
    }

    void MainMenu::init()
    {
        m_gameLogo.setTexture(getResource().getTexture("logo"));
        m_gameLogo.setPosition(
                (info::getWindowSize().x - m_gameLogo.getGlobalBounds().width) / 2,
                (info::getWindowSize().y - m_gameLogo.getGlobalBounds().height) / 2 - 300);

    }

    void MainMenu::handleEvent(sf::Event &event, sf::RenderWindow &window)
    {
    }

    void MainMenu::update(float dt)
    {
        AScene::updateUI(dt);
    }

    void MainMenu::render(sf::RenderTarget &target)
    {
        AScene::renderUi(target);
        target.draw(m_gameLogo);
    }
}
