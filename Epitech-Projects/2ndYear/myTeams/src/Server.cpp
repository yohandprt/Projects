/*
** EPITECH PROJECT, 2025
** myTeams
** File description:
** Server.cpp
*/

#include "Server.hpp"
#include "User.hpp"
#include <cerrno>

TEAMS::Server::Server(std::size_t port)
{
    int optval = 1;

    this->setPort(port);
    this->setInterface("127.0.0.1");

    this->addFd(this->_fd);

    setsockopt(this->_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    if (bind(this->_fd, reinterpret_cast<struct sockaddr *>(&this->_addr), this->_sock_size) != 0)
        throw ServerError("Bind error.");

    if (listen(this->_fd, 50000) == -1)
        throw ServerError("Listen error.");
}

void TEAMS::Server::addFd(int newFd)
{
    struct pollfd new_fds;

    new_fds.fd = newFd;
    new_fds.events = POLLIN;
    new_fds.revents = 0;
    this->_pfds.push_back(new_fds);
}

void TEAMS::Server::newConnection()
{
    struct sockaddr_in user_addr;
    int fd = accept(this->_fd, (struct sockaddr *)&user_addr, &this->_sock_size);

    if (fd == -1)
        return;

    this->addFd(fd);
    this->_handlers.emplace(fd, std::make_unique<TEAMS::CommandHandler>());
    this->_state.createUser(fd);
    dprintf(fd, "820 Service ready for new user.\r\n");
}

void TEAMS::Server::disconnection(std::size_t &index)
{
    int fd = this->_pfds[index].fd;
    
    auto it = this->_state.getUser(fd);

    close(fd);

    if (this->_state.isUserFinded()) {
        if (it->second->isConnected()) {
            it->second->disconnection();
            server_event_user_logged_out(it->first.c_str());
        }
        this->_saver.saveUser(it->first, it->second);
    }

    this->_handlers.erase(fd);
    this->_pfds.erase(this->_pfds.begin() + index);
    index--;
}

bool TEAMS::Server::checkCommand(TEAMS::User &user, std::string line)
{
    user.addCommandPart(line);
    if (user.getCurrentCommand().find("\r\n") != std::string::npos)
        return true;
    return false;
}

void TEAMS::Server::checkEvents()
{
    char content[1024];
    int n = 0;

    for (std::size_t i = 1; i < this->_pfds.size(); i++) {
        if (this->_pfds[i].revents & (POLLHUP | POLLERR)) {
            this->disconnection(i);
            continue;
        }

        if (this->_pfds[i].revents & POLLIN) {
            n = read(this->_pfds[i].fd, content, sizeof(content));

            if (n <= 0) {
                this->disconnection(i);
                continue;
            }

            content[n] = '\0';

            auto itUser = this->_state.getUser(this->_pfds[i].fd);

            if (this->checkCommand(this->_state.getUser(itUser->first), content)) {
                this->_handlers.at(this->_pfds[i].fd)->handleCommand(itUser->first, this->_state.getUser(itUser->first).getCurrentCommand().c_str(), this->_state);
                this->_state.getUser(this->_pfds[i].fd)->second->resetCommand();
            }
        }
    }
}

void TEAMS::Server::run()
{
    this->_loader.loadUsers(this->_state);
    this->_loader.loadBackup(this->_state);

    while (true) {
        int ready = poll(this->_pfds.data(), this->_pfds.size(), 350);

        if (ready == -1) {
            if (errno == EINTR)
                continue;
            throw ServerError("Poll error.");
        }
        else if (ready == 0)
            continue;

        if (this->_pfds[0].revents & POLLIN)
            this->newConnection();

        this->checkEvents();
    }
}