/*
** EPITECH PROJECT, 2023
** RPGproject
** File description:
** TestScene
*/

#include "TestScene.hpp"
#include "ResourceManager.hpp"
#include "SceneManager.hpp"
#include "Clock.hpp"
#include "info.hpp"
#include "Button.hpp"
#include "Slider.hpp"
#include "Text.hpp"

namespace bya
{

    TestScene::TestScene()
    {
    }

    void TestScene::init()
    {
        sf::Vector2u winSize = info::getWindowSize();

        m_background.setSize(sf::Vector2f(winSize.x, winSize.y));
        m_background.setFillColor(sf::Color(50, 50, 50, 255));

        m_oobb1.setPosition(sf::Vector2f(500, 500));
        m_oobb1.setSize(sf::Vector2f(100, 200));
        m_oobb1.setRotation(45);

        m_oobb1.setOrigin(sf::Vector2f(50, 100));
    }

    void TestScene::close()
    {
    }

    void TestScene::reset()
    {
    }

    TestScene::~TestScene()
    {
    }

    void TestScene::handleEvent(sf::Event &event, sf::RenderWindow &window)
    {
        for (auto &[key, elem] : m_UIelements)
            elem->handleEvent(event, window);
    }

    void TestScene::update(float dt)
    {
        m_humanoid.update(dt);


        // test oobb //
        if (m_oobb1.contains(info::getMousePosition()))
            m_oobb1.setColor(sf::Color::Green);
        else
            m_oobb1.setColor(sf::Color(255, 0, 0, 100));

        float scale = std::cos(getTime().asSeconds());
        m_oobb1.setScale(sf::Vector2f(scale, 1));
        //           //
    }

    void TestScene::render(sf::RenderTarget &target)
    {
        target.draw(m_background);
        for (auto &[key, elem] : m_UIelements)
            elem->render(target);

        m_humanoid.render(target);
        m_oobb1.render(target);
    }

    void TestScene::addUIelement(const std::string& id, std::shared_ptr<ui::IUIelement> element)
    {
        m_UIelements.insert(std::make_pair(id, std::move(element)));
    }

}
