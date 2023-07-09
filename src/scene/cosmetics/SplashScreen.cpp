/*
 *  Author: Clément Thomas
 *  Create Time: 2023-07-07 01:08:15
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-09 02:34:35
 *  Description:
 */

#include "SplashScreen.hpp"
#include "SceneManager.hpp"
#include "ResourceManager.hpp"
#include "logger.hpp"
#include "Clock.hpp"
#include "Engine.hpp"
#include "info.hpp"

namespace bya
{
    SplashScreen::SplashScreen()
    {
        ResourceManager::getInstance().loadTexture("logo", "asset/texture/default/logo.png");
        ResourceManager::getInstance().loadTexture("loading", "asset/texture/default/loading.png");
    }

    SplashScreen::~SplashScreen()
    {
    }

    void SplashScreen::init()
    {
        m_background.setSize(sf::Vector2f(info::getWindowSize().x, info::getWindowSize().y));
        m_background.setFillColor(sf::Color(20, 20, 20, 255));
        m_splashIcon.setTexture(getResource().getTexture("logo"));
        m_loading.setTexture(getResource().getTexture("loading"));
        m_loading.setOrigin(m_loading.getGlobalBounds().width / 2, m_loading.getGlobalBounds().height / 2);
        m_loading.setPosition(info::getWindowSize().x / 2, info::getWindowSize().y / 2 + 400);
        m_loading.setScale(5, 5);
        m_splashIcon.setOrigin(m_splashIcon.getGlobalBounds().width / 2, m_splashIcon.getGlobalBounds().height / 2);
        m_splashIcon.setPosition(info::getWindowSize().x / 2, info::getWindowSize().y / 2);
        fadeIn.setDuration(2.f);
    }

    void SplashScreen::update(float)
    {
        m_background.setFillColor(sf::Color(20, 20, 20, 255 * fadeIn.getAlpha()));
        m_splashIcon.setColor(sf::Color(255, 255, 255, 255 * fadeIn.getAlpha()));
        m_loading.setColor(sf::Color(255, 255, 255, 255 * fadeIn.getAlpha()));
        m_loading.rotate(500 * Clock::getInstance().getFrameDt());
        fadeIn.update();

        if (ResourceManager::getInstance().isLoaded() && fadeIn.isDone())
            Engine::getInstance().init();
    }

    void SplashScreen::render(sf::RenderTarget &target)
    {
        target.draw(m_background);
        target.draw(m_splashIcon);
        target.draw(m_loading);
    }
}
