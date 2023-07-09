/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-03 18:50:24
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-09 02:30:52
 *  Description:
 */

#include "SplashScreen.hpp"
#include "AnimationEditor.hpp"
#include "Engine.hpp"
#include "TestScene.hpp"
#include "ResourceManager.hpp"
#include "Clock.hpp"
#include "info.hpp"

namespace bya {
    Engine::Engine()
    : m_sceneManager(SceneManager::getInstance())
    {
        Clock::getInstance().setTickRate(60);
    }

    Engine::~Engine()
    {
    }

    Engine& Engine::getInstance()
    {
        static Engine instance;
        return instance;
    }

    void Engine::preProcessor()
    {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;
        m_renderer.init(WINDOW_SIZE, "BurunyaEngine", sf::Style::Default, settings);
        //m_window->setVerticalSyncEnabled(true);
        ResourceManager::getInstance().init();
        m_sceneManager.addScene("IntroLogo", std::make_shared<SplashScreen>());
        setIcon("logo");
        m_sceneManager.setCurrentScene("IntroLogo");
    }

    void Engine::init()
    {
        m_fpsHint.setFont(ResourceManager::getInstance().getFont("defaultFont"));
        m_fpsHint.setCharacterSize(20);
        m_fpsHint.setFillColor(sf::Color::Green);
        m_fpsHint.setOutlineColor(sf::Color::Black);
        m_fpsHint.setOutlineThickness(1);
        m_fpsHint.setPosition(10, 10);
        m_fpsHint.setString("FPS: 0");
        m_sceneManager.addScene("TestScene", std::make_shared<TestScene>());
        m_sceneManager.addScene("AnimationEditor", std::make_shared<AnimationEditor>());
        SceneManager::getInstance().setCurrentScene("AnimationEditor");
    }

    void Engine::setIcon(const std::string& name)
    {
        sf::Image& icon = ResourceManager::getInstance().getTextureImage(name);
        m_renderer.getWindow().setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    void Engine::handleEvents()
    {
        while (m_renderer.getWindow().pollEvent(m_event)) {
            switch (m_event.type) {
                case sf::Event::Closed:
                    m_renderer.close();
                    break;
            }
            m_sceneManager.getCurrentScene()->handleUIEvent(m_event, m_renderer.getWindow());
            m_sceneManager.getCurrentScene()->handleEvent(m_event, m_renderer.getWindow());
        }
    }

    void Engine::render()
    {
        sf::RenderWindow& window = m_renderer.getWindow();

        window.clear();
        m_sceneManager.getCurrentScene()->render(window);
        window.setView(m_renderer.getView());
        window.draw(m_fpsHint);
        window.display();
    }

    void Engine::updateFpsHint()
    {
        static float tick = -0.01f;

        if (getTime().asSeconds() > tick + 0.1) {
            tick = getTime().asSeconds();
            m_fpsHint.setString("FPS: " + std::to_string(getClock().getFps()));
            if (getClock().getFps() < 30)
                m_fpsHint.setFillColor(sf::Color::Red);
            else if (getClock().getFps() < 60)
                m_fpsHint.setFillColor(sf::Color::Yellow);
            else
                m_fpsHint.setFillColor(sf::Color::Green);
        }
    }

    void Engine::update()
    {
        getClock().update();
        updateFpsHint();
        m_sceneManager.getCurrentScene()->updateUI(getClock().getFrameDt());
        m_sceneManager.getCurrentScene()->update(getClock().getFrameDt());
    }

    void Engine::run()
    {
        while (m_renderer.isOpen()) {
            update();
            render();
            handleEvents();
        }
    }
}
