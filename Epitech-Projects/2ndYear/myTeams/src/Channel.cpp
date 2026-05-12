/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** Channel.cpp
*/

#include "Channel.hpp"

TEAMS::Channel::Channel(std::string author, std::string name, std::string description)
{
    this->generateUUID();
    this->_author = author;
    this->_name = name;
    this->_description = description;
}

TEAMS::Channel::Channel(std::string uuid, std::string author, std::string name, std::string description)
{
    this->setUUID(uuid);
    this->_author = author;
    this->_name = name;
    this->_description = description;
}

void TEAMS::Channel::createThread(std::string author, std::string title, std::string content)
{
    std::string uuid = this->getNewUUID();

    this->_threads.emplace(uuid, std::make_unique<TEAMS::Thread>(author, title, content));
}

std::string TEAMS::Channel::addThread(std::string author, std::string title, std::string content, std::time_t timestamp)
{
    std::string uuid = this->getNewUUID();

    this->_threads.emplace(uuid, std::make_unique<TEAMS::Thread>(uuid, author, title, content, timestamp));
    return uuid;
}

void TEAMS::Channel::addThread(std::string uuid, std::string author, std::string title, std::string content, std::time_t timestamp)
{
    this->_threads.emplace(uuid, std::make_unique<TEAMS::Thread>(uuid, author, title, content, timestamp));
}

std::string TEAMS::Channel::getAuthor() const
{
    return this->_author;
}

std::string TEAMS::Channel::getName() const
{
    return this->_name;
}

std::string TEAMS::Channel::getDescription() const
{
    return this->_description;
}

TEAMS::Thread& TEAMS::Channel::getThread(std::string uuid)
{
    return *this->_threads.at(uuid);
}

std::vector<std::string> TEAMS::Channel::getThreadsUuids()
{
    std::vector<std::string> uuids;
    auto itThread = this->threadBegin();

    for (; itThread != this->threadEnd(); itThread++)
        uuids.push_back(itThread->first);
    
    return uuids;
}

bool TEAMS::Channel::isThreadExist(std::string uuid)
{
    if (this->_threads.find(uuid) != this->_threads.end())
        return true;
    return false;
}

std::map<std::string, std::unique_ptr<TEAMS::Thread>>::iterator& TEAMS::Channel::threadBegin()
{
    this->_itThread = this->_threads.begin();

    return this->_itThread;
}

std::map<std::string, std::unique_ptr<TEAMS::Thread>>::iterator& TEAMS::Channel::threadEnd()
{
    this->_itThread = this->_threads.end();

    return this->_itThread;
}