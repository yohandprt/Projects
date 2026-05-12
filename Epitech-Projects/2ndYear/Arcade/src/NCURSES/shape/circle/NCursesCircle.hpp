/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** NCursesCircle.hpp
*/

#pragma once

#include "ACircle.hpp"
#include "ArcadeNCurses.hpp"

#include <ncurses.h>
#include <iostream>
#include <vector>

namespace ARCADE {
    class NCursesCircle : public ACircle
    {
    private:
        std::vector<std::string> _content {};
        float _ndiameter;
        float _cutDiameter;
        float _radius;
        float _nx;
        float _ny;
        bool _pair;
        std::size_t _offset;
        void initParams();
        void setLines();
    public:
        NCursesCircle() = default;
        ~NCursesCircle() = default;
        
        void draw() override;
    };
}