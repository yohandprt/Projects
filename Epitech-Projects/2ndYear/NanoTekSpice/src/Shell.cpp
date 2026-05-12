/*
** EPITECH PROJECT, 2025
** NanoTekSpice
** File description:
** Shell.cpp
*/

#include "Shell.hpp"

nts::Shell::Shell(std::shared_ptr<nts::IComponent> circuit)
{
    this->_circuit = std::dynamic_pointer_cast<nts::Circuit>(circuit);
    this->_funcs = {
        {"simulate", [this]() {return this->_circuit->simulate(1);}},
        {"display", [this]() {return this->_circuit->display();}},
        {"instantiate", [this]() {return this->_circuit->instantiate(this->_instanceInput, this->_instanceState);}},
        {"exit", []() {throw nts::Shell::EndOfFile();}},
        {"loop", [this]() {return this->_circuit->loop();}}
    };
}

std::size_t nts::Shell::run()
{
    while (true) {
        try {
            std::cout << "> " << std::flush;
            this->next();
            this->execFunc();
        } catch (const nts::Shell::EndOfFile& e) {
            std::cerr << e.what();
            break;
        } catch (const nts::Shell::Error& e) {
            std::cerr << e.what() << std::endl;
            return NTS_ERROR;
        } catch (const std::exception& e) {
            return NTS_ERROR;
        }
    }
    return NTS_SUCCESS;
}

void nts::Shell::next()
{
    std::string line = "";

    if (!std::getline(std::cin, line))
        throw nts::Shell::EndOfFile();
    std::istringstream iss(line);

    if (line.find("=") != std::string::npos)
        return this->parseInstantiation(line);
    this->_functionName = "";
    iss >> this->_functionName;
    if (this->_functionName == "instantiate")
        this->_functionName = "";
}

std::string nts::Shell::getFunc()
{
    return this->_functionName;
}

void nts::Shell::execFunc()
{
    if (this->_functionName.empty())
        return;
    if (this->_funcs[this->_functionName])
        return this->_funcs[this->_functionName]();
    throw nts::Shell::Error("Unknown function name '" + this->_functionName + "'.");
}

void nts::Shell::parseInstantiation(std::string line)
{
    nts::Parser parser;
    std::deque<std::string> parts = parser.split(line, '=');

    if (parts.size() != 2)
        throw nts::Shell::Error("Syntax error in instantiation.");

    this->_functionName = "instantiate";
    this->_instanceInput = parts[0];
    if (!this->_circuit->isInput(this->_instanceInput))
        throw nts::Shell::Error("Non-modifiable component '" + this->_instanceInput + "'.");
    if (parts[1] == "U")
        this->_instanceState = nts::Undefined;
    else if (parts[1] == "0")
        this->_instanceState = nts::False;
    else if (parts[1] == "1")
        this->_instanceState = nts::True;
    else
        throw nts::Shell::Error("Undefined type '" + parts[1] + "'.");
}