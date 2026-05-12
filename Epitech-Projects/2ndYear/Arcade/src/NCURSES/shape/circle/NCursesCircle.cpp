/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** NCursesCircle.cpp
*/

#include "NCursesCircle.hpp"
#include <cmath>

void ARCADE::NCursesCircle::initParams()
{
    int screenSizeX;
    int screenSizeY;
    getmaxyx(stdscr, screenSizeY, screenSizeX);

    this->_ndiameter = std::round((this->_d * screenSizeX / 1920));
    this->_nx = std::round((this->_x * screenSizeX / 1920));
    this->_ny = std::round((this->_y * screenSizeY / 1080));
    if (this->_ndiameter < 2)
        this->_ndiameter = 2;
    this->_pair = static_cast<int>(this->_ndiameter) % 2 == 0 ? true : false;
    this->_cutDiameter = this->_pair ? this->_ndiameter / 2 + 2 : (this->_ndiameter - 1) / 2 + 2;
    this->_radius = this->_pair ? this->_cutDiameter / 2 : (this->_cutDiameter - 1) / 2 + 1;
    this->_offset = 0;
}

void ARCADE::NCursesCircle::setLines()
{
    std::size_t firtSize = (this->_pair ? 2 : 3) + (this->_pair ? this->_ndiameter / 4 : (this->_ndiameter - 1) / 4) * 2;
    std::string line(firtSize, '#');

    this->_content.clear();

    if (line.size() > this->_ndiameter) {
        line = line.substr(0, this->_ndiameter);
        for (std::size_t i = 0; i < this->_ndiameter; i++)
            this->_content.push_back(line);
        return;
    }

    for (std::size_t i = 0; i < this->_radius; i++) {
        this->_content.push_back(line);
        line += "##";
    }

    line = line.substr(0, line.size() - 2);

    if (!this->_pair) {
        this->_content.push_back(line);
        this->_offset = 1;
    }

    for (std::size_t i = 0; i < this->_radius; i++) {
        this->_content.push_back(line);
        line = line.substr(0, line.size() - 2);
    }
}

void ARCADE::NCursesCircle::draw()
{
    std::size_t index = 0;

    this->initParams();
    this->setLines();

    std::size_t color = ncursesColors.at(this->_color);
    attron(COLOR_PAIR(color));

    for (; index < this->_radius; index++)
        mvprintw(this->_ny + index, this->_nx + this->_cutDiameter - this->_content[index].size() / 2, "%s", this->_content[index].c_str());

    if (!this->_pair)
        mvprintw(this->_ny + this->_radius, this->_nx + this->_cutDiameter - this->_content[index].size() / 2, "%s", this->_content[index].c_str());

    for (; index < this->_content.size(); index++)
        mvprintw(this->_ny + index + this->_offset, this->_nx + this->_cutDiameter - this->_content[index].size() / 2, "%s", this->_content[index].c_str());
    
    attroff(COLOR_PAIR(color));
}