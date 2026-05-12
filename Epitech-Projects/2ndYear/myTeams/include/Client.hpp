/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** Client.hpp
*/

#pragma once

#include <iostream>
#include <poll.h>
#include <exception>
#include <vector>

#include "Socket.hpp"
#include "EventClientHandler.hpp"
#include "CommandParser.hpp"

namespace TEAMS {
    class Client : public TEAMS::Socket
    {
    private:
        std::string _ip;
        std::size_t _port;
        std::vector<struct pollfd> _pfds;
        TEAMS::EventClientHandler _eventHandler;
        TEAMS::CommandParser _cParser;
    public:
        Client(std::string ip, std::size_t port);
        ~Client() = default;
        void addFd(int newFd);
        void send(std::string msg);
        void connect();
        void disconnect();
        int run();
        bool checkEvents();
        class ClientError : std::exception
        {
        protected:
            std::string _message;
        public:
            explicit ClientError(const std::string &message) : _message(message) {}

            const char *what(void) const noexcept override { return _message.c_str(); };
        };
    };
}