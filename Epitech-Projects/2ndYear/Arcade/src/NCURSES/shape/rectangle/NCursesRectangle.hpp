/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** NCursesRectangle.hpp
*/

#pragma once

#include "ARectangle.hpp"
#include "ArcadeNCurses.hpp"

#include <ncurses.h>
#include <iostream>
#include <vector>
#include <cstring>

namespace ARCADE {
    class NCursesRectangle : public ARectangle
    {
    private:
        std::vector<std::string> _content {};
        MEVENT mouseEvent;
        std::string _text;
        ARCADE::Color _textColor;
    public:
        NCursesRectangle();
        ~NCursesRectangle() = default;

        std::string getText() const override;
        ARCADE::Color getTextColor() const override;
        void setText(std::string text, std::size_t charactereSize, ARCADE::Color color) override;

        bool isMouseHover() override;
        bool isClick() override;

        void draw() override;
    };
    
}