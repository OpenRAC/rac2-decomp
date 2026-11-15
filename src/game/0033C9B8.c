#include "include_asm.h"
#include "names.h"

extern void Ffb202470_FUN_0033AB50(char *p);

/* Cleans up the button prompt bar inside this menu and gives the menu back. */
char *four_option_menu_destroy(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}

