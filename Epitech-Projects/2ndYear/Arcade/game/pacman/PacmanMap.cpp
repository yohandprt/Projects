/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** PacmanMap.cpp
*/

#include "PacmanMap.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

// Consomme une case (dot/powerdot) et la remplace par une case vide.
ARCADE::TileType ARCADE::PacmanMap::eatTile(int x, int y)
{
    if (!this->isInside(x, y))
        return ARCADE::TileType::Empty;
    ARCADE::TileType result = this->_tiles[y][x];
    if (static_cast<std::size_t>(y) < this->_rawRows.size() &&
        static_cast<std::size_t>(x) < this->_rawRows[y].size()) {
        this->_rawRows[y][x] = ' ';
    }
    this->_tiles[y][x] = ARCADE::TileType::Empty;
    return result;
}

// Charge une map depuis un fichier puis delegue le parsing a loadFromData.
void ARCADE::PacmanMap::loadFromFile(const std::string &path)
{
    std::ifstream file(path);
    std::stringstream buffer;

    if (!file)
        throw std::runtime_error("PacmanMap: cannot open map file: " + path);
    buffer << file.rdbuf();
    this->loadFromData(buffer.str());
}

// Parse le texte de map et construit la grille logique (_tiles) et les lignes brutes (_rawRows).
void ARCADE::PacmanMap::loadFromData(const std::string &mapData)
{
    std::istringstream stream(mapData);
    std::string line;

    this->_rawRows.clear();
    this->_tiles.clear();
    this->_playerSpawn = {0, 0};
    this->_width = 0;
    this->_height = 0;
    while (std::getline(stream, line)) {
        if (line.size() > this->_width)
            this->_width = line.size();
        this->_rawRows.push_back(line);
    }
    this->_height = this->_rawRows.size();
    this->_tiles.assign(this->_height, std::vector<ARCADE::TileType>(this->_width, ARCADE::TileType::Empty));
    for (std::size_t row = 0; row < this->_rawRows.size(); row++) {
        const std::string &raw = this->_rawRows[row];
        for (std::size_t col = 0; col < raw.size(); col++)
            this->_tiles[row][col] = this->parseTile(raw[col], col, row);
    }
}

// Retourne la largeur max de la map en tuiles.
std::size_t ARCADE::PacmanMap::getWidth() const
{
    return this->_width;
}

// Retourne la hauteur de la map en tuiles.
std::size_t ARCADE::PacmanMap::getHeight() const
{
    return this->_height;
}

// Retourne le type d'une case; hors map est considere comme un mur.
ARCADE::TileType ARCADE::PacmanMap::getTile(int x, int y) const
{
    if (!this->isInside(x, y))
        return ARCADE::TileType::Wall;
    return this->_tiles[static_cast<std::size_t>(y)][static_cast<std::size_t>(x)];
}

// Indique si une case est un mur.
bool ARCADE::PacmanMap::isWall(int x, int y) const
{
    return this->getTile(x, y) == ARCADE::TileType::Wall;
}

// Verifie si des coordonnees sont dans les bornes de la grille.
bool ARCADE::PacmanMap::isInside(int x, int y) const
{
    if (x < 0 || y < 0)
        return false;
    if (this->_tiles.empty())
        return false;
    if (static_cast<std::size_t>(y) >= this->_tiles.size())
        return false;
    if (this->_tiles[static_cast<std::size_t>(y)].empty())
        return false;
    if (static_cast<std::size_t>(x) >= this->_tiles[static_cast<std::size_t>(y)].size())
        return false;
    return true;
}

// Retourne la position de spawn du joueur detectee au parsing.
ARCADE::Position ARCADE::PacmanMap::getPlayerSpawn() const
{
    return this->_playerSpawn;
}

// Retourne la version texte brute de la map.
const std::vector<std::string> &ARCADE::PacmanMap::getRawRows() const
{
    return this->_rawRows;
}

// Convertit un caractere de map en TileType et capture les positions speciales.
ARCADE::TileType ARCADE::PacmanMap::parseTile(char c, std::size_t x, std::size_t y)
{
    switch (c) {
        case '#':
            return ARCADE::TileType::Wall;
        case '.':
            return ARCADE::TileType::Dot;
        case 'o':
            return ARCADE::TileType::PowerDot;
        case 'P':
            this->_playerSpawn = {static_cast<int>(x), static_cast<int>(y)};
            return ARCADE::TileType::PlayerSpawn;
        case 'G':
            return ARCADE::TileType::GhostSpawn;
        case '-':
            return ARCADE::TileType::Wall;
        case ' ':
            return ARCADE::TileType::Empty;
        default:
            return ARCADE::TileType::Empty;
    }
}

// Retourne toutes les positions de spawn des fantomes presentes sur la map.
std::vector<ARCADE::Position> ARCADE::PacmanMap::getGhostSpawns() const
{
    std::vector<ARCADE::Position> spawns;
    for (std::size_t y = 0; y < _tiles.size(); y++) {
        for (std::size_t x = 0; x < _tiles[y].size(); x++) {
            if (_tiles[y][x] == ARCADE::TileType::GhostSpawn)
                spawns.push_back({static_cast<int>(x), static_cast<int>(y)});
        }
    }
    return spawns;
}

// Compte le nombre total de dots encore presents (normaux + power dots).
int ARCADE::PacmanMap::getTotalDots() const
{
    int dots = 0;
    for (std::size_t y = 0; y < _tiles.size(); y++) {
        for (std::size_t x = 0; x < _tiles[y].size(); x++) {
            if (_tiles[y][x] == ARCADE::TileType::Dot || _tiles[y][x] == ARCADE::TileType::PowerDot)
                dots++;
        }
    }
    return dots;
}