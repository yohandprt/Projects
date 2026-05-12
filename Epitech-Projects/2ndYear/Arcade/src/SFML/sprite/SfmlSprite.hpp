/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** SfmlSprite.hpp
*/

#pragma once

#include "ISprite.hpp"

#include <SFML/Graphics.hpp>

namespace ARCADE {
    class SfmlSprite : public ARCADE::ISprite
    {
    private:
        sf::RenderWindow &_window;
        sf::Texture _texture;
        sf::Sprite _sprite;
        sf::Vector2u _textureSize;
        std::string _imagePath;
    public:
        SfmlSprite(sf::RenderWindow &window);
        ~SfmlSprite() = default;

        std::string getImagePath() const override;
        void setImagePath(std::string imagePath) override;
        void draw() override;
    };
}