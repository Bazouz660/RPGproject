/*
** EPITECH PROJECT, 2023
** RPGproject
** File description:
** PartEntity
*/

#pragma once

#include "AMultPartEntity.hpp"

namespace bya::gameObj
{
    class PartEntity : public AMultPartEntity
    {
        public:
            PartEntity() = default;
            ~PartEntity() = default;

            void update(float dt) override;
    };
}