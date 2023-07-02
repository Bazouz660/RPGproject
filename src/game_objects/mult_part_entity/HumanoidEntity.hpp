/*
** EPITECH PROJECT, 2023
** RPGproject
** File description:
** HumanoidEntity
*/

#pragma once

#include "AMultPartEntity.hpp"

namespace bya::gameObj
{
    class HumanoidEntity : public AMultPartEntity
    {
        public:
            HumanoidEntity();
            ~HumanoidEntity() = default;

            void update(float dt) override;
    };
}