/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** 4001.hpp
*/

#ifndef NTS_4001
    #define NTS_4001

    #include "AComponent.hpp"

namespace nts {
    class nts4001Component : public nts::AComponent
    {
    private:
        std::vector<nts::IComponent *> _visited;
    public:
        nts4001Component() : nts::AComponent(14, "4001") {};
        virtual ~nts4001Component() = default;

        virtual nts::Tristate compute(std::size_t pin) override;
        virtual void simulate(std::size_t tick) override;
    };
}

#endif