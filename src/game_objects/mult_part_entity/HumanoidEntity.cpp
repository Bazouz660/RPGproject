/*
** EPITECH PROJECT, 2023
** RPGproject
** File description:
** HumanoidEntity
*/

#include "HumanoidEntity.hpp"
#include "EntityPartBuilder.hpp"
#include "info.hpp"
#include "math.hpp"
#include "Clock.hpp"

namespace bya::gameObj
{
    HumanoidEntity::HumanoidEntity()
    : PartEntity("torso")
    {
        loadFromJson("humanoid.json");

        getPart("head")->setTexture(getResource().getTexture("human_head1"));

        setPosition(300.f, 300.f);

        return;
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
            maxAngle = -maxAngle;
            angle = math::invertAngle(angle);
            angle = std::clamp(angle, maxAngle, -maxAngle);
        } else {
            angle = std::clamp(angle, -maxAngle, maxAngle);
        }

        head->setRotation(angle);

        sf::Vector2f leftArmPos = leftArm->getPosition();
        angle = math::toDeg(math::angle(leftArmPos, mousePos));
        maxAngle = 45.f;
        float angleOffset = 90.f;

        if (leftArm->getScale().x < 0.f) {
            maxAngle = -maxAngle;
            angle = math::invertAngle(angle);
            angle = std::clamp(angle, maxAngle, -maxAngle);
            angle -= angleOffset;
        } else {
            angle = std::clamp(angle, -maxAngle, maxAngle);
            angle -= angleOffset;
        }
        leftArm->setRotation(angle);
    }

}