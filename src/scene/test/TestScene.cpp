/*
** EPITECH PROJECT, 2023
** RPGproject
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-07 13:39:21
*/

#include "TestScene.hpp"
#include "ResourceManager.hpp"
#include "SceneManager.hpp"
#include "Clock.hpp"
#include "context.hpp"
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
        sf::Vector2u winSize = context::getWindowSize();

        m_oobb1.setPosition(sf::Vector2f(500, 500));
        m_oobb1.setSize(sf::Vector2f(100, 200));
        m_oobb1.setRotation(45);

        m_oobb1.setOrigin(sf::Vector2f(50, 100));

        m_humanoid.setPosition(300.f, 300.f);
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

    void TestScene::update(float dt)
    {
        m_humanoid.update(dt);


        // test oobb //
        if (m_oobb1.contains(context::getMousePosition()))
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
        AScene::renderUi(target);
        m_humanoid.render(target);
        m_oobb1.render(target);
    }
}
