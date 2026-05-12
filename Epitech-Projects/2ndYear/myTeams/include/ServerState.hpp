/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** ServerState.hpp
*/

#pragma once

#include <iostream>
#include <map>
#include <memory>

#include "User.hpp"
#include "Team.hpp"

namespace TEAMS {

    class User;
    class Team;

    class ServerState
    {
    private:
        std::map<std::string, std::unique_ptr<TEAMS::User>> _users;
        std::map<std::string, std::unique_ptr<TEAMS::Team>> _teams;

        std::map<std::string, std::unique_ptr<TEAMS::User>>::iterator _itUser;
        std::map<std::string, std::unique_ptr<TEAMS::Team>>::iterator _itTeam;
        bool _userExist = false;
    public:
        ServerState() = default;
        ~ServerState() = default;

        void createUser(std::string uuid);
        std::string createUser(int userFd);
        void createUser(std::string uuid, int userFd);
        void createTeam(std::string authorUuid, std::string name, std::string description);
        std::string addTeam(std::string authorUuid, std::string name, std::string description);
        void addTeam(std::string uuid, std::string authorUuid, std::string name, std::string description);

        TEAMS::User& getUser(std::string uuid);
        std::map<std::string, std::unique_ptr<TEAMS::User>>::iterator& getUser(int userFd);
        std::unique_ptr<TEAMS::User> getCopyUser(std::string uuid);
        TEAMS::Team& getTeam(std::string uuid);
        std::vector<std::string> getTeamsUuids();

        void replaceUser(std::string uuid, std::unique_ptr<TEAMS::User> newUser);
        void removeUser(std::string uuid);
        void deleteTeam(std::string uuid);

        std::string findUuid(std::string username);

        bool isUserExist(std::string uuid);
        bool isUserFinded();
        bool isTeamExist(std::string uuid);

        std::map<std::string, std::unique_ptr<TEAMS::User>>::iterator& userBegin();
        std::map<std::string, std::unique_ptr<TEAMS::User>>::iterator& userEnd();
        std::map<std::string, std::unique_ptr<TEAMS::Team>>::iterator& teamBegin();
        std::map<std::string, std::unique_ptr<TEAMS::Team>>::iterator& teamEnd();

        void sendToEveryone(std::string msg);
    };
}