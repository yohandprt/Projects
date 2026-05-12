/*
** EPITECH PROJECT, 2025
** myTeams
** File description:
** Helper.cpp
*/

#include "Helper.hpp"

void *TEAMS::Helper::_handle = nullptr;

void TEAMS::Helper::send(int userFd, std::string msg)
{
    if (msg.ends_with("\n") && !msg.ends_with("\r\n"))
        msg = msg.substr(0, msg.size() - 1);
    dprintf(userFd, "%s\r\n", msg.c_str());
}

void TEAMS::Helper::serverHelp()
{
    printf("USAGE: ./myteams_server port\n" \
            "\n" \
            "port is the port number on which the server socket listens.\n");
}

void TEAMS::Helper::clientHelp()
{
    printf("USAGE: ./myteams_cli ip port\n" \
            "\n" \
            " ip is the server ip address on which the server socket listens\n" \
            " port is the port number on which the server socket listens\n"
        );
}