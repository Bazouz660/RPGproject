/*
** EPITECH PROJECT, 2023
** RPGproject
** File description:
** HumanoidEntity
*/

#include "HumanoidEntity.hpp"
#include "PartEntity.hpp"
#include "EntityPartBuilder.hpp"
#include "info.hpp"
#include "math.hpp"

namespace bya::gameObj
{
    HumanoidEntity::HumanoidEntity()
    : AMultPartEntity("torso")
    {
        EntityPartBuilder builder;

        // torso
        setSize(45.f, 50.f);
        setPivotPoint(22.5f, 20.f);
        setPosition(0.f, -30.f);
        setTint(sf::Color::Blue);

        addPart("abdomen", builder
            .setName("abdomen")
            .setSize(40.f, 50.f)
            .setPivotPoint(20.f, 0.f)
            .setPosition(0.f, 0.f)
            .setParent(this)
            .build()
        );

        setFixedRotation(-3.f);
        getPart("abdomen")->setFixedRotation(8.f);

        // limbs
        addPart("head", builder
            .setName("head")
            .setSize(45.f, 50.f)
            .setPivotPoint(22.5f, 50.f)
            .setPosition(2.f, -60.f)
            .setZIndex(1)
            .setParent(this)
            .build()
        );

        // right arm
        addPart("rightArm", builder
            .setName("righttArm")
            .setSize(20.f, 50.f)
            .setPivotPoint(10.f, 10.f)
            .setPosition(-15.f, -40.f)
            .setZIndex(2)
            .setParent(this)
            .build()
        );
        getPart("rightArm")->addPart("rightForearm", builder
            .setName("rightForearm")
            .setSize(20.f, 50.f)
            .setPivotPoint(10.f, 0.f)
            .setPosition(-15.f, 0.f)
            .setZIndex(1)
            .setParent(getPart("rightArm").get())
            .build()
        );

        getPart("rightArm")->setFixedRotation(-20.f);
        getPart("rightArm")->getPart("rightForearm")->setFixedRotation(-40.f);


        // left arm
        addPart("leftArm", builder
            .setName("lefttArm")
            .setSize(20.f, 50.f)
            .setPivotPoint(10.f, 10.f)
            .setPosition(15.f, -40.f)
            .setZIndex(-2)
            .setParent(this)
            .build()
        );
        getPart("leftArm")->addPart("leftForearm", builder
            .setName("leftForearm")
            .setSize(20.f, 50.f)
            .setPivotPoint(10.f, 0.f)
            .setPosition(15.f, 0.f)
            .setZIndex(-1)
            .setParent(getPart("leftArm").get())
            .build()
        );

        getPart("leftArm")->setFixedRotation(-20.f);
        getPart("leftArm")->getPart("leftForearm")->setFixedRotation(-40.f);


        // right leg
        addPart("rightThigh", builder
            .setName("rightThigh")
            .setSize(22.f, 50.f)
            .setPivotPoint(11.f, 0.f)
            .setPosition(-15.f, 40.f)
            .setZIndex(2)
            .setParent(this)
            .build()
        );
        getPart("rightThigh")->addPart("rightTibia", builder
            .setName("rightTibia")
            .setSize(20.f, 55.f)
            .setPivotPoint(10.f, 0.f)
            .setPosition(-15.f, 90.f)
            .setZIndex(1)
            .setParent(getPart("rightThigh").get())
            .build()
        );

        getPart("rightThigh")->setFixedRotation(0.f);
        getPart("rightThigh")->getPart("rightTibia")->setFixedRotation(10.f);

        // left leg
        addPart("leftThigh", builder
            .setName("leftThigh")
            .setSize(22.f, 50.f)
            .setPivotPoint(11.f, 0.f)
            .setPosition(15.f, 40.f)
            .setZIndex(-2)
            .setParent(this)
            .build()
        );
        getPart("leftThigh")->addPart("leftTibia", builder
            .setName("leftTibia")
            .setSize(20.f, 55.f)
            .setPivotPoint(10.f, 0.f)
            .setPosition(15.f, 90.f)
            .setZIndex(-1)
            .setParent(getPart("leftThigh").get())
            .build()
        );

        getPart("leftThigh")->setFixedRotation(-5.f);
        getPart("leftThigh")->getPart("leftTibia")->setFixedRotation(10.f);



        setPosition(300.f, 300.f);
        sortZIndex();
    }

    void HumanoidEntity::update(float dt)
    {
        for (auto &[partName, part] : m_parts)
            part->update(dt);

        PartEntity *head = dynamic_cast<PartEntity *>(getPart("head").get());

        // get angle between head and mouse
        sf::Vector2f mousePos = info::getMousePosition();
        sf::Vector2f headPos = head->getPosition();

        float angle = math::toDeg(math::angle(headPos, mousePos));

        if (angle > 20.f || angle < -20.f)
            angle = (angle > 0) ? 20.f : -20.f;

        head->setRotation(angle);
    }

}