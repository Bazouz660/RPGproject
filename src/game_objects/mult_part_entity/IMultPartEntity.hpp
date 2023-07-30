/*
** EPITECH PROJECT, 2023
** RPGproject
** File description:
** IMultPartEntity
*/

#pragma once

#include "common.hpp"
#include "OrientedBoundingBox.hpp"

namespace bya::gameObj
{
    class IMultPartEntity : public OrientedBoundingBox, public std::enable_shared_from_this<IMultPartEntity>
    {
        public:
            virtual ~IMultPartEntity() = default;
            virtual void update(float dt) = 0;
            virtual void addPart(std::shared_ptr<IMultPartEntity> part) = 0;
            virtual void removePart(std::shared_ptr<IMultPartEntity> part, std::string name = "") = 0;
            virtual std::shared_ptr<IMultPartEntity> getPart(std::string name) = 0;
            virtual void render(sf::RenderTarget &target) = 0;

            virtual void setRotation(float angle, bool changeOwn = true) = 0;
            virtual float getGlobalRotation() const = 0;
            virtual float getOwnRotation() const = 0;
            virtual float getHeritedRotation() const = 0;

            virtual void setPosition(sf::Vector2f pos) = 0;
            virtual void setPosition(float x, float y) = 0;

            virtual void setAttachPointOnParent(const sf::Vector2f& attachPoint) = 0;
            virtual sf::Vector2f getAttachPointOnParent() const = 0;

            //virtual void addAttachPoint(const std::string& name, sf::Vector2f pos) = 0;

            struct AttachPoint {
                sf::Vector2f pos;
                std::shared_ptr<IMultPartEntity> part;
            };

            //virtual std::vector<AttachPoint> getAvailableAttachPoints() const = 0;

            virtual void setZIndex(int zIndex) = 0;
            virtual int getZIndex() const = 0;

            virtual void sortZIndex() = 0;
            virtual std::vector<std::shared_ptr<IMultPartEntity>>& getSortedZParts() = 0;

            virtual void setTint(sf::Color tint) = 0;
            virtual sf::Color getTint() const = 0;

            virtual void setParent(IMultPartEntity* parent) = 0;
            virtual IMultPartEntity* getParent() const = 0;
            virtual IMultPartEntity* getRoot() = 0;
            virtual std::vector<std::shared_ptr<IMultPartEntity>> getRecursiveChildren() const = 0;
            virtual std::vector<std::shared_ptr<IMultPartEntity>>& getDirectChildren() = 0;

            virtual void setName(const std::string& name) = 0;
            virtual std::string getName() const = 0;

            virtual bool isHovered() const = 0;

            virtual void flipX() = 0;

            virtual void loadFromJson(std::string path) = 0;
            virtual void saveToJson(std::string path) = 0;
    };

}