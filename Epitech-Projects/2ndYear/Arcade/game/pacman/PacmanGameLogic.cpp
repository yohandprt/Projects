/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-arcade-16
** File description:
** PacmanGameLogic.cpp
*/

#include "packmangame.hpp"

// Gere un input de mouvement joueur, applique le score et met a jour les visuels.
void ARCADE::PacmanGame::handlePlayerMovement(int x, int y, GameState &state)
{
    Position previousPos = _player.getPos();
    _player.move(x, y, _map);
    if (_player.getPos() == previousPos) {
        updateVisuals(state);
        return;
    }

    TileType eaten = _map.eatTile(_player.getPos().x, _player.getPos().y);
    if (eaten == TileType::Dot) {
        _score += 10;
        _dotsRemaining--;
    }
    if (eaten == TileType::PowerDot) {
        _score += 50;
        _dotsRemaining--;
        activatePowerUp();
    }
    updateVisuals(state);
}

// Active l'etat power-up et demarre son timer.
void ARCADE::PacmanGame::activatePowerUp()
{
    _powerUpActive = true;
    _powerUpStartMs = getNowMs();
}

// Desactive l'etat power-up et reinitialise son timer.
void ARCADE::PacmanGame::deactivatePowerUp()
{
    _powerUpActive = false;
    _powerUpStartMs = 0;
}

// Indique si la duree du power-up est terminee.
bool ARCADE::PacmanGame::isPowerUpExpired() const
{
    return (getNowMs() - _powerUpStartMs) >= POWER_UP_DURATION_MS;
}

// Retourne le nombre de secondes restantes pour le power-up.
int ARCADE::PacmanGame::getPowerUpSecondsLeft() const
{
    if (!_powerUpActive) return 0;
    long long remaining = POWER_UP_DURATION_MS - (getNowMs() - _powerUpStartMs);
    return remaining > 0 ? static_cast<int>(remaining / 1000) : 0;
}

// Gere les collisions joueur/fantomes et applique les consequences gameplay.
bool ARCADE::PacmanGame::checkCollisionsWithGhosts(GameState &state)
{
    const auto &ghosts = _ghostManager.getGhosts();
    for (std::size_t i = 0; i < ghosts.size(); i++) {
        if (_player.getPos() != ghosts[i].getPos())
            continue;
        if (_powerUpActive) {
            _score += 200;
            _ghostManager.respawnGhost(i);
        } else {
            _lives--;
            if (_lives <= 0) {
                _gameover = true;
                return true;
            }
            respawnPlayer();
        }
        updateVisuals(state);
        return false;
    }
    return false;
}

// Verifie la condition de victoire (plus aucun point a manger).
bool ARCADE::PacmanGame::checkVictory() const
{
    return _dotsRemaining <= 0;
}

// Replace le joueur et tous les fantomes sur leurs positions de spawn.
void ARCADE::PacmanGame::respawnPlayer()
{
    _player.setPos(_playerSpawn);

    const auto &ghosts = _ghostManager.getGhosts();
    for (std::size_t i = 0; i < ghosts.size(); i++) {
        _ghostManager.respawnGhost(i);
    }
}
