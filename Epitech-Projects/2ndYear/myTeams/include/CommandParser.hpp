/*
** EPITECH PROJECT, 2025
** myTeams
** File description:
** CommandParser.hpp
*/

#ifndef TEAMS_COMMAND_PARSER
    #define TEAMS_COMMAND_PARSER

    #include <iostream>
    #include <vector>
    #include <sstream>
    #include <algorithm>

namespace TEAMS {
    class CommandParser
    {
    private:
        std::string _line;
        std::string _command;
        std::vector<std::string> _args;

    public:
        CommandParser() = default;

        void setLine(const std::string &line);
        void parseCommand();

        const std::string &getLine() const;
        const std::string &getCommand() const;
        const std::vector<std::string> &getArgs() const;
        std::size_t getNbArgs() const;

        std::vector<std::string> split(const std::string &line, char delimiter);
        std::string trim(const std::string &str);
    };
}

#endif