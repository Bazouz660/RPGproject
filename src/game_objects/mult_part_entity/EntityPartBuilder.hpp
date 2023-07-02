/*
** EPITECH PROJECT, 2023
** RPGproject
** File description:
** EntityPartBuilder
*/

#pragma once

#include "IMultPartEntity.hpp"
#include "PartEntity.hpp"

namespace bya::gameObj {

    class EntityPartBuilder {

        public:
            EntityPartBuilder() {
                m_collisionBox.setFillColor(sf::Color(255, 0, 0, 100));
                m_collisionBox.setOutlineColor(sf::Color::Red);
                m_collisionBox.setOutlineThickness(1);
                m_pivotPointIndicator.setFillColor(sf::Color::White);
                m_pivotPointIndicator.setRadius(2);
            }

            EntityPartBuilder &setName(std::string name) {
                m_name = name;
                return *this;
            }

            EntityPartBuilder &setPivotPoint(sf::Vector2f pivotPoint) {
                m_pivotPoint = pivotPoint;
                return *this;
            }

            EntityPartBuilder &setPivotPoint(float x, float y) {
                setPivotPoint({x, y});
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

            std::shared_ptr<IMultPartEntity> build() {
                auto entity = std::make_shared<PartEntity>(m_name);
                entity->setPivotPoint(m_pivotPoint);
                entity->setPosition(m_position);
                entity->setRotation(m_rotation);
                entity->setSize(m_collisionBox.getSize());
                return entity;
            }

        private:
            sf::Vector2f m_pivotPoint = {0, 0};
            sf::Vector2f m_position = {0, 0};
            float m_rotation = 0;
            float m_previousRotation = 0;
            std::string m_name = "";
            sf::RectangleShape m_collisionBox;
            sf::CircleShape m_pivotPointIndicator;

    };

}