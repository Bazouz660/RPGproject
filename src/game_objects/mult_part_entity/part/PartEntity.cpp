/*
** EPITECH PROJECT, 2023
** RPGproject
** File description:
** PartEntity
*/

#include "PartEntity.hpp"

namespace bya::gameObj
{
    void PartEntity::update(float dt)
    {
        for (auto &part : getDirectChildren())
            part->update(dt);
    }
}