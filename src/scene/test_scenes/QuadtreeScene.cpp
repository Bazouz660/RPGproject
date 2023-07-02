/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** QuadtreeScene
*/

#include "QuadtreeScene.hpp"
#include "info.hpp"
#include "numberGenerator.hpp"
#include "ResourceManager.hpp"
#include "color.hpp"

namespace bya {

    QuadtreeScene::QuadtreeScene()
        : m_quadtree(sf::FloatRect(0, 0, 1920, 1080), [](gameObj::IObject* obj) { return static_cast<gameObj::AObject*>(obj)->getBounds(); })
    {
        m_objectCountText.setFont(getResource().getFont("defaultFont"));
        m_objectCountText.setCharacterSize(30);
        m_objectCountText.setOutlineColor(sf::Color::Black);
        m_objectCountText.setOutlineThickness(1.f);
        m_objectCountText.setFillColor(sf::Color::White);
        m_objectCountText.setPosition(10, 50);
        m_objectCountText.setString("number of objects: 0");

        m_boxes.push_back(new gameObj::AABBcollider(sf::Vector2f(0, 950), sf::Vector2f(1920, 400)));
        (static_cast<gameObj::AABBcollider*>(m_boxes.back()))->setStatic(true);

        m_boxes.push_back(new gameObj::AABBcollider(sf::Vector2f(960, 560), sf::Vector2f(100, 100)));
    }

    void QuadtreeScene::init()
    {
        m_camera.activate();
    }

    void QuadtreeScene::close()
    {
    }

    void QuadtreeScene::reset()
    {
    }

    QuadtreeScene::~QuadtreeScene()
    {
        for (auto& box : m_boxes)
            delete box;
    }

    void QuadtreeScene::handleEvent(sf::Event &event, sf::RenderWindow &window)
    {
        m_camera.activate();

        if (event.type == sf::Event::Resized)
            m_camera.setRect(sf::IntRect(0, 0, event.size.width, event.size.height));

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                // click event
            }
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Key::Space) {
                m_boxes.clear();
            }
        }
    }

    void QuadtreeScene::update(float dt)
    {
        m_camera.update(dt);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2f mpos = info::getMousePosition();
            sf::Vector2f pos(mpos.x - 7, mpos.y - 7);
            m_boxes.push_back(new gameObj::AABBcollider(pos, {14, 14}));
            static_cast<gameObj::AABBcollider*>(m_boxes.back())->getAcc() = sf::Vector2f(std::cos(nbgen::between(0, 360) * 3.14f / 180.0f),
            std::sin(nbgen::between(0, 360) * 3.14f / 180.0f)) * 20000.0f;
            static_cast<gameObj::AABBcollider*>(m_boxes.back())->setFillColor(bya::coloring::randomColor());
            static_cast<gameObj::AABBcollider*>(m_boxes.back())->getFriction() = 3.f;
            m_objectCountText.setString("number of objects: " + std::to_string(m_boxes.size()));
        }

        gameObj::AABBcollider* player = static_cast<gameObj::AABBcollider*>(m_boxes[1]);

        m_solver.solveSystem(m_boxes, dt, 0.016, &m_quadtree);

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

    void QuadtreeScene::batchDraw(sf::RenderTarget &target)
    {
        sf::VertexArray vertices(sf::Quads, m_boxes.size() * 4);

        for (int i = 0; i < m_boxes.size(); i++) {
            sf::FloatRect bounds = static_cast<gameObj::AABBcollider*>(m_boxes[i])->getBounds();
            vertices[i * 4].position = {bounds.left, bounds.top};
            vertices[i * 4 + 1].position = {bounds.left + bounds.width, bounds.top};
            vertices[i * 4 + 2].position = {bounds.left + bounds.width, bounds.top + bounds.height};
            vertices[i * 4 + 3].position = {bounds.left, bounds.top + bounds.height};

            vertices[i * 4].color = static_cast<gameObj::AABBcollider*>(m_boxes[i])->getFillColor();
            vertices[i * 4 + 1].color = static_cast<gameObj::AABBcollider*>(m_boxes[i])->getFillColor();
            vertices[i * 4 + 2].color = static_cast<gameObj::AABBcollider*>(m_boxes[i])->getFillColor();
            vertices[i * 4 + 3].color = static_cast<gameObj::AABBcollider*>(m_boxes[i])->getFillColor();
        }

        target.draw(vertices);
    }

    void QuadtreeScene::render(sf::RenderTarget &target)
    {
        //for (auto &AABBcollider : m_boxes) {
        //    static_cast<gameObj::AABBcollider*>(AABBcollider)->draw(target);
        //}

        batchDraw(target);

        m_quadtree.draw(target);

        info::getWindowInstance()->setView(info::getStaticView());

        target.draw(m_objectCountText);
    }

}
