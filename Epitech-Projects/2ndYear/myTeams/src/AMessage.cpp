/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** AMessage.cpp
*/

#include "AMessage.hpp"

TEAMS::AMessage::AMessage(std::string authorUuid, std::string content)
{
    this->_authorUuid = authorUuid;
    this->_content = content;
}

TEAMS::AMessage::AMessage(std::string authorUuid, std::string content, std::time_t createdTime)
{
    this->_authorUuid = authorUuid;
    this->_content = content;
    this->_createdTime = createdTime;
}

std::string TEAMS::AMessage::getContent()
{
    return this->_content;
}

std::time_t TEAMS::AMessage::getCreatedTime()
{
    return this->_createdTime;
}

std::string TEAMS::AMessage::getAuthor()
{
    return this->_authorUuid;
}

void TEAMS::AMessage::setCreatedTime(std::time_t timestamp)
{
    this->_createdTime = timestamp;
}