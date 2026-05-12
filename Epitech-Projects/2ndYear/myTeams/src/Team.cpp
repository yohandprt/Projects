/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** Team.cpp
*/

#include "Team.hpp"

TEAMS::Team::Team(std::string author, std::string name, std::string description)
{
    this->generateUUID();
    this->_author = author;
    this->_name = name;
    this->_description = description;
}

TEAMS::Team::Team(std::string uuid, std::string author, std::string name, std::string description)
{
    this->setUUID(uuid);
    this->_author = author;
    this->_name = name;
    this->_description = description;
}

std::string TEAMS::Team::getAuthor() const
{
    return this->_author;
}

std::string TEAMS::Team::getName() const
{
    return this->_name;
}

std::string TEAMS::Team::getDescription() const
{
    return this->_description;
}


void TEAMS::Team::createChannel(std::string author, std::string name, std::string description)
{
    std::string uuid = this->getNewUUID();

    this->_channels.emplace(uuid, std::make_unique<TEAMS::Channel>(uuid, author, name, description));
}

std::string TEAMS::Team::addChannel(std::string author, std::string name, std::string description)
{
    std::string uuid = this->getNewUUID();

    this->_channels.emplace(uuid, std::make_unique<TEAMS::Channel>(uuid, author, name, description));

    return uuid;
}

void TEAMS::Team::addChannel(std::string uuid, std::string author, std::string name, std::string description)
{
    this->_channels.emplace(uuid, std::make_unique<TEAMS::Channel>(uuid, author, name, description));
}

TEAMS::Channel& TEAMS::Team::getChannel(std::string uuid)
{
    return *this->_channels.at(uuid);
}

std::vector<std::string> TEAMS::Team::getChannelsUuids()
{
    std::vector<std::string> uuids;
    auto itChannel = this->channelBegin();

    for (; itChannel != this->channelEnd(); itChannel++)
        uuids.push_back(itChannel->first);

    return uuids;
}

bool TEAMS::Team::isChannelExist(std::string uuid)
{
    if (this->_channels.find(uuid) != this->_channels.end())
        return true;
    return false;
}

std::map<std::string, std::unique_ptr<TEAMS::Channel>>::iterator& TEAMS::Team::channelBegin()
{
    this->_itChannel = this->_channels.begin();

    return this->_itChannel;
}

std::map<std::string, std::unique_ptr<TEAMS::Channel>>::iterator& TEAMS::Team::channelEnd()
{
    this->_itChannel = this->_channels.end();

    return this->_itChannel;
}