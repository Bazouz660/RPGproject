/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-25 21:23:53
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-25 21:25:50
 * @ Description:
 */

#include "common.hpp"
#include <functional>

#pragma once

namespace bya::utils {

    template<typename T, typename... U>
    static size_t getAddress(std::function<T(U...)> f) {
        typedef T(fnType)(U...);
        fnType ** fnPointer = f.template target<fnType*>();
        return (size_t) *fnPointer;
    }

}