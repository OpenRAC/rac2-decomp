/* func_L20_00447930 (UpdateMoby_4687): a platform that eases from its start
 * position to path point state[0x80] of D_L20_001B308C.  Mode 0 records the start
 * (or, when already triggered, jumps straight to the end and retires the moby),
 * mode 1 waits for a trigger, mode 2 eases along a half cosine, mode 3 waits for the
 * linked moby state[0x94] to release it.  Same family as func_L20_00449338.
 * Built -G8 (D_001A79F0 and D_L20_001B2F9C through $gp).
 * The end-of-path copies use qcopy_nc: the only accesses around them read the path
 * table pointer and state[0x80], never the moby's position/rotation being written,
 * and retail keeps the table base and the scaled index across the first copy. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern s32 D_001A79F0 __attribute__((sda));
extern u8 *D_L20_001B2F9C __attribute__((sda));
extern u8 D_0019B2E8[][16] __attribute__((nosda));
extern u32 D_00189EA0[] __attribute__((nosda));
extern struct { u8 header[0x464]; u8 collected[0]; } D_L20_0021EFB0;
typedef struct { u8 pad[0x30]; TI128 pos; u8 pad2[0x30]; TI128 rot; } PathPoint;
extern PathPoint *D_L20_001B308C;

extern int func_L00_00329520(void *, int);
extern int func_002B38B8(void *);
extern void func_002AD6F0(void *, void *, void *, void *);
extern void func_002A7750(char *, int, int);
extern void func_002A0430(int);
extern void func_0029F338(void *);
extern void func_L20_002C5A48(s32);
extern float func_00283180(float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

void func_L20_00447930(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    TI128 v0, v1, v2;

    qcopy(&v0, arg0 + 0x10);
    qcopy(&v1, arg0 + 0xF0);
    switch (*(u8 *)(arg0 + 0x20)) {
    case 0:
        if (*(int *)(state + 0x80) == -1) {
            *(u16 *)(arg0 + 0x34) |= 2;
            func_002A7750(arg0, 4, -1);
            return;
        }
        *(float *)(state + 0x88) = 0.0f;
        *(int *)(state + 0x5C) |= 1;
        qcopy(state + 0x60, arg0 + 0x10);
        qcopy(state + 0x70, arg0 + 0xF0);
        *(u16 *)(arg0 + 0x34) |= 0x100;
        if (D_L20_0021EFB0.collected[*(int *)(state + 0x8C)] != 0
            || (*(u8 *)(arg0 + 0xB0) != 0xFF && *(u8 *)(state + 0x92) != 0
                && (D_0019B2E8[D_001A79F0][*(u8 *)(arg0 + 0xB0)] & 0x80))
            || (*(int *)(state + 0x98) != -1
                && func_L00_00329520(D_00189EA0, *(int *)(state + 0x98)) != 0)) {
            /* Already triggered: snap to the end of the path. */
            qcopy_nc(arg0 + 0x10, &D_L20_001B308C[*(int *)(state + 0x80)].pos);
            qcopy_nc(arg0 + 0xF0, &D_L20_001B308C[*(int *)(state + 0x80)].rot);
            func_0029F338(arg0);
            return;
        }
        func_002A7750(arg0, 1, -1);
        break;
    case 1:
        if (*(u8 *)(arg0 + 0xBC) != 0 || func_002B38B8(arg0) != 0
            || *(int *)(state + 0x8C) == -1
            || D_L20_001B2F9C[(*(int *)(state + 0x8C) << 8) + 0x20] == 0xFE
            || D_L20_001B2F9C[(*(int *)(state + 0x8C) << 8) + 0x20] == 0xFD
            || (*(u8 *)(arg0 + 0xB0) != 0xFF && *(u8 *)(state + 0x92) != 0
                && (D_0019B2E8[D_001A79F0][*(u8 *)(arg0 + 0xB0)] & 0x80))
            || (*(int *)(state + 0x98) != -1
                && func_L00_00329520(D_00189EA0, *(int *)(state + 0x98)) != 0)) {
            if (*(int *)(state + 0x94) != -1) {
                D_L20_001B2F9C[(*(int *)(state + 0x94) << 8) + 0xBC] = 1;
            }
            if (*(u8 *)(state + 0x93) != 0) {
                func_002A0430(*(u8 *)(arg0 + 0xB0));
            }
            func_002A7750(arg0, 2, -1);
        }
        break;
    case 2: {
        float t, ease;

        *(float *)(state + 0x88) += 1.0f / *(float *)(state + 0x84);
        if (*(float *)(state + 0x88) > 1.0f) {
            *(float *)(state + 0x88) = 1.0f;
        }
        t = *(float *)(state + 0x88);
        ease = (1.0f - func_00283180(t * 3.1415927f)) * 0.5f;
        func_00282F20(arg0 + 0xE0, arg0 + 0xE0, 1.0f - ease);
        func_00282CF0(&v2, &D_L20_001B308C[*(int *)(state + 0x80)].pos, state + 0x60);
        func_00282D30(&v2, &v2, ease);
        func_00282CC0(arg0 + 0x10, state + 0x60, &v2);
        if (*(float *)(state + 0x88) >= 1.0f) {
            func_002A7750(arg0, 3, -1);
        }
        break;
    }
    case 3:
        if (*(int *)(state + 0x94) == -1
            || D_L20_001B2F9C[(*(int *)(state + 0x94) << 8) + 0xBC] == 0) {
            if (*(u8 *)(state + 0x90) != 0) {
                func_L20_002C5A48(0);
            }
            func_0029F338(arg0);
            return;
        }
        break;
    }
    if (*(u8 *)(arg0 + 0x20) < 3) {
        func_00282CF0(&v2, arg0 + 0x10, &v0);
        func_002AD6F0(state + 0x20, &v2, &v1, arg0 + 0xF0);
    }
}
