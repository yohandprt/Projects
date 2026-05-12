/*
** EPITECH PROJECT, 2025
** myTeams
** File description:
** User.cpp
*/

#include "User.hpp"
#include "CommandHandler.hpp"

TEAMS::User::User(std::string uuid) : _connect(false), _username("")
{
    this->setUUID(uuid);
}

TEAMS::User::User(int fd) : _fd(fd), _connect(false), _username("")
{
    this->generateUUID();
}

TEAMS::User::User(std::string uuid, int fd) : _connect(false), _username("")
{
    this->setUUID(uuid);
    this->_fd = fd;
}

void TEAMS::User::send(std::string msg)
{
    if (msg.ends_with("\n") && !msg.ends_with("\r\n"))
        msg = msg.substr(0, msg.size() - 1);
    dprintf(this->_fd, "%s\r\n", msg.c_str());
}

std::string TEAMS::User::getCurrentCommand()
{
    std::size_t eol = this->_command.find("\r\n");

    if (eol == std::string::npos || eol + 2 == this->_command.size())
        return this->_command;
    else {
        std::string firstCommand = this->_command.substr(0, eol + 2);
        return firstCommand;
    }
}

int TEAMS::User::getFd()
{
    return this->_fd;
}

std::string TEAMS::User::getUsername()
{
    return this->_username;
}

std::vector<std::unique_ptr<TEAMS::AMessage>>& TEAMS::User::getMessages(std::string userUuid)
{
    return this->_convs.at(userUuid);
}

std::vector<std::string>& TEAMS::User::getSubTeams()
{
    return this->_teams;
}

void TEAMS::User::setUsername(std::string username)
{
    this->_username = username;
}

void TEAMS::User::setFd(int newFd)
{
    this->_fd = newFd;
}

void TEAMS::User::addMessage(std::string authorUuid, std::string destUuid, std::string content, std::time_t createdTime)
{
    this->_convs[destUuid].push_back(std::make_unique<TEAMS::AMessage>(authorUuid, content, createdTime));
}

void TEAMS::User::addCommandPart(std::string part)
{
    this->_command += part;
}

void TEAMS::User::resetCommand()
{
    std::size_t eol = this->getCurrentCommand().find("\r\n");

    if (eol != std::string::npos) {
        if (eol + 2 >= this->_command.size())
            this->_command.clear();
        else
            this->_command = this->_command.substr(eol + 2, this->_command.size());
    }
}

void TEAMS::User::connection()
{
    this->_connect = true;
}

void TEAMS::User::disconnection()
{
    this->_connect = false;
}

void TEAMS::User::subscribe(std::string teamUuid)
{
    if (std::find(this->_teams.begin(), this->_teams.end(), teamUuid) == this->_teams.end())
        this->_teams.push_back(teamUuid);
}

void TEAMS::User::unsubscribe(std::string teamUuid)
{
    this->_teams.erase(std::remove(this->_teams.begin(), this->_teams.end(), teamUuid), this->_teams.end());
}

bool TEAMS::User::isSubscribed(const std::string& teamUuid) const
{
    if (std::find(this->_teams.begin(), this->_teams.end(), teamUuid) != this->_teams.end())
        return true;
    return false;
}

bool TEAMS::User::isConvExist(std::string userUuid)
{
    if (this->_convs.find(userUuid) != this->_convs.end())
        return true;
    return false;
}

bool TEAMS::User::isConnected()
{
    return this->_connect;
}