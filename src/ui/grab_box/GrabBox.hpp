/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-10 23:00:40
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-12 03:36:11
 *  Description:
 */

#pragma once

#include "AUIelement.hpp"
#include "OrientedBoundingBox.hpp"
#include "context.hpp"

namespace bya::ui {

    class GrabBox : public AUIelement, public gameObj::OrientedBoundingBox {
        public:
            GrabBox() = default;
            ~GrabBox() = default;

            virtual void render(sf::RenderTarget &target) override;
            virtual void setPosition(const sf::Vector2f &pos) override { OrientedBoundingBox::setPosition(pos); }
            virtual sf::FloatRect getBounds() const override { return OrientedBoundingBox::getBounds(); }

            virtual void setGrabbed(bool grabbed) { m_grabbed = grabbed; }
            virtual bool isGrabbed() const { return m_grabbed; }

        protected:
            virtual void anyEventHandler(sf::Event &event) override;
            virtual void hoverEventHandler(sf::Event &event) override;

        protected:
            bool m_grabbed = false;
            sf::Vector2f m_diffToOrigin = {0, 0};
    };

}