/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** Saver.hpp
*/

#pragma once

#include "User.hpp"
#include "ServerState.hpp"

#include <format>

namespace TEAMS {
    class Saver
    {
    private:
    public:
        Saver() = default;
        ~Saver() = default;

        void saveInFile(std::string filePath, std::vector<std::string> &lines);
        std::string formatUserLine(std::string userUuid, std::unique_ptr<TEAMS::User>& user);
        void saveUser(std::string userUuid, std::unique_ptr<TEAMS::User>& user);
        void saveBackup(TEAMS::ServerState& state);
        void saveTeam(TEAMS::ServerState& state, std::vector<std::string>& backupLines);
        void saveChannel(TEAMS::ServerState& state, std::vector<std::string>& backupLines, std::string teamUuid);
        void saveThread(TEAMS::ServerState& state, std::vector<std::string>& backupLines, std::string teamUuid, std::string channelUuid);
        void saveReply(TEAMS::ServerState& state, std::vector<std::string>& backupLines, std::string teamUuid, std::string channelUuid, std::string threadUuid);
        void savePrivateMessages(TEAMS::ServerState& state, std::vector<std::string>& backupLines);
    };
}