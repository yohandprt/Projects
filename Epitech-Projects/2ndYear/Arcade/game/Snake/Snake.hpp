/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** snake.hpp
*/

#pragma once

#include "AGameModule.hpp"
#include "GameState.hpp"
#include <chrono>
#include <vector>
#include <deque>

namespace ARCADE {
    class Snake : public ARCADE::AGameModule
    {
        public:
            enum class faceDirection {
                NORTH,
                WEST,
                EAST,
                SOUTH
            };

            enum class element {
                VOID,
                WALL,
                TAIL,
                HEAD,
                APPLE,
            };

            Snake() = default;
            ~Snake() = default;
            void init(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state) override;
            void stop() override;
            void handleKeys(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state) override;
            void update(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state) override;

            bool isRunning() const override;
            std::size_t getScore() const override;

        private:
            void spawFruit(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state);
            void deleteSnake(ARCADE::GameState& state);

            std::chrono::time_point<std::chrono::high_resolution_clock> _lastUpdate;
            float _timer = 0.0f;
            float _delay = 0.3f;

            faceDirection _direction;
            faceDirection _nextDirection;

            std::vector<std::vector<element>> _grid;
            std::deque<std::pair<int, int>> _snake;
            std::size_t _lastRenderdSize = 0;

            int _fruitX;
            int _fruitY;

            int _tileSize = 40;

            bool _running = true;
            int tick;
            std::size_t _score;
    };
}