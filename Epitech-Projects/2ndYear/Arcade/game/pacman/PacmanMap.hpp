/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** PacmanMap.hpp
*/

#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "PacmanTypes.hpp"

namespace ARCADE {
    class PacmanMap
    {
    public:
        PacmanMap() = default;
        ~PacmanMap() = default;

        TileType eatTile(int x, int y);
        void loadFromFile(const std::string &path);
        void loadFromData(const std::string &mapData);
        std::size_t getWidth() const;
        std::size_t getHeight() const;
        TileType getTile(int x, int y) const;
        bool isWall(int x, int y) const;
        bool isInside(int x, int y) const;
        Position getPlayerSpawn() const;
        std::vector<Position> getGhostSpawns() const;
        int getTotalDots() const;
        const std::vector<std::string> &getRawRows() const;

    private:
        std::vector<std::string> _rawRows;
        std::vector<std::vector<TileType>> _tiles;
        Position _playerSpawn = {0, 0};
        std::size_t _width = 0;
        std::size_t _height = 0;
        TileType parseTile(char c, std::size_t x, std::size_t y);
    };
}
