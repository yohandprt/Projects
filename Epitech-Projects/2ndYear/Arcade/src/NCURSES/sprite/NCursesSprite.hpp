/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** NCursesSprite.hpp
*/

#pragma once

#include "ISprite.hpp"
#include "NCursesRectangle.hpp"

namespace ARCADE {
    class NCursesRectangle;
    class NCursesSprite : public ARCADE::ISprite
    {
    private:
        std::unique_ptr<ARCADE::NCursesRectangle> _rectMaker;
        std::string _imagePath;
    public:
        NCursesSprite();
        ~NCursesSprite() = default;

        std::string getImagePath() const override;
        void setImagePath(std::string imagePath) override;
        void draw() override;
    };
}