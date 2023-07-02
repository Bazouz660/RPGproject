/*
** EPITECH PROJECT, 2023
** RPGproject
** File description:
** AMultPartEntity
*/

#pragma once

#include "IMultPartEntity.hpp"

namespace bya::gameObj
{
    class AMultPartEntity : public IMultPartEntity
    {
        public:
            virtual ~AMultPartEntity() = default;
            virtual void update(float dt) override = 0;

            virtual void addPart(std::string partName, std::shared_ptr<IMultPartEntity> part) override {
                m_parts[partName] = part;
            }

            virtual void removePart(std::shared_ptr<IMultPartEntity> part, std::string name = "") override {
                if (name == "")
                    for (auto &[partName, part] : m_parts)
                        if (part == part)
                            m_parts.erase(partName);
                else
                    m_parts.erase(name);
            }

            virtual std::shared_ptr<IMultPartEntity> getPart(std::string name) override {
                if (m_parts.find(name) == m_parts.end())
                    throw std::runtime_error("Part not found");
                return m_parts[name];
            }

            virtual void render(sf::RenderTarget &target) override {
                target.draw(m_collisionBox);
                m_pivotPointIndicator.setPosition(m_position);
                target.draw(m_pivotPointIndicator);
                for (auto &[partName, part] : m_parts)
                    part->render(target);
            }

            virtual void setPosition(sf::Vector2f pos) override {
                sf::Vector2f offset = pos - m_position;
                m_position = pos;
                m_collisionBox.setPosition(pos);
                updateChildsPosition(offset);
            }

            virtual void setPosition(float x, float y) override {
                setPosition({x, y});
            }

            virtual sf::Vector2f getPosition() const override {
                return m_position;
            }

            virtual void setPivotPoint(sf::Vector2f pivotPoint) override {
                m_pivotPoint = pivotPoint;
                m_collisionBox.setOrigin(pivotPoint);
            }

            virtual void setPivotPoint(float x, float y) override {
                setPivotPoint({x, y});
            }

            virtual sf::Vector2f getPivotPoint() const override {
                return m_pivotPoint;
            }

            virtual void setRotation(float angle) override {
                float offset = m_rotation - m_previousRotation;
                m_previousRotation = m_rotation;
                m_rotation = angle;
                m_collisionBox.setRotation(angle);
                m_pivotPointIndicator.setPosition(std::cos(angle), std::sin(angle));

                sf::Transform transform = sf::Transform::Identity;
                transform.rotate(offset, m_position);

                // rotate childs
                for (auto &[partName, part] : m_parts) {
                    sf::Vector2f pos = part->getPosition();
                    pos = transform.transformPoint(pos);
                    part->setPosition(pos);
                    part->setRotation(part->getRotation() + offset);
                }
            }

            virtual float getRotation() const override {
                return m_rotation;
            }

            virtual void setSize(sf::Vector2f size) override {
                m_collisionBox.setSize(size);
            }

            virtual void setSize(float x, float y) override {
                setSize({x, y});
            }

        protected:
            void updateChildsPosition(sf::Vector2f offset) {
                for (auto &[partName, part] : m_parts)
                    part->setPosition(part->getPosition() + offset);
            }

        protected:
            AMultPartEntity(const std::string& name)
            : m_name(name)
            {
                m_pivotPointIndicator.setRadius(2);
                m_collisionBox.setFillColor(sf::Color(255, 0, 0, 100));
                m_collisionBox.setOutlineColor(sf::Color::Red);
                m_collisionBox.setOutlineThickness(1);
            }
            std::map<std::string, std::shared_ptr<IMultPartEntity>> m_parts;
            sf::Vector2f m_pivotPoint = {0, 0};
            sf::Vector2f m_position = {0, 0};
            float m_rotation = 0;
            float m_previousRotation = 0;
            std::string m_name;
            sf::RectangleShape m_collisionBox;
            sf::CircleShape m_pivotPointIndicator;
    };

}