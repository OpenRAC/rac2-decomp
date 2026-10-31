#include "include_asm.h"

/* This unit is built with -G8: the body reaches a global through $gp. */

/* func_L20_0044AC38: the id-list walk of group arg1 (the for(;;) shape of the matched
   func_L20_0039E890), returning the first actor in state 1 and setting it up at arg2
   heading along arg3.  D_L20_001B2FB8 and D_L20_001B2F9C are incomplete sda arrays read
   as [0]: retail's tied absolute macro loads (lui $r; lw $r,%lo($r)), which keep the
   table address in one register for the whole walk. */
#include "common.h"

extern int D_L20_001B2FB8[] __attribute__((sda));
extern char *D_L20_001B2F9C[] __attribute__((sda));
extern char *D_L20_001FBB20[];
extern int D_L20_001B2440 __attribute__((sda));

extern void func_002A7470(void *, int, int, int);
extern void func_002AEC18(void *, int);
extern int func_002A77E0(int);
extern void func_002A7750(void *, int, int);
extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283248(float, float);
extern float func_002A7940(void);

char *func_L20_0044AC38(int arg0, int arg1, float *arg2, float *arg3) {
    char *idp = D_L20_001FBB20[arg1];
    char *found = 0;

    if ((arg1 & 0xFF) == 0xFF) {
        goto end;
    }
    if (D_L20_001B2FB8[0] < arg1) {
        goto end;
    }
    if (idp == 0) {
        goto end;
    }
    for (;;) {
        char *moby = D_L20_001B2F9C[0] + ((*(u16 *)idp & 0x7FFF) << 8);

        if (moby == 0) {
            goto end;
        }
        if (*(u8 *)(moby + 0x20) == 1) {
            found = moby;
            goto end;
        }
        idp += 2;
        if ((arg1 & 0xFF) == 0xFF) {
            goto end;
        }
        if (D_L20_001B2FB8[0] < arg1) {
            goto end;
        }
        if (idp == 0) {
            goto end;
        }
        if (*(s16 *)(idp - 2) >= 0) {
            continue;
        }
        if (idp == D_L20_001FBB20[arg1]) {
            continue;
        }
        break;
    }
end:
    if (found != 0) {
        char *state;
        char *pos;

        *(u16 *)(found + 0x34) = (*(u16 *)(found + 0x34) & 0xFFBE) | 0x1000;
        *(int *)(found + 0x98) = *(int *)(*(char **)(found + 0x24) + 0x10);
        func_002A7470(found, 0, 0, 0xF);
        func_002AEC18(found, D_L20_001B2440);
        if (func_002A77E0(2) != 0) {
            *(u16 *)(found + 0x34) |= 0x8000;
        } else {
            *(u16 *)(found + 0x34) &= 0x7FFF;
        }
        state = *(char **)(found + 0x68);
        pos = found + 0x10;
        qcopy(pos, arg2);
        qcopy(state + 0x180, arg2);
        qcopy(state + 0x170, arg3);
        *(int *)(found + 0xB8) = arg0;
        func_002A7750(found, 2, -1);
        func_00282F20(state + 0x190, arg3, func_002A7878(20.0f, 30.0f));
        func_00282CC0(state + 0x190, state + 0x190, pos);
        *(float *)(state + 0x198) = arg2[2];
        *(float *)(state + 0x20) = (float)*(s16 *)(state + 0x24);
        *(float *)(found + 0xF8) = func_00283248(arg3[0], arg3[1]);
        *(float *)(state + 0x1A0) = func_002A7940();
        *(float *)(state + 0x20) = (float)*(s16 *)(state + 0x24);
    }
    return found;
}
