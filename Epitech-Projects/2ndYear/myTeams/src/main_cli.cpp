/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** test_main.cpp
*/

#include <string.h>

#include "Client.hpp"
#include "Helper.hpp"

int main(int argc, char *argv[])
{
    TEAMS::Helper helper;

    if (argc < 2 || argc > 3)
        return 84;
    
    if (argc == 2) {
        if (strcmp(argv[1], "--help") != 0)
            return 84;
        helper.clientHelp();
        return 0;
    }

    TEAMS::Client client(argv[1], std::stoi(argv[2]));

    try {
        client.connect();
        return client.run();
    } catch (const TEAMS::Client::ClientError &e) {
        printf("%s\n", e.what());
        return 84;
    } catch (const std::exception &e) {
        printf("%s\n", e.what());
        return 84;
    }
    return 0;
}