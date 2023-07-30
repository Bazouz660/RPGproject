/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-29 19:41:32
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-30 03:24:10
 * @ Description:
 */

#pragma once

#include "common.hpp"
#include <functional>

namespace bya {

    class Subject;

    class Observer {

        public:
            Observer(Subject &subject);
            ~Observer();

            void onNotify();
            void setOnUpdate(std::function<void(void)> onUpdate) { m_onUpdate = onUpdate; }

            void removeMeFromTheList();

        private:
            std::string m_msgFromSubject;
            Subject& m_subject;
            std::function<void(void)> m_onUpdate = [](){};
    };
}
