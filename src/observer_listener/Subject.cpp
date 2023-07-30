/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-29 19:53:00
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-30 03:32:23
 * @ Description:
 */

#include "Subject.hpp"
#include "Observer.hpp"
#include "logger.hpp"

namespace bya {

    void Subject::attach(Observer *Observer)
    {
        m_listAObserver.push_back(Observer);
    }

    void Subject::detach(Observer *Observer)
    {
        m_listAObserver.remove(Observer);
    }

    void Subject::notify()
    {
        auto iterator = m_listAObserver.begin();
        while (iterator != m_listAObserver.end()) {
            (*iterator)->onNotify();
            ++iterator;
        }
    }

    void Subject::howManyAObserver()
    {
        logger::debug("There are " + std::to_string(m_listAObserver.size()) + " AObservers in the list.");
    }
}
