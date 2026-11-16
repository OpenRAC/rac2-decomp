#include "common.h"

typedef int Q128 __attribute__((mode(TI)));

extern char *CreateMoby(int);
extern int g_tweak_item_ptrs[16];
extern int g_tweak_item_labels[16];
extern char g_tweak_item_types[16] MACRO_ADDR;

/* spawns object 0x118A at the owner's position, binds it to the owner and clears the three
   16-entry tables */
char *museum_tweak_menu_spawn(char *owner)
{
    char *menu = CreateMoby(0x118A /* moby class 4490 */);
    int i;

    if (menu != 0) {
        *(Q128 *)(menu + 0x10) = *(Q128 *)(owner + 0x10);
        *(char **)(menu + 0xB8) = owner;
        *(unsigned char *)(menu + 0x30) = 0xFF;
        for (i = 0; i < 16; i++) {
            g_tweak_item_ptrs[i] = 0;
            g_tweak_item_labels[i] = 0;
            g_tweak_item_types[i] = 0;
        }
    }
    return menu;
}
