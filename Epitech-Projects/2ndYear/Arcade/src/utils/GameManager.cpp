/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-arcade-16
** File description:
** GameManager.cpp
*/

#include "GameManager.hpp"
#include "Menu.hpp"

ARCADE::GameManager::GameManager()
{
    this->_dlHandler.findLibs("./lib/");
}

int ARCADE::GameManager::runMenu(std::string firstGraphicLib, bool enterName)
{
    ARCADE::DLLoader loader;

    this->_dlHandler.initFirstLibs(firstGraphicLib, "");
    std::unique_ptr<ARCADE::ADisplayModule> graphic = this->_dlHandler.loadGraphic(firstGraphicLib);
    std::unique_ptr<ARCADE::Menu> menu = loader.getInstance<ARCADE::Menu>("./lib/menu.so");

    this->_firstGraphicLib = firstGraphicLib;

    if (!graphic || !menu)
        return 84;

    menu->setEnterName(enterName);
    graphic->init();
    this->_state.clear();
    menu->init(graphic, this->_state);

    while (graphic->isOpen() && menu->isRunning() && !menu->runGame()) {
        while (graphic->pollEvent() && !menu->runGame())
            menu->handleKeys(graphic, this->_state);

        menu->update(graphic, this->_state);
        graphic->clear();
        this->_state.drawAll();
        graphic->display();
    }
    menu->stop();
    this->_state.clear();
    graphic->stop();
    if (this->canLaunchGraphic())
        this->_firstGraphicLib = menu->getSelectedGraphicLib();
    this->_firstGameLib = menu->getSelectedGameLib();
    if (menu->runGame())
        return 1;
    else if (menu->setName())
        this->_playerName = menu->getName();
    return 0;
}

int ARCADE::GameManager::runGame()
{
    this->_dlHandler.initFirstLibs(this->_firstGraphicLib, this->_firstGameLib);
    std::unique_ptr<ARCADE::ADisplayModule> graphic = this->_dlHandler.loadGraphic(this->_firstGraphicLib);
    std::unique_ptr<ARCADE::AGameModule> game = this->_dlHandler.loadGame(this->_firstGameLib);

    if (!graphic || !game)
        return 84;

    graphic->init();
    this->_state.clear();
    game->init(graphic, this->_state);
    this->_state.loadGame(graphic, this->_dlHandler.currentGameLib());

    bool openMenu = false;

    while (graphic->isOpen() && game->isRunning() && !openMenu) {
        while (graphic->pollEvent() && !openMenu) {

            if (graphic->isKeyPressed("m"))
                openMenu = true;

            if (graphic->isKeyPressed("tab") && this->canLaunchGraphic()) {

                this->_state.saveGame(this->_dlHandler.currentGameLib());
                this->_state.clear();
                graphic->stop();
                graphic.reset();
                graphic = this->_dlHandler.loadGraphic(this->_dlHandler.nextGraphicLib());
                graphic->init();
                game->init(graphic, this->_state);
                this->_state.loadGame(graphic, this->_dlHandler.currentGameLib());
            }
            if (graphic->isKeyPressed("space")) {
                this->_state.saveGame(this->_dlHandler.currentGameLib());
                this->_state.clear();

                game->stop();
                game.reset();
                game = this->_dlHandler.loadGame(this->_dlHandler.nextGameLib());
                game->init(graphic, this->_state);

                this->_state.loadGame(graphic, this->_dlHandler.currentGameLib());
            }
            if (graphic->isKeyPressed("r"))
                game->init(graphic, this->_state);

            game->handleKeys(graphic, this->_state);

        }

        game->handleKeys(graphic, this->_state);
        game->update(graphic, this->_state);

        graphic->clear();
        this->_state.drawAll();
        graphic->display();
    }

    if (game->isGameOver())
        game->removeGameOverScreen(this->_state);

    this->_state.saveGame(this->_dlHandler.currentGameLib());
    this->_state.saveScore(this->_dlHandler.currentGameLib(), this->getName(), game->getScore());
    game->stop();
    this->_state.clear();
    graphic->stop();

    if (openMenu)
        return 1;
    return 0;
}

void ARCADE::GameManager::initVectorEnvp(char *envp[])
{
    for (std::size_t i = 0; envp[i]; i++)
        this->_vectorEnvp.push_back(envp[i]);
}

bool ARCADE::GameManager::canLaunchGraphic()
{
    bool findDisplay = false;

    for (std::size_t i = 0; i < this->_vectorEnvp.size(); i++) {
        if (this->_vectorEnvp[i].starts_with("DISPLAY") || this->_vectorEnvp[i].starts_with("WAYLAND_DISPLAY"))
            findDisplay = true;
    }

    return findDisplay;
}

ARCADE::DLHandler& ARCADE::GameManager::getDLHandler()
{
    return this->_dlHandler;
}

ARCADE::GameState& ARCADE::GameManager::getGameState()
{
    return this->_state;
}

std::string ARCADE::GameManager::getName() const
{
    return this->_playerName;
}