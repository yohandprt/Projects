/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** Loader.hpp
*/

#pragma once

#include "User.hpp"
#include "ServerState.hpp"
#include "CommandParser.hpp"

extern "C" {
    #include "logging_server.h"
}

#include <memory>

namespace TEAMS {
    class Loader
    {
    private:
        TEAMS::CommandParser _cParser;
    public:
        Loader() = default;
        ~Loader() = default;

        void loadUsers(TEAMS::ServerState& state);
        void loadUser(std::string &userUuid, std::string username, TEAMS::ServerState& state);
        void loadBackup(TEAMS::ServerState& state);
        void loadTeam(TEAMS::ServerState& state);
        void loadChannel(TEAMS::ServerState& state);
        void loadThread(TEAMS::ServerState& state);
        void loadReply(TEAMS::ServerState& state);
        void loadPrivateMessages(TEAMS::ServerState& state);
    };
}