/*
** EPITECH PROJECT, 2024
** task07
** File description:
** task07
*/

#include "../../include/my.h"

int my_find_prime_sup(int nb)
{
    if (nb <= 2)
        return 2;
    for (int i = 2; i != nb; i++)
        if (nb % i == 0)
            return my_find_prime_sup(nb + 1);
    return nb;
}
