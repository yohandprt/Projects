/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** SfmlCircle.hpp
*/

#pragma once

#include "ACircle.hpp"
#include "ArcadeSfml.hpp"

#include <SFML/Graphics.hpp>

namespace ARCADE {
    class SfmlCircle : public ACircle
    {
    private:
        sf::RenderWindow &_window;
        sf::CircleShape _circle;
    public:
        SfmlCircle(sf::RenderWindow &window);
        ~SfmlCircle() = default;

        void draw() override;
    };
}