/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Logger.hpp
*/

#ifndef NTS_LOGGER
    #define NTS_LOGGER

    #include <vector>
    #include <fstream>

    #include "AComponent.hpp"
    #include "Utils.hpp"

namespace nts {
    class LoggerComponent : public nts::AComponent
    {
    private:
        nts::Utils _utils;
        std::vector<nts::Tristate> _triBin;
    public:
        LoggerComponent() : nts::AComponent(10, "logger") {};
        virtual ~LoggerComponent() = default;

        virtual void simulate(std::size_t tick) override;
    };
}

#endif