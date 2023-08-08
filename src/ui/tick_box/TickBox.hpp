/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-08-08 17:41:00
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-08-08 18:11:23
 * @ Description:
 */

#pragma once

#include "ButtonNBG.hpp"

namespace bya::ui
{
    class TickBox : public ButtonNBG
    {
        public:
            TickBox();
            virtual ~TickBox() override = default;

            virtual void render(sf::RenderTarget &target) override;
            virtual sf::FloatRect getBounds() const override;

            virtual void onClick() override;

            void setChecked(bool checked);
            bool isChecked() const { return m_checked; }

        private:
            bool m_checked;
            sf::RectangleShape m_tick;
            const sf::Color m_checkedColor = sf::Color(0, 255, 0, 255);
            const sf::Color m_uncheckedColor = sf::Color(255, 255, 255, 255);
    };
}