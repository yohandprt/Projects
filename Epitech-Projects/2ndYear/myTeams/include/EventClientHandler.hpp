/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** EventClientHandler.hpp
*/

#pragma once

#include "CommandParser.hpp"

extern "C" {
    #include "logging_client.h"
}

#include <map>
#include <functional>
#include <sstream>
#include <ctime>

namespace TEAMS {

    struct EventInfo {
        std::size_t nbArgsNeeded;
        std::function<void()> func;
    };

    class EventClientHandler
    {
    private:
        TEAMS::CommandParser _cParser;
        std::map<std::string, TEAMS::EventInfo> _handler;
        std::istringstream _iss;
    public:
        EventClientHandler() = default;
        ~EventClientHandler() = default;

        void exec_client_event_logged_in();
        void exec_client_event_logged_out();
        void exec_client_event_private_message_received();
        void exec_client_event_thread_reply_received();
        void exec_client_event_team_created();
        void exec_client_event_channel_created();
        void exec_client_event_thread_created();
        void exec_client_print_users();
        void exec_client_print_teams();
        void exec_client_team_print_channels();
        void exec_client_channel_print_threads();
        void exec_client_thread_print_replies();
        void exec_client_private_message_print_messages();
        void exec_client_error_unknown_team();
        void exec_client_error_unknown_channel();
        void exec_client_error_unknown_thread();
        void exec_client_error_unknown_user();
        void exec_client_error_unauthorized();
        void exec_client_error_already_exist();
        void exec_client_print_user();
        void exec_client_print_team();
        void exec_client_print_channel();
        void exec_client_print_thread();
        void exec_client_print_team_created();
        void exec_client_print_channel_created();
        void exec_client_print_thread_created();
        void exec_client_print_reply_created();
        void exec_client_print_subscribed();
        void exec_client_print_unsubscribed();

        bool verifEvent(TEAMS::EventInfo eventInfo);
        bool handleEvent(std::string line);
    };    
}