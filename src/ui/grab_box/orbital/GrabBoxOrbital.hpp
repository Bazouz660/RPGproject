/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-11 02:18:19
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-12 03:04:48
 *  Description:
 */

#pragma once

#include "GrabBox.hpp"

namespace bya::ui {

    class GrabBoxOrbital : public GrabBox {
        public:
            GrabBoxOrbital() = default;
            ~GrabBoxOrbital() = default;

            virtual void setPosition(const sf::Vector2f &pos) override { OrientedBoundingBox::setPosition(pos); }
            virtual sf::FloatRect getBounds() const override { return OrientedBoundingBox::getBounds(); }

            virtual void setGrabbed(bool grabbed) { m_grabbed = grabbed; }
            virtual bool isGrabbed() const { return m_grabbed; }

            virtual void setCenter(const sf::Vector2f &center) { m_center = center; }
            virtual sf::Vector2f getCenter() const { return m_center; }

            virtual void setRadius(float radius) { m_radius = radius; }
            virtual float getRadius() const { return m_radius; }

            virtual void setAngle(float angle) { m_angle = angle; }
            virtual float getAngle() const { return m_angle; }

            virtual void applyTransform(float angle);

        protected:
            virtual void anyEventHandler(sf::Event &event) override;
            virtual void hoverEventHandler(sf::Event &event) override;

        private:
            sf::Vector2f m_center = {0, 0};
            float m_radius = 50;
            float m_angle = 0;
    };

}