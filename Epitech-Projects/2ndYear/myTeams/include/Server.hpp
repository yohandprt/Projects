/*
** EPITECH PROJECT, 2025
** myTeams
** File description:
** Server.hpp
*/

#ifndef TEAMS_SERVER
    #define TEAMS_SERVER

    #include "Socket.hpp"
    #include "ServerState.hpp"
    #include "CommandHandler.hpp"
    #include "Loader.hpp"
    #include "Saver.hpp"

    extern "C" {
        #include "logging_server.h"
    }
    
    #include <poll.h>
    #include <iostream>
    #include <vector>
    #include <memory>
    #include <map>
    #include <fstream>
    #include <format>

namespace TEAMS {

    class User;

    extern std::map<std::string, std::unique_ptr<TEAMS::User>> users;

    class Server : public TEAMS::Socket
    {
    private:
        TEAMS::Loader _loader;
        TEAMS::Saver _saver;
        TEAMS::ServerState _state;
        std::vector<struct pollfd> _pfds;
        std::map<int, std::unique_ptr<TEAMS::CommandHandler>> _handlers;
    public:
        Server(std::size_t port);
        ~Server() = default;
        void run();
        void addFd(int newFd);
        void newConnection();
        void disconnection(std::size_t &index);
        bool checkCommand(User &user, std::string line);
        void checkEvents();
        class ServerError : public std::exception
        {
        protected:
            std::string _message;

        public:
            explicit ServerError(const std::string &message) : _message(message) {}

            const char *what(void) const noexcept override { return _message.c_str(); };
        };
        
    };
}

#endif
