/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Circuit.hpp
*/

#ifndef NTS_CIRCUIT
    #define NTS_CIRCUIT

    #include <map>
    #include <deque>
    #include <memory>

    #include "AComponent.hpp"

namespace nts {
    class Circuit : public nts::AComponent
    {
    private:
        std::size_t _currentTick = 0;
        std::deque<std::string> _orderedComponentNames;
        std::map<std::string, std::shared_ptr<nts::IComponent>> _inputs;
        std::map<std::string, std::shared_ptr<nts::IComponent>> _outputs;
        std::map<std::string, std::shared_ptr<nts::IComponent>> _gates;
    public:
        Circuit() : nts::AComponent(2, "circuit") {};
        virtual ~Circuit() = default;

        virtual void simulate(std::size_t tick) override;
        virtual nts::Tristate compute(std::size_t pin) override;

        void addInput(std::shared_ptr<nts::IComponent> component, std::string name);
        void addOutput(std::shared_ptr<nts::IComponent> component, std::string name);
        void addGate(std::shared_ptr<nts::IComponent> component, std::string name);
        std::shared_ptr<nts::IComponent> getComponent(const std::string &name);
        bool isInput(const std::string &name);
        bool containsComponent(const std::string &name);
        void display();
        void instantiate(const std::string &name, nts::Tristate state);
        void loop();
    };
}

std::ostream& operator<<(std::ostream& s, nts::Tristate v);

#endif