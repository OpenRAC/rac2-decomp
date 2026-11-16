#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

/* The bound of the object bank, read through $gp in the third test's delay slot. */
extern u32 g_moby_l20_list_end __attribute__((sda));

/* The same bound, read absolutely (the retail materialises it with lui/lw). */
extern u32 D_L20_001B2FA0_abs __attribute__((nosda));

/* The first object of the bank. */
extern u32 D_L20_001B2F9C_abs __attribute__((nosda));

/* Walks through every object in the level and turns off the ones from four particular classes. */
void yeedil_boss_disable_hazards(void) {
    u8 *base = (u8 *)D_L20_001B2F9C_abs;
    u32 bound;

    if (D_L20_001B2FA0_abs < (u32)base) {
        return;
    }
    if (*(u8 *)(base + 0x20) == 0xFF) {
        return;
    }
    for (;;) {
        u16 id = *(u16 *)(base + 0xAA);

        if ((u16)(id - 0x1233 /* moby classes 4659, 4660 */) < 2) {
            goto store;
        }
        if ((s16)id == 0x1231 /* moby class 4657 */) {
            goto store;
        }
        if ((s16)id != 0x1232 /* moby class 4658 */) {
            bound = g_moby_l20_list_end;
            goto next;
        }
    store:
        base[0x31] = 0;
        *(u16 *)(base + 0x34) |= 1;
        bound = D_L20_001B2FA0_abs;
    next:
        base += 0x100;
        if (bound < (u32)base) {
            return;
        }
        if (*(u8 *)(base + 0x20) != 0xFF) {
            continue;
        }
        return;
    }
}
