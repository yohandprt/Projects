/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-arcade-16
** File description:
** Menu.hpp
*/

#pragma once

#include "AGameModule.hpp"
#include "GameState.hpp"
#include "DLHandler.hpp"
#include "Leaderboard.hpp"

namespace ARCADE {

    class Menu : public ARCADE::AGameModule
    {
    private:
        ARCADE::DLHandler _dlHandler;
        ARCADE::Leaderboard _leaderboard;
        bool _running = true;
        bool _runGame = false;
        bool _setName = false;
        bool _enterName = false;
        std::string _selectedGraphicLib;
        std::string _selectedGameLib;
        std::size_t _index;
        std::string _keyOver;
        std::string _name;
        std::size_t _fontSize;
        std::size_t _borderSize;
    public:
        Menu() = default;
        ~Menu() = default;

        void init(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state) override;
        void stop() override;
        void handleKeys(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state) override;
        void update(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state) override;

        bool isRunning() const override;
        std::size_t getScore() const override;
        bool runGame() const;
        bool setName() const;
        std::string getName() const;

        void setEnterName(bool enterName);
        void handleWriting(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state);

        std::string getSelectedGraphicLib() const;
        std::string getSelectedGameLib() const;

        void handleNavigateIndex(std::unique_ptr<ARCADE::ADisplayModule>& display);
        void createBox(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state, std::string boxName, std::string text, float posY);
        void handleBoxEvent(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state, std::string boxName);
    };
}