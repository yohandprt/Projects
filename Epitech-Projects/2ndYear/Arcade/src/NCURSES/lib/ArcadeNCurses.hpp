/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** ArcadeNCurses.hpp
*/

#pragma once

#include <ncurses.h>
#include <iostream>
#include <map>

#include "ADisplayModule.hpp"

#include "NCursesRectangle.hpp"
#include "NCursesCircle.hpp"
#include "NCursesSprite.hpp"

namespace ARCADE {

    static std::map<std::string, int> ncursesKeys = {
        {"z", 'z'},
        {"q", 'q'},
        {"s", 's'},
        {"d", 'd'},
        {"m", 'm'},
        {"r", 'r'},
        {"up", KEY_UP},
        {"down", KEY_DOWN},
        {"left", KEY_LEFT},
        {"right", KEY_RIGHT},
        {"space", ' '},
        {"tab", '\t'},
        {"enter", '\n'},
        {"esc", 27}
    };

    static std::map<ARCADE::Color, std::size_t> ncursesColors = {
        {ARCADE::Color::Black, 1},
        {ARCADE::Color::White, 2},
        {ARCADE::Color::Red, 3},
        {ARCADE::Color::Green, 4},
        {ARCADE::Color::Blue, 5},
        {ARCADE::Color::Yellow, 6},
    };

    class NCURSES : public ARCADE::ADisplayModule
    {
    private:
        bool _isOpen;
        int _ch;
        int _maxX;
        int _maxY;
    public:
        NCURSES();
        ~NCURSES() = default;
        void init() override;
        void stop() override;
        bool isOpen() override;
        bool pollEvent() override;
        void close() override;
        void clear() override;
        void display() override;

        std::size_t getWindowSizeX() const override;
        std::size_t getWindowSizeY() const override;
        bool isKeyPressed(std::string key) override;
        std::string getKeyPressed() override;
        std::unique_ptr<ARCADE::IRectangle> createRectangle() override;
        std::unique_ptr<ARCADE::ICircle> createCircle() override;
        std::unique_ptr<ARCADE::IRectangle> createSprite() override;
    };
}