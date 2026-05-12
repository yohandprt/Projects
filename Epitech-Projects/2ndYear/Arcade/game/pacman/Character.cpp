/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-arcade-16
** File description:
** Character.cpp
*/

#include "Character.hpp"

void ARCADE::Character::move(int x, int y, const PacmanMap &map)
{
    int nextPosX = _pos.x + x;
    int nextPosY = _pos.y + y;

    if (map.isInside(nextPosX, nextPosY) && !map.isWall(nextPosX, nextPosY)) {
        _pos.x = nextPosX;
        _pos.y = nextPosY;
    }
}