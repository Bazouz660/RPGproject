/*
** EPITECH PROJECT, 2023
** RPGproject
** File description:
** HumanoidEntity
*/

#pragma once

#include "PartEntity.hpp"

namespace bya::gameObj
{
    class HumanoidEntity : public PartEntity
    {
        public:
            HumanoidEntity();
            virtual ~HumanoidEntity() override = default;

            void update(float dt) override;
    };
}