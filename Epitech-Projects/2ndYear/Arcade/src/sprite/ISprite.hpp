/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** ISprite.hpp
*/

#pragma once

#include "ARectangle.hpp"

namespace ARCADE {
    class ISprite : public ARCADE::ARectangle
    {
    public:
        ISprite() = default;
        ~ISprite() = default;

        virtual std::string getImagePath() const = 0;
        virtual void setImagePath(std::string imagePath) = 0;
    };
}