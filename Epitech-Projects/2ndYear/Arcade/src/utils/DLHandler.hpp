/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-arcade-16
** File description:
** DLHandler.hpp
*/

#pragma once

#include "DLLoader.hpp"
#include "ADisplayModule.hpp"
#include "AGameModule.hpp"

#include <vector>
#include <filesystem>

namespace ARCADE {
    class DLHandler
    {
    private:
        ARCADE::DLLoader _loader;
        std::vector<std::string> _graphicLibs;
        std::vector<std::string> _gameLibs;
        std::size_t _indexGraphic;
        std::size_t _indexGame;
        bool _firstLoadGraphic;
        bool _firstLoadGame;
        std::string _currentGraphicLib;
        std::string _currentGameLib;
    public:
        DLHandler();
        DLHandler(std::string libDirPath);
        ~DLHandler() = default;

        bool isGraphicLib(std::string libPath);
        bool isGameLib(std::string libPath);
        std::unique_ptr<ARCADE::ADisplayModule> loadGraphic(std::string libPath);
        std::unique_ptr<ARCADE::AGameModule> loadGame(std::string libPath);

        void findLibs(std::string libDirPath);
        std::vector<std::string> getGraphicLibs();
        std::vector<std::string> getGameLibs();

        std::string nextGraphicLib();
        std::string nextGameLib();

        std::string currentGraphicLib();
        std::string currentGameLib();

        void initFirstLibs(std::string firstGraphicLib, std::string firstGameLib);
    };
}