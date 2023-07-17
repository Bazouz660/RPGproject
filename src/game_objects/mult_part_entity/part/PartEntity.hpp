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
            virtual ~PartEntity() override = default;

            void update(float dt) override;
    };
}