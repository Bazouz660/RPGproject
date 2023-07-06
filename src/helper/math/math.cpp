/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** math
*/

#include "math.hpp"

namespace bya {
    namespace math {

        float toDeg(float rad)
        {
            float deg = rad * 180 / PI;
            // keep it between 180 and -180
            if (deg < -180)
                deg += 360;
            if (deg > 180)
                deg -= 360;
            return deg;
        }

        float toRad(float deg)
        {
            float rad = deg * PI / 180;
            // keep it between PI and -PI
            if (rad < -PI)
                rad += 2 * PI;
            if (rad > PI)
                rad -= 2 * PI;
            return rad;
        }

        float invertAngle(float deg)
        {
            deg = 180.f - deg;
            if (deg > 180.f)
                deg -= 360.f;
            else if (deg < -180.f)
                deg += 360.f;
            return deg;
        }

        float dist(sf::Vector2f p1, sf::Vector2f p2)
        {
            float distance = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
            return (distance);
        }

        float distSquared(sf::Vector2f p1, sf::Vector2f p2)
        {
            float distance = (pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
            return (distance);
        }

        sf::FloatRect multRect(sf::FloatRect rect, sf::Vector2f n)
        {
            float centerX = rect.left + (rect.width * 0.5f);
            float centerY = rect.top + (rect.height * 0.5f);
            rect.width *= n.x;
            rect.height *= n.y;
            rect.left = centerX - (rect.width * 0.5f);
            rect.top = centerY - (rect.height * 0.5f);
            return rect;
        }

        sf::Vector2f normalize(sf::Vector2f v)
        {
            float length = sqrt(v.x * v.x + v.y * v.y);
            if (length != 0)
                return sf::Vector2f(v.x / length, v.y / length);
            return v;
        }

        float dot(sf::Vector2f v1, sf::Vector2f v2)
        {
            return v1.x * v2.x + v1.y * v2.y;
        }

        float cross(sf::Vector2f v1, sf::Vector2f v2)
        {
            return v1.x * v2.y - v1.y * v2.x;
        }

        float angle(sf::Vector2f v1, sf::Vector2f v2, float offset)
        {
            float offsetRad = toRad(offset);
            double dx = v2.x - v1.x;
            double dy = v2.y - v1.y;
            double angle = atan2(dy, dx);
            angle += offsetRad;

            if (angle < -PI)
                angle += 2 * PI;
            if (angle > PI)
                angle -= 2 * PI;
            return angle;
        }

        float length(sf::Vector2f v)
        {
            return sqrt(v.x * v.x + v.y * v.y);
        }

        sf::Vector2f unit(sf::Vector2f v)
        {
            float l = length(v);
            if (l != 0)
                return sf::Vector2f(v.x / l, v.y / l);
            return v;
        }

        sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b, float t)
        {
            sf::Vector2f res;

            res.x = lerp(a.x, b.x, t);
            res.y = lerp(a.y, b.y, t);
            return res;
        }

        float lerp(float v1, float v2, float t)
        {
            return (1-t) * v1 + t * v2;
        }

        float flip(float x)
        {
            return 1 - x;
        }

        float dumbPow(float x, uint32_t p)
        {
            float res = 1.0f;
            for (uint32_t i(p); i--;) {
                res *= x;
            }
            return res;
        }

        float smoothStop(float t, uint32_t power)
        {
            return flip(dumbPow(flip(t), power));
        }
    }
}