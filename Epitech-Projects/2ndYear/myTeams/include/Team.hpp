/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** Team.hpp
*/

#pragma once

#include "UUID.hpp"
#include "Channel.hpp"
#include "AIdentifiable.hpp"

#include <iostream>
#include <map>
#include <memory>

namespace TEAMS {
    class Team : public TEAMS::AIdentifiable
    {
    private:
        std::string _author;
        std::string _name;
        std::string _description;
        std::map<std::string, std::unique_ptr<TEAMS::Channel>> _channels;
        std::map<std::string, std::unique_ptr<TEAMS::Channel>>::iterator _itChannel;
    public:
        Team(std::string author, std::string name, std::string description);
        Team(std::string uuid, std::string author, std::string name, std::string description);
        ~Team() = default;

        std::string getAuthor() const;
        std::string getName() const;
        std::string getDescription() const;

        void createChannel(std::string author, std::string name, std::string description);
        std::string addChannel(std::string author, std::string name, std::string description);
        void addChannel(std::string uuid, std::string author, std::string name, std::string description);
        TEAMS::Channel& getChannel(std::string uuid);
        std::vector<std::string> getChannelsUuids();
        bool isChannelExist(std::string uuid);

        std::map<std::string, std::unique_ptr<TEAMS::Channel>>::iterator& channelBegin();
        std::map<std::string, std::unique_ptr<TEAMS::Channel>>::iterator& channelEnd();
    };
}