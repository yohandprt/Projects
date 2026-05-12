/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Parser.hpp
*/

#ifndef NTS_PARSER
    #define NTS_PARSER

    #include <iostream>
    #include <memory>
    #include <fstream>
    #include <sstream>
    #include <deque>

    #include "IComponent.hpp"
    #include "ComponentFactory.hpp"
    #include "Circuit.hpp"

namespace nts {
    enum Parts {
        CHIPSETS,
        LINKS,
        COMMENTS
    };

    class Parser
    {
    private:
        char *_filename;
    public:
        Parser() = default;
        Parser(char *filename) : _filename(filename) {};
        ~Parser() = default;
        std::unique_ptr<nts::IComponent> parse();
        void parseChipsets(std::unique_ptr<nts::Circuit>& circuit, std::istringstream& iss);
        void parseLinks(std::unique_ptr<nts::Circuit>& circuit, std::istringstream& iss);
        std::deque<std::string> split(std::string line, char delimiter);
        std::string trim(std::string str);
        std::size_t to_size_t(std::string strNb);
        class Error : public std::exception
        {
        private:
            std::string _message;
        public:
            Error(std::string message) : _message(message) {};
            ~Error() = default;
            const char *what() const noexcept override { return _message.c_str();};
        };
    };
}

#endif