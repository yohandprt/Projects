/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Rectangle.cpp
*/

#include "SfmlRectangle.hpp"

ARCADE::SfmlRectangle::SfmlRectangle(sf::RenderWindow &window) : _window(window)
{
    this->_rectangle = sf::RectangleShape();

    this->_w = 20.0;
    this->_h = 20.0;

    this->_rectangle.setPosition(sf::Vector2f(this->_x, this->_y));
    this->_rectangle.setSize(sf::Vector2f(this->_w, this->_h));
    this->_rectangle.setFillColor(ARCADE::sfmlColors.at(this->_color));

    this->_font.loadFromFile("assets/fonts/font.otf");
    this->_text.setFont(this->_font);
    this->_text.setString("");
    this->_text.setFillColor(sf::Color::Green);
}

std::string ARCADE::SfmlRectangle::getText() const
{
    return this->_text.getString();
}

ARCADE::Color ARCADE::SfmlRectangle::getTextColor() const
{
    sf::Color color = this->_text.getFillColor();

    for (auto& [aColor, sColor] : sfmlColors) {
        if (color == sColor)
            return aColor;
    }
    return ARCADE::Color::Red;
}

void ARCADE::SfmlRectangle::setText(std::string text, std::size_t charactereSize, ARCADE::Color color)
{
    this->_text.setString(text);
    this->_text.setCharacterSize(charactereSize);
    this->_text.setFillColor(sfmlColors[color]);
}

bool ARCADE::SfmlRectangle::isMouseHover()
{
    sf::Vector2i pos = sf::Mouse::getPosition(this->_window);

    if (pos.x >= this->_x && pos.y >= this->_y &&
        pos.x <= (this->_x + this->_w) && pos.y <= (this->_y + this->_h))
        return true;
    return false;
}

bool ARCADE::SfmlRectangle::isClick()
{
    if (this->isMouseHover() && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        return true;
    return false;
}

void ARCADE::SfmlRectangle::draw()
{
    this->_rectangle.setPosition(sf::Vector2f(this->_x, this->_y));
    this->_rectangle.setFillColor(ARCADE::sfmlColors.at(this->_color));
    this->_rectangle.setSize(sf::Vector2f(this->_w, this->_h));

    this->_textShape = this->_text.getLocalBounds();
    this->_text.setPosition(
        this->_x + (this->_w - this->_textShape.width) / 2,
        this->_y + (this->_h - this->_textShape.height) / 2 - this->_textShape.top
    );

    this->_window.draw(this->_rectangle);
    this->_window.draw(this->_text);
}