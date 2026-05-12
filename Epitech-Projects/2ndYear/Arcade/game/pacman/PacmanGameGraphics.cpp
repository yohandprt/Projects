/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-arcade-16
** File description:
** PacmanGameGraphics.cpp
*/

#include "packmangame.hpp"
#include "IRectangle.hpp"
#include "ICircle.hpp"

// Cree tous les visuels une seule fois (map, fantomes, joueur et HUD).
void ARCADE::PacmanGame::createVisuals(std::unique_ptr<ADisplayModule> &display, GameState &state)
{
    for (std::size_t y = 0; y < _map.getHeight(); y++)
        for (std::size_t x = 0; x < _map.getWidth(); x++)
            state.storeShape(display->createRectangle(),
                "1_tile_" + std::to_string(x) + "_" + std::to_string(y));
    for (const auto &ghost : _ghostManager.getGhosts())
        state.storeShape(display->createRectangle(), "2_" + ghost.getShapeName());
    state.storeShape(display->createCircle(), "3_player");
    state.storeShape(display->createRectangle(), "4_hud_lives");
    state.storeShape(display->createRectangle(), "4_hud_score");
    state.storeShape(display->createRectangle(), "4_hud_powerup");
}

// Met a jour l'ensemble des visuels du jeu pour cette frame.
void ARCADE::PacmanGame::updateVisuals(GameState &state)
{
    updateMapVisuals(state);
    updatePlayerVisual(state);
    updateGhostVisuals(state);
    updateHUDVisuals(state);
}

// Met a jour les tuiles de la map (position, taille, couleur et texte selon le type de case).
void ARCADE::PacmanGame::updateMapVisuals(GameState &state)
{
    for (std::size_t y = 0; y < _map.getHeight(); y++) {
        for (std::size_t x = 0; x < _map.getWidth(); x++) {
            std::string elementName = "1_tile_" + std::to_string(x) + "_" + std::to_string(y);
            if (!state.hasShape(elementName))
                continue;
            auto &rect = state.getShapeAs<IRectangle>(elementName);
            rect.setPosX(_originX + static_cast<float>(x) * TILE_SIZE);
            rect.setPosY(_originY + static_cast<float>(y) * TILE_SIZE);
            rect.setWidth(TILE_SIZE);
            rect.setHeight(TILE_SIZE);
            switch (_map.getTile(static_cast<int>(x), static_cast<int>(y))) {
                case TileType::Wall:
                    rect.setColor(Color::Blue);
                    rect.setText("", 0, Color::Blue);
                    break;
                case TileType::Dot:
                    rect.setColor(Color::Black);
                    rect.setText(".", 18, Color::White);
                    break;
                case TileType::PowerDot:
                    rect.setColor(Color::Black);
                    rect.setText("o", 20, Color::Green);
                    break;
                default:
                    rect.setColor(Color::Black);
                    rect.setText("", 0, Color::Black);
                    break;
            }
        }
    }
}

// Met a jour la shape du joueur selon sa position actuelle et l'etat du power-up.
void ARCADE::PacmanGame::updatePlayerVisual(GameState &state)
{
    if (!state.hasShape("3_player"))
        return;
    auto &circle = state.getShapeAs<ICircle>("3_player");
    circle.setPosX(_originX + static_cast<float>(_player.getPos().x) * TILE_SIZE);
    circle.setPosY(_originY + static_cast<float>(_player.getPos().y) * TILE_SIZE);
    circle.setDiameter(TILE_SIZE);
    circle.setColor(_powerUpActive ? Color::Red : Color::Yellow);
}

// Met a jour les visual des fantomes avec leur position courante.
void ARCADE::PacmanGame::updateGhostVisuals(GameState &state)
{
    for (const auto &ghost : _ghostManager.getGhosts()) {
        std::string elementName = "2_" + ghost.getShapeName();
        if (!state.hasShape(elementName))
            continue;
        auto &rect = state.getShapeAs<IRectangle>(elementName);
        rect.setPosX(_originX + static_cast<float>(ghost.getPos().x) * TILE_SIZE);
        rect.setPosY(_originY + static_cast<float>(ghost.getPos().y) * TILE_SIZE);
        rect.setWidth(TILE_SIZE);
        rect.setHeight(TILE_SIZE);
        rect.setColor(Color::Red);
        rect.setText("", 0, Color::Red);
    }
}

// Met a jour les elements du HUD (vies, score et timer de power-up).
void ARCADE::PacmanGame::updateHUDVisuals(GameState &state)
{
    auto setupHUD = [&](const std::string &name, float posY, const std::string &text, Color textColor) {
        if (!state.hasShape(name))
            return;
        auto &rect = state.getShapeAs<IRectangle>(name);
        rect.setPosX(10.0f);
        rect.setPosY(posY);
        rect.setWidth(200.0f);
        rect.setHeight(30.0f);
        rect.setColor(Color::Black);
        rect.setText(text, 20, textColor);
    };

    setupHUD("4_hud_lives", 10.0f, "Lives: " + std::to_string(_lives), Color::White);
    setupHUD("4_hud_score", 50.0f, "Score: " + std::to_string(_score), Color::White);
    
    if (_powerUpActive)
        setupHUD("4_hud_powerup", 90.0f, "Power: " + std::to_string(getPowerUpSecondsLeft()) + "s", Color::Red);
    else
        setupHUD("4_hud_powerup", 90.0f, "", Color::Black);
}
