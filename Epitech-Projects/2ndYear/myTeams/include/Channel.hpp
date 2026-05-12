/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** Channel.hpp
*/

#pragma once

#include "UUID.hpp"
#include "Thread.hpp"
#include "AIdentifiable.hpp"

#include <iostream>
#include <map>
#include <memory>

namespace TEAMS {
    class Channel : public TEAMS::AIdentifiable
    {
    private:
        std::string _author;
        std::string _name;
        std::string _description;
        std::map<std::string, std::unique_ptr<TEAMS::Thread>> _threads;
        std::map<std::string, std::unique_ptr<TEAMS::Thread>>::iterator _itThread;
    public:
        Channel(std::string author, std::string name, std::string description);
        Channel(std::string uuid, std::string author, std::string name, std::string description);
        ~Channel() = default;

        void createThread(std::string author, std::string title, std::string content);
        std::string addThread(std::string author, std::string name, std::string description, std::time_t timestamp);
        void addThread(std::string uuid, std::string author, std::string name, std::string description, std::time_t timestamp);
        std::string getAuthor() const;
        std::string getName() const;
        std::string getDescription() const;
        TEAMS::Thread& getThread(std::string uuid);
        std::vector<std::string> getThreadsUuids();
        bool isThreadExist(std::string uuid);

        std::map<std::string, std::unique_ptr<TEAMS::Thread>>::iterator& threadBegin();
        std::map<std::string, std::unique_ptr<TEAMS::Thread>>::iterator& threadEnd();
    };
}