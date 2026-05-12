/*
** EPITECH PROJECT, 2025
** myTeams
** File description:
** Socket.cpp
*/

#include "Socket.hpp"

TEAMS::Socket::Socket()
{
    this->_sock_size = sizeof(struct sockaddr_in);
    this->_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (this->_fd == -1)
        throw SocketError("Socket creation error.");
    
    this->_addr.sin_family = AF_INET;
}

TEAMS::Socket::Socket(std::string networkInterface, std::size_t port)
{
    this->_sock_size = sizeof(struct sockaddr_in);
    this->_networkInterface = networkInterface;
    this->_port = port;
    this->_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (this->_fd == -1)
        throw SocketError("Socket creation error.");
    
    this->_addr.sin_family = AF_INET;
    this->_addr.sin_port = port == 0 ? 0 : htons(this->_port);
    inet_pton(AF_INET, this->_networkInterface.c_str(), &this->_addr.sin_addr);
}

TEAMS::Socket::~Socket()
{
    if (this->_fd != -1)
        close(this->_fd);
}

std::string TEAMS::Socket::getInterface()
{
    return this->_networkInterface;
}

std::size_t TEAMS::Socket::getPort()
{
    return this->_port;
}

int TEAMS::Socket::getFd()
{
    return this->_fd;
}

socklen_t TEAMS::Socket::getSockSize()
{
    return this->_sock_size;
}

struct sockaddr_in& TEAMS::Socket::getAddr()
{
    return this->_addr;
}

void TEAMS::Socket::setInterface(std::string networkInterface)
{
    this->_networkInterface = networkInterface;

    inet_pton(AF_INET, this->_networkInterface.c_str(), &this->_addr.sin_addr);
}

void TEAMS::Socket::setPort(std::size_t port)
{
    this->_port = port;
    this->_addr.sin_port = htons(this->_port);
}