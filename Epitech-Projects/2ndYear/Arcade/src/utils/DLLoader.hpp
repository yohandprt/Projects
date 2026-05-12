/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** DLLoader.hpp
*/

#include <iostream>
#include <dlfcn.h>
#include <vector>
#include <memory>

#include "IModule.hpp"

namespace ARCADE {
    class DLLoader
    {
    private:
        std::vector<void *> _handlers;
    public:
        DLLoader() = default;

        ~DLLoader() {
            if (!_handlers.empty()) {
                for (std::size_t i = 0; i < _handlers.size(); i++) {
                    if (_handlers[i]) {
                        dlclose(_handlers[i]);
                        _handlers[i] = nullptr;
                    }
                }
            }
        };

        template<typename T>
        std::unique_ptr<T> getInstance(std::string libPath) {
            void *handle = dlopen(libPath.c_str(), RTLD_LAZY);

            if (!handle) {
                printf("ERROR HANDLE: %s\n", dlerror());
                return nullptr;
            }

            _handlers.push_back(handle);

            std::unique_ptr<ARCADE::IModule> (*func)();

            void *f = dlsym(_handlers[_handlers.size() - 1], "entryPoint");

            if (!f) {
                printf("ERROR SYM: %s\n", dlerror());
                return nullptr;
            }

            func = reinterpret_cast<std::unique_ptr<IModule> (*)()>(f);

            std::unique_ptr<IModule> module = func();

            if (!dynamic_cast<T*>(module.get()))
                return nullptr;

            return std::unique_ptr<T>(static_cast<T*>(module.release()));
        };
    };

};