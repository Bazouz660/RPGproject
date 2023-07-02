/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** Clock
*/

#include "Clock.hpp"

namespace bya {

Clock& Clock::getInstance()
{
    static Clock instance;
    return instance;
}

void Clock::setTickRate(unsigned int rate)
{
    m_tickRate = 1.0f / float(rate);
}

void Clock::update()
{
    sf::Time currentTime = getElapsedTime();
    static sf::Time previousTime = currentTime;

    m_frameDt = currentTime.asSeconds() - previousTime.asSeconds();
    previousTime = currentTime;
}

float Clock::getTickRate() const
{
    return m_tickRate;
}

float Clock::getFrameDt() const
{
    return m_frameDt;
}

int Clock::getFps() const
{
    return (1.0 / m_frameDt);
}

}
