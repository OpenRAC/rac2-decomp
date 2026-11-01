#include "include_asm.h"

extern void F449e2f67_FUN_003361A8(char *p);
extern void F449e2f67_FUN_00336968(char *p);
extern void F449e2f67_FUN_003366D0(char *p);

char *func_PAL_003459F8(char *p)
{
    F449e2f67_FUN_003361A8(p);
    F449e2f67_FUN_003361A8(p + 76);
    F449e2f67_FUN_003361A8(p + 152);
    F449e2f67_FUN_003361A8(p + 228);
    F449e2f67_FUN_003361A8(p + 304);
    F449e2f67_FUN_003361A8(p + 380);
    F449e2f67_FUN_00336968(p + 456);
    F449e2f67_FUN_00336968(p + 544);
    F449e2f67_FUN_003366D0(p + 632);
    F449e2f67_FUN_00336968(p + 696);
    F449e2f67_FUN_00336968(p + 784);
    F449e2f67_FUN_00336968(p + 872);
    F449e2f67_FUN_00336968(p + 960);
    F449e2f67_FUN_00336968(p + 1048);
    return p;
}


INCLUDE_ASM("asm/pal/game", func_PAL_00345A88);

typedef struct {
    unsigned char gap0[0x4AC];
    int column, row, index, mode;
} DobboGridState312;
typedef struct { unsigned char pad[6]; short id; short tail; } SelectionRow;
extern SelectionRow D_001AA810[];
extern SelectionRow ref_L00_00286D68_00[];

void func_PAL_00345F98(DobboGridState312 *state, unsigned int buttons)
{
    if (buttons & 0x1000) {
        func_002E5E58(3, 0, 0);
        state->row = 1;
        state->mode = 2;
    } else if (buttons & 0x4000) {
        func_002E5E58(3, 0, 0);
        state->row = 0;
        state->mode = 2;
    } else if (buttons & 0x8000) {
        --state->column;
        func_002E5E58(3, 0, 0);
        if (state->column < 0) {
            state->column = 0;
            state->mode = 1;
        }
    } else if (buttons & 0x2000) {
        func_002E5E58(3, 0, 0);
        ++state->column;
        if (state->column >= 2) {
            state->column = 0;
            state->mode = 1;
            state->row = 0;
        }
    }
    state->index = D_001AA810[state->column].id;
}


/* The cursor's up/down/left/right move: the button mask picks the direction, the state keeps
   the column (0x43C), the row (0x440), the chosen index (0x444) and the mode (0x448). */
void func_PAL_003460A8(DobboGridState312 *state, unsigned int buttons)
{
    if (buttons & 0x1000) {
        func_002E5E58(3, 0, 0);
        if (--state->row < 0) {
            if (state->column < 2) {
                state->row = 0;
                state->mode = 0;
            } else if (state->column == 2) {
                state->row = 1;
            } else {
                state->row = 0;
                state->mode = 1;
                state->column = 0;
            }
        }
    } else if (buttons & 0x4000) {
        func_002E5E58(3, 0, 0);
        if (++state->row >= 2) {
            if (state->column < 2) {
                state->row = 0;
                state->mode = 0;
            } else if (state->column == 2) {
                state->row = 0;
            } else {
                state->row = 0;
                state->mode = 3;
                state->column = 0;
            }
        }
    } else if (buttons & 0x8000) {
        func_002E5E58(3, 0, 0);
        if (--state->column < 0) {
            state->column = 3;
        }
    } else if (buttons & 0x2000) {
        func_002E5E58(3, 0, 0);
        if (++state->column >= 4) {
            state->column = 0;
            state->mode = 3;
            state->row = 0;
        }
    }
    state->index = ref_L00_00286D68_00[state->column + state->row * 4].id;
}


/* prioritized masks1000/4000/8000/2000 update signedcolumns43C/rows440 and mode448 with originalevent3 flags0/entitynull; index444=column+2row */
void func_PAL_00346210(DobboGridState312 *state, unsigned int buttons)
{
    if (buttons & 0x1000) {
        func_002E5E58(3, 0, 0);
        --state->row;
        if (state->row < 0) {
            if (state->column == 0) {
                state->mode = 2;
                state->row = 1;
                state->column = 3;
            } else if (state->column == 1) {
                state->row = state->column;
            }
        }
    } else if (buttons & 0x4000) {
        int row;
        func_002E5E58(3, 0, 0);
        row = state->row + 1;
        state->row = row > 1 ? 0 : row;
    } else if (buttons & 0x8000) {
        func_002E5E58(3, 0, 0);
        --state->column;
        if (state->column < 0) {
            state->column = 3;
            state->row = 1;
            state->mode = 2;
        }
    } else if (buttons & 0x2000) {
        func_002E5E58(3, 0, 0);
        ++state->column;
        if (state->column >= 2)
            state->column = 0;
    }
    state->index = state->column + state->row * 2;
}


extern int func_002E5E58(int, unsigned int, void *);
extern short D_L00_001AAB76;

void func_PAL_00346348(char *object, unsigned int buttons)
{
    if (buttons & 0x1000) {
        func_002E5E58(3, 0, 0);
        *(int *)(object + 0x4B8) = 2;
        *(int *)(object + 0x4B0) = 1;
        *(int *)(object + 0x4AC) = 3;
    } else if (buttons & 0x4000) {
        func_002E5E58(3, 0, 0);
        *(int *)(object + 0x4B8) = 2;
        *(int *)(object + 0x4AC) = 3;
        *(int *)(object + 0x4B0) = 0;
    } else if (buttons & 0x8000) {
        func_002E5E58(3, 0, 0);
        *(int *)(object + 0x4B8) = 0;
        *(int *)(object + 0x4AC) = 1;
        *(int *)(object + 0x4B0) = 0;
    } else if (buttons & 0x2000) {
        func_002E5E58(3, 0, 0);
        *(int *)(object + 0x4B0) = 0;
        *(int *)(object + 0x4B8) = 3;
        *(int *)(object + 0x4AC) = 0;
    }
    *(int *)(object + 0x4B4) = D_L00_001AAB76;
}


extern unsigned char D_00139568[];
extern unsigned char D_001A7AF8[];
extern unsigned char D_001A7AFE __attribute__((sda));
extern unsigned char D_00239BA0[];
typedef struct { unsigned char pad[0x42]; short field42; unsigned char rest[0xE0 - 0x44]; } Entry224;
typedef struct { int v[4]; } Ids_00344378;
extern Ids_00344378 D_001AE260;

int func_PAL_00346428(DobboGridState312 *state)
{
    Ids_00344378 table = D_001AE260;
    int value;

    switch (state->mode) {
    case 0:
    case 2: {
        int index = state->index;
        if (D_001A7AF8[index] != 0) {
            value = ((Entry224 *)D_00239BA0)[D_00139568[index]].field42;
            break;
        }
        return 0;
    }
    case 1:
        if (D_001A7AFE != 0) {
            value = ((Entry224 *)D_00239BA0)[D_00139568[6]].field42;
            break;
        }
        return 0;
    case 3:
        value = table.v[state->index];
        break;
    default:
        value = 0;
        break;
    }
    return value;
}

