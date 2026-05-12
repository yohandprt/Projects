/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** EventClientHandler.cpp
*/

#include "EventClientHandler.hpp"

void TEAMS::EventClientHandler::exec_client_event_logged_in()
{
    std::string user_uuid = this->_cParser.getArgs()[0];
    std::string user_name = this->_cParser.getArgs()[1];

    client_event_logged_in(user_uuid.c_str(), user_name.c_str());
}

void TEAMS::EventClientHandler::exec_client_event_logged_out()
{
    std::string user_uuid = this->_cParser.getArgs()[0];
    std::string user_name = this->_cParser.getArgs()[1];

    client_event_logged_out(user_uuid.c_str(), user_name.c_str());
}

void TEAMS::EventClientHandler::exec_client_event_private_message_received()
{
    std::string user_uuid = this->_cParser.getArgs()[0];
    std::string message_body = this->_cParser.getArgs()[1];

    client_event_private_message_received(user_uuid.c_str(), message_body.c_str());
}

void TEAMS::EventClientHandler::exec_client_event_thread_reply_received()
{
    std::string team_uuid = this->_cParser.getArgs()[0];
    std::string thread_uuid = this->_cParser.getArgs()[1];
    std::string user_uuid = this->_cParser.getArgs()[2];
    std::string reply_body = this->_cParser.getArgs()[3];

    client_event_thread_reply_received(team_uuid.c_str(), thread_uuid.c_str(), user_uuid.c_str(), reply_body.c_str());
}

void TEAMS::EventClientHandler::exec_client_event_team_created()
{
    std::string team_uuid = this->_cParser.getArgs()[0];
    std::string team_name = this->_cParser.getArgs()[1];
    std::string team_description = this->_cParser.getArgs()[2];

    client_event_team_created(team_uuid.c_str(), team_name.c_str(), team_description.c_str());
}

void TEAMS::EventClientHandler::exec_client_event_channel_created()
{
    std::string channel_uuid = this->_cParser.getArgs()[0];
    std::string channel_name = this->_cParser.getArgs()[1];
    std::string channel_description = this->_cParser.getArgs()[2];

    client_event_channel_created(channel_uuid.c_str(), channel_name.c_str(), channel_description.c_str());
}

void TEAMS::EventClientHandler::exec_client_event_thread_created()
{
    std::string thread_uuid = this->_cParser.getArgs()[0];
    std::string user_uuid = this->_cParser.getArgs()[1];
    std::string thread_timestamp = this->_cParser.getArgs()[2];
    std::string thread_title = this->_cParser.getArgs()[3];
    std::string thread_body = this->_cParser.getArgs()[4];

    std::time_t timestamp = std::stoi(thread_timestamp);

    client_event_thread_created(thread_uuid.c_str(), user_uuid.c_str(), timestamp, thread_title.c_str(), thread_body.c_str());
}

void TEAMS::EventClientHandler::exec_client_print_users()
{
    std::string user_uuid = this->_cParser.getArgs()[0];
    std::string user_name = this->_cParser.getArgs()[1];
    std::string user_status = this->_cParser.getArgs()[2];

    client_print_users(user_uuid.c_str(), user_name.c_str(), std::stoi(user_status));
}

void TEAMS::EventClientHandler::exec_client_print_teams()
{
    std::string team_uuid = this->_cParser.getArgs()[0];
    std::string team_name = this->_cParser.getArgs()[1];
    std::string team_description = this->_cParser.getArgs()[2];

    client_print_teams(team_uuid.c_str(), team_name.c_str(), team_description.c_str());
}

void TEAMS::EventClientHandler::exec_client_team_print_channels()
{
    std::string channel_uuid = this->_cParser.getArgs()[0];
    std::string channel_name = this->_cParser.getArgs()[1];
    std::string channel_description = this->_cParser.getArgs()[2];

    client_team_print_channels(channel_uuid.c_str(), channel_name.c_str(), channel_description.c_str());
}

void TEAMS::EventClientHandler::exec_client_channel_print_threads()
{
    std::string thread_uuid = this->_cParser.getArgs()[0];
    std::string user_uuid = this->_cParser.getArgs()[1];
    std::string thread_timestamp = this->_cParser.getArgs()[2];
    std::string thread_title = this->_cParser.getArgs()[3];
    std::string thread_body = this->_cParser.getArgs()[4];

    std::time_t timestamp = std::stoi(thread_timestamp);

    client_channel_print_threads(thread_uuid.c_str(), user_uuid.c_str(), timestamp, thread_title.c_str(), thread_body.c_str());
}

void TEAMS::EventClientHandler::exec_client_thread_print_replies()
{
    std::string thread_uuid = this->_cParser.getArgs()[0];
    std::string user_uuid = this->_cParser.getArgs()[1];
    std::string reply_timestamp = this->_cParser.getArgs()[2];
    std::string reply_body = this->_cParser.getArgs()[3];

    std::time_t timestamp = std::stoi(reply_timestamp);

    client_thread_print_replies(thread_uuid.c_str(), user_uuid.c_str(), timestamp, reply_body.c_str());
}

void TEAMS::EventClientHandler::exec_client_private_message_print_messages()
{
    std::string sender_uuid = this->_cParser.getArgs()[0];
    std::string message_timestamp = this->_cParser.getArgs()[1];
    std::string message_body = this->_cParser.getArgs()[2];

    std::time_t timestamp = std::stoi(message_timestamp);

    client_private_message_print_messages(sender_uuid.c_str(), timestamp, message_body.c_str());
}

void TEAMS::EventClientHandler::exec_client_error_unknown_team()
{
    std::string team_uuid = this->_cParser.getArgs()[0];

    client_error_unknown_team(team_uuid.c_str());
}

void TEAMS::EventClientHandler::exec_client_error_unknown_channel()
{
    std::string channel_uuid = this->_cParser.getArgs()[0];

    client_error_unknown_channel(channel_uuid.c_str());
}

void TEAMS::EventClientHandler::exec_client_error_unknown_thread()
{
    std::string thread_uuid = this->_cParser.getArgs()[0];

    client_error_unknown_thread(thread_uuid.c_str());
}

void TEAMS::EventClientHandler::exec_client_error_unknown_user()
{
    std::string user_uuid = this->_cParser.getArgs()[0];

    client_error_unknown_user(user_uuid.c_str());
}

void TEAMS::EventClientHandler::exec_client_error_unauthorized()
{
    client_error_unauthorized();
}

void TEAMS::EventClientHandler::exec_client_error_already_exist()
{
    client_error_already_exist();
}

void TEAMS::EventClientHandler::exec_client_print_user()
{
    std::string user_uuid = this->_cParser.getArgs()[0];
    std::string user_name = this->_cParser.getArgs()[1];
    std::string user_status = this->_cParser.getArgs()[2];

    client_print_user(user_uuid.c_str(), user_name.c_str(), std::stoi(user_status));
}

void TEAMS::EventClientHandler::exec_client_print_team()
{
    std::string team_uuid = this->_cParser.getArgs()[0];
    std::string team_name = this->_cParser.getArgs()[1];
    std::string team_description = this->_cParser.getArgs()[2];

    client_print_team(team_uuid.c_str(), team_name.c_str(), team_description.c_str());
}

void TEAMS::EventClientHandler::exec_client_print_channel()
{
    std::string channel_uuid = this->_cParser.getArgs()[0];
    std::string channel_name = this->_cParser.getArgs()[1];
    std::string channel_description = this->_cParser.getArgs()[2];

    client_print_channel(channel_uuid.c_str(), channel_name.c_str(), channel_description.c_str());
}

void TEAMS::EventClientHandler::exec_client_print_thread()
{
    std::string thread_uuid = this->_cParser.getArgs()[0];
    std::string user_uuid = this->_cParser.getArgs()[1];
    std::string thread_timestamp = this->_cParser.getArgs()[2];
    std::string thread_title = this->_cParser.getArgs()[3];
    std::string thread_body = this->_cParser.getArgs()[4];

    std::time_t timestamp = std::stoi(thread_timestamp);

    client_print_thread(thread_uuid.c_str(), user_uuid.c_str(), timestamp, thread_title.c_str(), thread_body.c_str());
}

void TEAMS::EventClientHandler::exec_client_print_team_created()
{
    std::string team_uuid = this->_cParser.getArgs()[0];
    std::string team_name = this->_cParser.getArgs()[1];
    std::string team_description = this->_cParser.getArgs()[2];

    client_print_team_created(team_uuid.c_str(), team_name.c_str(), team_description.c_str());
}

void TEAMS::EventClientHandler::exec_client_print_channel_created()
{
    std::string channel_uuid = this->_cParser.getArgs()[0];
    std::string channel_name = this->_cParser.getArgs()[1];
    std::string channel_description = this->_cParser.getArgs()[2];

    client_print_channel_created(channel_uuid.c_str(), channel_name.c_str(), channel_description.c_str());
}

void TEAMS::EventClientHandler::exec_client_print_thread_created()
{
    std::string thread_uuid = this->_cParser.getArgs()[0];
    std::string user_uuid = this->_cParser.getArgs()[1];
    std::string thread_timestamp = this->_cParser.getArgs()[2];
    std::string thread_title = this->_cParser.getArgs()[3];
    std::string thread_body = this->_cParser.getArgs()[4];

    std::time_t timestamp = std::stoi(thread_timestamp);

    client_print_thread_created(thread_uuid.c_str(), user_uuid.c_str(), timestamp, thread_title.c_str(), thread_body.c_str());
}

void TEAMS::EventClientHandler::exec_client_print_reply_created()
{
    std::string thread_uuid = this->_cParser.getArgs()[0];
    std::string user_uuid = this->_cParser.getArgs()[1];
    std::string reply_timestamp = this->_cParser.getArgs()[2];
    std::string reply_body = this->_cParser.getArgs()[3];

    std::time_t timestamp = std::stoi(reply_timestamp);

    client_print_reply_created(thread_uuid.c_str(), user_uuid.c_str(), timestamp, reply_body.c_str());
}

void TEAMS::EventClientHandler::exec_client_print_subscribed()
{
    std::string user_uuid = this->_cParser.getArgs()[0];
    std::string team_uuid = this->_cParser.getArgs()[1];

    client_print_subscribed(user_uuid.c_str(), team_uuid.c_str());
}

void TEAMS::EventClientHandler::exec_client_print_unsubscribed()
{
    std::string user_uuid = this->_cParser.getArgs()[0];
    std::string team_uuid = this->_cParser.getArgs()[1];

    client_print_unsubscribed(user_uuid.c_str(), team_uuid.c_str());
}

bool TEAMS::EventClientHandler::verifEvent(TEAMS::EventInfo eventInfo)
{
    if (eventInfo.nbArgsNeeded != std::string::npos && eventInfo.nbArgsNeeded != this->_cParser.getNbArgs())
        return false;
    else
        eventInfo.func();
    return true;
}

bool TEAMS::EventClientHandler::handleEvent(std::string line)
{
    this->_cParser.setLine(line);

    this->_handler = {
        {"CLIENT_EVENT_LOGGED_IN", {2, [this]() {return TEAMS::EventClientHandler::exec_client_event_logged_in();}}},
        {"CLIENT_EVENT_LOGGED_OUT", {2, [this]() {return TEAMS::EventClientHandler::exec_client_event_logged_out();}}},
        {"CLIENT_EVENT_PRIVATE_MESSAGE_RECEIVED", {2, [this]() {return TEAMS::EventClientHandler::exec_client_event_private_message_received();}}},
        {"CLIENT_EVENT_THREAD_REPLY_RECEIVED", {4, [this]() {return TEAMS::EventClientHandler::exec_client_event_thread_reply_received();}}},
        {"CLIENT_EVENT_TEAM_CREATED", {3, [this]() {return TEAMS::EventClientHandler::exec_client_event_team_created();}}},
        {"CLIENT_EVENT_CHANNEL_CREATED", {3, [this]() {return TEAMS::EventClientHandler::exec_client_event_channel_created();}}},
        {"CLIENT_EVENT_THREAD_CREATED", {5, [this]() {return TEAMS::EventClientHandler::exec_client_event_thread_created();}}},
        {"CLIENT_PRINT_USERS", {3, [this]() {return TEAMS::EventClientHandler::exec_client_print_users();}}},
        {"CLIENT_PRINT_TEAMS", {3, [this]() {return TEAMS::EventClientHandler::exec_client_print_teams();}}},
        {"CLIENT_TEAM_PRINT_CHANNELS", {3, [this]() {return TEAMS::EventClientHandler::exec_client_team_print_channels();}}},
        {"CLIENT_CHANNEL_PRINT_THREADS", {5, [this]() {return TEAMS::EventClientHandler::exec_client_channel_print_threads();}}},
        {"CLIENT_THREAD_PRINT_REPLIES", {4, [this]() {return TEAMS::EventClientHandler::exec_client_thread_print_replies();}}},
        {"CLIENT_PRIVATE_MESSAGE_PRINT_MESSAGES", {3, [this]() {return TEAMS::EventClientHandler::exec_client_private_message_print_messages();}}},
        {"CLIENT_ERROR_UNKNOWN_TEAM", {1, [this]() {return TEAMS::EventClientHandler::exec_client_error_unknown_team();}}},
        {"CLIENT_ERROR_UNKNOWN_CHANNEL", {1, [this]() {return TEAMS::EventClientHandler::exec_client_error_unknown_channel();}}},
        {"CLIENT_ERROR_UNKNOWN_THREAD", {1, [this]() {return TEAMS::EventClientHandler::exec_client_error_unknown_thread();}}},
        {"CLIENT_ERROR_UNKNOWN_USER", {1, [this]() {return TEAMS::EventClientHandler::exec_client_error_unknown_user();}}},
        {"CLIENT_ERROR_UNAUTHORIZED", {0, [this]() {return TEAMS::EventClientHandler::exec_client_error_unauthorized();}}},
        {"CLIENT_ERROR_ALREADY_EXIST", {0, [this]() {return TEAMS::EventClientHandler::exec_client_error_already_exist();}}},
        {"CLIENT_PRINT_USER", {3, [this]() {return TEAMS::EventClientHandler::exec_client_print_user();}}},
        {"CLIENT_PRINT_TEAM", {3, [this]() {return TEAMS::EventClientHandler::exec_client_print_team();}}},
        {"CLIENT_PRINT_CHANNEL", {3, [this]() {return TEAMS::EventClientHandler::exec_client_print_channel();}}},
        {"CLIENT_PRINT_THREAD", {5, [this]() {return TEAMS::EventClientHandler::exec_client_print_thread();}}},
        {"CLIENT_PRINT_TEAM_CREATED", {3, [this]() {return TEAMS::EventClientHandler::exec_client_print_team_created();}}},
        {"CLIENT_PRINT_CHANNEL_CREATED", {3, [this]() {return TEAMS::EventClientHandler::exec_client_print_channel_created();}}},
        {"CLIENT_PRINT_THREAD_CREATED", {5, [this]() {return TEAMS::EventClientHandler::exec_client_print_thread_created();}}},
        {"CLIENT_PRINT_REPLY_CREATED", {4, [this]() {return TEAMS::EventClientHandler::exec_client_print_reply_created();}}},
        {"CLIENT_PRINT_SUBSCRIBED", {2, [this]() {return TEAMS::EventClientHandler::exec_client_print_subscribed();}}},
        {"CLIENT_PRINT_UNSUBSCRIBED", {2, [this]() {return TEAMS::EventClientHandler::exec_client_print_unsubscribed();}}},
    };

    if (this->_cParser.getCommand().empty())
        return false;

    auto itHandler = this->_handler.find(this->_cParser.getCommand());

    if (itHandler != this->_handler.end())
        return this->verifEvent(this->_handler.at(this->_cParser.getCommand()));
    return false;
}