/*
 *  Author: Clément Thomas
 *  Create Time: 2023-07-07 01:08:15
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-10 03:39:44
 *  Description:
 */

#include "SplashScreen.hpp"
#include "SceneManager.hpp"
#include "ResourceManager.hpp"
#include "logger.hpp"
#include "Clock.hpp"
#include "Engine.hpp"
#include "context.hpp"

namespace bya
{
    SplashScreen::SplashScreen()
    {
        RESOURCE().loadResource<sf::Texture>("asset/texture/gui/splash_screen/splash.png");
        RESOURCE().loadResource<sf::Texture>("asset/texture/gui/splash_screen/loading.png");
    }

    SplashScreen::~SplashScreen()
    {
    }

    void SplashScreen::init()
    {
        MusicManager::getInstance().switchTrack("Aleph", 0.5f, false, false);

        m_background.setSize(sf::Vector2f(context::getWindowSize().x, context::getWindowSize().y));
        m_background.setFillColor(sf::Color(15, 15, 15, 255));
        m_splashIcon.setTexture(RESOURCE().getTexture("splash_screen", "splash"));
        m_loading.setTexture(RESOURCE().getTexture("splash_screen", "loading"));
        m_loading.setOrigin(m_loading.getGlobalBounds().width / 2, m_loading.getGlobalBounds().height / 2);
        m_loading.setPosition(context::getWindowSize().x / 2, context::getWindowSize().y * 0.8f);
        m_loading.setScale(3, 3);
        m_splashIcon.setOrigin(m_splashIcon.getGlobalBounds().width / 2, m_splashIcon.getGlobalBounds().height / 2);
        m_splashIcon.setPosition(context::getWindowSize().x / 2, context::getWindowSize().y / 2);
        fadeIn.setDuration(1.5f);
    }

    void SplashScreen::update(float)
    {
        m_background.setFillColor(sf::Color(15, 15, 15, 255 * fadeIn.getAlpha()));
        m_splashIcon.setColor(sf::Color(255, 255, 255, 255 * fadeIn.getAlpha()));
        m_loading.setColor(sf::Color(255, 255, 255, 255 * fadeIn.getAlpha()));
        m_loading.rotate(700 * Clock::getInstance().getFrameDt());
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
