/*
 *  Author: Clément Thomas
 *  Create Time: 2023-07-09 00:11:08
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-09 00:57:27
 *  Description:
 */

#pragma once

#include "IFading.hpp"

namespace bya::Animation
{
    class FadeIn : public IFading {
        public:
            FadeIn();
            ~FadeIn() override;
            void update() override;
            void reset() override;
            void setDuration(float) override;
            float getAlpha() const override;
            bool isDone() const override;

        private:
            float m_time;
            float m_duration;
            float m_alpha;
    };
}
