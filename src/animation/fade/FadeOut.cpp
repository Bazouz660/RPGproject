/*
 *  Author: Clément Thomas
 *  Create Time: 2023-07-09 00:22:56
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-09 01:20:33
 *  Description:
 */

#include "FadeOut.hpp"
#include "Clock.hpp"

namespace bya::Animation
{
    FadeOut::FadeOut()
    {
        m_time = 0.f;
        m_duration = 1.f;
        m_alpha = 1.f;
    }

    FadeOut::~FadeOut()
    {
    }

    void FadeOut::update()
    {
        m_time += getClock().getFrameDt();
        m_alpha = m_time / m_duration;
        if (m_alpha < 0)
            m_alpha = 0;
    }

    void FadeOut::reset()
    {
        m_time = 0.f;
        m_alpha = 1.f;
    }

    void FadeOut::setDuration(float duration)
    {
        m_duration = duration;
    }

    float FadeOut::getAlpha() const
    {
        return m_alpha;
    }

    bool FadeOut::isDone() const
    {
        if (m_alpha == 0.f)
            return true;
        return false;
    }
}
