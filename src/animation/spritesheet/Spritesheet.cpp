/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** Spritesheet
*/

#include "Spritesheet.hpp"
#include "Clock.hpp"

namespace bya::Animation
{

    Spritesheet::Spritesheet(unsigned frameWidth, unsigned frameHeight)
        : FRAME_WIDTH(frameWidth), FRAME_HEIGHT(frameHeight)
    {
    }

    void Spritesheet::addFrame(unsigned int index, sf::Time delay)
    {
        sf::IntRect bounds;
        bounds.top = 0;
        bounds.height = FRAME_HEIGHT;
        bounds.width = FRAME_WIDTH;
        bounds.left = index * FRAME_WIDTH;

        m_frames.emplace_back(bounds, delay);
    }

    void Spritesheet::pause()
    {
        m_paused = true;
    }

    bool Spritesheet::isPlaying() const
    {
        return m_paused;
    }

    void Spritesheet::play()
    {
        m_paused = false;
    }

    const sf::IntRect &Spritesheet::getFrame()
    {
        if (isPlaying()) {
            m_overlappedTime += getTime();
            while (m_overlappedTime >= m_frames[m_framePointer].delay) {
                m_overlappedTime -= m_frames[m_framePointer].delay;
                m_framePointer++;
            }
        }
        return m_frames[m_framePointer % m_frames.size()].bounds;
    }

    const sf::IntRect &Spritesheet::getFrame(unsigned int index) const
    {
        return m_frames[index].bounds;
    }

}
