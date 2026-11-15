/* func_L20_00449338: mode 0 records the start position, mode 1 waits for a trigger,
 * mode 2 moves z up by state[0x80] over state[0x84] updates, then mode 3.  An object
 * already triggered in mode 0 goes straight to the end position.  The trigger is flag
 * 0x80 of the object's entry (byte 0xB0) in the current level's row of D_0019B2E8, or
 * func_L00_00329520 on D_00189EA0 and index state[0x88].
 * Built -G8 (D_001A79F0 through $gp).  The entry byte is read at each use rather than
 * kept in a variable: that is what gives the row sum retail's register. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern s32 D_001A79F0 __attribute__((sda));

extern u8 D_0019B2E8[][16] __attribute__((nosda));

extern u32 D_00189EA0[] __attribute__((nosda));

extern int func_L00_00329520(void *, int);

extern int func_002B38B8(void *);

extern void func_002AD6F0(void *, void *, void *, void *);
extern void func_002A7750(char *, int, int);
extern void func_00282CF0(void *, void *, void *);

void func_L20_00449338(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    TI128 v0, v1, v2;

    qcopy(&v0, arg0 + 0x10);
    qcopy(&v1, arg0 + 0xF0);
    switch (*(u8 *)(arg0 + 0x20)) {
    case 0:
        *(float *)(state + 0x90) = 0.0f;
        qcopy(state + 0x60, arg0 + 0x10);
        qcopy(state + 0x70, arg0 + 0xF0);
        if ((*(u8 *)(arg0 + 0xB0) != 0xFF && *(u32 *)(state + 0x8C) != 0
             && (D_0019B2E8[D_001A79F0][*(u8 *)(arg0 + 0xB0)] & 0x80))
            || (*(int *)(state + 0x88) != -1
                && func_L00_00329520(D_00189EA0, *(int *)(state + 0x88)) != 0)) {
            float base = *(float *)(state + 0x68);
            float rise = *(float *)(state + 0x80);

            *(u16 *)(arg0 + 0x34) |= 2;
            *(float *)(arg0 + 0x18) = base + rise;
            func_002A7750(arg0, 3, -1);
        } else {
            func_002A7750(arg0, 1, -1);
        }
        break;
    case 1:
        if (*(u8 *)(arg0 + 0xBC) != 0 || func_002B38B8(arg0) != 0
            || (*(u8 *)(arg0 + 0xB0) != 0xFF && *(u32 *)(state + 0x8C) != 0
                && (D_0019B2E8[D_001A79F0][*(u8 *)(arg0 + 0xB0)] & 0x80))
            || (*(int *)(state + 0x88) != -1
                && func_L00_00329520(D_00189EA0, *(int *)(state + 0x88)) != 0)) {
            func_002A7750(arg0, 2, -1);
        }
        break;
    case 2: {
        float step, progress, amplitude, baseline;
        step = 1.0f / *(float *)(state + 0x84);
        *(float *)(state + 0x90) += step;
        if (*(float *)(state + 0x90) > 1.0f) *(float *)(state + 0x90) = 1.0f;
        progress = *(float *)(state + 0x90);
        amplitude = *(float *)(state + 0x80);
        baseline = *(float *)(state + 0x68);
        progress *= amplitude;
        baseline += progress;
        *(float *)(arg0 + 0x18) = baseline;
        if (*(float *)(state + 0x90) >= 1.0f)
            func_002A7750(arg0, 3, -1);
        break;
    }
    }
    if (*(u8 *)(arg0 + 0x20) < 3) {
        FastVecSub(&v2, arg0 + 0x10, &v0);
        func_002AD6F0(state + 0x20, &v2, &v1, arg0 + 0xF0);
    }
}
