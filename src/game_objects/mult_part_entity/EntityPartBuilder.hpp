/*
** EPITECH PROJECT, 2023
** RPGproject
** File description:
** EntityPartBuilder
*/

#pragma once

#include "IMultPartEntity.hpp"
#include "PartEntity.hpp"
#include "ResourceManager.hpp"

namespace bya::gameObj {

    class EntityPartBuilder {

        public:
            EntityPartBuilder() {
                m_collisionBox.setFillColor(sf::Color(255, 0, 0, 100));
                m_collisionBox.setOutlineColor(sf::Color::Red);
                m_collisionBox.setOutlineThickness(1);
                m_originIndicator.setFillColor(sf::Color::White);
                m_originIndicator.setRadius(2);
            }

            EntityPartBuilder &setName(std::string name) {
                m_name = name;
                return *this;
            }

            EntityPartBuilder &setOrigin(sf::Vector2f pivotPoint) {
                m_origin = pivotPoint;
                return *this;
            }

            EntityPartBuilder &setOrigin(float x, float y) {
                setOrigin({x, y});
                return *this;
            }

            EntityPartBuilder &setPosition(sf::Vector2f position) {
                m_position = position;
                return *this;
            }

            EntityPartBuilder &setPosition(float x, float y) {
                setPosition({x, y});
                return *this;
            }

            EntityPartBuilder &setRotation(float rotation) {
                m_rotation = rotation;
                return *this;
            }

            EntityPartBuilder &setSize(sf::Vector2f size) {
                m_collisionBox.setSize(size);
                return *this;
            }

            EntityPartBuilder &setSize(float x, float y) {
                setSize({x, y});
                return *this;
            }

            EntityPartBuilder &setZIndex(unsigned int zIndex) {
                m_ZIndex = zIndex;
                return *this;
            }

            EntityPartBuilder &setParent(IMultPartEntity *parent) {
                m_parent = parent;
                return *this;
            }

            EntityPartBuilder &setTint(sf::Color tint) {
                m_tint = tint;
                return *this;
            }

            std::shared_ptr<IMultPartEntity> build() {
                auto entity = std::make_shared<PartEntity>();
                entity->setName(m_name);
                entity->setOrigin(m_origin);
                entity->setPosition(m_position);
                entity->setRotation(m_rotation);
                entity->setZIndex(m_ZIndex);
                entity->setTint(m_tint);
                entity->setParent(m_parent);
                entity->setSize(m_collisionBox.getSize());
                m_tint = sf::Color(255, 0, 0, 255);
                return entity;
            }

        private:
            sf::Vector2f m_origin = {0, 0};
            sf::Vector2f m_position = {0, 0};
            sf::Color m_tint = sf::Color(255, 0, 0, 255);
            float m_rotation = 0;
            float m_previousRotation = 0;
            int m_ZIndex = 0;
            std::string m_name = "";
            IMultPartEntity *m_parent = nullptr;
            sf::RectangleShape m_collisionBox;
            sf::CircleShape m_originIndicator;
    };

}