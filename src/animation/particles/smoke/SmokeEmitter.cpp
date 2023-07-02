/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** SmokeEmitter
*/

#include "SmokeEmitter.hpp"
#include "math.hpp"
#include "numberGenerator.hpp"
#include "ResourceManager.hpp"

namespace bya::effects {

    SmokeEmitter::SmokeEmitter(sf::Texture& texture)
    : m_texture(texture), m_ejectForce(0)
    {
        m_emissionRate = 100;
        m_partLifeTime = 3;
        m_partSize = {10, 10};
        m_maxSize = m_partSize * SMOKE_MAX_SCALE;
        m_partSpeed = 1;
        m_state = true;
        m_texture = getResource().getTexture("smoke");
        m_va.setPrimitiveType(sf::Quads);
    }

    void SmokeEmitter::addPart()
    {
        Particle particle;
        sf::Vertex part[4];

        part[0].position = m_pos - m_partSize / 2.f;
        part[1].position = m_pos + sf::Vector2f(m_partSize.x / 2.f, -m_partSize.y / 2.f);
        part[2].position = m_pos + m_partSize / 2.f;
        part[3].position = m_pos + sf::Vector2f(-m_partSize.x / 2.f, m_partSize.y / 2.f);

        part[0].texCoords = sf::Vector2f(0, 0);
        part[1].texCoords = sf::Vector2f(m_texture.getSize().x, 0);
        part[2].texCoords = sf::Vector2f(m_texture.getSize().x, m_texture.getSize().y);
        part[3].texCoords = sf::Vector2f(0, m_texture.getSize().y);

        for (auto &vertex : part) {
            vertex.color = sf::Color(255, 255, 255, 200);
        }

        particle.vertices = {part[0], part[1], part[2], part[3]};
        particle.lifeTime = m_partLifeTime + nbgen::between(-0.75f, 0.75f);
        particle.lifeTimer = 0;
        particle.rotation = 0;
        particle.rotationSpeed = nbgen::between(-100, 100);
        float xSpeed = nbgen::between(-200, 200);

        particle.acceleration = {xSpeed, 0};
        particle.acceleration.y = (nbgen::between(0.f, 10.f) * 0.2f * std::abs(xSpeed));
        particle.acceleration.y -= 10 * m_ejectForce;

        // apply dir to acceleration
        particle.velocity = {0, 0};
        particle.size = m_partSize;
        particle.pos = m_pos;
        m_particles.push_back(std::make_unique<Particle>(particle));
    }

    void SmokeEmitter::setEjectForce(float mult)
    {
        m_ejectForce = mult;
    }

    void SmokeEmitter::update(float dt)
    {
        if (isEmmiting()) {
            m_emissionTimer += dt;
            if (m_emissionTimer >= 1.0 / m_emissionRate) {
                m_emissionTimer = 0;
                addPart();
            }
            for (int i = 0; i < m_particles.size(); i++) {
                auto &part = m_particles[i];
                part->lifeTimer += dt;

                // compute velocity
                part->velocity += sf::Vector2f(0, -GRAVITY) * 10.f * dt;
                part->velocity += math::rotate(part->acceleration, m_angle) * dt;
                part->velocity *= m_partSpeed;

                part->pos += part->velocity * dt;

                part->velocity = math::lerp(part->velocity, sf::Vector2f(0, 0), dt * 0.7f);
                part->acceleration = math::lerp(part->acceleration, sf::Vector2f(0, 0), std::pow(dt, 0.4) * 0.1f);

                part->rotation += part->rotationSpeed * dt;
                part->rotation = math::lerp(part->rotation, 0.f, dt * 0.1f);

                // increase size over time (very fast at the beginning then slower and slower)
                part->size = math::lerp(part->size, m_maxSize, std::pow(dt, 0.8) * 0.1f);

                part->vertices[0].position = part->pos - part->size / 2.f;
                part->vertices[1].position = part->pos + sf::Vector2f(part->size.x / 2.f, -part->size.y / 2.f);
                part->vertices[2].position = part->pos + part->size / 2.f;
                part->vertices[3].position = part->pos + sf::Vector2f(-part->size.x / 2.f, part->size.y / 2.f);

                for (auto &vertex : part->vertices) {
                    vertex.color.a = 255 - (part->lifeTimer / part->lifeTime) * 255;
                    vertex.position -= part->pos;
                    vertex.position = math::rotate(vertex.position, part->rotation);
                    vertex.position += part->pos;
                }

                if (part->lifeTimer >= part->lifeTime)
                    m_particles.erase(std::remove(m_particles.begin(), m_particles.end(), part), m_particles.end());
            }
        }
    }

    void SmokeEmitter::draw(sf::RenderTarget &target)
    {
        m_va.clear();
        // parse particles in reverse order
        for (int i = m_particles.size() - 1; i >= 0; i--) {
            auto& part = m_particles.at(i);
            for (auto& vertex : part->vertices)
                m_va.append(vertex);
        }

        sf::RenderStates states = sf::RenderStates::Default;
        states.texture = &m_texture;

        target.draw(m_va, states);
    }

}