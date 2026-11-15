#include "include_asm.h"
#include "names.h"

/* func_US2_002D1F28, the v2.00 copy of func_002D0FA0: the same C, where entry 7 also sets D_001A7904 and
 * saves D_001A79F0 in a word v2.00 added, unless it is already 21. */

typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;

typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;

extern SelectionCallback g_pause_menu_state;
extern CallbackMenuState g_pad_state;
extern int snd_play_from_global_bank(int, unsigned int, void *);

extern int D_001ABA28 __attribute__((sda));
extern unsigned char D_001ABA30[8] __attribute__((sda));
extern int D_001A7904 __attribute__((sda));
extern int D_US2_001A7908;
extern int g_current_map_index;
extern short D_001A63AC[];
extern void data_set_small_value_and_refresh(int, int);

typedef struct { char reserved00[0x10]; int flags; } FlagTarget;
typedef struct { char reserved00[0x44]; int f44; int f48; int f4c; int f50; int f54; int f58; } MenuFields;
extern FlagTarget *D_0025C540[];
extern MenuFields D_0025C580;
extern int D_0026CD20[];

int func_US2_002D1F28(void)
{
    static void *cases[8] = {&&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7};
    int flags = ((CallbackMenuState *)&g_pad_state)->flags;
    int old = D_001ABA28;
    int result = 0;

    if (flags & 0x10) {
        int value;
        int status;
        D_001ABA28 = 0;
        value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            status = -1;
            goto finish;
        }
        status = 0;
finish:
        return status;
    }
    if (flags & 0x900) {
        D_001ABA28 = 0;
        result = 1;
    } else {
        if (flags & 0x1000) {
            snd_play_from_global_bank(3, 0, 0);
            if (--D_001ABA28 < 0)
                D_001ABA28 = 7;
        } else if (flags & 0x4000) {
            snd_play_from_global_bank(3, 0, 0);
            if (++D_001ABA28 >= 8)
                D_001ABA28 = 0;
        }
        if (((CallbackMenuState *)&g_pad_state)->flags & 0x40) {
            if (D_001ABA30[D_001ABA28] != 0) {
                snd_play_from_global_bank(4, 0, 0);
                if ((unsigned)D_001ABA28 < 8)
                    goto *D_0026CD20[D_001ABA28];
                goto cont;
c0:            D_001A7904 = 2; data_set_small_value_and_refresh(2, 1); goto cont;
c1:            D_001A7904 = 3; data_set_small_value_and_refresh(4, 1); goto cont;
c2:            D_001A7904 = 3; data_set_small_value_and_refresh(11, 1); goto cont;
c3:            D_001A7904 = 2; data_set_small_value_and_refresh(11, 1); goto cont;
c4:            D_001A7904 = 1; data_set_small_value_and_refresh(26, 1); goto cont;
c5:            D_001A7904 = 1; data_set_small_value_and_refresh(22, 1); goto cont;
c6:            D_001A7904 = 1; data_set_small_value_and_refresh(23, 1); goto cont;
c7:            D_001A7904 = 1; if (g_current_map_index != 21) D_US2_001A7908 = g_current_map_index; data_set_small_value_and_refresh(21, 1); goto cont;
            } else {
                snd_play_from_global_bank(5, 0, 0);
            }
        }
cont:
        {
            MenuFields *menu = &D_0025C580;
            menu->f58 = D_001ABA28;
            if (D_001ABA30[D_001ABA28] != 0) {
                if (old == D_001ABA28) {
                    if (D_001A63AC[0] == 0) {
                        if (menu->f50 == old && menu->f44 == 2) {
                            D_0025C540[0]->flags &= -5;
                        } else if (menu->f54 == old && menu->f44 == 4) {
                            D_0025C540[0]->flags &= -5;
                        }
                    }
                }
            } else {
                D_0025C540[0]->flags |= 4;
            }
        }
    }
    return result;
}
