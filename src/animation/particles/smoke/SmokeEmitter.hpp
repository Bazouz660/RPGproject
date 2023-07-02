/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** SmokeEmitter
*/

#pragma once

#include "AParticleEmitter.hpp"
#define SMOKE_MAX_SCALE 12.f

namespace bya::effects {

    class SmokeEmitter : public AParticleEmitter {

        public:
            SmokeEmitter(sf::Texture& texture);
            ~SmokeEmitter() = default;

            void update(float dt) override;
            void draw(sf::RenderTarget &target) override;

            void setPartSize(const sf::Vector2f &size) override { m_partSize = size; m_maxSize = size * SMOKE_MAX_SCALE;}
            void setPartSize(float x, float y) override { m_partSize = {x, y}; m_maxSize = {x * SMOKE_MAX_SCALE, y * SMOKE_MAX_SCALE};}

            void setEjectForce(float mult);

        private:
            void addPart();

        private:
            sf::Texture& m_texture;
            sf::VertexArray m_va;
            float m_ejectForce;
    };

}