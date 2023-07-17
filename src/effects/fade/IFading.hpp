/*
 *  Author: Clément Thomas
 *  Create Time: 2023-07-09 00:38:58
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-09 01:23:13
 *  Description:
 */

#pragma once

#include "common.hpp"

namespace bya::Animation
{
    class IFading {
        public:
            virtual ~IFading() = default;
            virtual void update() = 0;
            virtual void reset() = 0;
            virtual void setDuration(float) = 0;
            virtual float getAlpha() const = 0;
            virtual bool isDone() const = 0;
    };
}

