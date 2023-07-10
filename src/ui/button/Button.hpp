/*
** EPITECH PROJECT, 2023
** RPG3
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-10 02:28:03
*/

#ifndef BUTTON_HPP_
    #define BUTTON_HPP_

    #include "AUIelement.hpp"
    #include "Spritesheet.hpp"
    #include "ResourceManager.hpp"
    #include "Scaling.hpp"
    #include "Box.hpp"
    #include <functional>

    namespace bya::ui {
        class Button : public AUIelement, public gameObj::Box {
            public:
                enum State { IDLE, HOVERED, PRESSED };
                Button(const sf::Texture& texture = getResource().getTexture("defaultButton"), const std::string& label = "");

                virtual void setCallback(std::function<void(void)> func);
                virtual void setLabel(const std::string& label);
                virtual sf::Text& getLabel() { return m_label; }
                virtual void drawBox(bool draw);
                virtual bool isBoxDrawn() const;
                virtual void setSize(const sf::Vector2f& size);

                virtual void setIdle();
                virtual void setHovered();
                virtual void setPressed();

                virtual State getState() const { return m_state; }

                virtual void activate();

                virtual void handleEvent(sf::Event event, const sf::RenderWindow& window) override;

                virtual void setPosition(const sf::Vector2f& pos) override;
                virtual sf::FloatRect getBounds() const override;

                virtual void render(sf::RenderTarget& target) override;

            protected:
                sf::Text m_label;
                bool m_drawBox = true;
                Animation::Scaling m_scaling;
                State m_state = IDLE;
                std::function<void(void)> m_callback = []() {};
        };
    }

#endif /* !BUTTON_HPP_ */
