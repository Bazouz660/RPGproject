/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-03 18:50:24
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-06 21:37:03
 *  Description:
 */

#include "Scaling.hpp"

namespace bya::Animation {

        Scaling::Scaling()
        {
            m_currentStateIndex = 0;
        }

        void Scaling::addState(const sf::Vector2f &scale)
        {
            m_states.push_back(scale);
        }

        void Scaling::addState(float x, float y)
        {
            m_states.push_back(sf::Vector2f(x, y));
        }

        void Scaling::nextState()
        {
            m_currentStateIndex++;
            if (m_currentStateIndex >= m_states.size())
                m_currentStateIndex = 0;
        }

        void Scaling::setState(int state)
        {
            m_currentStateIndex = state;
        }

        sf::Vector2f Scaling::getCurrentState() const
        {
            return m_states[m_currentStateIndex];
        }

        int Scaling::getCurrentStateIndex() const
        {
            return m_currentStateIndex;
        }

        int Scaling::getNbStates() const
        {
            return m_states.size();
        }

        sf::Vector2f Scaling::getState(int state)
        {
            return m_states[state];
        }
}