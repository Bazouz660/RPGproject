/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-16 21:26:00
 * @ Modified by: Basile Trebus--Hamann
 * @ Modified time: 2023-07-31 03:27:27
 * @ Description:
 */

#pragma once

#include "common.hpp"
#include "IMultPartEntity.hpp"
#include "Keyframe.hpp"

namespace bya::Animation {

    class MultiPartAnimation {
        public:
            MultiPartAnimation() = default;
            MultiPartAnimation(std::shared_ptr<gameObj::IMultPartEntity> entity) : m_entity(entity) {}
            ~MultiPartAnimation() = default;

            enum State { PLAYING, PAUSED };

            void addKeyframe(std::shared_ptr<Keyframe> keyframe);
            void removeKeyframe(std::shared_ptr<gameObj::IMultPartEntity> entity, float time);

            void setEntity(std::shared_ptr<gameObj::IMultPartEntity> entity) { m_entity = entity; }
            const std::map<std::shared_ptr<gameObj::IMultPartEntity>, std::vector<std::shared_ptr<Keyframe>>>& getKeyframesMap() const { return m_keyframesMap; }

            std::shared_ptr<Keyframe> getKeyframe(std::shared_ptr<gameObj::IMultPartEntity> entity, unsigned int index);
            std::shared_ptr<Keyframe> getKeyframe(std::shared_ptr<gameObj::IMultPartEntity> entity, float time);

            void sortKeyframes();

            void play();
            void pause();
            void restart() { m_timer = 0; }

            void setTimer(float timer) { m_timer = timer; }

            void update(float dt);
            void update();

            void setLoop(bool loop) { m_loop = loop; }
            bool getLoop() const { return m_loop; }

            void clear();

            State getState() const { return m_state; }

            MultiPartAnimation blend(MultiPartAnimation& other, float blendFactor);

            void saveToJson(std::string path);
            void loadFromJson(std::string path);

        private:
            std::shared_ptr<gameObj::IMultPartEntity> m_entity;
            std::map<std::shared_ptr<gameObj::IMultPartEntity>, std::vector<std::shared_ptr<Keyframe>>> m_keyframesMap;

            float m_timer = 0;
            bool m_loop = true;
            State m_state = PAUSED;
    };

}