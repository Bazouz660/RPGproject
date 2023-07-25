/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-26 00:24:28
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-26 00:44:40
 * @ Description:
 */

#pragma once

#include "common.hpp"
#include "Button.hpp"

namespace bya::ui {

    class DropDownButton : public Button {
        public:
            DropDownButton();
            virtual ~DropDownButton() = default;

            virtual void render(sf::RenderTarget& target) override;

            virtual void setSize(const sf::Vector2f& size) override;
            virtual void setCharacterSize(unsigned int size);

            void addOption(const std::string& option);
            void removeOption(const std::string& option);

            sf::FloatRect getBounds() const override;

        protected:
            virtual void hoverEventHandler(sf::Event& event) override;
            virtual void anyEventHandler(sf::Event& event) override;

        private:
            bool m_isOpen = false;
    };
}