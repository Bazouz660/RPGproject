/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** Engine
*/

#include "Engine.hpp"
#include "TilemapScene.hpp"
#include "UIScene.hpp"
#include "QuadtreeScene.hpp"
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

    void Engine::init()
    {
        m_renderer.init(WINDOW_SIZE, "BurunyaEngine");
        //m_window->setVerticalSyncEnabled(true);

        m_fpsHint.setFont(ResourceManager::getInstance().getFont("defaultFont"));
        m_fpsHint.setCharacterSize(30);
        m_fpsHint.setFillColor(sf::Color::White);
        m_fpsHint.setOutlineColor(sf::Color::Black);
        m_fpsHint.setOutlineThickness(1);
        m_fpsHint.setPosition(10, 10);
        m_fpsHint.setString("FPS: 0");

        m_sceneManager.addScene("Test Scene", std::shared_ptr<IScene>(new QuadtreeScene()));
        m_sceneManager.addScene("UI Scene", std::shared_ptr<IScene>(new UIScene()));

        m_sceneManager.setCurrentScene("UI Scene");
    }

    void Engine::handleEvents()
    {
        while (m_renderer.getWindow().pollEvent(m_event)) {
            switch (m_event.type) {
                case sf::Event::Closed:
                    m_renderer.close();
                    break;
                case sf::Event::Resized:
                    m_renderer.getView() = sf::View(sf::FloatRect(0, 0, m_event.size.width, m_event.size.height));
                    break;
            }
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
        }
    }

    void Engine::update()
    {
        getClock().update();
        updateFpsHint();
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