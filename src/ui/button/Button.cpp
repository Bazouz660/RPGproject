/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** Button
*/

#include "Button.hpp"
#include "ResourceManager.hpp"

namespace bya::ui
{
    Button::Button(const sf::Texture &texture, const std::string &label)
    {
        setTexture(&texture);

        m_scaling.addState(1, 1);
        m_scaling.addState(1.03, 1.03);
        m_scaling.addState(0.97, 0.97);

        Box::setSize(sf::Vector2f(texture.getSize().x, texture.getSize().y));
        setOrigin(getSize() * 0.5f);
        m_label.setString(label);
        m_label.setFont(getResource().getFont("gameFont"));
        m_label.setOrigin(m_label.getGlobalBounds().width / 2, m_label.getGlobalBounds().height / 2);
        m_label.setPosition(this->getPosition());
        m_label.setFillColor(sf::Color(30, 30, 30, 255));

        setIdle();
    }

    void Button::setLabel(const std::string &label)
    {
        m_label.setString(label);
        m_label.setOrigin(m_label.getGlobalBounds().width / 2, m_label.getGlobalBounds().height / 2);
    }

    void Button::setCallback(std::function<void(void)> func)
    {
        m_callback = func;
    }

    void Button::setIdle()
    {
        m_state = IDLE;
        setScale(m_scaling.getState(0));
        setFillColor(sf::Color(85, 85, 85, 255));
        m_label.setFillColor(sf::Color(85, 85, 85, 255));
    }

    void Button::setHovered()
    {
        m_state = HOVERED;
        setScale(m_scaling.getState(1));
        setFillColor(sf::Color(170, 170, 170, 255));
        m_label.setFillColor(sf::Color::White);
    }

    void Button::activate()
    {
        m_callback();
    }

    void Button::setPressed()
    {
        m_state = PRESSED;
        setScale(m_scaling.getState(2));
        setFillColor(sf::Color::White);
        m_label.setFillColor(sf::Color::White);
    }

    void Button::handleEvent(sf::Event event, const sf::RenderWindow &window)
    {
        if (isHovered()) {
            if (m_state == PRESSED && !isClicked()) {
                m_callback();
                setIdle();
            } else if (isClicked())
                setPressed();
            if (m_state == IDLE)
                setHovered();
        } else if (m_state != IDLE) {
            setIdle();
        }
    }

    void Button::setPosition(const sf::Vector2f &pos)
    {
        Box::setPosition(pos);

        sf::FloatRect bounds = Box::getGlobalBounds();
        sf::Vector2f labelPos(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);

        m_label.setPosition(labelPos);
    }

    sf::FloatRect Button::getBounds() const
    {
        return Box::getGlobalBounds();
    }

    void Button::setSize(const sf::Vector2f &size)
    {
        Box::setSize(size);
        setOrigin(size * 0.5f);
    }

    void Button::render(sf::RenderTarget &target)
    {
        if (m_drawBox)
            target.draw(*this);
        target.draw(m_label);

        // draw label bounds
        // sf::RectangleShape bounds;
        // bounds.setSize(sf::Vector2f(m_label.getGlobalBounds().width, m_label.getGlobalBounds().height));
        // bounds.setOrigin(bounds.getSize() * 0.5f);
        // bounds.setPosition(m_label.getPosition());
        // bounds.setFillColor(sf::Color::Transparent);
        // bounds.setOutlineColor(sf::Color::Red);
        // bounds.setOutlineThickness(1);
        // target.draw(bounds);
    }

    void Button::drawBox(bool draw)
    {
        m_drawBox = draw;
    }

    bool Button::isBoxDrawn() const
    {
        return m_drawBox;
    }

}
