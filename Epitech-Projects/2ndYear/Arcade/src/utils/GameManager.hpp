/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-arcade-16
** File description:
** GameManager.hpp
*/

#pragma once

#include <dlfcn.h>
#include <iostream>
#include <algorithm>
#include <vector>

#include "IDisplayModule.hpp"
#include "ADisplayModule.hpp"
#include "IGameModule.hpp"
#include "AGameModule.hpp"

#include "DLHandler.hpp"
#include "GameState.hpp"

namespace ARCADE {
    class GameManager
    {
    private:
        ARCADE::DLHandler _dlHandler;
        ARCADE::GameState _state;
        std::vector<std::string> _vectorEnvp;
        std::string _firstGraphicLib;
        std::string _firstGameLib;
        std::string _playerName;
    public:
        GameManager();
        ~GameManager() = default;

        int runMenu(std::string firstGraphicLib, bool enterName);
        int runGame();

        void initVectorEnvp(char *envp[]);
        bool canLaunchGraphic();

        ARCADE::DLHandler& getDLHandler();
        ARCADE::GameState& getGameState();
        
        std::string getName() const;
    };
}