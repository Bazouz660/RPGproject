/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-16 21:17:00
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-25 21:42:50
 * @ Description:
 */

#pragma once

#include "common.hpp"
#include "IMultPartEntity.hpp"
#include "utils.hpp"
#include "logger.hpp"

namespace bya::Animation {

    class Keyframe {
        public:
            Keyframe(std::shared_ptr<gameObj::IMultPartEntity> entity);
            Keyframe(std::shared_ptr<gameObj::IMultPartEntity> entity, sf::Vector2f position, sf::Vector2f size, sf::Vector2f pivot, float rotation, int zIndex);
            ~Keyframe() = default;

            Keyframe& setPosition(sf::Vector2f position) { m_position = position; return *this; }
            Keyframe& setSize(sf::Vector2f size) { m_size = size; return *this; }
            Keyframe& setPivot(sf::Vector2f pivot) { m_pivot = pivot; return *this; }
            Keyframe& setRotation(float rotation) { m_rotation = rotation; return *this; }
            Keyframe& setZIndex(int zIndex) { m_zIndex = zIndex; return *this; }
            Keyframe& setTime(float time) { m_time = time; return *this; }

            sf::Vector2f getPosition() const { return m_position; }
            sf::Vector2f getSize() const { return m_size; }
            sf::Vector2f getPivot() const { return m_pivot; }
            float getRotation() const { return m_rotation; }
            int getZIndex() const { return m_zIndex; }
            float getTime() const { return m_time; }

            std::shared_ptr<gameObj::IMultPartEntity> getEntity() const { return m_entity; }

            void apply() const;

            void setEasingFunction(std::function<float(float)> easingFunction) { m_easingFunction = easingFunction; }

            void setEasingFunction(std::string easingFunction) {
                if (easingFunctions.find(easingFunction) != easingFunctions.end()) {
                    m_easingFunction = easingFunctions.at(easingFunction);
                } else {
                    m_easingFunction = linear;
                    logger::warn("Easing function [" + easingFunction + "] not found, using linear instead");
                }
            }

            std::function<float(float)> getEasingFunction() const { return m_easingFunction; }

            std::string getEasingFunctionName() const {
                for (auto& [name, func] : easingFunctions) {
                    // compare the target function to the current function
                    if (utils::getAddress(func) == utils::getAddress(m_easingFunction))
                        return name;
                }
                return "linear";
            }

            Keyframe interpolate(const Keyframe& other, float time) const;

            // map of easing functions to their names
            static std::map<std::string, std::function<float(float)>> easingFunctions;

        private:
            std::shared_ptr<gameObj::IMultPartEntity> m_entity;
            sf::Vector2f m_position;
            sf::Vector2f m_size;
            sf::Vector2f m_pivot;
            float m_rotation;
            int m_zIndex;

            float m_time = 0;

            static float linear(float x) { return x; }
            static float easeInQuad(float x) { return x * x; }
            static float easeOutQuad(float x) { return x * (2 - x); }
            static float easeInOutQuad(float x) { return x < 0.5 ? 2 * x * x : -1 + (4 - 2 * x) * x; }
            static float easeInCubic(float x) { return x * x * x; }
            static float easeOutCubic(float x) { return 1 - pow(1 - x, 3); }
            static float easeInOutCubic(float x) { return x < 0.5 ? 4 * x * x * x : (x - 1) * (2 * x - 2) * (2 * x - 2) + 1; }
            static float easeInQuart(float x) { return x * x * x * x; }
            static float easeOutQuart(float x) { return 1 - pow(1 - x, 4); }
            static float easeInOutQuart(float x) { return x < 0.5 ? 8 * x * x * x * x : 1 - pow(1 - x, 4); }
            static float easeInQuint(float x) { return x * x * x * x * x; }
            static float easeOutQuint(float x) { return 1 - pow(1 - x, 5); }
            static float easeInOutQuint(float x) { return x < 0.5 ? 16 * x * x * x * x * x : 1 - pow(1 - x, 5); }

            std::function<float(float)> m_easingFunction = easeInOutQuad;
    };
}
