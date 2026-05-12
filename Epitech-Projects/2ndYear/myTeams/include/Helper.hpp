/*
** EPITECH PROJECT, 2025
** myTeams
** File description:
** Helper.hpp
*/

#ifndef TEAMS_HELPER
    #define TEAMS_HELPER

    #include <dlfcn.h>
    #include <iostream>
    #include <functional>

namespace TEAMS {

    class Helper
    {
    private:
        static void *_handle;
    public:
        Helper() = default;
        ~Helper() = default;
        void send(int userFd, std::string msg);
        void serverHelp();
        void clientHelp();
    };
}

#endif