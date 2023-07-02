/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** AABBdiscrete
*/

#pragma once

#include "common.hpp"
#include "AABBcollider.hpp"
#include "Quadtree.hpp"
#include <functional>

namespace bya {

    namespace physics {

        class AABBdiscrete {
        public:
            AABBdiscrete() = default;
            ~AABBdiscrete() = default;

            void solveSystem(std::vector<gameObj::IObject*> &boxes, float dt, float timeStep,
                spacePart::Quadtree<gameObj::IObject *, std::function<sf::FloatRect(gameObj::IObject *)>> *m_quadtree = nullptr);

        private:
            sf::Vector2f getOverlap(sf::FloatRect box1, sf::FloatRect box2);

            void solveCollision(gameObj::AABBcollider &box1, gameObj::AABBcollider &box2);

            void bruteForceSolving(std::vector<gameObj::IObject*> &boxes);

            void quadtreeSolving(std::vector<gameObj::IObject*> &boxes, spacePart::Quadtree<gameObj::IObject *,
                std::function<sf::FloatRect(gameObj::IObject *)>> *m_quadtree);

        private:
            float m_time = 0;
        };

    }

}