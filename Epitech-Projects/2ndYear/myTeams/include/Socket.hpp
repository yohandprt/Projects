/*
** EPITECH PROJECT, 2025
** myTeams
** File description:
** Socket.hpp
*/

#ifndef TEAMS_SOCKET
    #define TEAMS_SOCKET

    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>

    #include <iostream>
    #include <exception>

namespace TEAMS {
    class Socket
    {
    private:
        std::string _networkInterface;
        std::size_t _port;
    protected:
        struct sockaddr_in _addr;
        int _fd;
        socklen_t _sock_size;
    public:
        Socket();
        Socket(std::string networkInterface, std::size_t port);
        ~Socket();
        std::string getInterface();
        std::size_t getPort();
        int getFd();
        socklen_t getSockSize();
        struct sockaddr_in& getAddr();
        void setInterface(std::string networkInterface);
        void setPort(std::size_t port);
        class SocketError : public std::exception
        {
        protected:
            std::string _message;

        public:
            explicit SocketError(const std::string &message) : _message(message) {}

            const char *what(void) const noexcept override { return _message.c_str(); };
        };
    };
}

#endif