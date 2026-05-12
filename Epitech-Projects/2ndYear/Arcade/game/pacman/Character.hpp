/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-arcade-16
** File description:
** Character.hpp
*/

#pragma once
#include "PacmanTypes.hpp"
#include "PacmanMap.hpp"

namespace ARCADE {
    class Character {
    public:
        Character() = default;
        explicit Character(Position spawn) : _pos(spawn) {}
        virtual ~Character() = default;
        virtual void move(int x, int y, const PacmanMap &map);
        virtual void update(const PacmanMap &) {}
        Position getPos() const
        {
            return _pos;
        }
        void setPos(Position newPos) 
        {
            _pos = newPos;
        }

    protected:
        Position _pos = {0, 0};
    };

}