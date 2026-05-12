/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** main.cpp
*/

#include <exception>
#include <ostream>
#include <memory>

#include "IComponent.hpp"
#include "AComponent.hpp"
#include "ComponentFactory.hpp"
#include "Circuit.hpp"
#include "Parser.hpp"
#include "Shell.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
        return NTS_ERROR;

    nts::Parser parser(argv[1]);
    std::unique_ptr<nts::IComponent> circuit;

    try {
        circuit = parser.parse();
    } catch (const nts::Parser::Error& e) {
        std::cerr << e.what() << std::endl;
        return NTS_ERROR;
    } catch (const std::exception& e) {
        return NTS_ERROR;
    }

    nts::Shell shell(std::move(circuit));
    return shell.run();
}