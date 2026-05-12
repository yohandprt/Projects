/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** GameState.hpp
*/

#pragma once

#include <memory>
#include <map>
#include <array>
#include <concepts>
#include <vector>
#include <fstream>
#include <sstream>
#include <format>
#include <filesystem>

#include "IShape.hpp"
#include "ICircle.hpp"
#include "IRectangle.hpp"
#include "IDisplayModule.hpp"
#include "ADisplayModule.hpp"
#include "AGameModule.hpp"
#include "ISprite.hpp"

namespace ARCADE {

    typedef struct shapeState_s {
        float x;
        float y;
        float w;
        float h;
        float d;
        ARCADE::Color color;
        std::string text;
        ARCADE::Color textColor;
        std::string imagePath;
    } shapeState;

    class GameState
    {
    private:
        std::map<std::string, std::unique_ptr<ARCADE::IShape>> _shapes;
        std::map<std::string, shapeState> _storage;
        std::vector<std::string> _shapeTypes;
    public:
        GameState() = default;
        ~GameState() = default;

        void saveGame(std::string currentGameLib);
        void loadGame(std::unique_ptr<ARCADE::ADisplayModule>& display, std::string currentGameLib);
        void removeGameSaves();
        void storeState(const std::unique_ptr<ARCADE::IShape> &shape, const std::string &name, std::string type);
        void storeShape(std::unique_ptr<ARCADE::IShape> shape, const std::string &name);
        void removeShape(std::string name);
        bool hasShape(const std::string &name) const;
        std::unique_ptr<ARCADE::IShape>& getShape(const std::string &name);
        std::vector<std::string> getShapes();
        void saveShapes();
        void drawAll();
        void clear();
        void saveScore(std::string currentGameLib, std::string playerName, std::size_t score);
        void saveInFile(std::string filePath, std::vector<std::string> &lines);

        template<typename SHAPE>
        SHAPE& getShapeAs(const std::string &name)
        {
            return *dynamic_cast<SHAPE*>(getShape(name).get());
        }

    };
}