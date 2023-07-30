/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-29 19:46:08
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-30 02:06:45
 * @ Description:
 */

#pragma once

#include "common.hpp"
#include <list>

namespace bya
{
    class Observer;

    class Subject {
        public:
            Subject() = default;
            ~Subject() = default;

            void attach(Observer *Observer);
            void detach(Observer *Observer);
            void notify();
            void howManyAObserver();

        private:
            std::list<Observer *> m_listAObserver;
            std::string m_message;
    };
}