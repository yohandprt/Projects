/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** AIdentifiable.hpp
*/

#pragma once

#include "IIdentifiable.hpp"
#include "UUID.hpp"

namespace TEAMS {

    class AIdentifiable : public TEAMS::IIdentifiable
    {
    protected:
        TEAMS::UUID _uuidGenerator;
        std::string _uuid;
    public:
        AIdentifiable();
        ~AIdentifiable() = default;

        std::string getUUID() override;
        std::string getNewUUID() override;
        void generateUUID() override;
        void setUUID(std::string uuid) override;
    };
}