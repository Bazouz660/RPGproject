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

            EntityPartBuilder &setTexture(std::string textureName) {
                m_textureName = textureName;
                return *this;
            }

            EntityPartBuilder &setTextureRect(sf::IntRect textureRect) {
                m_textureRect = textureRect;
                return *this;
            }

            std::shared_ptr<IMultPartEntity> build() {
                auto entity = std::make_shared<PartEntity>();
                entity->setName(m_name);
                entity->setPivotPoint(m_pivotPoint);
                entity->setPosition(m_position);
                entity->setRotation(m_rotation);
                entity->setZIndex(m_ZIndex);
                entity->setTint(m_tint);
                entity->setParent(m_parent);
                entity->setSize(m_collisionBox.getSize());

                if (m_textureName != "nullptr") {
                    entity->setTexture(getResource().getTexture(m_textureName));
                    if (m_textureRect != sf::IntRect(0, 0, 0, 0))
                        entity->setTextureRect(m_textureRect);
                    m_textureName = "nullptr";
                    m_textureRect = sf::IntRect(0, 0, 0, 0);
                }

                m_tint = sf::Color(255, 0, 0, 255);
                return entity;
            }

        private:
            sf::Vector2f m_pivotPoint = {0, 0};
            sf::Vector2f m_position = {0, 0};
            sf::Color m_tint = sf::Color(255, 0, 0, 255);
            float m_rotation = 0;
            float m_previousRotation = 0;
            int m_ZIndex = 0;
            std::string m_name = "";
            IMultPartEntity *m_parent = nullptr;
            sf::RectangleShape m_collisionBox;
            sf::CircleShape m_pivotPointIndicator;
            std::string m_textureName = "nullptr";
            sf::IntRect m_textureRect = {0, 0, 0, 0};
    };

}