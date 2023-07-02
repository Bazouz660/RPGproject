/*
** EPITECH PROJECT, 2023
** RPGproject
** File description:
** HumanoidEntity
*/

#include "HumanoidEntity.hpp"
#include "PartEntity.hpp"
#include "EntityPartBuilder.hpp"

namespace bya::gameObj
{
    HumanoidEntity::HumanoidEntity()
    : AMultPartEntity("body")
    {
        EntityPartBuilder builder;

        // body
        setSize(35.f, 100.f);
        setPivotPoint(17.5f, 50.f);

        // limbs
        addPart("head", builder
            .setName("head")
            .setSize(45.f, 50.f)
            .setPivotPoint(22.5f, 50.f)
            .setPosition(0.f, -50.f)
            .build()
        );

        addPart("leftArm", builder
            .setName("leftArm")
            .setSize(20.f, 40.f)
            .setPivotPoint(10.f, 10.f)
            .setPosition(0.f, -40.f)
            .build()
        );

        m_parts["leftArm"]->addPart("leftForearm", builder
            .setName("leftForearm")
            .setSize(20.f, 40.f)
            .setPivotPoint(10.f, 0.f)
            .setPosition(0.f, -10.f)
            .build()
        );

        addPart("rightArm", builder
            .setName("rightArm")
            .setSize(20.f, 40.f)
            .setPivotPoint(10.f, 10.f)
            .setPosition(0.f, -40.f)
            .build()
        );

        m_parts["rightArm"]->addPart("rightForearm", builder
            .setName("rightForearm")
            .setSize(20.f, 40.f)
            .setPivotPoint(10.f, 0.f)
            .setPosition(0.f, -10.f)
            .build()
        );

        m_parts["leftArm"]->setRotation(-45.f);



        setPosition(300.f, 300.f);
    }

    void HumanoidEntity::update(float dt)
    {
        for (auto &[partName, part] : m_parts)
            part->update(dt);

        setRotation(m_rotation += dt * 10.f);
    }

}