/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** ServerState.cpp
*/

#include "ServerState.hpp"
#include "User.hpp"
#include "Team.hpp"

void TEAMS::ServerState::createUser(std::string uuid)
{
    this->_users.emplace(uuid, std::make_unique<TEAMS::User>(uuid));
}

std::string TEAMS::ServerState::createUser(int userFd)
{
    TEAMS::User user(userFd);
    std::string uuid = user.getNewUUID();

    this->_users.emplace(uuid, std::make_unique<TEAMS::User>(uuid, userFd));
    return uuid;
}

void TEAMS::ServerState::createUser(std::string uuid, int userFd)
{
    this->_users.emplace(uuid, std::make_unique<TEAMS::User>(uuid, userFd));
}

void TEAMS::ServerState::createTeam(std::string authorUuid, std::string name, std::string description)
{
    TEAMS::Team team(authorUuid, name, description);
    std::string uuid = team.getNewUUID();

    this->_teams.emplace(uuid, std::make_unique<TEAMS::Team>(uuid, authorUuid, name, description));
    this->getUser(authorUuid).subscribe(uuid);
}

std::string TEAMS::ServerState::addTeam(std::string authorUuid, std::string name, std::string description)
{
    TEAMS::Team team(authorUuid, name, description);
    std::string uuid = team.getNewUUID();

    this->_teams.emplace(uuid, std::make_unique<TEAMS::Team>(uuid, authorUuid, name, description));
    this->getUser(authorUuid).subscribe(uuid);
    return uuid;
}

void TEAMS::ServerState::addTeam(std::string uuid, std::string authorUuid, std::string name, std::string description)
{
    this->_teams.emplace(uuid, std::make_unique<TEAMS::Team>(uuid, authorUuid, name, description));
}

TEAMS::User& TEAMS::ServerState::getUser(std::string uuid)
{
    return *this->_users.at(uuid);
}

std::map<std::string, std::unique_ptr<TEAMS::User>>::iterator& TEAMS::ServerState::getUser(int userFd)
{
    this->_itUser = std::find_if(this->_users.begin(), this->_users.end(), [userFd](auto &it) {
        return it.second->getFd() == userFd;
    });

    if (this->_itUser != this->_users.end())
        this->_userExist = true;
    else
        this->_userExist = false;

    return this->_itUser;
}

std::unique_ptr<TEAMS::User> TEAMS::ServerState::getCopyUser(std::string uuid)
{
    return std::move(this->_users.at(uuid));
}

TEAMS::Team& TEAMS::ServerState::getTeam(std::string uuid)
{
    return *this->_teams.at(uuid);
}

std::vector<std::string> TEAMS::ServerState::getTeamsUuids()
{
    std::vector<std::string> uuids;
    auto itTeam = this->teamBegin();

    for (; itTeam != this->teamEnd(); itTeam++)
        uuids.push_back(itTeam->first);
    
    return uuids;
}

void TEAMS::ServerState::replaceUser(std::string uuid, std::unique_ptr<TEAMS::User> newUser)
{
    this->_users[uuid] = std::move(newUser);
}

void TEAMS::ServerState::removeUser(std::string uuid)
{
    this->_users.erase(uuid);
}

void TEAMS::ServerState::deleteTeam(std::string uuid)
{
    this->_teams.erase(uuid);
}

std::string TEAMS::ServerState::findUuid(std::string username)
{
    auto itUser = this->userBegin();

    for (; itUser != this->userEnd(); itUser++) {
        if (itUser->second->getUsername() == username)
            return itUser->first;
    }
    return "";
}

bool TEAMS::ServerState::isUserExist(std::string uuid)
{
    if (this->_users.find(uuid) != this->_users.end())
        return true;
    return false;
}

bool TEAMS::ServerState::isUserFinded()
{
    return this->_userExist;
}

bool TEAMS::ServerState::isTeamExist(std::string uuid)
{
    if (this->_teams.find(uuid) != this->_teams.end())
        return true;
    return false;
}

std::map<std::string, std::unique_ptr<TEAMS::User>>::iterator& TEAMS::ServerState::userBegin()
{
    this->_itUser = this->_users.begin();

    return this->_itUser;
}

std::map<std::string, std::unique_ptr<TEAMS::User>>::iterator& TEAMS::ServerState::userEnd()
{
    this->_itUser = this->_users.end();

    return this->_itUser;
}

std::map<std::string, std::unique_ptr<TEAMS::Team>>::iterator& TEAMS::ServerState::teamBegin()
{
    this->_itTeam = this->_teams.begin();

    return this->_itTeam;
}

std::map<std::string, std::unique_ptr<TEAMS::Team>>::iterator& TEAMS::ServerState::teamEnd()
{
    this->_itTeam = this->_teams.end();

    return this->_itTeam;
}

void TEAMS::ServerState::sendToEveryone(std::string msg)
{
    auto itUser = this->userBegin();

    for (; itUser != this->userEnd(); itUser++) {
        if (itUser->second->isConnected())
            itUser->second->send(msg);
    }
}