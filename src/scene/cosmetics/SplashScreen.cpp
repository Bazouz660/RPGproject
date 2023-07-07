/*
 *  Author: Clément Thomas
 *  Create Time: 2023-07-07 01:08:15
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-07 03:10:32
 *  Description:
 */

#include "SplashScreen.hpp"
#include "SceneManager.hpp"
#include "ResourceManager.hpp"
#include "Engine.hpp"
#include "info.hpp"

namespace bya
{
    SplashScreen::SplashScreen()
    {
    }

    SplashScreen::~SplashScreen()
    {
    }

    void SplashScreen::init()
    {
        m_background.setSize(sf::Vector2f(info::getWindowSize().x, info::getWindowSize().y));
        m_background.setFillColor(sf::Color(20, 20, 20, 255));
        m_splashIcon.setTexture(getResource().getTexture("logo"));
        m_splashIcon.setOrigin(m_splashIcon.getGlobalBounds().width / 2, m_splashIcon.getGlobalBounds().height / 2);
        m_splashIcon.setPosition(info::getWindowSize().x / 2, info::getWindowSize().y / 2);
    }

    void SplashScreen::update(float)
    {
        if (ResourceManager::getInstance().isLoaded()) {
            Engine::getInstance().init();
            SceneManager::getInstance().setCurrentScene("TestScene");
        }
    }

    void SplashScreen::render(sf::RenderTarget &target)
    {
        target.draw(m_background);
        target.draw(m_splashIcon);
    }
}
