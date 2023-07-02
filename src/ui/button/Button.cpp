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
        : m_animation(texture.getSize().x / 3, texture.getSize().y)
    {
        setTexture(&texture);

        m_animation.addFrame(0, sf::seconds(0.5));
        m_animation.addFrame(1, sf::seconds(0.5));
        m_animation.addFrame(2, sf::seconds(0.5));
        setTextureRect(m_animation.getFrame(0));

        m_scaling.addState(1, 1);
        m_scaling.addState(1.03, 1.03);
        m_scaling.addState(0.97, 0.97);

        Box::setSize(sf::Vector2f(texture.getSize().x / 3, texture.getSize().y));
        setOrigin(getSize() * 0.5f);
        m_label.setString(label);
        m_label.setFont(getResource().getFont("gameFont"));
        m_label.setOrigin(m_label.getGlobalBounds().width / 2, m_label.getGlobalBounds().height / 2);
        m_label.setPosition(this->getPosition());
        m_label.setFillColor(sf::Color(80, 80, 80, 255));
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

    void Button::handleEvent(sf::Event event, const sf::RenderWindow &window)
    {
        if (isHovered()) {
            if (m_state == PRESSED && !isClicked()) {
                m_callback();
                m_state = IDLE;
            } else if (isClicked()) {
                m_state = PRESSED;
                setTextureRect(m_animation.getFrame(2));
                setScale(m_scaling.getState(2));
                m_label.setFillColor(sf::Color::White);
            }
            if (m_state == IDLE) {
                m_state = HOVERED;
                setTextureRect(m_animation.getFrame(1));
                setScale(m_scaling.getState(1));
                m_label.setFillColor(sf::Color::White);
            }
        } else if (m_state != IDLE) {
            m_state = IDLE;
            setTextureRect(m_animation.getFrame(0));
            setScale(m_scaling.getState(0));
            m_label.setFillColor(sf::Color(80, 80, 80, 255));
        }
    }

    void Button::setPosition(const sf::Vector2f &pos)
    {
        Box::setPosition(pos);
        m_label.setPosition(pos);
    }

    sf::FloatRect Button::getBounds() const
    {
        return Box::getGlobalBounds();
    }

    void Button::render(sf::RenderTarget &target)
    {
        if (m_drawBox)
            target.draw(*this);
        target.draw(m_label);
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
