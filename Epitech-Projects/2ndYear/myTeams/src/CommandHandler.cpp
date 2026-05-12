/*
** EPITECH PROJECT, 2025
** myTeams
** File description:
** CommandHandler.cpp
*/

#include "CommandHandler.hpp"
#include "User.hpp"
#include "ServerState.hpp"

TEAMS::CommandHandler::CommandHandler()
{
    this->_isLogin = false;
}

void TEAMS::CommandHandler::noopCommand(TEAMS::ServerState& state)
{
    (void)state;
    this->_helper.send(this->_userFd, "800 Command okay.");
}

void TEAMS::CommandHandler::usersCommand(TEAMS::ServerState& state)
{
    std::string message;
    std::map<std::string, std::unique_ptr<TEAMS::User>>::iterator it = state.userBegin();

    for (; it != state.userEnd(); it++) {
        if (it->second->getUsername().empty())
            continue;
        message += std::format("client_print_users \"{}\" \"{}\" \"{}\"", it->second->getUUID(), it->second->getUsername(), static_cast<std::size_t>(it->second->isConnected()));
        message += "\n";
    }

    state.getUser(this->_userUuid).send(message);
    this->_helper.send(this->_userFd, "800 Command okay.");
}

void TEAMS::CommandHandler::sendCommand(TEAMS::ServerState& state)
{
    std::string destUuid = this->_cParser.getArgs()[0];
    std::string message = this->_cParser.getArgs()[1];

    if (!state.isUserExist(destUuid)) {
        state.getUser(this->_userUuid).send(std::format("client_error_unknown_user \"{}\"", destUuid));
        return this->_helper.send(this->_userFd, "604 Not found. The requested resource does not exist.");
    }

    state.getUser(destUuid).send(std::format("client_event_private_message_received \"{}\" \"{}\"", this->_userUuid, message));

    state.getUser(this->_userUuid).addMessage(this->_userUuid, destUuid, message, time(nullptr));
    state.getUser(destUuid).addMessage(this->_userUuid, this->_userUuid, message, time(nullptr));

    this->_saver.saveBackup(state);

    server_event_private_message_sended(this->_userUuid.c_str(), destUuid.c_str(), message.c_str());

    this->_helper.send(this->_userFd, "800 Command okay.");
}

void TEAMS::CommandHandler::loginCommand(TEAMS::ServerState& state)
{
    std::string username = this->_cParser.getArgs()[0];
    std::string userUuid = state.findUuid(username);
    bool isNew = userUuid.empty();

    if (userUuid == this->_userUuid)
        return this->_helper.send(this->_userFd, "701 User is already logged in.");

    if (isNew) {
        if (this->_isLogin) {
            state.removeUser(this->_userUuid);
            this->_userUuid = state.createUser(this->_userFd);
        } else
            state.createUser(this->_userUuid, this->_userFd);
        state.getUser(this->_userUuid).setUsername(username);
    } else {
        state.removeUser(this->_userUuid);
        this->_userUuid = userUuid;
        state.getUser(this->_userUuid).setFd(this->_userFd);
    }

    state.getUser(this->_userUuid).connection();
    this->_isLogin = true;

    if (isNew)
        server_event_user_created(this->_userUuid.c_str(), username.c_str());
    server_event_user_logged_in(this->_userUuid.c_str());

    std::string message = std::format("client_event_logged_in \"{}\" \"{}\"", this->_userUuid, username);
    state.sendToEveryone(message);
    this->_helper.send(this->_userFd, "700 User logged in.");
}

void TEAMS::CommandHandler::logoutCommand(TEAMS::ServerState& state)
{
    server_event_user_logged_out(this->_userUuid.c_str());
    std::string message = std::format("client_event_logged_out \"{}\" \"{}\"", this->_userUuid, state.getUser(this->_userUuid).getUsername());
    this->_helper.send(this->_userFd, "821 Service closing connection.");
    state.getUser(this->_userUuid).send(message);
    state.getUser(this->_userUuid).disconnection();
    this->_isLogin = false;
    shutdown(this->_userFd, SHUT_RDWR);
}

void TEAMS::CommandHandler::subscribeCommand(TEAMS::ServerState& state)
{
    std::string teamUuid = this->_cParser.getArgs()[0];

    if (!state.isTeamExist(teamUuid)) {
        state.getUser(this->_userUuid).send(std::format("client_error_unknown_team \"{}\"", teamUuid));
        return this->_helper.send(this->_userFd, "604 Not found. The requested resource does not exist.");
    }

    if (state.getUser(this->_userUuid).isSubscribed(teamUuid))
        return this->_helper.send(this->_userFd, "609 Conflict. Resource already exists.");

    state.getUser(this->_userUuid).subscribe(teamUuid);

    server_event_user_subscribed(teamUuid.c_str(), this->_userUuid.c_str());

    state.getUser(this->_userUuid).send(
        std::format("client_print_subscribed \"{}\" \"{}\"", this->_userUuid, teamUuid));

    this->_helper.send(this->_userFd, "800 Command okay.");
}

void TEAMS::CommandHandler::postCommand(TEAMS::ServerState& state)
{
    std::string teamUuid = this->_cParser.getArgs()[0];
    std::string message = this->_cParser.getArgs()[1];
    std::map<std::string, std::unique_ptr<TEAMS::User>>::iterator it = state.userBegin();

    if (!state.isTeamExist(teamUuid))
        return this->_helper.send(this->_userFd, "604 Not found. The requested resource does not exist.");

    for (; it != state.userEnd(); it++) {
        if (it->second->isSubscribed(teamUuid) && it->first != this->_userUuid)
            it->second->send(message);
    }

    this->_helper.send(this->_userFd, "800 Command okay.");
}

void TEAMS::CommandHandler::useCommand(TEAMS::ServerState& state)
{
    (void)state;

    this->_teamUuid.clear();
    this->_channelUuid.clear();
    this->_threadUuid.clear();

    if (this->_cParser.getNbArgs() >= 1)
        this->_teamUuid = this->_cParser.getArgs()[0];
    if (this->_cParser.getNbArgs() >= 2)
        this->_channelUuid = this->_cParser.getArgs()[1];
    if (this->_cParser.getNbArgs() >= 3)
        this->_threadUuid = this->_cParser.getArgs()[2];

    this->_helper.send(this->_userFd, "800 Command okay.");
}

void TEAMS::CommandHandler::createTeam(TEAMS::ServerState& state)
{
    const std::string& name = this->_cParser.getArgs()[0];
    const std::string& desc = this->_cParser.getArgs()[1];

    std::string teamUuid = state.addTeam(this->_userUuid, name, desc);

    server_event_team_created(teamUuid.c_str(), name.c_str(), this->_userUuid.c_str());

    std::string eventMsg = std::format("client_event_team_created \"{}\" \"{}\" \"{}\"", teamUuid, name, desc);
    auto it = state.userBegin();
    for (; it != state.userEnd(); it++) {
        if (it->second->isConnected() && it->first != this->_userUuid)
            it->second->send(eventMsg);
    }

    state.getUser(this->_userUuid).send(
        std::format("client_print_team_created \"{}\" \"{}\" \"{}\"", teamUuid, name, desc));
    this->_helper.send(this->_userFd, "801 Resource created successfully.");
}

void TEAMS::CommandHandler::createChannel(TEAMS::ServerState& state)
{
    const std::string& name = this->_cParser.getArgs()[0];
    const std::string& desc = this->_cParser.getArgs()[1];

    std::string channelUuid = state.getTeam(this->_teamUuid).addChannel(this->_userUuid, name, desc);

    server_event_channel_created(this->_teamUuid.c_str(), channelUuid.c_str(), name.c_str());

    std::string eventMsg = std::format("client_event_channel_created \"{}\" \"{}\" \"{}\"", channelUuid, name, desc);
    auto it = state.userBegin();
    for (; it != state.userEnd(); it++) {
        if (it->second->isConnected() && it->second->isSubscribed(this->_teamUuid) && it->first != this->_userUuid)
            it->second->send(eventMsg);
    }

    state.getUser(this->_userUuid).send(
        std::format("client_print_channel_created \"{}\" \"{}\" \"{}\"", channelUuid, name, desc));
    this->_helper.send(this->_userFd, "801 Resource created successfully.");
}

void TEAMS::CommandHandler::createThread(TEAMS::ServerState& state)
{
    const std::string& title = this->_cParser.getArgs()[0];
    const std::string& body  = this->_cParser.getArgs()[1];
    std::time_t timestamp = time(nullptr);
    std::string threadUuid = state.getTeam(this->_teamUuid)
                                 .getChannel(this->_channelUuid)
                                 .addThread(this->_userUuid, title, body, timestamp);

    server_event_thread_created(this->_channelUuid.c_str(), threadUuid.c_str(), this->_userUuid.c_str(), title.c_str(), body.c_str());

    std::string eventMsg = std::format("client_event_thread_created \"{}\" \"{}\" \"{}\" \"{}\" \"{}\"",
        threadUuid, this->_userUuid, timestamp, title, body);
    auto it = state.userBegin();
    for (; it != state.userEnd(); it++) {
        if (it->second->isConnected() && it->second->isSubscribed(this->_teamUuid) && it->first != this->_userUuid)
            it->second->send(eventMsg);
    }

    state.getUser(this->_userUuid).send(std::format(
        "client_print_thread_created \"{}\" \"{}\" \"{}\" \"{}\" \"{}\"",
        threadUuid, this->_userUuid, timestamp, title, body));
    this->_helper.send(this->_userFd, "801 Resource created successfully.");
}

void TEAMS::CommandHandler::createReply(TEAMS::ServerState& state)
{
    const std::string& body = this->_cParser.getArgs()[0];
    std::time_t timestamp = time(nullptr);
    state.getTeam(this->_teamUuid)
         .getChannel(this->_channelUuid)
         .getThread(this->_threadUuid)
         .addReply(this->_userUuid, body, timestamp);

    server_event_reply_created(this->_threadUuid.c_str(), this->_userUuid.c_str(), body.c_str());

    std::string eventMsg = std::format("client_event_thread_reply_received \"{}\" \"{}\" \"{}\" \"{}\"",
        this->_teamUuid, this->_threadUuid, this->_userUuid, body);
    auto it = state.userBegin();
    for (; it != state.userEnd(); it++) {
        if (it->second->isConnected() && it->second->isSubscribed(this->_teamUuid) && it->first != this->_userUuid)
            it->second->send(eventMsg);
    }

    state.getUser(this->_userUuid).send(std::format(
        "client_print_reply_created \"{}\" \"{}\" \"{}\" \"{}\"",
        this->_threadUuid, this->_userUuid, timestamp, body));
    this->_helper.send(this->_userFd, "801 Resource created successfully.");
}

void TEAMS::CommandHandler::createCommand(TEAMS::ServerState& state)
{
    if (!this->checkUseArgs(state))
        return;

    if (this->_teamUuid.empty())
        this->createTeam(state);
    else if (this->_channelUuid.empty())
        this->createChannel(state);
    else if (this->_threadUuid.empty())
        this->createThread(state);
    else
        this->createReply(state);

    this->_saver.saveBackup(state);
}

void TEAMS::CommandHandler::listCommand(TEAMS::ServerState& state)
{
    if (!this->checkUseArgs(state))
        return;

    std::string message;

    if (this->_teamUuid.empty()) {
        auto it = state.teamBegin();
        for (; it != state.teamEnd(); it++)
            message += std::format("client_print_teams \"{}\" \"{}\" \"{}\"\n", it->second->getUUID(), it->second->getName(), it->second->getDescription());
    } else if (this->_channelUuid.empty()) {
        auto it = state.getTeam(this->_teamUuid).channelBegin();
        for (; it != state.getTeam(this->_teamUuid).channelEnd(); it++)
            message += std::format("client_team_print_channels \"{}\" \"{}\" \"{}\"\n", it->second->getUUID(), it->second->getName(), it->second->getDescription());
    } else if (this->_threadUuid.empty()) {
        auto it = state.getTeam(this->_teamUuid).getChannel(this->_channelUuid).threadBegin();
        for (; it != state.getTeam(this->_teamUuid).getChannel(this->_channelUuid).threadEnd(); it++)
            message += std::format("client_channel_print_threads \"{}\" \"{}\" \"{}\" \"{}\" \"{}\"\n", it->second->getUUID(), it->second->getAuthor(), it->second->getCreatedTime(), it->second->getTitle(), it->second->getContent());
    } else {
        auto& replies = state.getTeam(this->_teamUuid).getChannel(this->_channelUuid).getThread(this->_threadUuid).getReplies();
        for (std::size_t i = 0; i < replies.size(); i++)
            message += std::format("client_thread_print_replies \"{}\" \"{}\" \"{}\" \"{}\"\n", this->_threadUuid, replies[i]->getAuthor(), replies[i]->getCreatedTime(), replies[i]->getContent());
    }

    state.getUser(this->_userUuid).send(message);
}

void TEAMS::CommandHandler::messagesCommand(TEAMS::ServerState& state)
{
    std::string message;

    if (!state.isUserExist(this->_cParser.getArgs()[0])) {
        state.getUser(this->_userUuid).send(std::format("client_error_unknown_user \"{}\"", this->_cParser.getArgs()[0]));
        return this->_helper.send(this->_userFd, "604 Not found. The requested resource does not exist.");
    }

    if (state.getUser(this->_userUuid).isConvExist(this->_cParser.getArgs()[0])) {
        auto& msgs = state.getUser(this->_userUuid).getMessages(this->_cParser.getArgs()[0]);

        for (std::size_t i = 0; i < msgs.size(); i++) {
            message += std::format("client_private_message_print_messages \"{}\" \"{}\" \"{}\"", msgs[i]->getAuthor(), msgs[i]->getCreatedTime(), msgs[i]->getContent());
            message += "\n";
        }
    }

    if (!message.empty())
        state.getUser(this->_userUuid).send(message);
    this->_helper.send(this->_userFd, "800 Command okay.");
}

void TEAMS::CommandHandler::userInfoCommand(TEAMS::ServerState& state)
{
    std::string uuid = this->_cParser.getArgs()[0];

    if (!state.isUserExist(uuid)) {
        state.getUser(this->_userUuid).send(std::format("client_error_unknown_user \"{}\"", uuid));
        return this->_helper.send(this->_userFd, "604 Not found. The requested resource does not exist.");
    }

    auto& u = state.getUser(uuid);
    state.getUser(this->_userUuid).send(std::format(
        "client_print_user \"{}\" \"{}\" \"{}\"",
        uuid, u.getUsername(), static_cast<std::size_t>(u.isConnected())));
    this->_helper.send(this->_userFd, "800 Command okay.");
}

void TEAMS::CommandHandler::subscribedCommand(TEAMS::ServerState& state)
{
    std::string message;

    if (this->_cParser.getNbArgs() == 0) {
        auto it = state.teamBegin();
        for (; it != state.teamEnd(); it++) {
            if (state.getUser(this->_userUuid).isSubscribed(it->first))
                message += std::format("client_print_teams \"{}\" \"{}\" \"{}\"\n",
                    it->first, it->second->getName(), it->second->getDescription());
        }
    } else {
        std::string teamUuid = this->_cParser.getArgs()[0];

        if (!state.isTeamExist(teamUuid)) {
            state.getUser(this->_userUuid).send(std::format("client_error_unknown_team \"{}\"", teamUuid));
            return this->_helper.send(this->_userFd, "604 Not found. The requested resource does not exist.");
        }

        auto it = state.userBegin();
        for (; it != state.userEnd(); it++) {
            if (it->second->getUsername().empty()) continue;
            if (it->second->isSubscribed(teamUuid))
                message += std::format("client_print_users \"{}\" \"{}\" \"{}\"\n",
                    it->first, it->second->getUsername(),
                    static_cast<std::size_t>(it->second->isConnected()));
        }
    }

    state.getUser(this->_userUuid).send(message);
    this->_helper.send(this->_userFd, "800 Command okay.");
}

void TEAMS::CommandHandler::unsubscribeCommand(TEAMS::ServerState& state)
{
    std::string teamUuid = this->_cParser.getArgs()[0];

    if (!state.isTeamExist(teamUuid)) {
        state.getUser(this->_userUuid).send(std::format("client_error_unknown_team \"{}\"", teamUuid));
        return this->_helper.send(this->_userFd, "604 Not found. The requested resource does not exist.");
    }

    if (!state.getUser(this->_userUuid).isSubscribed(teamUuid))
        return this->_helper.send(this->_userFd, "609 Conflict. Resource already exists.");

    state.getUser(this->_userUuid).unsubscribe(teamUuid);

    server_event_user_unsubscribed(teamUuid.c_str(), this->_userUuid.c_str());

    state.getUser(this->_userUuid).send(
        std::format("client_print_unsubscribed \"{}\" \"{}\"", this->_userUuid, teamUuid));
    this->_helper.send(this->_userFd, "800 Command okay.");
}

void TEAMS::CommandHandler::infoCommand(TEAMS::ServerState& state)
{
    if (!this->checkUseArgs(state))
        return;

    if (!this->_threadUuid.empty()) {
        auto& thread = state.getTeam(this->_teamUuid)
                            .getChannel(this->_channelUuid)
                            .getThread(this->_threadUuid);
        state.getUser(this->_userUuid).send(std::format(
            "client_print_thread \"{}\" \"{}\" \"{}\" \"{}\" \"{}\"",
            this->_threadUuid, thread.getAuthor(), thread.getCreatedTime(),
            thread.getTitle(), thread.getContent()));
    } else if (!this->_channelUuid.empty()) {
        auto& ch = state.getTeam(this->_teamUuid).getChannel(this->_channelUuid);
        state.getUser(this->_userUuid).send(std::format(
            "client_print_channel \"{}\" \"{}\" \"{}\"",
            this->_channelUuid, ch.getName(), ch.getDescription()));
    } else if (!this->_teamUuid.empty()) {
        auto& team = state.getTeam(this->_teamUuid);
        state.getUser(this->_userUuid).send(std::format(
            "client_print_team \"{}\" \"{}\" \"{}\"",
            this->_teamUuid, team.getName(), team.getDescription()));
    } else {
        auto& u = state.getUser(this->_userUuid);
        state.getUser(this->_userUuid).send(std::format(
            "client_print_user \"{}\" \"{}\" \"{}\"",
            this->_userUuid, u.getUsername(),
            static_cast<std::size_t>(u.isConnected())));
    }
}

void TEAMS::CommandHandler::helpCommand(TEAMS::ServerState& state)
{
    (void)state;
    this->_helper.send(this->_userFd,
        "/login \"user_name\"\n"
        "/logout\n"
        "/users\n"
        "/user \"user_uuid\"\n"
        "/send \"user_uuid\" \"message_body\"\n"
        "/messages \"user_uuid\"\n"
        "/subscribe \"team_uuid\"\n"
        "/subscribed [\"team_uuid\"]\n"
        "/unsubscribe \"team_uuid\"\n"
        "/use [\"team_uuid\" [\"channel_uuid\" [\"thread_uuid\"]]]\n"
        "/create ...\n"
        "/list\n"
        "/info\n"
        "814 Help message listing available commands.");
}

bool TEAMS::CommandHandler::checkUseArgs(TEAMS::ServerState& state)
{
    if (!this->_teamUuid.empty() && !state.isTeamExist(this->_teamUuid)) {
        state.getUser(this->_userUuid).send(std::format("client_error_unknown_team \"{}\"", this->_teamUuid));
        this->_helper.send(this->_userFd, "604 Not found. The requested resource does not exist.");
        return false;
    } else if (!this->_channelUuid.empty() && !state.getTeam(this->_teamUuid).isChannelExist(this->_channelUuid)) {
        state.getUser(this->_userUuid).send(std::format("client_error_unknown_channel \"{}\"", this->_channelUuid));
        this->_helper.send(this->_userFd, "604 Not found. The requested resource does not exist.");
        return false;
    } else if (!this->_threadUuid.empty() && !state.getTeam(this->_teamUuid).getChannel(this->_channelUuid).isThreadExist(this->_threadUuid)) {
        state.getUser(this->_userUuid).send(std::format("client_error_unknown_thread \"{}\"", this->_threadUuid));
        this->_helper.send(this->_userFd, "604 Not found. The requested resource does not exist.");
        return false;
    }
    return true;
}

void TEAMS::CommandHandler::verifCommand(TEAMS::CommandInfo commandInfo, TEAMS::ServerState& state)
{
    if (commandInfo.needAuth && !this->_isLogin) {
        this->_helper.send(this->_userFd, "client_error_unauthorized");
        this->_helper.send(this->_userFd, "601 Unauthorized. User not logged in.");
    } else if (commandInfo.nbArgsNeeded != std::string::npos && commandInfo.nbArgsNeeded != this->_cParser.getNbArgs())
        this->_helper.send(this->_userFd, "600 Bad request. missing argument.");
    else
        commandInfo.func(state);
}

void TEAMS::CommandHandler::handleCommand(std::string userUuid, std::string line, TEAMS::ServerState& state)
{
    this->_userUuid = userUuid;
    this->_userFd = state.getUser(this->_userUuid).getFd();
    this->_cParser.setLine(line);
    this->_handler = {
        {"/NOOP",        {false, 0,                  [this](TEAMS::ServerState& ss) {return CommandHandler::noopCommand(ss);}}},
        {"/USERS",       {true,  0,                  [this](TEAMS::ServerState& ss) {return CommandHandler::usersCommand(ss);}}},
        {"/USER",        {true,  1,                  [this](TEAMS::ServerState& ss) {return CommandHandler::userInfoCommand(ss);}}},
        {"/SEND",        {true,  2,                  [this](TEAMS::ServerState& ss) {return CommandHandler::sendCommand(ss);}}},
        {"/MESSAGES",    {true,  1,                  [this](TEAMS::ServerState& ss) {return CommandHandler::messagesCommand(ss);}}},
        {"/LOGIN",       {false, 1,                  [this](TEAMS::ServerState& ss) {return CommandHandler::loginCommand(ss);}}},
        {"/LOGOUT",      {true,  0,                  [this](TEAMS::ServerState& ss) {return CommandHandler::logoutCommand(ss);}}},
        {"/SUBSCRIBE",   {true,  1,                  [this](TEAMS::ServerState& ss) {return CommandHandler::subscribeCommand(ss);}}},
        {"/SUBSCRIBED",  {true,  std::string::npos,  [this](TEAMS::ServerState& ss) {return CommandHandler::subscribedCommand(ss);}}},
        {"/UNSUBSCRIBE", {true,  1,                  [this](TEAMS::ServerState& ss) {return CommandHandler::unsubscribeCommand(ss);}}},
        {"/USE",         {true,  std::string::npos,  [this](TEAMS::ServerState& ss) {return CommandHandler::useCommand(ss);}}},
        {"/CREATE",      {true,  std::string::npos,  [this](TEAMS::ServerState& ss) {return CommandHandler::createCommand(ss);}}},
        {"/LIST",        {true,  std::string::npos,  [this](TEAMS::ServerState& ss) {return CommandHandler::listCommand(ss);}}},
        {"/INFO",        {true,  std::string::npos,  [this](TEAMS::ServerState& ss) {return CommandHandler::infoCommand(ss);}}},
        {"/HELP",        {false, std::string::npos,  [this](TEAMS::ServerState& ss) {return CommandHandler::helpCommand(ss);}}},
        {"/POST",        {true,  2,                  [this](TEAMS::ServerState& ss) {return CommandHandler::postCommand(ss);}}},
    };

    std::map<std::string, CommandInfo>::iterator itHandler = this->_handler.find(this->_cParser.getCommand());

    if (itHandler != this->_handler.end())
        return this->verifCommand(this->_handler.at(this->_cParser.getCommand()), state);
    this->_helper.send(this->_userFd, "650 Unknown command.");
}

TEAMS::CommandHandler::~CommandHandler() = default;