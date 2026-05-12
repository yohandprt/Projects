/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** GameState.cpp
*/

#include "GameState.hpp"

void ARCADE::GameState::saveGame(std::string currentGameLib)
{
    currentGameLib = currentGameLib.starts_with("./") ? "." + currentGameLib.substr(6, currentGameLib.size() - 9) + "-save.txt" : "." + currentGameLib.substr(4, currentGameLib.size() - 7) + "-save.txt";
    this->saveShapes();
    std::ofstream file(currentGameLib);
    std::map<std::string, ARCADE::shapeState>::iterator it = this->_storage.begin();
    std::string line;
    std::size_t i = 0;

    if (this->_shapeTypes.size() != this->_storage.size()) {
        std::cerr << "Erreur : _shapeTypes.size() = " << this->_shapeTypes.size() 
                  << ", _storage.size() = " << this->_storage.size() << std::endl;
        return;  // Ou throw, ou corriger
    }

    for (; it != this->_storage.end(); it++) {
        std::string safeText = it->second.text;
        if (safeText.empty())
            safeText = "\"\"";
        else {
            std::size_t pos = 0;
            while ((pos = safeText.find(" ", pos)) != std::string::npos) {
                safeText.replace(pos, 1, "%20");
                pos += 3;
            }
        }

        std::string safeImagePath = it->second.imagePath;
        if (safeImagePath.empty())
            safeImagePath = "\"\"";
        else {
            std::size_t pos = 0;
            while ((pos = safeImagePath.find(" ", pos)) != std::string::npos) {
                safeImagePath.replace(pos, 1, "%20");
                pos += 3;
            }
        }

        line = std::format("{} {} {} {} {} {} {} {} {} {} {}\n", this->_shapeTypes[i], it->first, it->second.x, it->second.y, it->second.w, it->second.h, it->second.d, static_cast<int>(it->second.color), safeText, static_cast<int>(it->second.textColor), safeImagePath);
        file << line;
        i++;
    }
    file.close();
}

void ARCADE::GameState::loadGame(std::unique_ptr<ARCADE::ADisplayModule>& display, std::string currentGameLib)
{
    currentGameLib = currentGameLib.starts_with("./") ? "." + currentGameLib.substr(6, currentGameLib.size() - 9) + "-save.txt" : "." + currentGameLib.substr(4, currentGameLib.size() - 7) + "-save.txt";
    std::ifstream file(currentGameLib);
    std::istringstream iss;
    std::string line;

    if (!file)
        return;

    std::string type;
    std::string name;

    std::string strX;
    std::string strY;
    std::string strW;
    std::string strH;
    std::string strD;

    std::string strColor;
    std::string text;
    std::string strTextColor;
    std::string imagePath;

    float x = 0;
    float y = 0;
    float w = 0;
    float h = 0;
    float d = 0;

    ARCADE::Color c;
    ARCADE::Color textColor;

    while (std::getline(file, line)) {
        iss.clear();
        iss.str(line);

        iss >> type;
        iss >> name;
        iss >> strX;
        iss >> strY;
        iss >> strW;
        iss >> strH;
        iss >> strD;
        iss >> strColor;
        iss >> text;
        iss >> strTextColor;
        iss >> imagePath;

        x = std::stof(strX);
        y = std::stof(strY);
        w = std::stof(strW);
        h = std::stof(strH);
        d = std::stof(strD);
        c = static_cast<ARCADE::Color>(std::stoi(strColor));
        if (text == "\"\"") {
            text = "";
        } else {
            std::size_t pos = 0;
            while ((pos = text.find("%20", pos)) != std::string::npos) {
                text.replace(pos, 3, " ");
                pos += 1;
            }
        }
        if (imagePath == "\"\"") {
            imagePath = "";
        } else {
            std::size_t pos = 0;
            while ((pos = imagePath.find("%20", pos)) != std::string::npos) {
                imagePath.replace(pos, 3, " ");
                pos += 1;
            }
        }
        textColor = static_cast<ARCADE::Color>(std::stoi(strTextColor));

        if (type == "sprite") {
            this->storeShape(std::move(display->createSprite()), name);
            this->getShapeAs<ARCADE::ISprite>(name).setWidth(w);
            this->getShapeAs<ARCADE::ISprite>(name).setHeight(h);
            this->getShapeAs<ARCADE::ISprite>(name).setImagePath(imagePath);
        } else if (type == "circle") {
            this->storeShape(std::move(display->createCircle()), name);
            this->getShapeAs<ARCADE::ICircle>(name).setDiameter(d);
        } else if (type == "rectangle") {
            this->storeShape(std::move(display->createRectangle()), name);
            this->getShapeAs<ARCADE::IRectangle>(name).setWidth(w);
            this->getShapeAs<ARCADE::IRectangle>(name).setHeight(h);
            this->getShapeAs<ARCADE::IRectangle>(name).setText(text, 20, textColor);
        }
        this->getShape(name)->setPosX(x);
        this->getShape(name)->setPosY(y);
        this->getShape(name)->setColor(c);
    }
    file.close();
}

void ARCADE::GameState::removeGameSaves()
{
    for (auto const& entry : std::filesystem::directory_iterator("."))
    {
        auto const& path = entry.path();
        if (path.has_filename() && path.filename().string().ends_with("-save.txt")) {
            std::filesystem::remove(path);
        }
    }
}

void ARCADE::GameState::storeState(const std::unique_ptr<ARCADE::IShape> &shape, const std::string &name, std::string type)
{
    shapeState state = {.x = shape->getPosX(), .y = shape->getPosY(), .w = 10.0, .h = 10.0, .d = 40.0, .color = shape->getColor(), .text = "", .textColor = shape->getColor(), .imagePath = ""};

    if (type == "sprite") {
        state.w = dynamic_cast<ARCADE::ISprite*>(shape.get())->getWidth();
        state.h = dynamic_cast<ARCADE::ISprite*>(shape.get())->getHeight();
        state.imagePath = dynamic_cast<ARCADE::ISprite*>(shape.get())->getImagePath();
    } else if (type == "circle")
        state.d = dynamic_cast<ARCADE::ICircle*>(shape.get())->getDiameter();
    else if (type == "rectangle") {
        state.w = dynamic_cast<ARCADE::IRectangle*>(shape.get())->getWidth();
        state.h = dynamic_cast<ARCADE::IRectangle*>(shape.get())->getHeight();
        state.text = dynamic_cast<ARCADE::IRectangle*>(shape.get())->getText();
        state.textColor = dynamic_cast<ARCADE::IRectangle*>(shape.get())->getTextColor();
    }
    this->_storage[name] = state;
}

void ARCADE::GameState::storeShape(std::unique_ptr<ARCADE::IShape> shape, const std::string &name)
{
    this->_shapes[name] = std::move(shape);
}

void ARCADE::GameState::removeShape(std::string name)
{
    this->_shapes.erase(name);
    this->_storage.erase(name);

    auto it = std::find(this->_shapeTypes.begin(), this->_shapeTypes.end(), name);
    if (it != this->_shapeTypes.end())
        this->_shapeTypes.erase(it);
}

std::unique_ptr<ARCADE::IShape>& ARCADE::GameState::getShape(const std::string &name)
{
    return this->_shapes.at(name);
}

std::vector<std::string> ARCADE::GameState::getShapes()
{
    std::vector<std::string> names;

    for (auto& [name, shape] : this->_shapes)
        names.push_back(name);
    
    return names;
}

void ARCADE::GameState::saveShapes()
{
    this->_storage.clear();
    this->_shapeTypes.clear();

    for (auto& [name, shape] : this->_shapes) {
        std::string type;

        if (dynamic_cast<ARCADE::ISprite*>(shape.get()))
            type = "sprite";
        else if (dynamic_cast<ARCADE::ICircle*>(shape.get()))
            type = "circle";
        else if (dynamic_cast<ARCADE::IRectangle*>(shape.get()))
            type = "rectangle";
        this->_shapeTypes.push_back(type);
        this->storeState(shape, name, type);
        shape.reset();
    }
    this->_shapes.clear();
}

void ARCADE::GameState::drawAll()
{
    for (auto& [name, shape] : this->_shapes) {
        if (shape)
            shape->draw();
    }
}

void ARCADE::GameState::clear()
{
    if (!this->_shapes.empty())
        this->_shapes.clear();
    if (!this->_storage.empty())
        this->_storage.clear();
    if (!this->_shapeTypes.empty())
        this->_shapeTypes.clear();
}

bool ARCADE::GameState::hasShape(const std::string &name) const
{
    return this->_shapes.find(name) != this->_shapes.end();
}

void ARCADE::GameState::saveScore(std::string currentGameLib, std::string playerName, std::size_t score)
{
    currentGameLib = currentGameLib.starts_with("./") ? "." + currentGameLib.substr(6, currentGameLib.size() - 9) + "-scores.txt" : "." + currentGameLib.substr(4, currentGameLib.size() - 7) + "-scores.txt";

    std::ifstream file(currentGameLib);
    std::vector<std::string> lines;
    std::size_t index = std::string::npos;
    std::string line;
    std::string playerScoreLine = std::format("{}:{}\n", playerName, score);
    std::string strScoreFinded;

    if (file) {

        for (std::size_t i = 0; std::getline(file, line); i++) {
            if (line.starts_with(playerName + ":")) {
                index = i;
                strScoreFinded = line.substr(line.find_first_of(":") + 1, line.size() - (playerName.size() + 1));
                if (static_cast<std::size_t>(std::stoul(strScoreFinded)) >= score)
                    return;
            }
            lines.push_back(line);
        }

        file.close();

        if (index == std::string::npos)
            lines.push_back(playerScoreLine);
        else if (lines.size() > index)
            lines[index] = playerScoreLine;
    } else
        lines.push_back(playerScoreLine);

    this->saveInFile(currentGameLib, lines);
}

void ARCADE::GameState::saveInFile(std::string filePath, std::vector<std::string> &lines)
{
    std::ofstream file(filePath);

    for (auto& l : lines)
        file << l << std::endl;

    file.close();
}
