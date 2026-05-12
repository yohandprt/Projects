/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** main.cpp
*/

#include <iostream>

#include "GameManager.hpp"

int main(int argc, char *argv[], char *envp[])
{
    if (argc != 2) {
        printf("ERROR: %s need one argument 'graphical-lib'\n", argv[0]);
        return 84;
    }

    ARCADE::GameManager gm;
    std::string firstGraphicLib = argv[1];
    std::size_t state = 0;

    if (!gm.getDLHandler().isGraphicLib(firstGraphicLib)) {
        printf("ERROR: '%s' not a graphical library\n", firstGraphicLib.c_str());
        return 84;
    }

    gm.initVectorEnvp(envp);

    if (!firstGraphicLib.ends_with("arcade_ncurses.so") && !gm.canLaunchGraphic()) {
        printf("ERROR: no graphical environment available\n");
        return 84;
    }

    gm.runMenu(firstGraphicLib, true);

    while (true) {
        state = gm.runMenu(firstGraphicLib, false);

        if (state == 1) {
            try {
                state = gm.runGame();
            } catch (std::exception &e) {
                printf("%s\n", e.what());
            }
            if (state == 1)
                continue;
            else if (state == 84) {
                printf("ERROR: graphic lib load failed\n");
                return 84;
            }
        } else if (state == 84) {
            printf("ERROR: graphic lib load failed\n");
            return 84;
        }
        break;
    }
    gm.getGameState().removeGameSaves();
    return state;
}
