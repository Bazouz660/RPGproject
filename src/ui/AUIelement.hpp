/*
 * @ Author: Basile Trebus--Hamann
 * @ Create Time: 2023-07-08 17:23:16
 *  Modified by: Basile Trebus--Hamann
 *  Modified time: 2023-07-12 04:25:54
 * @ Description:
 */

#pragma once

#include "IUIelement.hpp"

namespace bya::ui {

    class AUIelement : public IUIelement {
        public:
            virtual ~AUIelement() = default;

            virtual void update(float dt) override {};

        protected:
            AUIelement() = default;
    };

}
