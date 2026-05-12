/*
** EPITECH PROJECT, 2025
** myTeams
** File description:
** main.cpp
*/

#include "Server.hpp"
#include "Helper.hpp"

#include <cstring>
#include <csignal>

int main(int argc, char *argv[])
{
    TEAMS::Helper helper;

    if (argc != 2)
        return 84;

    if (strcmp(argv[1], "--help") == 0) {
        helper.serverHelp();
        return 0;
    }

    signal(SIGPIPE, SIG_IGN);

    try {
        TEAMS::Server server(atoi(argv[1]));
        server.run();
    } catch (const TEAMS::Server::ServerError &e) {
        printf("%s\n", e.what());
        return 84;
    } catch (const std::exception &e) {
        printf("%s\n", e.what());
        return 84;
    }
    return 0;
}