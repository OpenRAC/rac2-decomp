#include "common.h"

typedef struct {
    int count;
    int id;
    int pad;
    int state[25];
} LevelSelect_210A40;

extern LevelSelect_210A40 D_00210A40;
extern unsigned char D_001A7BC8[] __attribute__((sda));
extern unsigned char D_001A7C01[] __attribute__((sda));
extern int D_00258D70[];
extern void data_set_small_value_and_refresh(int, int);
extern void menu_ring_list_step_backward(s32 *);
extern void menu_ring_list_step_forward(s32 *);
extern s32 menu_is_index_allowed(s32);

/* Refreshes which planets can be picked in the level select list and handles the buttons: open, close, or choose a planet. */
int RebuildLevelSelectAvailability(int flags)
{
    int result = -1;
    int i;

    for (i = 0; i <= D_00210A40.count; i++) {
        if (menu_is_index_allowed(i))
            D_00210A40.state[i] = D_001A7BC8[i] != 0;
    }
    D_00210A40.state[0] = 0;
    if (flags & 0x1000) {
        menu_ring_list_step_backward((s32 *)&D_00210A40);
    } else if (flags & 0x4000) {
        menu_ring_list_step_forward((s32 *)&D_00210A40);
    } else if (flags & 0x40) {
        result = D_00210A40.id;
        if (D_00258D70[result * 2] == 0xB47 && D_001A7C01[0] == 0)
            data_set_small_value_and_refresh(0x19, 1);
        else
            data_set_small_value_and_refresh(result, 1);
    }
    return result;
}
