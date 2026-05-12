/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** NCursesRectangle.cpp
*/

#include "NCursesRectangle.hpp"
#include <cmath>

ARCADE::NCursesRectangle::NCursesRectangle()
: _text(""),
_textColor(ARCADE::Color::White)
{
}

std::string ARCADE::NCursesRectangle::getText() const
{
    return this->_text;
}

ARCADE::Color ARCADE::NCursesRectangle::getTextColor() const
{
    return this->_textColor;
}

void ARCADE::NCursesRectangle::setText(std::string text, std::size_t charactereSize, ARCADE::Color color)
{
    (void)charactereSize;

    this->_text = text;
    this->_textColor = color;
}

bool ARCADE::NCursesRectangle::isMouseHover()
{
    // if (getmouse(&this->mouseEvent) == OK) {

    //     mvprintw(0, 0, "MOUSE: (%d, %d)", this->mouseEvent.x, this->mouseEvent.y);

    //     if (this->mouseEvent.x >= this->_x && this->mouseEvent.y >= this->_y &&
    //         this->mouseEvent.x <= (this->_x + this->_w) && this->mouseEvent.y <= (this->_y + this->_h))
    //         return true;
    // }
    return false;
}

bool ARCADE::NCursesRectangle::isClick()
{
    // if (getmouse(&this->mouseEvent) == OK) {
    //     if (this->isMouseHover() && (this->mouseEvent.bstate & BUTTON1_PRESSED))
    //         return true;
    // }
    return false;
}

void ARCADE::NCursesRectangle::draw()
{
    int screenSizeX;
    int screenSizeY;
    getmaxyx(stdscr, screenSizeY, screenSizeX);

    float x = std::round((this->_x * screenSizeX / 1920));
    float y = std::round((this->_y * screenSizeY / 1080));
    float w = std::round((this->_w * screenSizeX / 1920));
    float h = std::round((this->_h * screenSizeY / 1080));

    if (x < 1.0)
        x = 1.0;
    if (y < 1.0)
        y = 1.0;
    if (w < 1.0)
        w = 1.0;
    if (h < 1.0)
        h = 1.0;

    std::string line(w, '#');

    this->_content.clear();
    for (float i = 0.0; i < h; i++)
        this->_content.push_back(line);

    std::size_t rectColor = ncursesColors.at(this->_color);
    attron(COLOR_PAIR(rectColor));

    for (std::size_t i = 0; i < this->_content.size(); i++)
        mvprintw(y + i, x, "%s", this->_content[i].c_str());

    attroff(COLOR_PAIR(rectColor));

    std::size_t textX = 0;
    std::size_t textY = 0;
    std::size_t textColor = ncursesColors.at(this->_textColor);

    textX = x + ((w - std::strlen(this->_text.c_str())) / 2);

    if (this->_content.size() <= 1)
        textY = y;
    else if (this->_content.size() % 2 == 0)
        textY = y + (this->_content.size() / 2);
    else
        textY = y + ((this->_content.size() - 1) / 2) + 1;

    attron(COLOR_PAIR(textColor));
    mvprintw(textY, textX, "%s", this->_text.c_str());
    attroff(COLOR_PAIR(textColor));
    
    

}