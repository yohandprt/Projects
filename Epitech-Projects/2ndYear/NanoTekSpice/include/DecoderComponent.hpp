/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** DecoderComponent.hpp
*/

#ifndef NTS_DECODER
    #define NTS_DECODER

    #include <map>

    #include "AComponent.hpp"

namespace nts {
    class DecoderComponent : public nts::AComponent
    {
    private:
        std::map<std::size_t, nts::Tristate> _currentOutputs;
    public:
        DecoderComponent();
        virtual ~DecoderComponent() = default;

        virtual nts::Tristate compute(std::size_t pin) override;

        nts::Tristate getValue(std::size_t pin, nts::Tristate DValue, nts::Tristate CValue, nts::Tristate BValue, nts::Tristate AValue);
    };
}

#endif