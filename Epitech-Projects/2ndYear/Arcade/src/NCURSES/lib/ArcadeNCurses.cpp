/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** ArcadeNCurses.cpp
*/

#include "ArcadeNCurses.hpp"

extern "C" std::unique_ptr<ARCADE::IModule> entryPoint()
{
    return std::make_unique<ARCADE::NCURSES>();
}

void ARCADE::NCURSES::init()
{
    initscr();
    cbreak();
    start_color();
    assume_default_colors(-1, -1);
    start_color();
    init_pair(1, COLOR_BLACK, -1);
    init_pair(2, COLOR_WHITE, -1);
    init_pair(3, COLOR_RED, -1);
    init_pair(4, COLOR_GREEN, -1);
    init_pair(5, COLOR_BLUE, -1);
    init_pair(6, COLOR_YELLOW, -1);
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    // mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    // printf("\033[?1003h\n");
    // curs_set(0);
};

void ARCADE::NCURSES::stop()
{
    endwin();
    // printf("\033[?1003l");
}

ARCADE::NCURSES::NCURSES() : _maxX(1920), _maxY(1080)
{
    this->_isOpen = true;
    this->_ch = -1;
    // getmaxyx(stdscr, this->_maxX, this->_maxY);
}

bool ARCADE::NCURSES::isOpen()
{
    return this->_isOpen;
}

bool ARCADE::NCURSES::pollEvent()
{
    this->_ch = getch();

    if (this->_ch == -1)
        return false;

    if (this->_ch == ncursesKeys.at("esc")) {
        this->close();
        return false;
    }
    return true;
}

void ARCADE::NCURSES::close()
{
    this->_isOpen = false;
}

void ARCADE::NCURSES::clear()
{
    ::clear();
}

void ARCADE::NCURSES::display()
{
    ::refresh();
    napms(16);
}

std::size_t ARCADE::NCURSES::getWindowSizeX() const
{
    return this->_maxX;
}

std::size_t ARCADE::NCURSES::getWindowSizeY() const
{
    return this->_maxY;
}

bool ARCADE::NCURSES::isKeyPressed(std::string key)
{
    if (!ARCADE::ncursesKeys.contains(key))
        return false;
    return (this->_ch == ARCADE::ncursesKeys.at(key));
}

std::string ARCADE::NCURSES::getKeyPressed()
{
    if (std::isalnum(static_cast<unsigned char>(this->_ch)))
        return std::string(1, static_cast<char>(this->_ch));
    return "";
}

std::unique_ptr<ARCADE::IRectangle> ARCADE::NCURSES::createRectangle()
{
    return std::make_unique<ARCADE::NCursesRectangle>();
}

std::unique_ptr<ARCADE::ICircle> ARCADE::NCURSES::createCircle()
{
    return std::make_unique<ARCADE::NCursesCircle>();
}

std::unique_ptr<ARCADE::IRectangle> ARCADE::NCURSES::createSprite()
{
    return std::make_unique<ARCADE::NCursesSprite>();
}