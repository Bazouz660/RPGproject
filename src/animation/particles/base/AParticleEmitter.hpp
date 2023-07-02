/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** AParticleEmitter
*/

#pragma once

#include "IParticleEmitter.hpp"

namespace bya::effects {

    class AParticleEmitter : public IParticleEmitter {

        public:
            ~AParticleEmitter() override = default;

            void toggle(bool state) override { m_state = state;}
            void update(float dt) override = 0;
            void draw(sf::RenderTarget &target) override = 0;

            void setPos(const sf::Vector2f &pos) override { m_pos = pos;}
            void setPos(float x, float y) override { m_pos = {x, y};}

            void setAngle(float angle) override { m_angle = angle;}
            float getAngle() const override { return m_angle;}

            void setEmissionRate(float rate) override { m_emissionRate = rate;}

            void setPartLifeTime(float time) override { m_partLifeTime = time;}

            void setPartSize(const sf::Vector2f &size) override { m_partSize = size; m_maxSize = size * 10.f;}
            void setPartSize(float x, float y) override { m_partSize = {x, y}; m_maxSize = {x * 10.f, y * 10.f};}

            void setPartSpeed(float speed) override { m_partSpeed = speed;}

            sf::Vector2f getPos() const override { return m_pos;}
            float getEmissionRate() const override { return m_emissionRate;}
            float getPartLifeTime() const override { return m_partLifeTime;}
            sf::Vector2f getPartSize() const override { return m_partSize;}
            float getPartSpeed() const override { return m_partSpeed;}
            bool isEmmiting() const override { return m_state;}

        protected:
            AParticleEmitter()
            : m_pos(0, 0), m_partSize(0, 0), m_partLifeTime(0), m_emissionRate(0),
            m_emissionTimer(0), m_partSpeed(0), m_angle(0), m_state(false) {}

            typedef struct
            {
                sf::Vector2f pos;
                sf::Vector2f velocity;
                sf::Vector2f acceleration;
                sf::Vector2f size;
                std::vector<sf::Vertex> vertices;
                float rotation;
                float rotationSpeed;
                float lifeTime;
                float lifeTimer;
            } Particle;

            sf::Vector2f m_pos;
            sf::Vector2f m_partSize;
            sf::Vector2f m_maxSize;
            float m_partLifeTime;
            float m_emissionRate;
            float m_emissionTimer;
            float m_partSpeed;
            float m_angle;
            bool m_state;

            std::vector<std::shared_ptr<Particle>> m_particles;
    };

}