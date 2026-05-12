/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-arcade-16
** File description:
** PacmanGhost.cpp
*/

#include "PacmanGhost.hpp"

namespace ARCADE {

    std::mt19937 PacmanGhost::_rng(std::random_device{}());

    static const std::vector<std::pair<int, int>> ALL_DIRECTIONS = {
        {0, -1},
        {0,  1},
        {-1, 0},
        {1,  0},
    };

    // Cree un fantome a son spawn avec une direction initiale aleatoire.
    PacmanGhost::PacmanGhost(const Position &spawn, const std::string &shapeName)
        : Character(spawn), _shapeName(shapeName)
    {
        std::uniform_int_distribution<int> dist(0, ALL_DIRECTIONS.size() - 1);
        auto dir = ALL_DIRECTIONS[dist(_rng)];
        _dirX = dir.first;
        _dirY = dir.second;
    }

    // Met a jour le fantome: calcule la direction puis avance d'une case.
    void PacmanGhost::update(const PacmanMap &map, const Position &playerPos, bool fleeing)
    {
        auto nextDir = computeNextMove(map, playerPos, fleeing);

        _dirX = nextDir.first;
        _dirY = nextDir.second;
        applyMovement(map, nextDir);
    }

    // Applique un pas de deplacement si la case cible est valide et non murale.
    void PacmanGhost::applyMovement(const PacmanMap &map, const Direction &dir)
    {
        int newX = _pos.x + dir.first;
        int newY = _pos.y + dir.second;
        if (map.isInside(newX, newY) && !map.isWall(newX, newY)) {
            _pos.x = newX;
            _pos.y = newY;
        }
    }

}
