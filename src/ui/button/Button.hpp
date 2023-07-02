/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** Button
*/

#ifndef BUTTON_HPP_
    #define BUTTON_HPP_

    #include "IUIelement.hpp"
    #include "Spritesheet.hpp"
    #include "ResourceManager.hpp"
    #include "Scaling.hpp"
    #include "Box.hpp"
    #include <functional>

    namespace bya::ui {
        class Button : public IUIelement, public gameObj::Box {
            public:
                enum State { IDLE, HOVERED, PRESSED };
                Button(const sf::Texture& texture = getResource().getTexture("defaultButton"), const std::string& label = "");

                void setCallback(std::function<void(void)> func);
                void setLabel(const std::string& label);
                void drawBox(bool draw);
                bool isBoxDrawn() const;

                virtual void handleEvent(sf::Event event, const sf::RenderWindow& window) override;

                virtual void setPosition(const sf::Vector2f& pos) override;
                virtual sf::FloatRect getBounds() const override;

                virtual void render(sf::RenderTarget& target) override;

            protected:
                sf::Text m_label;
                bool m_drawBox = true;
                Animation::Spritesheet m_animation;
                Animation::Scaling m_scaling;
                State m_state = IDLE;
                std::function<void(void)> m_callback = []() {};
        };
    }

#endif /* !BUTTON_HPP_ */
