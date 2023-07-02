/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** AABBcontinuous
*/

#pragma once

#include "common.hpp"
#include "AABBcollider.hpp"
#include "Quadtree.hpp"
#include <functional>

namespace bya::physics {

        class AABBcontinuous {
        public:
            AABBcontinuous() = default;
            ~AABBcontinuous() = default;

            void solveSystem(std::vector<gameObj::IObject*> &boxes, float dt);

        private:

            float sweptAABB(gameObj::AABBcollider &box1, gameObj::AABBcollider &box2, sf::Vector2f& normal);

            sf::FloatRect getBroadphaseBox(gameObj::AABBcollider &box);

            void solveCollision(gameObj::AABBcollider &box1, gameObj::AABBcollider &box2);

            void solveIntersection(gameObj::AABBcollider &box1, gameObj::AABBcollider &box2);

            void bruteForceSolving(std::vector<gameObj::IObject*> &boxes);

            void quadtreeSolving(std::vector<gameObj::IObject*> &boxes, spacePart::Quadtree<gameObj::IObject *,
                std::function<sf::FloatRect(gameObj::IObject *)>> *m_quadtree);

        private:
            float m_dt = 0;
            float m_timer = 0;
        };

}