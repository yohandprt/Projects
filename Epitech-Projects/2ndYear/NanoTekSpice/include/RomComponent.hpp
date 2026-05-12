/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** RomComponent.hpp
*/

#ifndef NTS_ROM
    #define NTS_ROM

    #include "AComponent.hpp"
    #include "Utils.hpp"

    #include <vector>
    #include <fstream>

namespace nts {
    class RomComponent : public nts::AComponent
    {
    private:
        nts::Utils _utils;
        std::vector<unsigned char> _content;
        std::size_t _address;
        bool _undefinedValue;
    public:
        RomComponent();
        virtual ~RomComponent() = default;

        virtual void simulate(std::size_t tick) override;
        virtual nts::Tristate compute(std::size_t pin) override;

        nts::Tristate getValue(std::size_t idxBit);
    };
}

#endif