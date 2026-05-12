/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** AMessage.hpp
*/

#pragma once

#include "IMessage.hpp"

namespace TEAMS {
    class AMessage : public TEAMS::IMessage
    {
    protected:
        std::string _authorUuid;
        std::string _content;
        std::time_t _createdTime;
    public:
        AMessage(std::string authorUuid, std::string content);
        AMessage(std::string authorUuid, std::string content, std::time_t createdTime);
        ~AMessage() = default;

        std::string getContent() override;
        std::time_t getCreatedTime() override;
        std::string getAuthor() override;

        void setCreatedTime(std::time_t timestamp) override;
    };
}