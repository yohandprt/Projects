/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Shell.hpp
*/

#ifndef NTS_SHELL
    #define NTS_SHELL

    #define NTS_SUCCESS 0
    #define NTS_ERROR 84

    #include <iostream>
    #include <sstream>
    #include <map>
    #include <functional>
    #include <memory>
    #include <deque>

    #include "Circuit.hpp"
    #include "Parser.hpp"

namespace nts {
    class Shell
    {
    private:
        std::shared_ptr<nts::Circuit> _circuit;
        std::map<std::string, std::function<void()>> _funcs;
        std::string _functionName = "";
        std::string _instanceInput;
        nts::Tristate _instanceState;
    public:
        Shell(std::shared_ptr<nts::IComponent> circuit);
        ~Shell() = default;

        std::size_t run();
        void next();
        std::string getFunc();
        void execFunc();
        void parseInstantiation(std::string line);
        class Error : public std::exception
        {
        private:
            std::string _message;
        public:
            Error(std::string message) : _message(message) {};
            ~Error() = default;
            const char *what() const noexcept override { return _message.c_str();};
        };
        class EndOfFile : public std::exception
        {
        private:
            std::string _message = "";
        public:
            EndOfFile() = default;
            EndOfFile(std::string message) : _message(message) {};
            ~EndOfFile() = default;
            const char *what() const noexcept override { return _message.c_str();};
        };
    };
    
}

#endif