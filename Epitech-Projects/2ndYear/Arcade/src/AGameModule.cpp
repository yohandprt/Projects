/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-arcade-16
** File description:
** AGameModule.cpp
*/

#include "AGameModule.hpp"

ARCADE::AGameModule::AGameModule()
{
    this->_gameover = false;
}

void ARCADE::AGameModule::gameOver(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state)
{
    state.storeShape(std::move(display->createRectangle()), "blackBG");
    state.getShapeAs<ARCADE::IRectangle>("blackBG").setPosX(0);
    state.getShapeAs<ARCADE::IRectangle>("blackBG").setPosY(0);
    state.getShapeAs<ARCADE::IRectangle>("blackBG").setWidth(display->getWindowSizeX());
    state.getShapeAs<ARCADE::IRectangle>("blackBG").setHeight(display->getWindowSizeY());
    state.getShapeAs<ARCADE::IRectangle>("blackBG").setColor(ARCADE::Color::Black);

    state.storeShape(std::move(display->createRectangle()), "gameOverText");
    state.getShapeAs<ARCADE::IRectangle>("gameOverText").setPosX(display->getWindowSizeX() / 4);
    state.getShapeAs<ARCADE::IRectangle>("gameOverText").setPosY(display->getWindowSizeY() / 2 - 100);
    state.getShapeAs<ARCADE::IRectangle>("gameOverText").setWidth(display->getWindowSizeX() / 2);
    state.getShapeAs<ARCADE::IRectangle>("gameOverText").setHeight(200);
    state.getShapeAs<ARCADE::IRectangle>("gameOverText").setColor(ARCADE::Color::Black);
    state.getShapeAs<ARCADE::IRectangle>("gameOverText").setText("Game Over", 50, ARCADE::Color::White);
}

void ARCADE::AGameModule::removeGameOverScreen(ARCADE::GameState& state)
{
    if (state.hasShape("blackBG"))
        state.removeShape("blackBG");
    if (state.hasShape("gameOverText"))
        state.removeShape("gameOverText");
}

bool ARCADE::AGameModule::isGameOver() const
{
    return this->_gameover;
}