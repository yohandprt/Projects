/*
** EPITECH PROJECT, 2025
** myTeams
** File description:
** CommandHandler.hpp
*/

#ifndef TEAMS_COMMAND_HANDLER
    #define TEAMS_COMMAND_HANDLER

    #include <iostream>
    #include <functional>
    #include <map>
    #include <sstream>
    #include <algorithm>
    #include <string.h>
    #include <vector>
    #include <fcntl.h>
    #include <unistd.h>
    #include <filesystem>
    #include <format>

    #include "Socket.hpp"
    #include "CommandParser.hpp"
    #include "Helper.hpp"
    #include "Loader.hpp"
    #include "Saver.hpp"

    extern "C" {
        #include "logging_server.h"
    }

namespace TEAMS {

    class User;
    class ServerState;

    extern std::map<std::string, std::unique_ptr<TEAMS::User>> users;

    struct CommandInfo {
        bool needAuth;
        std::size_t nbArgsNeeded;
        std::function<void(TEAMS::ServerState&)> func;
    };

    class CommandHandler
    {
    private:
        TEAMS::Helper _helper;
        TEAMS::CommandParser _cParser;
        TEAMS::Loader _loader;
        TEAMS::Saver _saver;

        std::map<std::string, TEAMS::CommandInfo> _handler;

        std::string _userUuid;
        int _userFd;

        bool _isLogin;

        std::string _teamUuid;
        std::string _channelUuid;
        std::string _threadUuid;

        void noopCommand(TEAMS::ServerState& state);
        void usersCommand(TEAMS::ServerState& state);
        void userInfoCommand(TEAMS::ServerState& state);
        void sendCommand(TEAMS::ServerState& state);
        void loginCommand(TEAMS::ServerState& state);
        void logoutCommand(TEAMS::ServerState& state);
        void subscribeCommand(TEAMS::ServerState& state);
        void subscribedCommand(TEAMS::ServerState& state);
        void unsubscribeCommand(TEAMS::ServerState& state);
        void postCommand(TEAMS::ServerState& state);
        void useCommand(TEAMS::ServerState& state);
        void createCommand(TEAMS::ServerState& state);
        void createTeam(TEAMS::ServerState& state);
        void createChannel(TEAMS::ServerState& state);
        void createThread(TEAMS::ServerState& state);
        void createReply(TEAMS::ServerState& state);
        void listCommand(TEAMS::ServerState& state);
        void infoCommand(TEAMS::ServerState& state);
        void messagesCommand(TEAMS::ServerState& state);
        void helpCommand(TEAMS::ServerState& state);
        bool checkUseArgs(TEAMS::ServerState& state);
    public:
        CommandHandler();
        ~CommandHandler();
        void verifCommand(TEAMS::CommandInfo commandInfo, TEAMS::ServerState& state);
        void handleCommand(std::string userUuid, std::string line, TEAMS::ServerState& state);
    };
}

#endif