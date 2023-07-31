/*
 *  Author: Basile Trebus--Hamann
 *  Create Time: 2023-07-03 18:50:24
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-07 02:59:18
 *  Description:
 */

#ifndef COMMON_HPP_
    #define COMMON_HPP_

    #define WINDOW_SIZE sf::Vector2u(1920, 1080)

    #define uptr std::unique_ptr
    #define GRAVITY 9.81f

    #include <stdint.h>
    #include <string>
    #include <iostream>
    #include <memory>
    #include <cmath>
    #include <unordered_map>
    #include <chrono>
    #include <ctime>
    #include <cassert>

    #include <SFML/Graphics.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/System.hpp>
    #include <SFML/Audio.hpp>
    #include <SFML/Config.hpp>

    #include "Exception.hpp"

#endif /* !COMMON_HPP_ */
