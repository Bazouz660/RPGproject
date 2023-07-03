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
                if (m_parts.find(name) == m_parts.end()) {
                    for (auto &[partName, part] : m_parts) {
                        std::shared_ptr<IMultPartEntity> found = part->getPart(name);
                        if (found != nullptr)
                            return found;
                    }
                    return nullptr;
                }
                return m_parts[name];
            }

            virtual void draw(sf::RenderTarget &target) override {
                target.draw(m_collisionBox);
                m_pivotPointIndicator.setPosition(m_position);
                target.draw(m_pivotPointIndicator);
            }

            virtual void render(sf::RenderTarget &target) override {
                sortZIndex();
                for (auto &part : m_sortedZparts)
                    part->draw(target);
            }

            virtual void setPosition(sf::Vector2f pos) override {
                sf::Vector2f offset = pos - m_position;
                m_position = pos;
                m_collisionBox.setPosition(pos);
                for (auto &[partName, part] : m_parts)
                    part->setPosition(part->getPosition() + offset);
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
                m_previousRotation = m_rotation;
                if (m_parent)
                    angle += m_parent->getRotation();
                float offset = angle - m_previousRotation;
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

            virtual void setFixedRotation(float angle) override {
                m_previousRotation = m_rotation;
                if (m_parent)
                    angle += m_parent->getRotation();
                float offset = angle - m_previousRotation;
                m_rotation = angle;
                m_previousRotation = angle;
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

            virtual void setZIndex(int zIndex) override {
                m_zIndex = zIndex;
            }

            virtual int getZIndex() const override {
                return m_zIndex;
            }

            bool needsSorting() const override {
                if (m_sortedZparts.size() != m_parts.size())
                    return true;
                return false;
            }

            std::vector<IMultPartEntity*> sortZIndex() override {
                if (needsSorting()) {
                    m_sortedZparts.clear();
                    m_sortedZparts.push_back(this);
                    for (auto &[partName, part] : m_parts) {
                        m_sortedZparts.push_back(part.get());
                        std::vector<IMultPartEntity*> childs = part->sortZIndex();
                        m_sortedZparts.insert(m_sortedZparts.end(), childs.begin(), childs.end());
                    }
                    std::sort(m_sortedZparts.begin(), m_sortedZparts.end(),
                        [](IMultPartEntity* a, IMultPartEntity* b) {
                        return a->getZIndex() < b->getZIndex();
                    });
                }
                return m_sortedZparts;
            }

            virtual void setTint(sf::Color tint) override {
                m_tint = tint;
                m_collisionBox.setFillColor(tint);
            }

            virtual sf::Color getTint() const override {
                return m_tint;
            }

            virtual void setParent(IMultPartEntity* parent) override {
                m_parent = parent;
            }

            virtual IMultPartEntity* getParent() const override {
                return m_parent;
            }

        protected:
            AMultPartEntity(const std::string& name, IMultPartEntity* parent = nullptr)
            : m_name(name), m_parent(parent)
            {
                m_pivotPointIndicator.setRadius(2);
                sf::FloatRect bounds = m_pivotPointIndicator.getGlobalBounds();
                m_pivotPointIndicator.setOrigin(bounds.width / 2, bounds.height / 2);
                m_collisionBox.setFillColor(sf::Color(255, 0, 0, 100));
                m_collisionBox.setOutlineColor(sf::Color::Red);
                m_collisionBox.setOutlineThickness(1);
            }
            std::map<std::string, std::shared_ptr<IMultPartEntity>> m_parts;
            sf::Vector2f m_pivotPoint = {0, 0};
            sf::Vector2f m_position = {0, 0};
            sf::Color m_tint = sf::Color::White;
            float m_rotation = 0;
            float m_previousRotation = 0;
            int m_zIndex = 0;
            std::string m_name;
            sf::RectangleShape m_collisionBox;
            sf::CircleShape m_pivotPointIndicator;
            IMultPartEntity* m_parent = nullptr;
            std::vector<IMultPartEntity*> m_sortedZparts;
    };

}