/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** arcade_sfml.cpp
*/

#include "ArcadeSfml.hpp"

extern "C" std::unique_ptr<ARCADE::IModule> entryPoint()
{
    return std::make_unique<ARCADE::SFML>();
}

void ARCADE::SFML::init()
{
    this->_window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "SFML", sf::Style::Fullscreen);
};

void ARCADE::SFML::stop()
{
    this->_window->close();
}

bool ARCADE::SFML::isOpen()
{
    return this->_window->isOpen();
}

bool ARCADE::SFML::pollEvent()
{
    bool poll = this->_window->pollEvent(this->_event);

    if (!poll)
        return false;

    if (this->_event.type == sf::Event::Closed || this->isKeyPressed("esc")) {
        this->close();
        return false;
    }
    return poll;
}

void ARCADE::SFML::close()
{
    this->stop();
}

void ARCADE::SFML::clear()
{
    this->_window->clear();
}

void ARCADE::SFML::display()
{
    this->_window->display();
}

std::size_t ARCADE::SFML::getWindowSizeX() const
{
    return this->_window->getSize().x;
}

std::size_t ARCADE::SFML::getWindowSizeY() const
{
    return this->_window->getSize().y;
}

bool ARCADE::SFML::isKeyPressed(std::string key)
{
    if (!ARCADE::sfmlKeys.contains(key))
        return false;
    if (this->_event.type == sf::Event::KeyPressed) {
        if (this->_event.key.code == ARCADE::sfmlKeys.at(key))
            return true;
    }
    return false;
}

std::string ARCADE::SFML::getKeyPressed()
{
    if (this->_event.type == sf::Event::TextEntered) {
        sf::Uint32 letter = this->_event.text.unicode;

        if (letter < 128) {
            char c = static_cast<char>(letter);

            if (std::isalnum(static_cast<unsigned char>(c)))
                return std::string(1, c);
        }
    }
    return "";
}

std::unique_ptr<ARCADE::IRectangle> ARCADE::SFML::createRectangle()
{
    return std::make_unique<ARCADE::SfmlRectangle>(*this->_window);
}

std::unique_ptr<ARCADE::ICircle> ARCADE::SFML::createCircle()
{
    return std::make_unique<ARCADE::SfmlCircle>(*this->_window);
}

std::unique_ptr<ARCADE::IRectangle> ARCADE::SFML::createSprite()
{
    return std::make_unique<ARCADE::SfmlSprite>(*this->_window);
}