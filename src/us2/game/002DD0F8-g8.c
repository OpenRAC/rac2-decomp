#include "include_asm.h"
#include "common.h"

/* Prototype evidence (Sep 4/Sep 7 2003 builds): function is
 * the timed text/credits page controller in gui/game_menu.cpp.
 * Entry starts at 0x002DC3D0 (848 bytes), resetting timer dispatch.
 */
typedef struct { char pad[0x1c0]; u64 held; } InputC3;
typedef struct { char pad[0x14]; u8 *owner; int next; char pad1[0xec-0x1c]; int mode; char pad2[0x134-0xf0]; int active; } CtxC3;

/* func_US2_002DD0F8, the USA v2.00 copy of func_002DC3C8 (src/game/002DC3C8-g8.c): the same
 * C with v2.00's text ids, each 0xB8 above v1.01's. Its callable entry is 8 bytes in, as in
 * USA v1.01 (FUNCTION_ENTRY_OFFSETS). */

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

extern u8 g_pad_state[], g_pause_menu_state[], g_dialog_menu_text_a[], g_dialog_menu_text_b[], g_dialog_menu_text_c[];
extern u8 g_menu_text_a[] SDATA(D_001ABBA0);
extern u8 g_menu_text_b[] SDATA(D_001ABBB8);
extern int g_menu_text_id[];

/* Runs the timed text pages (such as the credits): each page shows a text for a while, scrolls it, then moves to the next. Holding buttons speeds it up and the player can leave early. */
int UpdateTimedTextPages_us2(PageC3 *menu)
{
    int fast_forward, previous, value, result;
    u8 *pad = g_pad_state;
    u8 *ctx = g_pause_menu_state;
    u8 *owner;
    fast_forward = (((InputC3 *)pad)->held & 15) == 15;
    if (!((CtxC3 *)ctx)->mode || (fast_forward && ((u32)((InputC3 *)pad)->held & 16))) {
        if ((((u32 *)&((InputC3 *)pad)->held)[1] & 0x900) && !((CtxC3 *)ctx)->active) return 1;
        {
            u8 *pad2 = g_pad_state;
            if (*(int *)(pad2 + 0x1c4) & 16) {
                owner = ((CtxC3 *)g_pause_menu_state)->owner;
                value = *(int *)(owner + 0xe0);
                if (value) {
                    ((CtxC3 *)g_pause_menu_state)->next = value;
                } else if (!((CtxC3 *)g_pause_menu_state)->active) {
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
    if (fast_forward) menu->timer = previous - 2;
    if (menu->timer < 0) menu->timer = 0;
    switch (menu->state) {
    case 0:
        ++menu->state;
        menu->timer = 180;
        menu->scroll = 0;
        g_menu_text_id[0] = 0x3478;
        menu->text = (int)g_dialog_menu_text_a;
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
        if (fast_forward) menu->scroll = previous + 20;
        if (menu->done) {
            menu->timer = 180;
            ++menu->state;
        }
        break;
    case 4:
        if (menu->timer) break;
        menu->state = 5;
        menu->timer = 180;
        menu->scroll = 0;
        g_menu_text_id[0] = 0x34c8;
        menu->text = (int)g_dialog_menu_text_b;
        break;
    case 3:
        if (menu->timer) break;
        g_menu_text_id[0] = 0x34c6;
        menu->text = 0x34c7;
        menu->timer = 240;
        menu->scroll = 0;
        ++menu->state;
        break;
    case 7:
        if (menu->timer) break;
        g_menu_text_id[0] = 0x3510;
        menu->text = (int)g_dialog_menu_text_c;
        menu->timer = 240;
        ++menu->state;
        menu->scroll = 0;
        break;
    case 10:
        if (menu->timer) break;
        g_menu_text_id[0] = 0x3540;
        menu->text = 0x3541;
        menu->timer = 240;
        menu->scroll = 0;
        ++menu->state;
        break;
    case 11:
        if (menu->timer) break;
        menu->scroll = 0;
        menu->timer = 180;
        g_menu_text_id[0] = 0x3542;
        menu->text = (int)g_menu_text_a;
        menu->state = 12;
        break;
    case 14:
        if (menu->timer) break;
        g_menu_text_id[0] = 0;
        menu->text = 0x3553;
        menu->timer = 240;
        menu->scroll = 0;
        ++menu->state;
        break;
    case 15:
        if (menu->timer) break;
        menu->scroll = 0;
        menu->timer = 180;
        g_menu_text_id[0] = 0x3555;
        menu->text = (int)g_menu_text_b;
        menu->state = 16;
        break;
    case 18:
        if (menu->timer) break;
        g_menu_text_id[0] = 0;
        menu->timer = 300;
        menu->text = 0;
        ++menu->state;
        break;
    case 19:
        if (menu->timer) break;
        if (((CtxC3 *)g_pause_menu_state)->mode) return 1;
    }
    return 0;
}
