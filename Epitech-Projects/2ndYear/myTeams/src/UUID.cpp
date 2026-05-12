/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** UUID.cpp
*/

#include "UUID.hpp"
#include "User.hpp"

TEAMS::UUID::UUID()
{
    this->_uuid = this->generate();
}

std::string TEAMS::UUID::generate()
{
    std::stringstream ss;
    std::random_device random;

    ss << "#";

    for (int i = 0; i < 8; i++)
        ss << random() % 10;

    return ss.str();
}

void TEAMS::UUID::read_uuids(std::ifstream &file)
{
    std::string content;

    while ((file >> content))
        this->_uuids.push_back(content);
}

void TEAMS::UUID::load_uuid()
{
    std::ofstream outFile(".uuids.txt", std::ios::app);

    if (!outFile)
        return;
    
    outFile << this->str() << std::endl;
    outFile.close();
}

std::string TEAMS::UUID::str()
{
    return this->_uuid;
}