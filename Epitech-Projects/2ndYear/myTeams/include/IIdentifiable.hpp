/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** IIdentifiable.hpp
*/

#pragma once

#include <iostream>

namespace TEAMS {
    class IIdentifiable
    {
    public:
        virtual ~IIdentifiable() = default;

        virtual std::string getUUID() = 0;
        virtual std::string getNewUUID() = 0;
        virtual void generateUUID() = 0;
        virtual void setUUID(std::string uuid) = 0;
    };    
}