/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** TilemapScene
*/

#include "TilemapScene.hpp"
#include "ResourceManager.hpp"
#include "SceneManager.hpp"
#include "Clock.hpp"
#include "info.hpp"

namespace bya
{

    TilemapScene::TilemapScene()
        : m_tilemap({32, 32})
    {
    }

    void TilemapScene::init()
    {
        m_camera.activate();
    }

    void TilemapScene::close()
    {
    }

    void TilemapScene::reset()
    {
    }

    TilemapScene::~TilemapScene()
    {
    }

    void TilemapScene::handleEvent(sf::Event &event, sf::RenderWindow &window)
    {
        if (event.type == sf::Event::Resized) {
            m_camera.setRect(sf::IntRect(0, 0, event.size.width, event.size.height));
        }
    }

    void TilemapScene::update(float dt)
    {
        m_camera.update(dt);
        m_tilemap.update(dt);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
            m_camera.move({0, -1});
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            m_camera.move({0, 1});
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
            m_camera.move({-1, 0});
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            m_camera.move({1, 0});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            m_camera.zoom(1 * dt);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
            m_camera.zoom(-1 * dt);
        }
    }

    void TilemapScene::render(sf::RenderTarget &target)
    {
        m_tilemap.render(target);
    }

}
