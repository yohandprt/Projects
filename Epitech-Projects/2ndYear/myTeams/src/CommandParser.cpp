/*
** EPITECH PROJECT, 2025
** myTeams
** File description:
** CommandParser.cpp
*/

#include "CommandParser.hpp"

std::vector<std::string> TEAMS::CommandParser::split(const std::string &line, char delimiter)
{
    std::istringstream iss(line);
    std::vector<std::string> linkParts;
    std::string part;

    while (std::getline(iss, part, delimiter))
        linkParts.push_back(part);
    return linkParts;
}

std::string TEAMS::CommandParser::trim(const std::string &str)
{
    std::size_t left = str.find_first_not_of(" \t\r\n");
    if (left == std::string::npos)
        return "";
    
    std::size_t right = str.find_last_not_of(" \t\r\n");
    return str.substr(left, right - left + 1);
}

void TEAMS::CommandParser::parseCommand()
{
    std::istringstream iss(this->_line);
    this->_args.clear();

    iss >> this->_command;

    for (char &c : this->_command) {
        if (c == '/')
            continue;
        c = std::toupper(c);
    }

    if (this->_line.find_first_of("\"") == this->_line.find_last_of("\"") || std::count(this->_line.begin(), this->_line.end(), '\"') % 2 != 0)
        return;

    std::istringstream issStrip(this->_line.substr(this->_line.find_first_of("\""), this->_line.find_last_of("\"") - this->_line.find_first_of("\"")));
    std::string arg;

    while (std::getline(issStrip, arg, '\"')) {
        if (!this->trim(arg).empty())
            this->_args.push_back(arg);
    }
}

void TEAMS::CommandParser::setLine(const std::string &line)
{
    this->_line = this->trim(line);
    if (this->_line.empty())
        this->_command.clear();
    else
        this->parseCommand();
}

const std::string& TEAMS::CommandParser::getLine() const
{
    return this->_line;
}

const std::string& TEAMS::CommandParser::getCommand() const
{
    return this->_command;
}

const std::vector<std::string>& TEAMS::CommandParser::getArgs() const
{
    return this->_args;
}

std::size_t TEAMS::CommandParser::getNbArgs() const
{
    return this->_args.size();
}