/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-03 18:50:24
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-12 00:20:27
 *  Description:
*/


#pragma once

#include "IMultPartEntity.hpp"
#include "context.hpp"
#include "parsing.hpp"
#include "json.hpp"
#include "OrientedBoundingBox.hpp"

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

            virtual void draw(sf::RenderTarget &target, bool drawDebug) override {
                if (drawDebug)
                    target.draw(m_collisionBox);
                m_orientedBox.render(target);
                target.draw(m_pivotPointIndicator);
            }

            virtual void render(sf::RenderTarget &target, bool drawDebug = false) override {
                sortZIndex();
                for (auto &part : m_sortedZparts)
                    part->draw(target, drawDebug);
            }

            virtual void setPosition(sf::Vector2f pos) override {
                sf::Vector2f offset = pos - m_position;
                m_position = pos;
                m_collisionBox.setPosition(m_position);
                m_pivotPointIndicator.setPosition(m_position);
                m_orientedBox.setPosition(m_position);
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
                m_orientedBox.setOrigin(pivotPoint);
            }

            virtual void setPivotPoint(float x, float y) override {
                setPivotPoint({x, y});
            }

            virtual sf::Vector2f getPivotPoint() const override {
                return m_pivotPoint;
            }

            virtual float getOwnRotation() const override {
                return m_ownRotation;
            }

            virtual float getHeritedRotation() const override
            {
                if (m_parent)
                    return m_parent->getGlobalRotation();
                return 0;
            }

            virtual float getGlobalRotation() const override {
                return m_ownRotation + getHeritedRotation();
            }

            // Helper function to recursively apply rotation to all child entities
            void applyRotationToChildren(IMultPartEntity& entity, float offsetRotation)
            {
                sf::Transform transform = sf::Transform::Identity;
                transform.rotate(offsetRotation * m_orientedBox.getScale().x, entity.getPosition());

                for (auto &part : entity.getChildren(false)) {
                    sf::Vector2f pos = part->getPosition();
                    pos = transform.transformPoint(pos);
                    part->setPosition(pos);
                    part->setRotation(part->getOwnRotation(), false);
                    applyRotationToChildren(*part, offsetRotation);
                }
            }

            virtual void setRotation(float angle, bool changeOwn = true) override
            {
                m_previousRotation = getGlobalRotation();

                if (changeOwn) {
                    m_ownRotation = angle;
                }

                m_collisionBox.setRotation(getGlobalRotation() * m_orientedBox.getScale().x);
                m_orientedBox.setRotation(getGlobalRotation());
                m_pivotPointIndicator.setPosition(m_position);

                float offset = getGlobalRotation() - m_previousRotation;

                // Apply rotation to the children recursively
                applyRotationToChildren(*this, offset);
            }


            virtual void setSize(sf::Vector2f size) override {
                m_collisionBox.setSize(size);
                m_orientedBox.setSize(size);
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

            void sortZIndex() override
            {
                m_sortedZparts.clear();
                m_sortedZparts.push_back(shared_from_this());
                for (auto &part : getChildren()) {
                    m_sortedZparts.push_back(part);
                }
                std::sort(m_sortedZparts.begin(), m_sortedZparts.end(), [](std::shared_ptr<IMultPartEntity> a, std::shared_ptr<IMultPartEntity> b) {
                    return a->getZIndex() < b->getZIndex();
                });
            }

            virtual std::vector<std::shared_ptr<IMultPartEntity>>& getSortedZParts() override
            {
                return m_sortedZparts;
            }

            virtual void setTint(sf::Color tint) override {
                m_tint = tint;
                m_collisionBox.setFillColor(tint);
                m_orientedBox.setColor(tint);
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

            virtual IMultPartEntity* getRoot() override {
                if (m_parent == nullptr)
                    return this;
                return m_parent->getRoot();
            }

            virtual sf::Vector2f getSize() const override {
                return m_collisionBox.getSize();
            }

            virtual bool isHovered() const override {
                return m_orientedBox.contains(context::getMousePosition());
            }

            virtual void flipX() override {
                m_collisionBox.setScale({m_collisionBox.getScale().x * -1, m_collisionBox.getScale().y});
                m_collisionBox.setRotation(m_collisionBox.getRotation() * -1);
                m_orientedBox.setScale({m_orientedBox.getScale().x * -1, m_orientedBox.getScale().y});
                if (m_parent) {
                    IMultPartEntity* root = getRoot();
                    sf::Vector2f posRelativeToRoot = root->getPosition() - m_orientedBox.getPosition();
                    posRelativeToRoot.x *= -1;
                    sf::Vector2f newPos(root->getPosition().x - posRelativeToRoot.x, m_orientedBox.getPosition().y);
                    m_orientedBox.setPosition(newPos);
                    m_position = newPos;
                }
                m_pivotPointIndicator.setScale({m_pivotPointIndicator.getScale().x * -1, m_pivotPointIndicator.getScale().y});

                setZIndex(-getZIndex());
                // flip childs
                for (auto &[partName, part] : m_parts)
                    part->flipX();
                if (!m_parent)
                    sortZIndex();

                for (const auto& mapping : m_partMapping) {
                    const std::string& part1 = mapping.first;
                    const std::string& part2 = mapping.second;
                    sf::Vector2f pos1 = m_parts[part1]->getPosition();
                    sf::Vector2f pos2 = m_parts[part2]->getPosition();
                    m_parts[part1]->setPosition(pos2);
                    m_parts[part2]->setPosition(pos1);
                }
            }

            std::vector<std::shared_ptr<IMultPartEntity>> getChildren(bool recursive = true) const {
                std::vector<std::shared_ptr<IMultPartEntity>> parts;
                for (auto &[partName, part] : m_parts) {
                    parts.push_back(part);
                    if (recursive) {
                        std::vector<std::shared_ptr<IMultPartEntity>> childs = part->getChildren(recursive);
                        parts.insert(parts.end(), childs.begin(), childs.end());
                    }
                }
                return parts;
            }

            sf::Vector2f getScale() const override {
                return m_orientedBox.getScale();
            }

            virtual void setName(const std::string& name) override { m_name = name; }
            virtual std::string getName() const override { return m_name; }
            virtual void setTexture(sf::Texture &texture) { m_orientedBox.setTexture(texture); }
            virtual void setTextureRect(sf::IntRect rect) { m_orientedBox.setTextureRect(rect); }
            virtual sf::IntRect getTextureRect() const { return m_orientedBox.getTextureRect(); }
            virtual sf::Texture* getTexture() const { return m_orientedBox.getTexture(); }

            virtual void loadFromJson(std::string path) override;
            virtual void saveToJson(std::string path) override;

        private:
            void parsePart(const std::string& name, const nlohmann::json& json, IMultPartEntity* parent = nullptr);
            void parseRotation(const std::string& name, const nlohmann::json& json);
            void savePartToJson(IMultPartEntity* part, nlohmann::json& json, std::map<std::string, float>& rotationMap);

        protected:
            AMultPartEntity(IMultPartEntity* parent = nullptr)
            : m_parent(parent)
            {
                m_pivotPointIndicator.setRadius(2);
                sf::FloatRect bounds = m_pivotPointIndicator.getGlobalBounds();
                m_pivotPointIndicator.setOrigin(bounds.width / 2, bounds.height / 2);
                m_collisionBox.setFillColor(sf::Color(255, 255, 255, 100));
                m_collisionBox.setOutlineColor(sf::Color::Black);
                m_collisionBox.setOutlineThickness(1);
            }
            sf::Vector2f m_pivotPoint = {0, 0};
            sf::Vector2f m_position = {0, 0};
            int m_zIndex = 0;
            float m_ownRotation = 0;
            float m_previousRotation = 0;
            sf::Color m_tint = sf::Color::White;
            std::string m_name = "";

            sf::RectangleShape m_collisionBox;
            OrientedBoundingBox m_orientedBox;
            sf::CircleShape m_pivotPointIndicator;

            IMultPartEntity* m_parent = nullptr;
            std::vector<std::shared_ptr<IMultPartEntity>> m_sortedZparts;
            std::map<std::string, std::string> m_partMapping;
            std::map<std::string, std::shared_ptr<IMultPartEntity>> m_parts;
    };

}