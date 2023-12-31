/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-26 00:24:28
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-28 02:40:30
 * @ Description:
 */

#pragma once

#include "common.hpp"
#include "Button.hpp"
#include "Slider.hpp"
#include "Subject.hpp"

namespace bya::ui {

    class DropDownButton : public Button, public Subject {
        public:
            DropDownButton();
            virtual ~DropDownButton() = default;

            virtual void render(sf::RenderTarget& target) override;

            virtual void setSize(const sf::Vector2f& size) override;
            virtual void setCharacterSize(unsigned int size);
            virtual void setPosition(const sf::Vector2f& pos) override;

            void addOption(const std::string& option);
            void removeOption(const std::string& option);

            const sf::Text& getLabel() const { return m_label; }

            std::string getSelectedOption() const { return getLabel().getString(); }

            void setMaxDisplayedOptions(unsigned int max) { m_maxDisplayedOptions = max; }

            sf::FloatRect getBounds() const override;

        protected:
            virtual void setCallback(const std::function<void()>& callback) { Button::setCallback(callback); };

        private:
            bool m_isOpen = false;

            std::shared_ptr<Slider> m_slider = nullptr;
            std::vector<std::shared_ptr<Button>> m_options;

            unsigned int m_maxDisplayedOptions = 5;
    };
}