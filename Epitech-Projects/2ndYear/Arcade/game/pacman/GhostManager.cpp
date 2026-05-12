/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-arcade-16
** File description:
** GhostManager.cpp
*/

#include "GhostManager.hpp"

void ARCADE::GhostManager::init(const std::vector<Position> &spawns)
{
    _ghosts.clear();
    _spawnPositions = spawns;

    for (std::size_t i = 0; i < spawns.size(); i++)
        _ghosts.emplace_back(spawns[i], "zz_ghost_" + std::to_string(i));
}

void ARCADE::GhostManager::update(const PacmanMap &map, const Position &playerPos, bool powerUpActive)
{
    for (auto &ghost : _ghosts)
        ghost.update(map, playerPos, powerUpActive);
}

void ARCADE::GhostManager::respawnGhost(std::size_t index)
{
    if (index < _ghosts.size() && index < _spawnPositions.size())
        _ghosts[index].setPos(_spawnPositions[index]);
}