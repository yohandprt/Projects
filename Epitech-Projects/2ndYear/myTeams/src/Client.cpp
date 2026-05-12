/*
** EPITECH PROJECT, 2025
** G-NWP-400-LIL-4-1-myteams-16
** File description:
** Client.cpp
*/

#include "Client.hpp"

TEAMS::Client::Client(std::string ip, std::size_t port)
{
    this->_ip = ip;
    this->_port = port;

    this->setInterface(ip);
    this->setPort(port);

    this->addFd(STDIN_FILENO);
    this->addFd(this->_fd);
}

void TEAMS::Client::addFd(int newFd)
{
    struct pollfd new_fds;

    new_fds.fd = newFd;
    new_fds.events = POLLIN;
    new_fds.revents = 0;
    this->_pfds.push_back(new_fds);
}

void TEAMS::Client::send(std::string msg)
{
    if (msg.ends_with("\n") && !msg.ends_with("\r\n"))
        msg = msg.substr(0, msg.size() - 1);
    dprintf(this->_fd, "%s\r\n", msg.c_str());
}

void TEAMS::Client::connect()
{
    if (::connect(this->_fd, (struct sockaddr *)&this->_addr, sizeof(this->_addr)) == -1)
        throw TEAMS::Client::ClientError("Client connect Error");
}

void TEAMS::Client::disconnect()
{
    shutdown(this->_fd, SHUT_RDWR);
}

bool TEAMS::Client::checkEvents()
{
    std::vector<std::string> lines;
    std::string strContent;
    char content[1024];
    int n = 0;

    n = read(this->_pfds[1].fd, content, sizeof(content));

    if (n <= 0) {
        this->disconnect();
        return false;
    }

    content[n] = '\0';
    strContent = content;
    lines = this->_cParser.split(strContent, '\n');

    if (lines[lines.size() - 1].ends_with("\r"))
        lines[lines.size() - 1] = lines[lines.size() - 1].substr(0, lines[lines.size() - 1].size() - 1);

    for (std::size_t i = 0; i < lines.size(); i++) {
        lines[i] += '\n';
        if (!this->_eventHandler.handleEvent(lines[i]))
            printf("%s", lines[i].c_str());
    }

    return true;
}

int TEAMS::Client::run()
{
    std::string line;

    while (true) {
        int ready = poll(this->_pfds.data(), this->_pfds.size(), 350);

        if (ready == -1)
            return 84;
        else if (ready == 0)
            continue;

        if (this->_pfds[0].revents & (POLLIN | POLLHUP)) {
            if (std::getline(std::cin, line))
                this->send(line);
            else {
                this->disconnect();
                return 0;
            }
        }

        if (this->_pfds[1].revents & POLLIN) {
            if (!this->checkEvents())
                return 0;
        }
    }
    return 84;
}
