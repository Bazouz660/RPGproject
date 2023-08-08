/*
** EPITECH PROJECT, 2023
** RPG3
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-17 23:58:03
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
                enum State { IDLE, HOVERED, PRESSED, DISABLED };
                Button(const sf::Texture& texture = RESOURCE().getTexture("default", "button"), const std::string& label = "");
                virtual ~Button() override = default;

                virtual void setCallback(std::function<void(void)> func);
                virtual void setLabel(const std::string& label);
                virtual sf::Text& getLabel() { return m_label; }
                virtual void drawBox(bool draw);
                virtual bool isBoxDrawn() const;
                virtual void setSize(const sf::Vector2f& size);

                virtual void setIdle();
                virtual void setHovered();
                virtual void setPressed();
                virtual void setDisabled();

                virtual State getState() const { return m_state; }

                virtual void activate();

                virtual void setPosition(const sf::Vector2f& pos) override;
                virtual sf::FloatRect getBounds() const override;

                virtual void render(sf::RenderTarget& target) override;

            protected:
                virtual void hoverEventHandler(sf::Event& event) override;
                virtual void anyEventHandler(sf::Event& event) override;
                virtual void updateHandler(float dt) override;
                virtual void onClick();

            protected:
                sf::Text m_label;
                bool m_drawBox = true;
                bool m_catchedMouseEvent = false;
                Animation::Scaling m_scaling;
                State m_state = IDLE;
                std::function<void(void)> m_callback = []() {};
        };
    }

#endif /* !BUTTON_HPP_ */
