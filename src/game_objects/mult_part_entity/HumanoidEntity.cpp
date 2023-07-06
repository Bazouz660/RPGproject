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
#include "clock.hpp"

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
            .setPosition(0.f, 0.f)
            .setSize(40.f, 50.f)
            .setPivotPoint(20.f, 0.f)
            .setParent(this)
            .build()
        );

        setFixedRotation(-3.f);
        getPart("abdomen")->setFixedRotation(8.f);

        // limbs
        addPart("head", builder
            .setName("head")
            .setPosition(2.f, -60.f)
            .setSize(45.f, 50.f)
            .setPivotPoint(22.5f, 50.f)
            .setZIndex(1)
            .setParent(this)
            .build()
        );

        // right arm
        addPart("rightArm", builder
            .setName("righttArm")
            .setPosition(-15.f, -40.f)
            .setSize(20.f, 50.f)
            .setPivotPoint(10.f, 10.f)
            .setZIndex(2)
            .setTint(sf::Color(255, 255, 0, 255))
            .setParent(this)
            .build()
        );
        getPart("rightArm")->addPart("rightForearm", builder
            .setName("rightForearm")
            .setPosition(-15.f, 0.f)
            .setSize(20.f, 50.f)
            .setPivotPoint(10.f, 0.f)
            .setTint(sf::Color(255, 255, 0, 255))
            .setZIndex(1)
            .setParent(getPart("rightArm").get())
            .build()
        );

        getPart("rightArm")->setFixedRotation(-10.f);
        getPart("rightForearm")->setFixedRotation(-40.f);


        // left arm
        addPart("leftArm", builder
            .setName("lefttArm")
            .setPosition(15.f, -40.f)
            .setSize(20.f, 50.f)
            .setPivotPoint(10.f, 10.f)
            .setZIndex(-2)
            .setParent(this)
            .build()
        );
        getPart("leftArm")->addPart("leftForearm", builder
            .setName("leftForearm")
            .setPosition(15.f, 0.f)
            .setSize(20.f, 50.f)
            .setPivotPoint(10.f, 0.f)
            .setZIndex(-1)
            .setParent(getPart("leftArm").get())
            .build()
        );

        getPart("leftArm")->setFixedRotation(-20.f);
        getPart("leftForearm")->setFixedRotation(-40.f);


        // right leg
        addPart("rightThigh", builder
            .setName("rightThigh")
            .setSize(22.f, 50.f)
            .setPivotPoint(11.f, 0.f)
            .setPosition(-15.f, 40.f)
            .setTint(sf::Color(255, 255, 0, 255))
            .setZIndex(2)
            .setParent(this)
            .build()
        );
        getPart("rightThigh")->addPart("rightTibia", builder
            .setName("rightTibia")
            .setSize(20.f, 55.f)
            .setPivotPoint(10.f, 0.f)
            .setPosition(-15.f, 90.f)
            .setTint(sf::Color(255, 255, 0, 255))
            .setZIndex(1)
            .setParent(getPart("rightThigh").get())
            .build()
        );

        getPart("rightThigh")->setFixedRotation(0.f);
        getPart("rightTibia")->setFixedRotation(10.f);

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
        getPart("leftTibia")->setFixedRotation(10.f);


        m_partMapping = {
            {"leftArm", "rightArm"},
            {"leftThigh", "rightThigh"},
        };

        setPosition(300.f, 300.f);
        sortZIndex();
    }

    void HumanoidEntity::flipX()
    {
        AMultPartEntity::flipX();

        return;

        // to do: find a way to do this automatically
        sf::Vector2f leftArmPos = m_parts["leftArm"]->getPosition();
        sf::Vector2f rightArmPos = m_parts["rightArm"]->getPosition();
        sf::Vector2f leftThighPos = m_parts["leftThigh"]->getPosition();
        sf::Vector2f rightThighPos = m_parts["rightThigh"]->getPosition();
        m_parts["leftArm"]->setPosition(rightArmPos);
        m_parts["rightArm"]->setPosition(leftArmPos);
        m_parts["leftThigh"]->setPosition(rightThighPos);
        m_parts["rightThigh"]->setPosition(leftThighPos);
    }

    void HumanoidEntity::update(float dt)
    {
        for (auto &[partName, part] : m_parts)
            part->update(dt);

        PartEntity *head = dynamic_cast<PartEntity *>(getPart("head").get());
        PartEntity *leftArm = dynamic_cast<PartEntity *>(getPart("leftArm").get());

        // get angle between head and mouse
        sf::Vector2f mousePos = info::getMousePosition();
        sf::Vector2f headPos = head->getPosition();

        float angle = math::toDeg(math::angle(headPos, mousePos));
        float maxAngle = 20.f;

        if (mousePos.x < headPos.x && head->getScale().x > 0.f)
            flipX();
        else if (mousePos.x > headPos.x && head->getScale().x < 0.f)
            flipX();

        if (head->getScale().x < 0.f) {
            angle = 180.f - angle;
            maxAngle = -maxAngle;
            if (angle > 180.f)
                angle -= 360.f;
            else if (angle < -180.f)
                angle += 360.f;
            angle = std::clamp(angle, maxAngle, -maxAngle);
        } else {
            angle = std::clamp(angle, -maxAngle, maxAngle);
        }

        head->setRotation(angle);

        sf::Vector2f leftArmPos = leftArm->getPosition();
        angle = math::toDeg(math::angle(leftArmPos, mousePos));

        leftArm->setRotation(angle);
    }

}