/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-03 18:50:24
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-06 21:36:49
 *  Description:
 */

#pragma once

#include "common.hpp"

namespace bya::effects {

    class IParticleEmitter {

        public:
            virtual ~IParticleEmitter() = default;

            virtual void toggle(bool state) = 0;
            virtual void update(float dt) = 0;
            virtual void draw(sf::RenderTarget &target) = 0;

            virtual void setPos(const sf::Vector2f &pos) = 0;
            virtual void setPos(float x, float y) = 0;

            virtual void setAngle(float angle) = 0;
            virtual float getAngle() const = 0;

            virtual void setEmissionRate(float rate) = 0;

            virtual void setPartLifeTime(float time) = 0;

            virtual void setPartSize(const sf::Vector2f &size) = 0;
            virtual void setPartSize(float x, float y) = 0;

            virtual void setPartSpeed(float speed) = 0;

            virtual sf::Vector2f getPos() const = 0;
            virtual float getEmissionRate() const = 0;
            virtual float getPartLifeTime() const = 0;
            virtual sf::Vector2f getPartSize() const = 0;
            virtual float getPartSpeed() const = 0;
            virtual bool isEmmiting() const = 0;
    };

}