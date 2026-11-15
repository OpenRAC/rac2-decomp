#include "names.h"
/* func_PAL_L23_0041D1A8, the PAL copy of func_L23_00418160: the same C, where both
 * arms of the timer store are scaled to 50 Hz; cross-jumping shares their tail.
 */
/* The quadword profile preserves the six aligned transfers. The effect-call
 * declaration interleaves typed integer/FP arguments while preserving each EE
 * register bank's order and the four stack words of func_L23_004256F0.
 */
typedef int TI128 __attribute__((mode(TI)));

extern float D_L23_001B15B4 __attribute__((sda));

extern TI128 D_L23_001B3800 __attribute__((sda));

extern char D_L23_001B3810[16] __attribute__((sda));

extern int D_L23_001B37F0;

extern char *D_L23_00259560[];

extern void moby_transform_joint_to_world(char *, int, char *);

extern void moby_transform_joint_point(char *, int, char *);

extern void FastVecScale(char *, char *, float);

extern void FastVecAdd(char *, char *, char *);

extern void FastVecSub(char *, char *, char *);

extern int D_L23_001B164C __attribute__((sda));

extern int D_L23_001B163C __attribute__((sda));

extern int D_L23_001B1640 __attribute__((sda));

extern float D_L23_001B15A8 __attribute__((sda));

extern short D_L23_001B15AC __attribute__((sda));

extern short D_L23_001B15B0 __attribute__((sda));

extern void mothership_project_point_onto_surface(char *, float);

extern void moby_set_state(char *, int, int);

extern int PlayMobySound(int, int, char *);

extern void *ribbon_trail_create(char *, float, char *, float, char *, float, unsigned char, float,
                               unsigned char, short, short, int, int, int, int, int);

void func_PAL_L23_0041D1A8(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    char *obj = D_L23_00259560[D_L23_001B164C];
    char *p16;
    float B[4];
    float A[4];
    float M[16];
    float D[4];
    float C[4];
    int type;

    type = *(unsigned char *)(arg0 + 0x20);
    if (type == 0xC || type == 0x10)
        *(int *)(state + 0x598) = (((int)(D_L23_001B1640) * 5 + 2) / 6);
    else
        *(int *)(state + 0x598) = (((int)(D_L23_001B163C) * 5 + 2) / 6);
    *(int *)(state + 0x59C) = (int)obj;
    *(int *)(state + 0x590) = *(int *)(state + 0x590) - 1;
    moby_transform_joint_to_world(arg0, *(int *)(state + 0x594) + 0x1E, (char *)A);
    D_L23_001B3800 = *(TI128 *)A;
    moby_transform_joint_point(arg0, *(int *)(state + 0x594) + 0x1E, (char *)M);
    FastVecScale((char *)B, (char *)(M + 8), -16.0f);
    *(TI128 *)C = *(TI128 *)A;
    mothership_project_point_onto_surface((char *)C, 0.0f);
    p16 = obj + 0x10;
    FastVecSub((char *)D, (char *)C, state + 0x3E0);
    FastVecScale((char *)D, (char *)D, 2.2f);
    FastVecAdd((char *)B, (char *)B, (char *)D);
    FastVecAdd((char *)A, (char *)A, (char *)B);
    if (*(unsigned char *)(obj + 0x20) != 2) {
        *(TI128 *)(obj + 0xC0) = *(TI128 *)(arg0 + 0xC0);
        *(TI128 *)(obj + 0xD0) = *(TI128 *)(arg0 + 0xD0);
        *(TI128 *)(obj + 0xE0) = *(TI128 *)(arg0 + 0xE0);
        *(TI128 *)p16 = *(TI128 *)A;
    }
    FastVecScale(D_L23_001B3810, arg0 + 0xE0, D_L23_001B15B4);
    FastVecAdd(D_L23_001B3810, D_L23_001B3810, p16);
    if (D_L23_001B37F0 == 0)
        D_L23_001B37F0 = (int)ribbon_trail_create((char *)&D_L23_001B3800, 1.7f, arg0, 1.9f, D_L23_001B3810, 0.5f, 0x32,
                                                D_L23_001B15A8, 0x46, D_L23_001B15AC, D_L23_001B15B0,
                                                0xF7F0F, 0x2F00, 1, -1, 1);
    moby_set_state(obj, 1, 0);
    PlayMobySound(4, 0, arg0);
    D_L23_001B164C = (D_L23_001B164C + 1) % 25;
}
