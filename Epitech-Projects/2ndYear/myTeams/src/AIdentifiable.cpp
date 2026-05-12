/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** AIdentifiable.cpp
*/

#include "AIdentifiable.hpp"
#include "Server.hpp"

TEAMS::AIdentifiable::AIdentifiable() : _uuid("")
{
}

std::string TEAMS::AIdentifiable::getUUID()
{
    return this->_uuid;
}

std::string TEAMS::AIdentifiable::getNewUUID()
{
    return this->_uuidGenerator.generate();
}

void TEAMS::AIdentifiable::generateUUID()
{
    this->_uuid = this->_uuidGenerator.str();
}

void TEAMS::AIdentifiable::setUUID(std::string uuid)
{
    this->_uuid = uuid;
}