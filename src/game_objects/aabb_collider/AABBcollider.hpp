/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** AABBcollider
*/

#pragma once

#include "common.hpp"
#include "Box.hpp"

namespace bya {

    namespace gameObj {

        class AABBcollider : public Box {
            public:
                AABBcollider();
                AABBcollider(sf::Vector2f pos, sf::Vector2f size);
                virtual ~AABBcollider() override = default;

                sf::Vector2f& getVel();
                sf::Vector2f& getAcc();
                float& getFriction();
                float& getGravity();
                bool isStatic() const;
                void setStatic(bool state);
                bool& shouldApplyGravity();
                float &getUpdateTimer();

                virtual void update(float dt);
                virtual void fixedUpdate(float dt, float timeStep);

            private:
                void init();
                sf::Vector2f m_velocity;
                sf::Vector2f m_acceleration;
                float m_friction;
                float m_updateTimer;
                bool m_static;
                float m_gravity;
                bool m_shouldApplyGravity;
        };

    }

}