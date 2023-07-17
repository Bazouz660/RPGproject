/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-03 18:50:24
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-06 21:37:12
 *  Description:
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