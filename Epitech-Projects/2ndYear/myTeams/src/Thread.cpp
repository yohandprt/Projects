/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** Thread.cpp
*/

#include "Thread.hpp"

TEAMS::Thread::Thread(std::string author, std::string title, std::string content) : AMessage(author, content)
{
    this->generateUUID();
    this->_authorUuid = author;
    this->_title = title;
}

TEAMS::Thread::Thread(std::string uuid, std::string author, std::string title, std::string content, std::time_t timestamp) : AMessage(author, content)
{
    this->setUUID(uuid);
    this->_authorUuid = author;
    this->_title = title;
    this->setCreatedTime(timestamp);
}

void TEAMS::Thread::createReply(std::string author, std::string content)
{
    this->_replies.push_back(std::make_unique<TEAMS::AMessage>(author, content, time(nullptr)));
}

void TEAMS::Thread::addReply(std::string author, std::string content, std::time_t timestamp)
{
    this->_replies.push_back(std::make_unique<TEAMS::AMessage>(author, content, timestamp));
}

std::string TEAMS::Thread::getTitle() const
{
    return this->_title;
}

std::vector<std::unique_ptr<TEAMS::AMessage>>& TEAMS::Thread::getReplies()
{
    return this->_replies;
}

std::vector<std::string> TEAMS::Thread::getRepliesContents()
{
    std::vector<std::string> contents;

    for (std::size_t i = 0; i < this->_replies.size(); i++)
        contents.push_back(this->_replies[i]->getContent());

    return contents;
}