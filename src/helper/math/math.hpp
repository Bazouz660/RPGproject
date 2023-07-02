/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** math
*/

#pragma once

#include "common.hpp"

namespace bya {
    namespace math {
        #define PI 3.14159265358979323
        #define RD 0.01745329251994329

        float dist(sf::Vector2f p1, sf::Vector2f p2);
        float distSquared(sf::Vector2f p1, sf::Vector2f p2);
        sf::FloatRect multRect(sf::FloatRect rect, sf::Vector2f n);
        sf::Vector2f normalize(sf::Vector2f v);
        float dot(sf::Vector2f v1, sf::Vector2f v2);
        float cross(sf::Vector2f v1, sf::Vector2f v2);
        float angle(sf::Vector2f v1, sf::Vector2f v2);
        float length(sf::Vector2f v);
        sf::Vector2f unit(sf::Vector2f v);
        sf::Vector2f lerp(sf::Vector2f v1, sf::Vector2f v2, float t);
        float lerp(float v1, float v2, float t);
        float toDeg(float rad);
        float toRad(float deg);

        float flip(float x);
        float dumbPow(float x, uint32_t p);
        float smoothStop(float t, uint32_t power);

        template <typename T>
        sf::Vector2<T> rotate(sf::Vector2<T> v, float angle)
        {
            float rad = angle * RD;
            float cs = cos(rad);
            float sn = sin(rad);
            return sf::Vector2<T>(v.x * cs - v.y * sn, v.x * sn + v.y * cs);
        }
    }
}
