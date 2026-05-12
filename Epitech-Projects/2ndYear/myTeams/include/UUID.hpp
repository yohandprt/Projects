/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** UUID.hpp
*/

#pragma once

#include <random>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <memory>

namespace TEAMS {

    class UUID
    {
    private:
        std::string _uuid;
        std::vector<std::string> _uuids;
    public:
        UUID();
        ~UUID() = default;

        std::string generate();
        void read_uuids(std::ifstream &file);
        void load_uuid();
        std::string str();
    };
}