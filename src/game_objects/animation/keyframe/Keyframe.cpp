/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-16 21:17:06
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-17 00:46:49
 * @ Description:
 */

#include "Keyframe.hpp"
#include "logger.hpp"

namespace bya::Animation {

    Keyframe::Keyframe(std::shared_ptr<gameObj::IMultPartEntity> entity) :
        m_entity(entity)
    {}

    Keyframe::Keyframe(std::shared_ptr<gameObj::IMultPartEntity> entity, sf::Vector2f position, sf::Vector2f size, sf::Vector2f pivot, float rotation, int zIndex) :
        m_entity(entity),
        m_position(position),
        m_size(size),
        m_pivot(pivot),
        m_rotation(rotation),
        m_zIndex(zIndex)
    {}

    void Keyframe::apply() const {
        //m_entity->setPosition(m_position);
        m_entity->setSize(m_size);
        m_entity->setPivotPoint(m_pivot);
        m_entity->setRotation(m_rotation);
        m_entity->setZIndex(m_zIndex);
    }

    Keyframe Keyframe::interpolate(const Keyframe& other, float time) const {
        Keyframe result = *this;

        // interpolate result with ease function
        result.m_position = m_position + (other.m_position - m_position) * m_easingFunction(time);
        result.m_size = m_size + (other.m_size - m_size) * m_easingFunction(time);
        result.m_pivot = m_pivot + (other.m_pivot - m_pivot) * m_easingFunction(time);
        result.m_rotation = m_rotation + (other.m_rotation - m_rotation) * m_easingFunction(time);
        result.m_zIndex = m_zIndex + (other.m_zIndex - m_zIndex) * m_easingFunction(time);
        return result;
    }

}