/*
 *  Author: Clément Thomas
 *  Create Time: 2023-07-10 02:18:20
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-10 02:38:34
 *  Description:
 */

#include "Button.hpp"

namespace bya::ui
{
    class MenuButton : public Button
    {
        public:
            MenuButton();
            virtual ~MenuButton() override = default;
            void setIdle() override;
            void setHovered() override;
            void setPressed() override;
            void setLabel(const std::string&) override;
    };
}