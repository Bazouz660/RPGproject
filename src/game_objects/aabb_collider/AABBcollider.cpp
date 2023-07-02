/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** AABBcollider
*/

#include "AABBcollider.hpp"
#include "math.hpp"

namespace bya {

    namespace gameObj {

        AABBcollider::AABBcollider()
        {
            init();
        }

        AABBcollider::AABBcollider(sf::Vector2f pos, sf::Vector2f size)
        {
            init();
            setPosition(pos);
            setSize(size);
        }

        void AABBcollider::init()
        {
            m_velocity = sf::Vector2f(0, 0);
            m_acceleration = sf::Vector2f(0, 0);
            m_friction = 0.5f;
            m_updateTimer = 0;
            m_static = false;
            m_gravity = 9.81f;
            m_shouldApplyGravity = true;
        }

        sf::Vector2f& AABBcollider::getVel()
        {
            return m_velocity;
        }

        sf::Vector2f& AABBcollider::getAcc()
        {
            return m_acceleration;
        }

        float& AABBcollider::getFriction()
        {
            return m_friction;
        }

        float& AABBcollider::getGravity()
        {
            return m_gravity;
        }

        bool AABBcollider::isStatic() const
        {
            return m_static;
        }

        void AABBcollider::setStatic(bool state)
        {
            m_static = state;
        }

        bool& AABBcollider::shouldApplyGravity()
        {
            return m_shouldApplyGravity;
        }

        void AABBcollider::update(float dt)
        {
            if (m_static)
                return;
            if (m_shouldApplyGravity)
                m_acceleration.y += m_gravity * 10000 * dt;
            m_velocity += m_acceleration * dt;
            move(m_velocity * dt);
            m_velocity = math::lerp(m_velocity, sf::Vector2f(0, 0), dt * m_friction);
            m_acceleration = sf::Vector2f(0, 0);
            shouldApplyGravity() = true;
        }

        void AABBcollider::fixedUpdate(float dt, float timeStep)
        {
            m_updateTimer += dt;
            if (m_updateTimer >= timeStep) {
                m_updateTimer = 0;
                update(timeStep);
            }
        }

        float &AABBcollider::getUpdateTimer()
        {
            return m_updateTimer;
        }

    }

}