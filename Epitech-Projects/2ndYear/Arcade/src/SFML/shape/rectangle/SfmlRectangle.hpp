/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** SfmlRectangle.hpp
*/

#pragma once

#include "ARectangle.hpp"
#include "ArcadeSfml.hpp"

#include <SFML/Graphics.hpp>

namespace ARCADE {
    class SfmlRectangle : public ARectangle
    {
    private:
        sf::RenderWindow &_window;
        sf::RectangleShape _rectangle;
        sf::FloatRect _textShape;
        sf::Font _font;
        sf::Text _text;
    public:
        SfmlRectangle(sf::RenderWindow &window);
        ~SfmlRectangle() = default;

        std::string getText() const override;
        ARCADE::Color getTextColor() const override;
        void setText(std::string text, std::size_t charactereSize, ARCADE::Color color) override;

        bool isMouseHover() override;
        bool isClick() override;

        void draw() override;
    };
    
}