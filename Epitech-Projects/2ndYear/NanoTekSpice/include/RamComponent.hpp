/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** RamComponent.hpp
*/

#ifndef NTS_RAM
    #define NTS_RAM

    #include "AComponent.hpp"
    #include "Utils.hpp"

    #include <vector>
    #include <fstream>
    #include <memory>

namespace nts {
    class RamComponent : public nts::AComponent
    {
    private:
        nts::Utils _utils;
        std::vector<std::size_t> _content;
        std::size_t _address;
        bool _undefinedValue;
    public:
        RamComponent();
        virtual ~RamComponent() = default;

        virtual void simulate(std::size_t tick) override;
        virtual nts::Tristate compute(std::size_t pin) override;

        nts::Tristate getLinkByType(std::size_t pin, const std::string &type);
        nts::Tristate getValue(std::size_t idxBit);
        void read();
        void write();
    };
}

#endif