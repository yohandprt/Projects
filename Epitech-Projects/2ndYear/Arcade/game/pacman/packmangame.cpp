/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-arcade-16
** File description:
** packamngame.cpp
*/

#include "packmangame.hpp"
#include "IRectangle.hpp"
#include "ICircle.hpp"
#include "ISprite.hpp"
#include <chrono>

extern "C" std::unique_ptr<ARCADE::IModule> entryPoint()
{
    return std::make_unique<ARCADE::PacmanGame>();
}

long long ARCADE::PacmanGame::getNowMs() const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count();
}

void ARCADE::PacmanGame::init(std::unique_ptr<ADisplayModule> &display, GameState &state)
{
    _map.loadFromFile("./game/pacman/maps/map.txt");
    _playerSpawn = _map.getPlayerSpawn();
    _player.setPos(_playerSpawn);
    _ghostManager.init(_map.getGhostSpawns());
    _lives = 3;
    _score = 0;
    _powerUpActive = false;
    _running = true;
    _lastUpdateMs = getNowMs();
    _lastMoveMs = getNowMs();
    _ghostUpdateCounter = 0;
    _dotsRemaining = _map.getTotalDots();
    _originX = (1280.0f - static_cast<float>(_map.getWidth())  * TILE_SIZE) / 2.0f;
    _originY = (720.0f  - static_cast<float>(_map.getHeight()) * TILE_SIZE) / 2.0f;
    if (_originX < 0.0f)
        _originX = 0.0f;
    if (_originY < 0.0f)
        _originY = 0.0f;
    state.clear();
    createVisuals(display, state);
    updateVisuals(state);
}

void ARCADE::PacmanGame::stop()
{
    _running = false;
}

bool ARCADE::PacmanGame::isRunning() const
{
    return _running;
}

std::size_t ARCADE::PacmanGame::getScore() const
{
    return _score;
}

void ARCADE::PacmanGame::handleKeys(std::unique_ptr<ADisplayModule> &display, GameState &state)
{
    long long now = getNowMs();
    if (now - _lastMoveMs < PLAYER_MOVE_INTERVAL_MS)
        return;
        
    bool moved = false;
    if (display->isKeyPressed("up")) {
        handlePlayerMovement(0, -1, state);
        moved = true;
    } else if (display->isKeyPressed("down")) {
        handlePlayerMovement(0,  1, state);
        moved = true;
    } else if (display->isKeyPressed("left")) {
        handlePlayerMovement(-1, 0, state);
        moved = true;
    } else if (display->isKeyPressed("right")) {
        handlePlayerMovement(1,  0, state);
        moved = true;
    }
    if (moved)
        _lastMoveMs = now;
}

void ARCADE::PacmanGame::update(std::unique_ptr<ADisplayModule> &display, GameState &state)
{
    if (_gameover)
        return this->gameOver(display, state);

    long long now = getNowMs();

    if (now - _lastUpdateMs < UPDATE_INTERVAL_MS)
        return;
    _lastUpdateMs = now;
    if (_powerUpActive && isPowerUpExpired())
        deactivatePowerUp();
    _ghostUpdateCounter++;
    if (_ghostUpdateCounter >= GHOST_UPDATE_FREQUENCY) {
        _ghostUpdateCounter = 0;
        _ghostManager.update(_map, _player.getPos(), _powerUpActive);
    }
    if (checkCollisionsWithGhosts(state))
        return;
    if (checkVictory()) {
        state.clear();
        this->init(display, state);
        return;
    }

    updateVisuals(state);
}
