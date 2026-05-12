/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-arcade-16
** File description:
** GhostManager.hpp
*/

#pragma once
#include "PacmanGhost.hpp"
#include <vector>

namespace ARCADE {
    class GhostManager {
    public:
        void init(const std::vector<Position> &spawns);
        void update(const PacmanMap &map, const Position &playerPos, bool powerUpActive);
        void respawnGhost(std::size_t index);

        const std::vector<PacmanGhost> &getGhosts() const
        {
            return _ghosts;
        }

    private:
        std::vector<PacmanGhost> _ghosts;
        std::vector<Position> _spawnPositions;
    };

}
