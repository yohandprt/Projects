/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** IMessage.hpp
*/

#pragma once

#include <iostream>
#include <ctime>

namespace TEAMS {
    class IMessage
    {
    public:
        virtual ~IMessage() = default;

        virtual std::string getContent() = 0;
        virtual std::time_t getCreatedTime() = 0;
        virtual std::string getAuthor() = 0;

        virtual void setCreatedTime(std::time_t timestamp) = 0;
    };
}