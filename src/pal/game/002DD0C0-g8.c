#include "include_asm.h"
#include "common.h"

/* Prototype evidence (Sep 4/Sep 7 2003 builds): function is
 * the timed text/credits page controller in gui/game_menu.cpp.
 * Entry starts at 0x002DC3D0 (848 bytes), resetting timer dispatch.
 */
typedef struct { char pad[0x1c0]; u64 held; } InputC3;
typedef struct { char pad[0x14]; u8 *owner; int next; char pad1[0xec-0x1c]; int mode; char pad2[0x134-0xf0]; int active; } CtxC3;

/* func_PAL_002DD0C0, the PAL copy of func_002DC3C8 (src/game/002DC3C8-g8.c): the same C
 * with the PAL text ids and 50 Hz page times (150, 200 and 250 frames for 180, 240 and 300).
 * Its callable entry is 8 bytes in, as in USA v1.01 (FUNCTION_ENTRY_OFFSETS). */

/* A timed text page: each state shows a text for a while, scrolls it, then waits. */
typedef struct {
    char pad00[0x34];
    int text;     /* 0x34: a text id or an address */
    char pad38[4];
    int scroll;   /* 0x3C */
    int timer;    /* 0x40 */
    char pad44[0x50 - 0x44];
    int state;    /* 0x50 */
    int done;     /* 0x54: cleared and tested here, set elsewhere */
} PageC3;

extern u8 D_00138180[], D_001F2840[], D_00261A08[], D_00261AB8[], D_00261B78[];
extern u8 D_001ABBA0[] SDATA(D_001ABBA0);
extern u8 D_001ABBB8[] SDATA(D_001ABBB8);
extern int D_0025ED8C[];

int func_PAL_002DD0C0(PageC3 *menu)
{
    int fast, previous, value, result;
    u8 *pad = D_00138180;
    u8 *ctx = D_001F2840;
    u8 *owner;
    fast = (((InputC3 *)pad)->held & 15) == 15;
    if (!((CtxC3 *)ctx)->mode || (fast && ((u32)((InputC3 *)pad)->held & 16))) {
        if ((((u32 *)&((InputC3 *)pad)->held)[1] & 0x900) && !((CtxC3 *)ctx)->active) return 1;
        {
            u8 *pad2 = D_00138180;
            if (*(int *)(pad2 + 0x1c4) & 16) {
                owner = ((CtxC3 *)D_001F2840)->owner;
                value = *(int *)(owner + 0xe0);
                if (value) {
                    ((CtxC3 *)D_001F2840)->next = value;
                } else if (!((CtxC3 *)D_001F2840)->active) {
                    result = -1;
                    goto back_done;
                }
                result = 0;
back_done:
                return result;
            }
        }
    }
    previous = menu->timer;
    menu->timer = previous - 1;
    if (fast) menu->timer = previous - 2;
    if (menu->timer < 0) menu->timer = 0;
    switch (menu->state) {
    case 0:
        ++menu->state;
        menu->timer = 150;
        menu->scroll = 0;
        D_0025ED8C[0] = 0x1cf4;
        menu->text = (int)D_00261A08;
        break;
    case 1:
    case 5:
    case 8:
    case 12:
    case 16:
        if (menu->timer) break;
        menu->done = 0;
        ++menu->state;
        break;
    case 2:
    case 6:
    case 9:
    case 13:
    case 17:
        previous = menu->scroll;
        menu->scroll = previous + 10;
        if (fast) menu->scroll = previous + 20;
        if (menu->done) {
            menu->timer = 150;
            ++menu->state;
        }
        break;
    case 4:
        if (menu->timer) break;
        menu->state = 5;
        menu->timer = 150;
        menu->scroll = 0;
        D_0025ED8C[0] = 0x1d44;
        menu->text = (int)D_00261AB8;
        break;
    case 3:
        if (menu->timer) break;
        D_0025ED8C[0] = 0x1d42;
        menu->text = 0x1d43;
        menu->timer = 200;
        menu->scroll = 0;
        ++menu->state;
        break;
    case 7:
        if (menu->timer) break;
        D_0025ED8C[0] = 0x1d8c;
        menu->text = (int)D_00261B78;
        menu->timer = 200;
        ++menu->state;
        menu->scroll = 0;
        break;
    case 10:
        if (menu->timer) break;
        D_0025ED8C[0] = 0x1dbc;
        menu->text = 0x1dbd;
        menu->timer = 200;
        menu->scroll = 0;
        ++menu->state;
        break;
    case 11:
        if (menu->timer) break;
        menu->scroll = 0;
        menu->timer = 150;
        D_0025ED8C[0] = 0x1dbe;
        menu->text = (int)D_001ABBA0;
        menu->state = 12;
        break;
    case 14:
        if (menu->timer) break;
        D_0025ED8C[0] = 0;
        menu->text = 0x1dcf;
        menu->timer = 200;
        menu->scroll = 0;
        ++menu->state;
        break;
    case 15:
        if (menu->timer) break;
        menu->scroll = 0;
        menu->timer = 150;
        D_0025ED8C[0] = 0x1dd1;
        menu->text = (int)D_001ABBB8;
        menu->state = 16;
        break;
    case 18:
        if (menu->timer) break;
        D_0025ED8C[0] = 0;
        menu->timer = 250;
        menu->text = 0;
        ++menu->state;
        break;
    case 19:
        if (menu->timer) break;
        if (((CtxC3 *)D_001F2840)->mode) return 1;
    }
    return 0;
}
