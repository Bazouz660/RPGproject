/*
 *  Author: Clément Thomas
 *  Create Time: 2023-07-09 00:22:56
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-09 01:15:52
 *  Description:
 */

#include "FadeIn.hpp"
#include "Clock.hpp"

namespace bya::Animation
{
    FadeIn::FadeIn()
    {
        m_time = 0.f;
        m_duration = 1.f;
        m_alpha = 0.f;
    }

    FadeIn::~FadeIn()
    {
    }

    void FadeIn::update()
    {
        m_time += getClock().getFrameDt();
        m_alpha = m_time / m_duration;
        if (m_alpha > 1)
            m_alpha = 1;
    }

    void FadeIn::reset()
    {
        m_time = 0.f;
        m_alpha = 0.f;
    }

    void FadeIn::setDuration(float duration)
    {
        m_duration = duration;
    }

    float FadeIn::getAlpha() const
    {
        return m_alpha;
    }

    bool FadeIn::isDone() const
    {
        if (m_alpha == 1.f)
            return true;
        return false;
    }
}
