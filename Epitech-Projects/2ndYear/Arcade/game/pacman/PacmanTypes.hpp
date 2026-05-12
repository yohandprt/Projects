/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** PacmanTypes.hpp
*/

#pragma once

namespace ARCADE {
    enum class TileType {
        Empty,
        Wall,
        Dot,
        PowerDot,
        PlayerSpawn,
        GhostSpawn,
    };

    struct Position {
        int x = 0;
        int y = 0;
        
        bool operator==(const Position& other) const {
            return x == other.x && y == other.y;
        }
        bool operator!=(const Position& other) const {
            return x != other.x || y != other.y;
        }
    };
}
