/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-arcade-16
** File description:
** PacmanGhostAlgo.cpp
*/

#include "PacmanGhost.hpp"

#include <climits>
#include <queue>

namespace ARCADE {

    static const std::vector<std::pair<int, int>> ALL_DIRECTIONS = {
        {0, -1},
        {0,  1},
        {-1, 0},
        {1,  0},
    };

    // Choisit la prochaine direction selon les mouvements possibles et la distance au joueur.
    PacmanGhost::Direction PacmanGhost::computeNextMove(const PacmanMap &map, const Position &playerPos, bool fleeing)
    {
        auto movable = getMovableDirections(map);

        if (movable.empty())
            return {-_dirX, -_dirY};
        auto distances = buildDistanceMap(playerPos, map);
        return selectDirection(movable, distances, map, fleeing);
    }

    // Retourne les directions valides depuis la position courante, sans demi-tour immediat.
    std::vector<PacmanGhost::Direction> PacmanGhost::getMovableDirections(const PacmanMap &map) const
    {
        std::vector<Direction> available;

        for (const auto &dir : ALL_DIRECTIONS) {
            bool isOpposite = (_dirX == -dir.first && _dirY == -dir.second && (_dirX != 0 || _dirY != 0));
            if (isOpposite)
                continue;
            int nextX = _pos.x + dir.first;
            int nextY = _pos.y + dir.second;
            if (map.isInside(nextX, nextY) && !map.isWall(nextX, nextY))
                available.push_back(dir);
        }
        return available;
    }

    // Construit une carte des distances minimales vers la cible via un BFS.
    std::unordered_map<int, int> PacmanGhost::buildDistanceMap(const Position &target, const PacmanMap &map) const
    {
        std::unordered_map<int, int> distances;
        std::queue<std::pair<Position, int>> queue;
        int width = static_cast<int>(map.getWidth());

        queue.push({target, 0});
        distances[target.y * width + target.x] = 0;
        while (!queue.empty()) {
            auto [currentPos, currentDistance] = queue.front();
            queue.pop();
            exploreNeighbors(currentPos, currentDistance, map, width, distances, queue);
        }
        return distances;
    }

    // Explore les voisins d'une case dans le BFS et enregistre leur distance.
    void PacmanGhost::exploreNeighbors(const Position &current, int currentDistance, const PacmanMap &map,
        int width, std::unordered_map<int, int> &distances, std::queue<std::pair<Position, int>> &queue) const
    {
        for (const auto &[dirX, dirY] : ALL_DIRECTIONS) {
            Position nextPos = {current.x + dirX, current.y + dirY};
            if (!map.isInside(nextPos.x, nextPos.y))
                continue;
            int nextKey = nextPos.y * width + nextPos.x;
            int nextDistance = currentDistance + 1;
            bool alreadyVisited = (distances.find(nextKey) != distances.end());
            bool isWall = map.isWall(nextPos.x, nextPos.y);

            if (!alreadyVisited && !isWall) {
                distances[nextKey] = nextDistance;
                queue.push({nextPos, nextDistance});
            }
        }
    }

    // Selectionne la meilleure direction: rapprochement ou fuite selon l'etat fleeing.
    PacmanGhost::Direction PacmanGhost::selectDirection(const std::vector<Direction> &available,
        const std::unordered_map<int, int> &distances, const PacmanMap &map, bool fleeing) const
    {
        Direction best = available[0];
        int bestDistance = fleeing ? -1 : INT_MAX;
        int width = static_cast<int>(map.getWidth());

        for (const auto &dir : available) {
            Position nextPos = {_pos.x + dir.first, _pos.y + dir.second};
            int key = nextPos.y * width + nextPos.x;
            int distance = (distances.find(key) != distances.end()) ? distances.at(key) : INT_MAX;
            if ((fleeing && distance > bestDistance) || (!fleeing && distance < bestDistance)) {
                bestDistance = distance;
                best = dir;
            }
        }

        return best;
    }

}
