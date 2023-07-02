/*
** EPITECH PROJECT, 2023
** RPGproject
** File description:
** PartEntity
*/

#include "PartEntity.hpp"

namespace bya::gameObj
{
    PartEntity::PartEntity(const std::string &name)
    : AMultPartEntity(name)
    {
    }

    void PartEntity::update(float dt)
    {
        for (auto &[partName, part] : m_parts)
            part->update(dt);
    }
}