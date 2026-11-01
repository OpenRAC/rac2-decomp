#include "include_asm.h"

#include "common.h"
extern s32 D_001A79F0 __attribute__((sda));
extern u8 D_0019B2E8[];
extern u8 *D_L19_001B2A1C[] __attribute__((sda));
extern int D_L19_001C9FC0[];
extern void func_L00_00323448(char *, char *, int, int, int, int, int, int);
extern void func_L00_00323958(char *, char *);
extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);
extern u16 *D_L19_001FB5A0[];
extern u8 *D_L19_001B2A1C[] __attribute__((sda));
extern s32 D_L19_001B2A38[] __attribute__((sda));
extern s32 D_001A79F0 __attribute__((sda));
extern u8 D_0019B2E8[];
extern s32 func_002B38B8(u8 *);
extern void func_0029F338(u8 *);
extern float D_L19_001B1ECC[] SDATA(D_L19_001B1ECC);
extern float D_L19_001B1ED0[] SDATA(D_L19_001B1ED0);
extern float D_L19_001B1ED4[] SDATA(D_L19_001B1ED4);
extern float D_L19_001B1ED8[] SDATA(D_L19_001B1ED8);
extern u8 D_L19_001B1EDC[] SDATA(D_L19_001B1EDC);
extern int D_L19_001B1EE0[] SDATA(D_L19_001B1EE0);
extern int D_L19_001B1EE4[] SDATA(D_L19_001B1EE4);
extern float D_L19_001B1EE8[] SDATA(D_L19_001B1EE8);
extern float D_L19_001B1EEC[] SDATA(D_L19_001B1EEC);
extern u32 D_L19_001B1EF0[] SDATA(D_L19_001B1EF0);
extern u32 D_L19_001B1EF4[] SDATA(D_L19_001B1EF4);
extern int D_L19_001B1EFC[] SDATA(D_L19_001B1EFC);
extern int D_L19_001B1F00[] SDATA(D_L19_001B1F00);

/* Arms the rig object once its data arrives, then, when the level word matches the rig's tag, applies the stored rotations to the object and to every joint record. */
void func_PAL_L19_004265E0(char *obj)
{
    char *rig = *(char **)(obj + 0x68);
    float turn[4] __attribute__((aligned(16)));
    char mat[0x30] __attribute__((aligned(16)));
    char *joint;
    int tag;

    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        if (*(long *)rig != -1) {
            { u8 a = 0xFF; *(u8 *)(obj + 0x30) = a; }
            func_L00_00323448(obj, rig + 0x30, 0x32, *(s32 *)(rig + 4), *(s32 *)rig, *(s32 *)(rig + 8), 7, 0);
            if (*(u8 *)(rig + 0x7A) == 0) {
                func_0029F338((u8 *)obj);
            } else {
                *(u8 *)(rig + 0x7D) = 1;
                *(u16 *)(obj + 0x34) |= 0x104;
                func_002833F0(obj + 0xC0, obj + 0xF0);
                *(u8 *)(obj + 0x20) = 1;
            }
        }
        return;
    case 1:
        if (D_L19_001C9FC0[0] == *(s32 *)(rig + 0xC)) {
            turn[0] = *(float *)(rig + 0x10) * 0.0003490659f;
            turn[1] = *(float *)(rig + 0x14) * 0.0003490659f;
            turn[2] = *(float *)(rig + 0x18) * 0.0003490659f;
            func_002833F0(mat, turn);
            func_00283738(obj + 0xC0, obj + 0xC0, mat);
            joint = rig + 0x30;
            do {
                turn[0] = *(float *)(rig + 0x1C) * 0.0003490659f;
                turn[1] = *(float *)(rig + 0x20) * 0.0003490659f;
                turn[2] = *(float *)(rig + 0x24) * 0.0003490659f;
                func_002833F0(mat, turn);
                func_00283738(joint, joint, mat);
                tag = *(u8 *)(joint + 0x4A);
                joint += 0x50;
            } while (tag != 1);
            func_L00_00323958(obj, rig + 0x30);
        }
        break;
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L19_00427570);
