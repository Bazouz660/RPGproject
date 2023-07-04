/*
** EPITECH PROJECT, 2023
** RPGproject
** File description:
** IMultPartEntity
*/

#pragma once

#include "common.hpp"

namespace bya::gameObj
{
    class IMultPartEntity : public std::enable_shared_from_this<IMultPartEntity>
    {
        public:
            virtual ~IMultPartEntity() = default;
            virtual void update(float dt) = 0;
            virtual void addPart(std::string partName, std::shared_ptr<IMultPartEntity> part) = 0;
            virtual void removePart(std::shared_ptr<IMultPartEntity> part, std::string name = "") = 0;
            virtual std::shared_ptr<IMultPartEntity> getPart(std::string name) = 0;
            virtual void render(sf::RenderTarget &target) = 0;
            virtual void draw(sf::RenderTarget &target) = 0;

            virtual void setPosition(sf::Vector2f pos) = 0;
            virtual void setPosition(float x, float y) = 0;
            virtual sf::Vector2f getPosition() const = 0;

            virtual void setPivotPoint(sf::Vector2f pivotPoint) = 0;
            virtual void setPivotPoint(float x, float y) = 0;
            virtual sf::Vector2f getPivotPoint() const = 0;

            virtual void setRotation(float angle) = 0;
            virtual void setFixedRotation(float angle) = 0;
            virtual float getRotation() const = 0;

            virtual void setSize(sf::Vector2f size) = 0;
            virtual void setSize(float x, float y) = 0;

            virtual void setZIndex(int zIndex) = 0;
            virtual int getZIndex() const = 0;

            virtual bool needsSorting() const = 0;
            virtual std::vector<IMultPartEntity*> sortZIndex() = 0;
            virtual std::vector<IMultPartEntity*>& getSortedZParts() = 0;

            virtual void setTint(sf::Color tint) = 0;
            virtual sf::Color getTint() const = 0;

            virtual void setParent(IMultPartEntity* parent) = 0;
            virtual IMultPartEntity* getParent() const = 0;

            virtual bool isHovered() const = 0;

            virtual void flipX() = 0;
    };

}