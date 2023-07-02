/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** QuadtreeScene
*/

#pragma once

#include "IScene.hpp"
#include "Quadtree.hpp"
#include "Box.hpp"
#include "Camera.hpp"
#include "AABBdiscrete.hpp"
#include "AABBcontinuous.hpp"
#include <functional>

namespace bya {

class QuadtreeScene : public IScene {
    public:
        QuadtreeScene();
        virtual ~QuadtreeScene() override;
        virtual void init() override;
        virtual void close() override;
        virtual void reset() override;
        virtual void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
        virtual void update(float dt) override;
        virtual void render(sf::RenderTarget& target) override;

    private:
        void batchDraw(sf::RenderTarget& target);

    private:
        std::vector<gameObj::IObject*> m_boxes;
        physics::AABBdiscrete m_solver;
        spacePart::Quadtree<gameObj::IObject*, std::function<sf::FloatRect(gameObj::IObject*)>> m_quadtree;
        Camera m_camera;

        sf::Text m_objectCountText;
};

}