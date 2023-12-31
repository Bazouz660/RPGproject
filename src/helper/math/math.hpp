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

        static const sf::FloatRect NULL_RECT = sf::FloatRect(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), 0, 0);

        extern float dist(sf::Vector2f p1, sf::Vector2f p2);
        extern float distSquared(sf::Vector2f p1, sf::Vector2f p2);
        extern sf::FloatRect multRect(sf::FloatRect rect, sf::Vector2f n);
        extern sf::Vector2f normalize(sf::Vector2f v);
        extern float dot(sf::Vector2f v1, sf::Vector2f v2);
        extern float cross(sf::Vector2f v1, sf::Vector2f v2);
        extern float angle(sf::Vector2f v1, sf::Vector2f v2);
        extern float length(sf::Vector2f v);
        extern sf::Vector2f unit(sf::Vector2f v);
        extern sf::Vector2f lerp(sf::Vector2f v1, sf::Vector2f v2, float t);
        extern float lerp(float v1, float v2, float t);
        extern float toDeg(float rad);
        extern float toRad(float deg);
        extern float invertAngle(float deg);

        extern float flip(float x);
        extern float dumbPow(float x, uint32_t p);
        extern float smoothStop(float t, uint32_t power);

        extern sf::FloatRect combineRects(const sf::FloatRect& r1, const sf::FloatRect& r2);

        // Function to compute the greatest common divisor (GCD) using Euclidean algorithm
        static int gcd(int a, int b) {
            while (b != 0) {
                int temp = b;
                b = a % b;
                a = temp;
            }
            return a;
        }

        // Function to calculate the aspect ratio in X:Y format
        static sf::Vector2i aspectRatio(int width, int height) {
            // Ensure width and height are positive integers
            if (width <= 0 || height <= 0) {
                throw std::invalid_argument("Width and height must be greater than 0");
            }

            // Calculate the greatest common divisor (GCD) to simplify the ratio
            int divisor = gcd(width, height);

            // Calculate the simplified width and height
            int simplifiedWidth = width / divisor;
            int simplifiedHeight = height / divisor;

            // Return the aspect ratio as a string in the format X:Y
            return sf::Vector2i(simplifiedWidth, simplifiedHeight);
        }

        template <typename T>
        sf::Vector2<T> rotate(sf::Vector2<T> v, float angle)
        {
            float rad = angle * RD;
            float cs = cos(rad);
            float sn = sin(rad);
            return sf::Vector2<T>(v.x * cs - v.y * sn, v.x * sn + v.y * cs);
        }

        template <typename T>
        int sgn(T val) {
            return (T(0) < val) - (val < T(0));
        }
    }
}
