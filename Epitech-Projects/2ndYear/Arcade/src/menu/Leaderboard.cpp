/*
** EPITECH PROJECT, 2025
** G-OOP-400-LIL-4-1-arcade-16
** File description:
** Leaderboard.cpp
*/

#include "Leaderboard.hpp"

void ARCADE::Leaderboard::initCoords(std::unique_ptr<ARCADE::ADisplayModule>& display)
{
    this->_width = display->getWindowSizeX() / 4;
    this->_height = 30.0;
    this->_leftX = display->getWindowSizeX() / 2;
    this->_rightX = this->_leftX + this->_width;
    this->_leftPosY = display->getWindowSizeY() / 4;
    this->_rightPosY = display->getWindowSizeY() / 4;
    this->_leftNameY = this->_leftPosY - (this->_height * 4);
    this->_rightNameY = this->_rightPosY - (this->_height * 4);
}

void ARCADE::Leaderboard::findScoreFiles()
{
    for (const auto& entry : std::filesystem::directory_iterator(".")) {
        if (entry.path().string().ends_with("-scores.txt"))
            this->_scoreFiles.push_back(entry.path().string());
    }
}

void ARCADE::Leaderboard::loadPlayers()
{
    std::string line;
    std::string playerName;
    std::string strScore;
    std::size_t score;

    (void)score;

    for (std::size_t i = 0; i < this->_scoreFiles.size(); i++) {
        std::ifstream file(this->_scoreFiles[i]);

        while (std::getline(file, line)) {
            playerName = line.substr(0, line.find_first_of(":"));
            strScore = line.substr(line.find_first_of(":") + 1, line.size() - line.find_first_of(":"));

            if (playerName.empty() || strScore.empty())
                continue;
        
            for (char c : strScore) {
                if (c < '0' || c > '9')
                    continue;
            }

            score = static_cast<std::size_t>(std::stoul(strScore));
            this->_players.push_back({this->_scoreFiles[i].substr(3, this->_scoreFiles[i].size() - 14) + ":" + playerName, score});
        }
    }
}

void ARCADE::Leaderboard::display(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state)
{
    this->findScoreFiles();
    this->loadPlayers();
    this->initCoords(display);

    std::string gameName;
    std::string endGamePath;
    std::string player;
    std::string strPlayer;
    std::size_t index;
    std::size_t i = 0;
    std::size_t posPlayerLeft = 1;
    std::size_t posPlayerRight = 1;

    std::sort(this->_players.begin(), this->_players.end(), [](const auto& a, const auto& b) {return a.second > b.second;});

    for (const auto& [playerName, score] : this->_players) {
        gameName = playerName.substr(0, playerName.find_first_of(":"));
        endGamePath = gameName + "-scores.txt";
        player = playerName.substr(playerName.find_first_of(":") + 1, playerName.size() - playerName.find_first_of(":") + 1);
        index = std::distance(this->_scoreFiles.begin(), std::find_if(this->_scoreFiles.begin(), this->_scoreFiles.end(), [&endGamePath](const std::string& gamePath) {return gamePath.ends_with(endGamePath);}));

        if (index == 0) {
            strPlayer = std::format("{}. {}        {}", posPlayerLeft, player, score);
            this->displayLeft(display, state, gameName, this->_leftNameY, std::string::npos - 1);
            this->displayLeft(display, state, strPlayer, this->_leftPosY, i);
            this->_leftPosY += this->_height;
            posPlayerLeft++;
        } else if (index == 1) {
            strPlayer = std::format("{}. {}        {}", posPlayerRight, player, score);
            this->displayRight(display, state, gameName, this->_rightNameY, std::string::npos);
            this->displayRight(display, state, strPlayer, this->_rightPosY, i);
            this->_rightPosY += this->_height;
            posPlayerRight++;
        } else
            continue;
        i++;
    }
}

void ARCADE::Leaderboard::displayLeft(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state, std::string strPlayer, float posY, std::size_t i)
{
    std::string playerIdx = "LBplayer" + std::to_string(i);
    state.storeShape(std::move(display->createRectangle()), playerIdx);
    state.getShapeAs<ARCADE::IRectangle>(playerIdx).setPosX(this->_leftX);
    state.getShapeAs<ARCADE::IRectangle>(playerIdx).setPosY(posY);
    state.getShapeAs<ARCADE::IRectangle>(playerIdx).setWidth(this->_width);
    state.getShapeAs<ARCADE::IRectangle>(playerIdx).setHeight(this->_height);
    state.getShapeAs<ARCADE::IRectangle>(playerIdx).setColor(ARCADE::Color::Black);
    state.getShapeAs<ARCADE::IRectangle>(playerIdx).setText(strPlayer, this->_height, ARCADE::Color::White);
}

void ARCADE::Leaderboard::displayRight(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state, std::string strPlayer, float posY, std::size_t i)
{
    std::string playerIdx = "LBplayer" + std::to_string(i);
    state.storeShape(std::move(display->createRectangle()), playerIdx);
    state.getShapeAs<ARCADE::IRectangle>(playerIdx).setPosX(this->_rightX);
    state.getShapeAs<ARCADE::IRectangle>(playerIdx).setPosY(posY);
    state.getShapeAs<ARCADE::IRectangle>(playerIdx).setWidth(this->_width);
    state.getShapeAs<ARCADE::IRectangle>(playerIdx).setHeight(this->_height);
    state.getShapeAs<ARCADE::IRectangle>(playerIdx).setColor(ARCADE::Color::Black);
    state.getShapeAs<ARCADE::IRectangle>(playerIdx).setText(strPlayer, this->_height, ARCADE::Color::White);
}