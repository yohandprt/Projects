/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** AGameModule.hpp
*/

#pragma once

#include "IGameModule.hpp"
#include "GameState.hpp"

namespace ARCADE {
    class AGameModule : public ARCADE::IGameModule
    {
    protected:
        bool _gameover;
    public:
        AGameModule();
        ~AGameModule() = default;

        void gameOver(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state);
        void removeGameOverScreen(ARCADE::GameState& state);
        bool isGameOver() const;
    };
    
}