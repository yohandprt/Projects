/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-arcade-16
** File description:
** Leaderboard.hpp
*/

#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <filesystem>

#include "AGameModule.hpp"
#include "GameState.hpp"

namespace ARCADE {
    class Leaderboard
    {
    private:
        std::vector<std::pair<std::string, size_t>> _players;
        std::vector<std::string> _scoreFiles;
        float _width;
        float _height;
        float _leftX;
        float _rightX;
        float _leftPosY;
        float _rightPosY;
        float _leftNameY;
        float _rightNameY;
        std::string _gameScoreSuffix;
    public:
        Leaderboard() = default;
        ~Leaderboard() = default;

        void initCoords(std::unique_ptr<ARCADE::ADisplayModule>& display);

        void findScoreFiles();
        void loadPlayers();
        void display(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state);
        void displayLeft(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state, std::string strPlayer, float posY, std::size_t i);
        void displayRight(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state, std::string strPlayer, float posY, std::size_t i);
    };    
}