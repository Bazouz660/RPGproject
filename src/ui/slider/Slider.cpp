/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** Slider
*/

#include "Slider.hpp"
#include "ResourceManager.hpp"
#include "context.hpp"
#include "math.hpp"

namespace bya::ui
{

    Slider::Slider(sf::Vector2f railSize, sf::Vector2f wagonSize, Orientation orientation)
        : m_orientation(orientation)
    {
        m_scaling.addState(1, 1);
        m_scaling.addState(1.05, 1.05);
        m_scaling.addState(0.95, 0.95);

        m_wagon.setSize(wagonSize);
        m_wagon.setColor(sf::Color::White);
        m_wagon.setOrigin(m_wagon.getSize() * 0.5f);

        m_outerRail.setSize(railSize);
        m_outerRail.setFillColor(sf::Color::Cyan);
        m_outerRail.setOutlineColor(sf::Color::Black);
        m_outerRail.setOutlineThickness(1);
        m_outerRail.setOrigin(m_outerRail.getSize() * 0.5f);
        m_wagon.setPosition(m_outerRail.getPosition());

        if (m_orientation == VERTICAL) {
            m_wagon.setRotation(90);
            m_outerRail.setRotation(90);
        }

        m_internRail = m_outerRail;
        m_internRail.setFillColor(sf::Color::Transparent);
        m_internRail.setOutlineColor(sf::Color::Red);
        m_internRail.setOutlineThickness(1);
        m_internRail.setSize(railSize);
        m_internRail.setOrigin(m_internRail.getSize() * 0.5f);

        m_size = m_outerRail.getSize();

        lockWagonPositon();
    }

    float Slider::getProgress() const
    {
        return std::round(m_progress * 100) / 100;
    }

    void Slider::anyEventHandler(sf::Event& event)
    {
        sf::Vector2f mousePos = context::getMousePosition();

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            m_state = IDLE;
        }

        if (event.type == sf::Event::MouseMoved && m_state == GRABBED) {
            m_wagon.setPosition(mousePos + m_diffToOrigin);
            lockWagonPositon();
            if (m_orientation == HORIZONTAL) {
                m_progress = (m_wagon.getPosition().x - m_internRail.getGlobalBounds().left) / m_internRail.getSize().x;
            } else if (m_orientation == VERTICAL) {
                m_progress = (m_wagon.getPosition().y - m_internRail.getGlobalBounds().top) / m_internRail.getSize().y;
            }
        }
    }

    void Slider::hoverEventHandler(sf::Event& event)
    {
        sf::Vector2f mousePos = context::getMousePosition();

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (m_wagon.contains(mousePos)) {
                m_diffToOrigin =  m_wagon.getPosition() - mousePos;
                m_state = GRABBED;
            }
        }
    }

    void Slider::setProgress(float progress)
    {
        m_progress = progress;
        sf::FloatRect railBound = m_internRail.getGlobalBounds();
        sf::Vector2f wagonPos = m_wagon.getPosition();

        if (m_orientation == HORIZONTAL) {
            wagonPos.x = railBound.left + (railBound.width * progress);
            m_wagon.setPosition(wagonPos);
        } else if (m_orientation == VERTICAL) {
            wagonPos.y = railBound.top + (railBound.height * progress);
            m_wagon.setPosition(wagonPos);
        }

        lockWagonPositon();
    }

    void Slider::lockWagonPositon()
    {
        sf::Vector2f wagonPos = m_wagon.getPosition();
        sf::FloatRect railBound = m_internRail.getGlobalBounds();
        float middleX = railBound.left + (railBound.width * 0.5f);
        float middleY = railBound.top + (railBound.height * 0.5f);

        if (m_orientation == HORIZONTAL) {
            if (wagonPos.x < railBound.left)
                m_wagon.setPosition({railBound.left, m_wagon.getPosition().y});
            if (wagonPos.x > railBound.left + railBound.width)
                m_wagon.setPosition({railBound.left + railBound.width, m_wagon.getPosition().y});
                m_wagon.setPosition({m_wagon.getPosition().x, middleY});
        } else if (m_orientation == VERTICAL) {
            if (wagonPos.y < railBound.top)
                m_wagon.setPosition({m_wagon.getPosition().x, railBound.top});
            if (wagonPos.y > railBound.top + railBound.height)
                m_wagon.setPosition({m_wagon.getPosition().x, railBound.top + railBound.height});
            m_wagon.setPosition({middleX, m_wagon.getPosition().y});
        }
    }

    void Slider::setPosition(const sf::Vector2f &pos)
    {
        m_outerRail.setPosition(pos);
        m_internRail.setPosition(pos);

        if (m_orientation == HORIZONTAL)
            m_wagon.setPosition({m_internRail.getGlobalBounds().left + (m_internRail.getGlobalBounds().width * m_progress), pos.y});
        else if (m_orientation == VERTICAL)
            m_wagon.setPosition({pos.x, m_internRail.getGlobalBounds().top + (m_internRail.getGlobalBounds().height * m_progress)});

        lockWagonPositon();
    }

    sf::FloatRect Slider::getBounds() const
    {
        return math::combineRects(m_outerRail.getGlobalBounds(), m_internRail.getGlobalBounds());
    }

    void Slider::render(sf::RenderTarget &target)
    {
        if (m_drawOuterRail)
            target.draw(m_outerRail);
        m_wagon.render(target);
        if (m_drawInternRail)
            target.draw(m_internRail);
    }

    void Slider::setSize(const sf::Vector2f &size)
    {
        m_outerRail.setSize(size);
        m_outerRail.setOrigin(size * 0.5f);

        if (m_orientation == VERTICAL) {
            m_wagon.setRotation(90);
            m_outerRail.setRotation(90);
        }

        m_internRail = m_outerRail;
        m_internRail.setFillColor(sf::Color::Transparent);
        m_internRail.setOutlineColor(sf::Color::Red);
        m_internRail.setOutlineThickness(1);
        m_internRail.setSize(size);
        m_internRail.setOrigin(size * 0.5f);

        m_size = m_outerRail.getSize();

        setProgress(m_progress);
    }

}