/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** AABBdiscrete
*/

#include "AABBdiscrete.hpp"

namespace bya {
    namespace physics {

        sf::Vector2f AABBdiscrete::getOverlap(sf::FloatRect box1, sf::FloatRect box2)
        {
            sf::Vector2f overlap;

            overlap.x = std::min(box1.left + box1.width, box2.left + box2.width) - std::max(box1.left, box2.left);
            overlap.y = std::min(box1.top + box1.height, box2.top + box2.height) - std::max(box1.top, box2.top);
            return overlap;
        }

        void AABBdiscrete::solveCollision(gameObj::AABBcollider &box1, gameObj::AABBcollider &box2)
        {
            if (box1.isStatic())
                return;
            sf::FloatRect box1Bounds = box1.getBounds();
            sf::FloatRect box2Bounds = box2.getBounds();

            if (box1Bounds.intersects(box2Bounds)) {
                sf::Vector2f overlap = getOverlap(box1Bounds, box2Bounds);
                if (overlap.x < overlap.y) {
                    if (box1Bounds.left < box2Bounds.left) {
                        box1.setPosition(box1Bounds.left - overlap.x, box1Bounds.top);
                        box1.getVel().x = 0;
                    } else {
                        box1.setPosition(box1Bounds.left + overlap.x, box1Bounds.top);
                        box1.getVel().x = 0;
                    }
                } else {
                    if (box1Bounds.top < box2Bounds.top) {
                        box1.setPosition(box1Bounds.left, box1Bounds.top - overlap.y);
                        box1.getVel().y = 0;
                        box1.shouldApplyGravity() = false;
                    } else {
                        box1.setPosition(box1Bounds.left, box1Bounds.top + overlap.y);
                        box1.getVel().y = 0;
                    }
                }
            }
        }

        void AABBdiscrete::solveSystem(std::vector<gameObj::IObject*> &boxes, float dt, float timeStep,
            spacePart::Quadtree<gameObj::IObject *, std::function<sf::FloatRect(gameObj::IObject *)>> *m_quadtree)
        {
            m_quadtree->clear();
            for (auto &AABBcollider : boxes) {
                static_cast<gameObj::AABBcollider*>(AABBcollider)->fixedUpdate(dt, timeStep);
                m_quadtree->add(AABBcollider);
            }
            if (m_quadtree == nullptr)
                bruteForceSolving(boxes);
            else
                quadtreeSolving(boxes, m_quadtree);
        }

        void AABBdiscrete::bruteForceSolving(std::vector<gameObj::IObject*> &boxes)
        {
            for (int i = 0; i < boxes.size(); i++) {
                for (int j = 0; j < boxes.size(); j++) {
                    if (boxes[i] == boxes[j])
                        continue;
                    solveCollision(dynamic_cast<gameObj::AABBcollider &>(*boxes[i]),
                        dynamic_cast<gameObj::AABBcollider &>(*boxes[j]));
                }
            }
        }

        void AABBdiscrete::quadtreeSolving(std::vector<gameObj::IObject*> &boxes,
            spacePart::Quadtree<gameObj::IObject *, std::function<sf::FloatRect(gameObj::IObject *)>> *m_quadtree)
        {
            for (int i = 0; i < boxes.size(); i++) {
                std::vector<gameObj::IObject *> objects = m_quadtree->query(boxes[i]->getBounds());
                for (int j = 0; j < objects.size(); j++) {
                    if (objects[j] == boxes[i])
                        continue;
                    solveCollision(dynamic_cast<gameObj::AABBcollider &>(*boxes[i]),
                        dynamic_cast<gameObj::AABBcollider &>(*objects[j]));
                }
            }
        }
    }
}