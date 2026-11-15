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
extern void func_00288CB0(int, int);
extern void func_002C9A98(s32 *);
extern void func_002C9AD8(s32 *);
extern s32 func_002CB4E8(s32);

/* Refreshes which planets can be picked in the level select list and handles the buttons: open, close, or choose a planet. */
int func_002CB510(int flags)
{
    int result = -1;
    int i;

    for (i = 0; i <= D_00210A40.count; i++) {
        if (IsMenuIndexAllowed(i))
            D_00210A40.state[i] = D_001A7BC8[i] != 0;
    }
    D_00210A40.state[0] = 0;
    if (flags & 0x1000) {
        StepRingListBackward((s32 *)&D_00210A40);
    } else if (flags & 0x4000) {
        StepRingListForward((s32 *)&D_00210A40);
    } else if (flags & 0x40) {
        result = D_00210A40.id;
        if (D_00258D70[result * 2] == 0xB47 && D_001A7C01[0] == 0)
            SetSmallDataValueAndRefresh(0x19, 1);
        else
            SetSmallDataValueAndRefresh(result, 1);
    }
    return result;
}
