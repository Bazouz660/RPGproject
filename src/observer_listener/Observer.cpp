/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-29 19:45:34
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-30 03:31:19
 * @ Description:
 */

#include "Observer.hpp"
#include "Subject.hpp"
#include "logger.hpp"

namespace bya {

    Observer::Observer(Subject &subject) : m_subject(subject)
    {
        m_subject.attach(this);
    }

    Observer::~Observer()
    {
    }

    void Observer::removeMeFromTheList()
    {
        m_subject.detach(this);
    }

    void Observer::onNotify()
    {
        m_onUpdate();
    }

}
