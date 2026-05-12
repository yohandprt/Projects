/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** Loader.cpp
*/

#include "Loader.hpp"

void TEAMS::Loader::loadUsers(TEAMS::ServerState& state)
{
    std::ifstream file(".users.txt");

    if (!file)
        return;

    std::istringstream iss;
    std::string line;

    while (std::getline(file, line)) {
        std::string name;
        std::string uuid;
        std::string teamUuid;

        iss.clear();
        iss.str(line);

        iss >> name;
        iss >> uuid;
        name = name.substr(1, name.size() - 2);
        uuid = uuid.substr(1, uuid.size() - 2);

        state.createUser(uuid);
        state.getUser(uuid).setUsername(name);

        while (iss >> teamUuid) {
            teamUuid = teamUuid.substr(1, teamUuid.size() - 2);
            state.getUser(uuid).subscribe(teamUuid);
        }

        server_event_user_loaded(uuid.c_str(), name.c_str());

    }
    file.close();
}

void TEAMS::Loader::loadBackup(TEAMS::ServerState& state)
{
    std::ifstream file(".teamsbackup.txt");
    std::string line;
    std::istringstream iss;
    std::string type;
    std::string teamUuid;
    std::string name;
    std::string description;
    std::string author;

    if (!file)
        return;

    while (std::getline(file, line)) {
        this->_cParser.setLine(line);

        if (this->_cParser.getCommand() == "TEAM")
            this->loadTeam(state);
        else if (this->_cParser.getCommand() == "CHANNEL")
            this->loadChannel(state);
        else if (this->_cParser.getCommand() == "THREAD")
            this->loadThread(state);
        else if (this->_cParser.getCommand() == "REPLY")
            this->loadReply(state);
        else if (this->_cParser.getCommand() == "PRIVATE")
            this->loadPrivateMessages(state);
    }
}

void TEAMS::Loader::loadTeam(TEAMS::ServerState& state)
{
    if (this->_cParser.getNbArgs() != 4)
        return;

    state.addTeam(this->_cParser.getArgs()[0], this->_cParser.getArgs()[1], this->_cParser.getArgs()[2], this->_cParser.getArgs()[3]);
}

void TEAMS::Loader::loadChannel(TEAMS::ServerState& state)
{
    if (this->_cParser.getNbArgs() != 5)
        return;

    state.getTeam(this->_cParser.getArgs()[0]).addChannel(this->_cParser.getArgs()[1], this->_cParser.getArgs()[2], this->_cParser.getArgs()[3], this->_cParser.getArgs()[4]);
}

void TEAMS::Loader::loadThread(TEAMS::ServerState& state)
{
    if (this->_cParser.getNbArgs() != 7)
        return;

    state.getTeam(this->_cParser.getArgs()[0]).getChannel(this->_cParser.getArgs()[1]).addThread(this->_cParser.getArgs()[2], this->_cParser.getArgs()[3], this->_cParser.getArgs()[4], this->_cParser.getArgs()[5], std::stoi(this->_cParser.getArgs()[6]));
}

void TEAMS::Loader::loadReply(TEAMS::ServerState& state)
{
    if (this->_cParser.getNbArgs() != 6)
        return;

    state.getTeam(this->_cParser.getArgs()[0]).getChannel(this->_cParser.getArgs()[1]).getThread(this->_cParser.getArgs()[2]).addReply(this->_cParser.getArgs()[3], this->_cParser.getArgs()[4], std::stoi(this->_cParser.getArgs()[5]));
}

void TEAMS::Loader::loadPrivateMessages(TEAMS::ServerState& state)
{
    if (this->_cParser.getNbArgs() != 4)
        return;

    const std::string sender = this->_cParser.getArgs()[0];
    const std::string receiver = this->_cParser.getArgs()[1];
    const std::string message = this->_cParser.getArgs()[2];
    const std::time_t timestamp = std::stoi(this->_cParser.getArgs()[3]);

    state.getUser(sender).addMessage(sender, receiver, message, timestamp);
    state.getUser(receiver).addMessage(sender, sender, message, timestamp);
}