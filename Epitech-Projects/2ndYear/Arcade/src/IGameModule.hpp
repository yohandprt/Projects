/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** IGameModule.hpp
*/

#pragma once

#include <memory>

#include "IModule.hpp"
#include "ADisplayModule.hpp"

namespace ARCADE {
    class GameState;
    class IGameModule : public ARCADE::IModule
    {
    public:
        virtual ~IGameModule() = default;

        virtual void init(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state) = 0;
        virtual void stop() = 0;
        virtual void handleKeys(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state) = 0;
        virtual void update(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state) = 0;

        virtual bool isRunning() const = 0;
        virtual std::size_t getScore() const = 0;
    };
}