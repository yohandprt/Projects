/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** Thread.hpp
*/

#pragma once

#include "UUID.hpp"
#include "AIdentifiable.hpp"
#include "AMessage.hpp"

#include <iostream>
#include <ctime>
#include <vector>
#include <memory>

namespace TEAMS {
    class Thread : public TEAMS::AIdentifiable, public TEAMS::AMessage
    {
    private:
        std::string _title;
        std::vector<std::unique_ptr<TEAMS::AMessage>> _replies;
    public:
        Thread(std::string author, std::string title, std::string content);
        Thread(std::string uuid, std::string author, std::string title, std::string content, std::time_t timestamp);
        ~Thread() = default;

        void createReply(std::string author, std::string content);
        void addReply(std::string author, std::string content, std::time_t timestamp);
        std::string getTitle() const;
        std::vector<std::unique_ptr<TEAMS::AMessage>>& getReplies();
        std::vector<std::string> getRepliesContents();
    };
}