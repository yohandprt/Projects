/*
** EPITECH PROJECT, 2025
** myTeams
** File description:
** User.hpp
*/

#ifndef TEAMS_USER
    #define TEAMS_USER

    #include "Socket.hpp"
    #include "UUID.hpp"
    #include "AIdentifiable.hpp"
    #include "Team.hpp"

    #include <memory>
    #include <vector>
    #include <map>

namespace TEAMS {

    class CommandHandler;

    class User : public TEAMS::AIdentifiable
    {
    private:
        int _fd;
        bool _connect;
        std::string _username;
        std::string _command;
        std::vector<std::string> _teams;
        std::map<std::string, std::vector<std::unique_ptr<TEAMS::AMessage>>> _convs;
    public:
        User(std::string uuid);
        User(int fd);
        User(std::string uuid, int fd);
        ~User() = default;

        std::string getCurrentCommand();
        int getFd();
        std::string getUsername();
        std::vector<std::unique_ptr<TEAMS::AMessage>>& getMessages(std::string userUuid);
        std::vector<std::string>& getSubTeams();

        void setUsername(std::string username);
        void setFd(int newFd);

        void addMessage(std::string authorUuid, std::string destUuid, std::string content, std::time_t createdTime);
        void addCommandPart(std::string part);

        void resetCommand();

        void connection();
        void disconnection();

        void send(std::string msg);
        void subscribe(std::string teamUuid);
        void unsubscribe(std::string teamUuid);
        bool isSubscribed(const std::string& teamUuid) const;
        bool isConvExist(std::string userUuid);
        bool isConnected();
    };
}

#endif