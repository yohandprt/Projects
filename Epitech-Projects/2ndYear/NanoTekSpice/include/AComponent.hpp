/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** AComponent.hpp
*/

#ifndef NTS_A_COMPONENT
    #define NTS_A_COMPONENT

    #include <vector>
    #include <map>
    #include <memory>
    #include <algorithm>

    #include "IComponent.hpp"
    #include "Link.hpp"

namespace nts {
    class AComponent : public nts::IComponent
    {
    protected:
        nts::Tristate _status;
        nts::Tristate _futurStatus;
        nts::Tristate _tempStatus;
        std::size_t _nbPins;
        std::map<std::size_t, std::vector<nts::Link>> _links;
        std::string _type;
        bool _modification;
    public:
        AComponent(std::size_t nbPins, std::string type);

        virtual void simulate(std::size_t tick) override;
        virtual nts::Tristate compute(std::size_t pin) override;
        virtual void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;

        nts::Tristate getLink(std::size_t pin);
        nts::Tristate getLink(std::size_t pin, std::vector<nts::IComponent *> &visited);
        
        nts::Tristate getStatus() const;
        std::string &getType();
        void setStatus(nts::Tristate status);
        void setFuturStatus(nts::Tristate status);
        void setTempStatus(nts::Tristate status);
        void hasBeenModified();
    };
}

nts::Tristate operator&&(nts::Tristate a, nts::Tristate b);
nts::Tristate operator||(nts::Tristate a, nts::Tristate b);
nts::Tristate operator^(nts::Tristate a, nts::Tristate b);
nts::Tristate operator!(nts::Tristate a);

#endif