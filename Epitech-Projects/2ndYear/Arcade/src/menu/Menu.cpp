/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-arcade-16
** File description:
** Menu.cpp
*/

#include "Menu.hpp"

extern "C" std::unique_ptr<ARCADE::IModule> entryPoint()
{
    return std::make_unique<ARCADE::Menu>();
}

void ARCADE::Menu::init(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state)
{
    this->_dlHandler.findLibs("./lib/");
    this->_index = std::string::npos;
    this->_running = true;
    this->_fontSize = 50;
    this->_borderSize = 5;

    if (this->_enterName) {
        state.storeShape(std::move(display->createRectangle()), "textName");
        state.getShapeAs<ARCADE::IRectangle>("textName").setPosX((display->getWindowSizeX() - 500) / 2);
        state.getShapeAs<ARCADE::IRectangle>("textName").setPosY((display->getWindowSizeY() - 100) / 2 - 200);
        state.getShapeAs<ARCADE::IRectangle>("textName").setWidth(500);
        state.getShapeAs<ARCADE::IRectangle>("textName").setHeight(100);
        state.getShapeAs<ARCADE::IRectangle>("textName").setColor(ARCADE::Color::Black);
        state.getShapeAs<ARCADE::IRectangle>("textName").setText("Entrez votre nom", this->_fontSize, ARCADE::Color::White);
        state.storeShape(std::move(display->createRectangle()), "backBorder");
        state.getShapeAs<ARCADE::IRectangle>("backBorder").setPosX((display->getWindowSizeX() - 500) / 2 - this->_borderSize);
        state.getShapeAs<ARCADE::IRectangle>("backBorder").setPosY((display->getWindowSizeY() - 100) / 2 - this->_borderSize);
        state.getShapeAs<ARCADE::IRectangle>("backBorder").setWidth(500 + (this->_borderSize * 2));
        state.getShapeAs<ARCADE::IRectangle>("backBorder").setHeight(100 + (this->_borderSize * 2));
        state.getShapeAs<ARCADE::IRectangle>("backBorder").setColor(ARCADE::Color::White);
        state.storeShape(std::move(display->createRectangle()), "name");
        state.getShapeAs<ARCADE::IRectangle>("name").setPosX((display->getWindowSizeX() - 500) / 2);
        state.getShapeAs<ARCADE::IRectangle>("name").setPosY((display->getWindowSizeY() - 100) / 2);
        state.getShapeAs<ARCADE::IRectangle>("name").setWidth(500);
        state.getShapeAs<ARCADE::IRectangle>("name").setHeight(100);
        state.getShapeAs<ARCADE::IRectangle>("name").setColor(ARCADE::Color::Black);
        state.getShapeAs<ARCADE::IRectangle>("name").setText(this->_name, this->_fontSize, ARCADE::Color::White);
    } else {
        std::string boxName = "";

        for (std::size_t i = 0; i < this->_dlHandler.getGraphicLibs().size(); i++) {
            boxName = std::format("box{}", i);
            this->createBox(display, state, boxName, this->_dlHandler.getGraphicLibs()[i], 50.0 * i);
        }
        for (std::size_t i = 0; i < this->_dlHandler.getGameLibs().size(); i++) {
            boxName = std::format("box{}", i + this->_dlHandler.getGraphicLibs().size());
            this->createBox(display, state, boxName, this->_dlHandler.getGameLibs()[i], (50.0 * i) + (50.0 * this->_dlHandler.getGraphicLibs().size() + 50.0));
        }
        this->createBox(display, state, "valid", "VALID", (50.0 * this->_dlHandler.getGraphicLibs().size() + 50.0 * this->_dlHandler.getGameLibs().size() + 100.0));
        
        this->_leaderboard.display(display, state);
    }
}

void ARCADE::Menu::stop()
{
    this->_running = false;
}

void ARCADE::Menu::handleKeys(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state)
{
    std::string boxName;

    if (display->isKeyPressed("esc"))
        this->_running = false;

    if (this->_enterName)
        return this->handleWriting(display, state);

    this->handleNavigateIndex(display);

    if ((state.getShape("valid")->isClick() || (display->isKeyPressed("enter") && this->_keyOver == "valid")) && !this->_selectedGraphicLib.empty() && !this->_selectedGameLib.empty())
        this->_runGame = true;
    else
        this->handleBoxEvent(display, state, "valid");

    for (std::size_t i = 0; i < this->_dlHandler.getGraphicLibs().size(); i++) {
        boxName = std::format("box{}", i);

        if (state.getShapeAs<ARCADE::IRectangle>(boxName).getText() == this->_selectedGraphicLib) {
            state.getShape(boxName)->setColor(ARCADE::Color::Red);
            continue;
        }

        if (state.getShape(boxName)->isClick()) {
            this->_selectedGraphicLib = state.getShapeAs<ARCADE::IRectangle>(boxName).getText();
            state.getShape(boxName)->setColor(ARCADE::Color::Red);
        } else
            this->handleBoxEvent(display, state, boxName);
    }

    for (std::size_t i = 0; i < this->_dlHandler.getGameLibs().size(); i++) {
        boxName = std::format("box{}", i + this->_dlHandler.getGraphicLibs().size());

        if (state.getShapeAs<ARCADE::IRectangle>(boxName).getText() == this->_selectedGameLib) {
            state.getShape(boxName)->setColor(ARCADE::Color::Red);
            continue;
        }

        if (state.getShape(boxName)->isClick()) {
            this->_selectedGameLib = state.getShapeAs<ARCADE::IRectangle>(boxName).getText();
            state.getShape(boxName)->setColor(ARCADE::Color::Red);
        } else
            this->handleBoxEvent(display, state, boxName);
    }
}

void ARCADE::Menu::update(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state)
{
    (void)display;
    (void)state;
}

bool ARCADE::Menu::isRunning() const
{
    return this->_running;
}

bool ARCADE::Menu::runGame() const
{
    return this->_runGame;
}

bool ARCADE::Menu::setName() const
{
    return this->_setName;
}

std::string ARCADE::Menu::getName() const
{
    return this->_name;
}

void ARCADE::Menu::setEnterName(bool enterName)
{
    this->_enterName = enterName;
}

void ARCADE::Menu::handleWriting(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state)
{
    std::string letter = display->getKeyPressed();

    if (!letter.empty())
        this->_name += letter;
    if (display->isKeyPressed("left") && !this->_name.empty())
        this->_name = this->_name.substr(0, this->_name.size() - 1);
    state.getShapeAs<ARCADE::IRectangle>("name").setText(this->_name, this->_fontSize, ARCADE::Color::White);
    if (display->isKeyPressed("enter")) {
        this->_setName = true;
        this->_running = false;
    }
}

std::string ARCADE::Menu::getSelectedGraphicLib() const
{
    return this->_selectedGraphicLib;
}

std::string ARCADE::Menu::getSelectedGameLib() const
{
    return this->_selectedGameLib;
}

void ARCADE::Menu::handleNavigateIndex(std::unique_ptr<ARCADE::ADisplayModule>& display)
{
    if (display->isKeyPressed("up") && this->_index > 0 && this->_index != std::string::npos) {
        if (this->_index > 0)
            this->_index--;
        else if (this->_index == std::string::npos)
            this->_index = this->_dlHandler.getGraphicLibs().size() + this->_dlHandler.getGameLibs().size();
    }

    if (display->isKeyPressed("down") && (this->_index == std::string::npos || this->_index < this->_dlHandler.getGraphicLibs().size() + this->_dlHandler.getGameLibs().size()))
        this->_index++;

    if (this->_index != std::string::npos) {
        if (this->_index == this->_dlHandler.getGraphicLibs().size() + this->_dlHandler.getGameLibs().size())
            this->_keyOver = "valid";
        else if (this->_index < this->_dlHandler.getGraphicLibs().size())
            this->_keyOver = std::format("box{}", this->_index);
        else if (this->_index >= this->_dlHandler.getGraphicLibs().size() && this->_index < this->_dlHandler.getGraphicLibs().size() + this->_dlHandler.getGameLibs().size())
            this->_keyOver = std::format("box{}", this->_index);
    } else
        this->_keyOver.clear();
}

void ARCADE::Menu::createBox(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state, std::string boxName, std::string text, float posY)
{
    std::size_t nbRect = this->_dlHandler.getGraphicLibs().size() + this->_dlHandler.getGameLibs().size() + 1;
    float rectH = 50.0;
    float rectW = 500.0;
    float posX = ((display->getWindowSizeX() / 2) - rectW) / 2;
    float basePosY = (display->getWindowSizeY() - (rectH * nbRect)) / 2;

    state.storeShape(std::move(display->createRectangle()), boxName);
    state.getShapeAs<ARCADE::IRectangle>(boxName).setPosX(posX);
    state.getShapeAs<ARCADE::IRectangle>(boxName).setPosY(basePosY + posY);
    state.getShapeAs<ARCADE::IRectangle>(boxName).setWidth(rectW);
    state.getShapeAs<ARCADE::IRectangle>(boxName).setHeight(rectH);
    state.getShapeAs<ARCADE::IRectangle>(boxName).setColor(ARCADE::Color::Black);
    state.getShapeAs<ARCADE::IRectangle>(boxName).setText(text, 20, ARCADE::Color::White);
}

void ARCADE::Menu::handleBoxEvent(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state, std::string boxName)
{
    if (display->isKeyPressed("enter") && !this->_keyOver.empty()) {
        std::string boxText = state.getShapeAs<ARCADE::IRectangle>(this->_keyOver).getText();
        if (this->_dlHandler.isGraphicLib(boxText))
            this->_selectedGraphicLib = boxText;
        else if (this->_dlHandler.isGameLib(boxText))
            this->_selectedGameLib = boxText;
    }

    if (state.getShape(boxName)->isMouseHover()) {
        this->_index = std::string::npos;
        state.getShape(boxName)->setColor(ARCADE::Color::Green);
    } else if (boxName == this->_keyOver) {
        state.getShape(boxName)->setColor(ARCADE::Color::Green);
    } else
        state.getShape(boxName)->setColor(ARCADE::Color::Black);
}

std::size_t ARCADE::Menu::getScore() const
{
    return 0;
}