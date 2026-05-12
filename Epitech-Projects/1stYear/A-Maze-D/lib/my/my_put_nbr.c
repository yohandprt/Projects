/*
** EPITECH PROJECT, 2024
** put_nbr
** File description:
** task07
*/

#include "../../include/my.h"

int my_put_nbr(int nb)
{
    if (nb == -2147483648){
        my_putchar('-');
        my_putchar('2');
        my_put_nbr(147483648);
        return 1;
    }
    if (nb == 0)
        my_putchar('0');
    if (nb <= 9 && nb > 0)
        my_putchar(nb + 48);
    if (nb >= 10) {
        my_put_nbr(nb / 10);
        my_putchar(nb % 10 + 48);
    }
    if (nb < 0) {
        my_putchar('-');
        my_put_nbr(- nb);
    }
    return 0;
}
