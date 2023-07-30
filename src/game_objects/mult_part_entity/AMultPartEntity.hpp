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

            virtual void addPart(std::shared_ptr<IMultPartEntity> part) override {
                m_parts[part->getName()] = part;

                // get the local position of the part relative to the parent
                sf::Vector2f localPos = part->getPosition() - getGlobalCenter();
                part->setAttachPointOnParent(localPos);

                m_directChildren.push_back(part);

                sortZIndex();
                if (m_parent)
                    m_parent->sortZIndex();
            }

            virtual void setAttachPointOnParent(const sf::Vector2f& attachPoint) override {
                m_attachPointOnParent = attachPoint;
            }

            virtual sf::Vector2f getAttachPointOnParent() const override {
                return m_attachPointOnParent;
            }

            virtual void removePart(std::shared_ptr<IMultPartEntity> part, std::string name = "") override {
                if (name == "")
                    for (auto &[partName, part] : m_parts)
                        if (part == part)
                            m_parts.erase(partName);
                else
                    m_parts.erase(name);

                m_directChildren.erase(std::remove(m_directChildren.begin(), m_directChildren.end(), part), m_directChildren.end());
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

            virtual void render(sf::RenderTarget &target) override {
                for (auto &part : m_sortedZparts)
                    ((AMultPartEntity*)part.get())->draw(target, false);
            }

            virtual void setPosition(sf::Vector2f pos) override {
                sf::Vector2f offset = pos - getPosition();
                OrientedBoundingBox::setPosition(pos);
                m_pivotPointIndicator.setPosition(getPosition());

                for (auto &child : getDirectChildren())
                    child->setPosition(child->getPosition() + offset);
            }

            virtual void setPosition(float x, float y) override {
                setPosition({x, y});
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

            virtual void setRotation(float angle, bool changeOwn = true) override
            {
                OrientedBoundingBox::setRotation(angle);
                if (changeOwn)
                    m_ownRotation = angle;

                if (m_parent)
                    OrientedBoundingBox::setRotation(m_ownRotation + m_parent->getRotation());

                // compute the new position of the childs using their attach point
                for (auto &child : getDirectChildren()) {
                    // transform the attach point to the part global space
                    sf::Vector2f attachPoint = child->getAttachPointOnParent();
                    sf::Vector2f newPos = transformPoint(attachPoint + getLocalCenter());
                    child->setPosition(newPos);
                }

                for (auto &child : getDirectChildren())
                    child->setRotation(child->getRotation(), false);
            }

            virtual void setZIndex(int zIndex) override {
                m_zIndex = zIndex;
                if (m_parent)
                    m_parent->sortZIndex();
            }

            virtual int getZIndex() const override {
                return m_zIndex;
            }

            void sortZIndex() override
            {
                m_sortedZparts.clear();
                m_sortedZparts.push_back(shared_from_this());
                for (auto &part : getRecursiveChildren()) {
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
                setColor(m_tint);
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

            virtual bool isHovered() const override {
                return contains(context::getMousePosition());
            }

            virtual void flipX() override {
                setScale({getScale().x * -1, getScale().y});
                if (m_parent) {
                    IMultPartEntity* root = getRoot();
                    sf::Vector2f posRelativeToRoot = root->getPosition() - getPosition();
                    posRelativeToRoot.x *= -1;
                    sf::Vector2f newPos(root->getPosition().x - posRelativeToRoot.x, getPosition().y);
                    setPosition(newPos);
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

            std::vector<std::shared_ptr<IMultPartEntity>>& getDirectChildren() override {
                return m_directChildren;
            }

            std::vector<std::shared_ptr<IMultPartEntity>> getRecursiveChildren() const override {
                std::vector<std::shared_ptr<IMultPartEntity>> parts;
                for (auto &[partName, part] : m_parts) {
                    parts.push_back(part);
                    std::vector<std::shared_ptr<IMultPartEntity>> childs = part->getRecursiveChildren();
                    parts.insert(parts.end(), childs.begin(), childs.end());
                }
                return parts;
            }

            virtual void setName(const std::string& name) override { m_name = name; }
            virtual std::string getName() const override { return m_name; }

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
                showOutline(true);
                setOutlineColor(sf::Color::Black);
                m_pivotPointIndicator.setRadius(2);
                sf::FloatRect bounds = m_pivotPointIndicator.getGlobalBounds();
                m_pivotPointIndicator.setOrigin(bounds.width / 2, bounds.height / 2);
            }

            void draw(sf::RenderTarget &target, bool drawDebug) {
                //if (drawDebug)
                //    target.draw(m_collisionBox);
                OrientedBoundingBox::render(target);
                target.draw(m_pivotPointIndicator);
            }

        private:
            std::string m_name = "";
            int m_zIndex = 0;
            float m_ownRotation = 0;
            sf::Vector2f m_attachPointOnParent = {0, 0};
            sf::Color m_tint = sf::Color::White;
            sf::CircleShape m_pivotPointIndicator;
            IMultPartEntity* m_parent = nullptr;
            std::vector<std::shared_ptr<IMultPartEntity>> m_sortedZparts;
            std::unordered_map<std::string, std::string> m_partMapping;
            std::unordered_map<std::string, std::shared_ptr<IMultPartEntity>> m_parts;

            std::vector<std::shared_ptr<IMultPartEntity>> m_directChildren;
    };

}