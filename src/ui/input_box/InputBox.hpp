/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-07 15:11:27
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-07 15:32:08
 *  Description:
 */

#include "Button.hpp"

namespace bya::ui {
    class InputBox : public IUIelement, public gameObj::Box {
        public:
            enum State { IDLE, HOVERED, PRESSED };
            InputBox(const sf::Texture& texture = getResource().getTexture("defaultButton"), const std::string& label = "");

            void setCallback(std::function<void(void)> func);
            void setLabel(const std::string& label);

            virtual void handleEvent(sf::Event event, const sf::RenderWindow& window) override;

            virtual void setPosition(const sf::Vector2f& pos) override;
            virtual sf::FloatRect getBounds() const override;

            virtual void render(sf::RenderTarget& target) override;

        protected:
            sf::Text m_label;
            std::shared_ptr<Button> m_applyButton;
            std::shared_ptr<Button> m_cancelButton;
            sf::RectangleShape m_background;
            sf::RectangleShape m_inputBox;
            std::string m_input = "";

            Animation::Scaling m_scaling;
            State m_state = IDLE;
            std::function<void(void)> m_callback = []() {};
    };
}
