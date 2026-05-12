/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** Saver.cpp
*/

#include "Saver.hpp"

void TEAMS::Saver::saveInFile(std::string filePath, std::vector<std::string> &lines)
{
    std::ofstream file(filePath);

    for (auto& l : lines)
        file << l << std::endl;

    file.close();
}

std::string TEAMS::Saver::formatUserLine(std::string userUuid, std::unique_ptr<TEAMS::User>& user)
{
    std::string userLine = std::format("\"{}\" \"{}\" ", user->getUsername(), userUuid);

    for (std::size_t i = 0; i < user->getSubTeams().size(); i++)
        userLine += std::format("\"{}\" ", user->getSubTeams()[i]);
    
    return userLine;
}

void TEAMS::Saver::saveUser(std::string userUuid, std::unique_ptr<TEAMS::User>& user)
{
    if (user->getUsername().empty())
        return;

    std::string userLine = this->formatUserLine(userUuid, user);
    std::ifstream file(".users.txt");
    std::vector<std::string> lines;
    std::size_t index = std::string::npos;
    std::string line;

    if (file) {

        for (std::size_t i = 0; std::getline(file, line); i++) {
            if (line.starts_with(("\"" + user->getUsername() + "\"")))
                index = i;
            lines.push_back(line);
        }

        file.close();

        if (index == std::string::npos)
            lines.push_back(userLine);
        else if (lines.size() > index)
            lines[index] = userLine;
    } else
        lines.push_back(userLine);

    this->saveInFile(".users.txt", lines);
}

void TEAMS::Saver::saveBackup(TEAMS::ServerState& state)
{
    std::vector<std::string> backupLines;

    this->saveTeam(state, backupLines);
    this->savePrivateMessages(state, backupLines);

    std::ofstream backupFile(".teamsbackup.txt");

    for (auto& l : backupLines)
        backupFile << l << "\n";

    backupFile.close();
}

void TEAMS::Saver::saveTeam(TEAMS::ServerState& state, std::vector<std::string>& backupLines)
{
    auto itTeam = state.teamBegin();

    for (; itTeam != state.teamEnd(); itTeam++) {
        std::string line = std::format("team \"{}\" \"{}\" \"{}\" \"{}\"", itTeam->first, itTeam->second->getAuthor(), itTeam->second->getName(), itTeam->second->getDescription());
        backupLines.push_back(line);
        this->saveChannel(state, backupLines, itTeam->first);
    }
}

void TEAMS::Saver::saveChannel(TEAMS::ServerState& state, std::vector<std::string>& backupLines, std::string teamUuid)
{
    auto itChannel = state.getTeam(teamUuid).channelBegin();

    for (; itChannel != state.getTeam(teamUuid).channelEnd(); itChannel++) {
        std::string line = std::format("channel \"{}\" \"{}\" \"{}\" \"{}\" \"{}\"", teamUuid, itChannel->first, itChannel->second->getAuthor(), itChannel->second->getName(), itChannel->second->getDescription());
        backupLines.push_back(line);
        this->saveThread(state, backupLines, teamUuid, itChannel->first);
    }
}

void TEAMS::Saver::saveThread(TEAMS::ServerState& state, std::vector<std::string>& backupLines, std::string teamUuid, std::string channelUuid)
{
    auto itThread = state.getTeam(teamUuid).getChannel(channelUuid).threadBegin();

    for (; itThread != state.getTeam(teamUuid).getChannel(channelUuid).threadEnd(); itThread++) {
        std::string line = std::format("thread \"{}\" \"{}\" \"{}\" \"{}\" \"{}\" \"{}\" \"{}\"", teamUuid, channelUuid, itThread->first, itThread->second->getAuthor(), itThread->second->getTitle(), itThread->second->getContent(), itThread->second->getCreatedTime());
        backupLines.push_back(line);
        this->saveReply(state, backupLines, teamUuid, channelUuid, itThread->first);
    }
}

void TEAMS::Saver::saveReply(TEAMS::ServerState& state, std::vector<std::string>& backupLines, std::string teamUuid, std::string channelUuid, std::string threadUuid)
{
    auto& replies = state.getTeam(teamUuid).getChannel(channelUuid).getThread(threadUuid).getReplies();

    for (std::size_t i = 0; i < replies.size(); i++) {
        std::string line = std::format("reply \"{}\" \"{}\" \"{}\" \"{}\" \"{}\" \"{}\"", teamUuid, channelUuid, threadUuid, replies[i]->getAuthor(), replies[i]->getContent(), replies[i]->getCreatedTime());
        backupLines.push_back(line);
    }
}

void TEAMS::Saver::savePrivateMessages(TEAMS::ServerState& state, std::vector<std::string>& backupLines)
{
    for (auto itSender = state.userBegin(); itSender != state.userEnd(); itSender++) {
        for (auto itReceiver = state.userBegin(); itReceiver != state.userEnd(); itReceiver++) {

            if (itSender->first == itReceiver->first)
                continue;

            if (!itSender->second->isConvExist(itReceiver->first))
                continue;

            auto& messages = itSender->second->getMessages(itReceiver->first);

            for (std::size_t i = 0; i < messages.size(); i++) {
                if (messages[i]->getAuthor() != itSender->first)
                    continue;

                backupLines.push_back(std::format("private \"{}\" \"{}\" \"{}\" \"{}\"", itSender->first, itReceiver->first, messages[i]->getContent(), messages[i]->getCreatedTime()));
            }
        }
    }
}