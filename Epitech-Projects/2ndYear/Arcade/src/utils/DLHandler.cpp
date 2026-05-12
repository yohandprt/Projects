/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-arcade-16
** File description:
** DLHandler.cpp
*/

#include "DLHandler.hpp"

ARCADE::DLHandler::DLHandler()
{
    this->_indexGraphic = 0;
    this->_indexGame = 0;
    this->_firstLoadGraphic = false;
    this->_firstLoadGame = false;
}

ARCADE::DLHandler::DLHandler(std::string libDirPath)
{
    this->findLibs(libDirPath);
    this->_indexGraphic = 0;
    this->_indexGame = 0;
    this->_firstLoadGraphic = false;
    this->_firstLoadGame = false;
}

bool ARCADE::DLHandler::isGraphicLib(std::string libPath)
{
    libPath = libPath.starts_with("./") ? libPath : ("./" + libPath);

    return std::find(this->_graphicLibs.begin(), this->_graphicLibs.end(), libPath) != this->_graphicLibs.end();
}

bool ARCADE::DLHandler::isGameLib(std::string libPath)
{
    libPath = libPath.starts_with("./") ? libPath : ("./" + libPath);

    return std::find(this->_gameLibs.begin(), this->_gameLibs.end(), libPath) != this->_gameLibs.end();
}

std::unique_ptr<ARCADE::ADisplayModule> ARCADE::DLHandler::loadGraphic(std::string libPath)
{
    if (!this->_firstLoadGraphic) {
        std::vector<std::string>::iterator it = std::find(this->_graphicLibs.begin(), this->_graphicLibs.end(), libPath);

        if (it != this->_graphicLibs.end())
            this->_indexGraphic = (std::distance(this->_graphicLibs.begin(), it) + 1) % this->_graphicLibs.size();
        this->_firstLoadGraphic = true;
    }

    return this->_loader.getInstance<ADisplayModule>(libPath);
}

std::unique_ptr<ARCADE::AGameModule> ARCADE::DLHandler::loadGame(std::string libPath)
{
    if (!this->_firstLoadGame) {
        std::vector<std::string>::iterator it = std::find(this->_gameLibs.begin(), this->_gameLibs.end(), libPath);

        if (it != this->_gameLibs.end())
            this->_indexGame = (std::distance(this->_gameLibs.begin(), it) + 1) % this->_gameLibs.size();
        this->_firstLoadGame = true;
    }

    return this->_loader.getInstance<AGameModule>(libPath);
}

void ARCADE::DLHandler::findLibs(std::string libDirPath)
{
    std::string filename;

    for (const auto& entry : std::filesystem::directory_iterator(libDirPath)) {
        libDirPath = libDirPath.starts_with("./") ? libDirPath : ("./" + libDirPath);
        if (entry.is_regular_file()) {
            filename = libDirPath.ends_with("/") ? (libDirPath + entry.path().filename().string()) : (libDirPath + "/" + entry.path().filename().string());
            if (filename == "./lib/menu.so")
                continue;
            if (this->_loader.getInstance<ARCADE::ADisplayModule>(filename))
                this->_graphicLibs.push_back(filename);
            else if (this->_loader.getInstance<ARCADE::AGameModule>(filename))
                this->_gameLibs.push_back(filename);
        }
    }
}

std::vector<std::string> ARCADE::DLHandler::getGraphicLibs()
{
    return this->_graphicLibs;
}

std::vector<std::string> ARCADE::DLHandler::getGameLibs()
{
    return this->_gameLibs;
}

std::string ARCADE::DLHandler::nextGraphicLib()
{
    this->_currentGraphicLib = this->_graphicLibs[this->_indexGraphic];

    this->_indexGraphic = (this->_indexGraphic + 1) % this->_graphicLibs.size();

    return this->_currentGraphicLib;
}

std::string ARCADE::DLHandler::nextGameLib()
{
    this->_currentGameLib = this->_gameLibs[this->_indexGame];

    this->_indexGame = (this->_indexGame + 1) % this->_gameLibs.size();

    return this->_currentGameLib;
}

std::string ARCADE::DLHandler::currentGraphicLib()
{
    return this->_currentGraphicLib;
}

std::string ARCADE::DLHandler::currentGameLib()
{
    return this->_currentGameLib;
}


void ARCADE::DLHandler::initFirstLibs(std::string firstGraphicLib, std::string firstGameLib)
{
    this->_currentGraphicLib = firstGraphicLib;
    this->_currentGameLib = firstGameLib;
    this->_firstLoadGraphic = false;
    this->_firstLoadGame = false;
}