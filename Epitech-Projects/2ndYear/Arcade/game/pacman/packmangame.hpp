#pragma once

#include "AGameModule.hpp"
#include "GameState.hpp"
#include "PacmanMap.hpp"
#include "Character.hpp"
#include "GhostManager.hpp"
#include "PacmanTypes.hpp"
#include <chrono>

namespace ARCADE {
    class PacmanGame : public ARCADE::AGameModule
    {
    public:
        PacmanGame() = default;
        ~PacmanGame() = default;

        void init(std::unique_ptr<ARCADE::ADisplayModule> &display, ARCADE::GameState &state) override;
        void stop() override;
        void handleKeys(std::unique_ptr<ARCADE::ADisplayModule> &display, ARCADE::GameState &state) override;
        void update(std::unique_ptr<ARCADE::ADisplayModule> &display, ARCADE::GameState &state) override;
        bool isRunning() const override;
        std::size_t getScore() const override;

    private:
        long long getNowMs() const;

        void handlePlayerMovement(int dx, int dy, ARCADE::GameState &state);
        
        void activatePowerUp();
        void deactivatePowerUp();
        bool isPowerUpExpired() const;
        int getPowerUpSecondsLeft() const;
        
        bool checkCollisionsWithGhosts(ARCADE::GameState &state);
        bool checkVictory() const;
        void respawnPlayer();

        void createVisuals(std::unique_ptr<ARCADE::ADisplayModule> &display, ARCADE::GameState &state);
        void updateVisuals(ARCADE::GameState &state);
        
        void updateMapVisuals(ARCADE::GameState &state);
        void updatePlayerVisual(ARCADE::GameState &state);
        void updateGhostVisuals(ARCADE::GameState &state);
        void updateHUDVisuals(ARCADE::GameState &state);

        float TILE_SIZE = 32.0f;
        int GHOST_UPDATE_FREQUENCY = 1;
        long long POWER_UP_DURATION_MS = 5000;
        long long UPDATE_INTERVAL_MS = 150;
        long long PLAYER_MOVE_INTERVAL_MS = 130;

        bool _running = true;
        PacmanMap _map;
        Character _player;
        Position _playerSpawn;
        GhostManager _ghostManager;
        
        int _lives = 3;
        int _score = 0;
        bool _powerUpActive = false;
        long long _lastUpdateMs = 0;
        long long _lastMoveMs = 0;
        long long _powerUpStartMs = 0;
        int _ghostUpdateCounter = 0;
        int _dotsRemaining = 0;

        float _originX = 0;
        float _originY = 0;

    };
}