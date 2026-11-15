#include "common.h"

typedef int Q128 __attribute__((mode(TI)));

extern char *func_0029EFD0(int);
extern int D_L30_00260E30[16];
extern int D_L30_00260EB0[16];
extern char D_L30_001B3D30[16] MACRO_ADDR;

/* spawns object 0x118A at the owner's position, binds it to the owner and clears the three
   16-entry tables */
char *func_L30_00413490(char *owner)
{
    char *menu = CreateMoby(0x118A /* moby class 4490 */);
    int i;

    if (menu != 0) {
        *(Q128 *)(menu + 0x10) = *(Q128 *)(owner + 0x10);
        *(char **)(menu + 0xB8) = owner;
        *(unsigned char *)(menu + 0x30) = 0xFF;
        for (i = 0; i < 16; i++) {
            D_L30_00260E30[i] = 0;
            D_L30_00260EB0[i] = 0;
            D_L30_001B3D30[i] = 0;
        }
    }
    return menu;
}
