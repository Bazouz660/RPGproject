/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** Clock
*/

#ifndef CLOCK_HPP_
    #define CLOCK_HPP_

    #include "common.hpp"

    #define getTime() bya::Clock::getInstance().getElapsedTime()
    #define getClock() bya::Clock::getInstance()

    namespace bya {
        class Clock : public sf::Clock {
            public:
                static Clock& getInstance();
                int getFps() const;
                void setTickRate(unsigned int rate);
                float getTickRate() const;
                float getFrameDt() const;
                void update();
            private:
                float m_tickRate;
                float m_frameDt;
        };
    }

#endif /* !CLOCK_HPP_ */
