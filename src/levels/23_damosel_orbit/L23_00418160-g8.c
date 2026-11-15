#include "names.h"
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

extern void func_0029FCC0(char *, int, char *);

extern void func_0029FC20(char *, int, char *);

extern void func_00282D30(char *, char *, float);

extern void func_00282CC0(char *, char *, char *);

extern void func_00282CF0(char *, char *, char *);

extern int D_L23_001B164C __attribute__((sda));

extern int D_L23_001B163C __attribute__((sda));

extern int D_L23_001B1640 __attribute__((sda));

extern float D_L23_001B15A8 __attribute__((sda));

extern short D_L23_001B15AC __attribute__((sda));

extern short D_L23_001B15B0 __attribute__((sda));

extern void func_L23_00418650(char *, float);

extern void func_002A7750(char *, int, int);

extern int func_002E5CF8(int, int, char *);

extern void *func_L23_004256F0(char *, float, char *, float, char *, float, unsigned char, float,
                               unsigned char, short, short, int, int, int, int, int);

/* Fires a shot from the gun joint at the next target in the ring, starts the beam effect and plays its sound. */
void func_L23_00418160(char *moby) {
    char *state = *(char **)(moby + 0x68);
    char *obj = D_L23_00259560[D_L23_001B164C];
    char *p16;
    float backOffset[4];
    float jointPos[4];
    float jointMatrix[16];
    float dirVec[4];
    float flatPos[4];
    int mode;

    mode = *(unsigned char *)(moby + 0x20);
    if (mode == 0xC || mode == 0x10)
        *(int *)(state + 0x598) = D_L23_001B1640;
    else
        *(int *)(state + 0x598) = D_L23_001B163C;
    *(int *)(state + 0x59C) = (int)obj;
    *(int *)(state + 0x590) = *(int *)(state + 0x590) - 1;
    TransformMobyJointToWorld(moby, *(int *)(state + 0x594) + 0x1E, (char *)jointPos);
    D_L23_001B3800 = *(TI128 *)jointPos;
    TransformMobyJointPoint(moby, *(int *)(state + 0x594) + 0x1E, (char *)jointMatrix);
    FastVecScale((char *)backOffset, (char *)(jointMatrix + 8), -16.0f);
    *(TI128 *)flatPos = *(TI128 *)jointPos;
    ProjectPointOntoPlanetSurface((char *)flatPos, 0.0f);
    p16 = obj + 0x10;
    FastVecSub((char *)dirVec, (char *)flatPos, state + 0x3E0);
    FastVecScale((char *)dirVec, (char *)dirVec, 2.2f);
    FastVecAdd((char *)backOffset, (char *)backOffset, (char *)dirVec);
    FastVecAdd((char *)jointPos, (char *)jointPos, (char *)backOffset);
    if (*(unsigned char *)(obj + 0x20) != 2) {
        *(TI128 *)(obj + 0xC0) = *(TI128 *)(moby + 0xC0);
        *(TI128 *)(obj + 0xD0) = *(TI128 *)(moby + 0xD0);
        *(TI128 *)(obj + 0xE0) = *(TI128 *)(moby + 0xE0);
        *(TI128 *)p16 = *(TI128 *)jointPos;
    }
    FastVecScale(D_L23_001B3810, moby + 0xE0, D_L23_001B15B4);
    FastVecAdd(D_L23_001B3810, D_L23_001B3810, p16);
    if (D_L23_001B37F0 == 0)
        D_L23_001B37F0 = (int)CreateRibbonTrail((char *)&D_L23_001B3800, 1.7f, moby, 1.9f, D_L23_001B3810, 0.5f, 0x32,
                                                D_L23_001B15A8, 0x46, D_L23_001B15AC, D_L23_001B15B0,
                                                0xF7F0F, 0x2F00, 1, -1, 1);
    SetMobyState(obj, 1, 0);
    PlayMobySound(4, 0, moby);
    D_L23_001B164C = (D_L23_001B164C + 1) % 25;
}
