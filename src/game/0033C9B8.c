#include "include_asm.h"

extern void Ffb202470_FUN_0033AB50(char *p);

/* Cleans up the button prompt bar inside this menu and gives the menu back. */
char *func_0033C9B8(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}

