/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** AdderComponent.hpp
*/

#ifndef NTS_ADDER
    #define NTS_ADDER

    #include "AComponent.hpp"

namespace nts {
    class AdderComponent : public nts::AComponent
    {
    public:
        AdderComponent() : nts::AComponent(16, "4008") {};
        virtual ~AdderComponent() = default;

        virtual nts::Tristate compute(std::size_t pin) override;

        nts::Tristate addTriBin(nts::Tristate b1, nts::Tristate b2, nts::Tristate &ci);
        std::vector<nts::Tristate> addVecTriBin(std::vector<nts::Tristate> triBin1, std::vector<nts::Tristate> triBin2);
    };
}

#endif