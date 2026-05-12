/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-arcade-16
** File description:
** PacmanGhost.hpp
*/

#pragma once
#include "Character.hpp"
#include <random>
#include <string>
#include <unordered_map>
#include <queue>

namespace ARCADE {

    class PacmanGhost : public Character {
    public:
        PacmanGhost(const Position &spawn, const std::string &shapeName);
        using Character::update;
        void update(const PacmanMap &map, const Position &playerPos, bool fleeing);
        const std::string &getShapeName() const {
            return _shapeName;
        }

    private:
        std::string _shapeName;
        int _dirX = 0;
        int _dirY = 0;
        static std::mt19937 _rng;

        using Direction = std::pair<int, int>;

        Direction computeNextMove(const PacmanMap &map, const Position &playerPos, bool fleeing);
        void applyMovement(const PacmanMap &map, const Direction &dir);

        std::vector<Direction> getMovableDirections(const PacmanMap &map) const;
        std::unordered_map<int, int> buildDistanceMap(const Position &target, const PacmanMap &map) const;
        void exploreNeighbors(const Position &current, int currentDistance, const PacmanMap &map, int width,
            std::unordered_map<int, int> &distances, std::queue<std::pair<Position, int>> &queue) const;
        Direction selectDirection(const std::vector<Direction> &available,
            const std::unordered_map<int, int> &distances, const PacmanMap &map, bool fleeing) const;
    };

}