/*
** EPITECH PROJECT, 2023
** BurunyaEngine
** File description:
** AABBcontinuous
*/

#include "AABBcontinuous.hpp"
#include "math.hpp"

namespace bya::physics {

    void AABBcontinuous::solveSystem(std::vector<gameObj::IObject *> &boxes, float dt)
    {
        m_dt = dt;
        bruteForceSolving(boxes);
    }

    float AABBcontinuous::sweptAABB(gameObj::AABBcollider &b1, gameObj::AABBcollider &b2, sf::Vector2f &normal)
    {
        float xInvEntry, yInvEntry;
        float xInvExit, yInvExit;

        // find the distance between the objects on the near and far sides for both x and y
        if (b1.getVel().x > 0.0f)
        {
            xInvEntry = b2.getPosition().x - (b1.getPosition().x + b1.getGlobalBounds().width);
            xInvExit = (b2.getPosition().x + b2.getGlobalBounds().width) - b1.getPosition().x;
        }
        else
        {
            xInvEntry = (b2.getPosition().x + b2.getGlobalBounds().width) - b1.getPosition().x;
            xInvExit = b2.getPosition().x - (b1.getPosition().x + b1.getGlobalBounds().width);
        }

        // find the distance between the objects on the near and far sides for both x and y (y is inverted)
        if (b1.getVel().y > 0.0f)
        {
            yInvEntry = b2.getPosition().y - (b1.getPosition().y + b1.getGlobalBounds().height);
            yInvExit = (b2.getPosition().y + b2.getGlobalBounds().height) - b1.getPosition().y;
        }
        else
        {
            yInvEntry = (b2.getPosition().y + b2.getGlobalBounds().height) - b1.getPosition().y;
            yInvExit = b2.getPosition().y - (b1.getPosition().y + b1.getGlobalBounds().height);
        }

        // find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
        float xEntry, yEntry;
        float xExit, yExit;

        if (b1.getVel().x == 0.0f)
        {
            xEntry = -std::numeric_limits<float>::infinity();
            xExit = std::numeric_limits<float>::infinity();
        }
        else
        {
            xEntry = xInvEntry / b1.getVel().x;
            xExit = xInvExit / b1.getVel().x;
        }

        if (b1.getVel().y == 0.0f)
        {
            yEntry = -std::numeric_limits<float>::infinity();
            yExit = std::numeric_limits<float>::infinity();
        }
        else
        {
            yEntry = yInvEntry / b1.getVel().y;
            yExit = yInvExit / b1.getVel().y;
        }

        // find the earliest/latest times of collision
        float entryTime = std::max(xEntry, yEntry);
        float exitTime = std::min(xExit, yExit);

        // if there was no collision
        if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
        {
            normal.x = 0.f;
            normal.y = 1.f;
            return 1.0f;
        }
        else
        {
            // calculate normal of collided surface
            if (xEntry > yEntry)
            {
                if (xInvEntry < 0.0f)
                {
                    normal.x = 1.0f;
                    normal.y = 0.0f;
                }
                else
                {
                    normal.x = -1.0f;
                    normal.y = 0.0f;
                }
            }
            else
            {
                if (yInvEntry < 0.0f)
                {
                    normal.x = 0.0f;
                    normal.y = 1.0f;
                }
                else
                {
                    normal.x = 0.0f;
                    normal.y = -1.0f;
                }
            } // return the time of collisionreturn entryTime;
        }
        return entryTime;
    }

    void AABBcontinuous::solveIntersection(gameObj::AABBcollider &box1, gameObj::AABBcollider &box2)
    {
        sf::FloatRect intersection;
        if (!(box1.getBounds().intersects(box2.getBounds(), intersection)))
            return;

        box1.setPosition(box1.getPosition() + sf::Vector2f(intersection.width, intersection.height));
    }

    void AABBcontinuous::solveCollision(gameObj::AABBcollider &box1, gameObj::AABBcollider &box2)
    {
        sf::Vector2f normal;
        float timeStep = 0.016f;

        if (box1.isStatic())
            return;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            box1.getAcc().y -= 1000 * timeStep;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            box1.getAcc().y += 1000 * timeStep;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            box1.getAcc().x -= 1000 * timeStep;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            box1.getAcc().x += 1000 * timeStep;
        }


        float collisiontime = sweptAABB(box1, box2, normal);

        float remainingTime = 1.0f - collisiontime;

        bool shouldApplyGravity = true;

        // update box position using the velocity and the collision time (velocity is computed from acceleration), and the remaining time (we use it to make the box slide)
        m_timer += m_dt;
        if (m_timer > timeStep) {
            m_timer = 0;
            box1.fixedUpdate(m_dt, timeStep);
        }

    }

    void AABBcontinuous::bruteForceSolving(std::vector<gameObj::IObject *> &boxes)
    {
        for (auto &box1 : boxes) {
            for (auto &box2 : boxes) {
                if (box1 == box2)
                    continue;
                //if (box1->getBounds().intersects(box2->getBounds())) {
                    solveCollision(*static_cast<gameObj::AABBcollider *>(box1),
                        *static_cast<gameObj::AABBcollider *>(box2));
                //}
            }
        }
    }

    sf::FloatRect AABBcontinuous::getBroadphaseBox(gameObj::AABBcollider &box)
    {
        sf::FloatRect broadphasebox;
        broadphasebox.left = box.getTopLeft().x + box.getVel().x;
        broadphasebox.top = box.getTopLeft().y + box.getVel().y;
        broadphasebox.width = box.getGlobalBounds().width + std::abs(box.getVel().x);
        broadphasebox.height = box.getGlobalBounds().height + std::abs(box.getVel().y);
        return broadphasebox;
    }
}