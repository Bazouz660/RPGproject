/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** Scaling
*/

#pragma once

#include "common.hpp"

namespace bya {

    namespace Animation {

        class Scaling {
            public:
                Scaling();
                ~Scaling() = default;

                void addState(const sf::Vector2f &scale);
                void addState(float x, float y);

                void nextState();
                void setState(int state);
                sf::Vector2f getState(int state);

                sf::Vector2f getCurrentState() const;
                int getCurrentStateIndex() const;
                int getNbStates() const;
            private:
                std::vector<sf::Vector2f> m_states;
                int m_currentStateIndex;
        };

    }

}