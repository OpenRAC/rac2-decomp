#include "include_asm.h"
#include "common.h"

INCLUDE_ASM("asm/levels", func_L19_003E9400);

INCLUDE_ASM("asm/levels", func_L19_00411890);

INCLUDE_ASM("asm/levels", func_L19_00411EF0);

INCLUDE_ASM("asm/levels", func_L19_00412140);

INCLUDE_ASM("asm/levels", func_L19_004160A0);

INCLUDE_ASM("asm/levels", func_L19_004170D8);

extern void func_2EB590();

extern void func_2EB5C0();

extern float func_3183D8(float, float);

extern float func_2EBF18(float);

extern float func_2EBF30(float);

void func_L19_00417A00(char *a0)
{
    int obj = *(int *)(a0 + 0x68);

    func_2EB590(obj + 0x218);
    func_2EB5C0(obj + 0x21C);
    if (*(unsigned short *)(a0 + 0x96) < 0xFFFF) {
        *(unsigned short *)(a0 + 0x96) += 1;
    }
}

INCLUDE_ASM("asm/levels", func_L19_00417A58);


INCLUDE_ASM("asm/levels", func_L19_00417CA0);

INCLUDE_ASM("asm/levels", func_L19_00417F88);

INCLUDE_ASM("asm/levels", func_L19_0041B078);

INCLUDE_ASM("asm/levels", func_L19_0041BFD0);

INCLUDE_ASM("asm/levels", func_L19_0041C328);


INCLUDE_ASM("asm/levels", func_L19_0041E5B0);

INCLUDE_ASM("asm/levels", func_L19_0041EE60);

INCLUDE_ASM("asm/levels", func_L19_004203F0);

INCLUDE_ASM("asm/levels", func_L19_00420818);

INCLUDE_ASM("asm/levels", func_L19_00420B48);

extern int D_L19_001C9FC0[];
extern void func_L00_00323448(char *, char *, int, int, int, int, int, int);
extern void func_L00_00323958(char *, char *);
extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);

/* Arms the rig object once its data arrives, then, when the level word matches the rig's tag, applies the stored rotations to the object and to every joint record. */
void func_L19_00420EF0(char *obj)
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
            turn[0] = *(float *)(rig + 0x10) * 0.00029088825f;
            turn[1] = *(float *)(rig + 0x14) * 0.00029088825f;
            turn[2] = *(float *)(rig + 0x18) * 0.00029088825f;
            func_002833F0(mat, turn);
            func_00283738(obj + 0xC0, obj + 0xC0, mat);
            joint = rig + 0x30;
            do {
                turn[0] = *(float *)(rig + 0x1C) * 0.00029088825f;
                turn[1] = *(float *)(rig + 0x20) * 0.00029088825f;
                turn[2] = *(float *)(rig + 0x24) * 0.00029088825f;
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

/* func_L19_00421E80 is defined in L19_00421E80-g8.c. */

INCLUDE_ASM("asm/levels", func_L19_00422238);

extern u16 *D_L19_001FB5A0[];
extern u8 *D_L19_001B2A1C[] __attribute__((sda));
extern s32 D_L19_001B2A38[] __attribute__((sda));
extern s32 D_001A79F0 __attribute__((sda));
extern u8 D_0019B2E8[];
extern char D_0019B4A8[];

extern s32 func_002B38B8(u8 *);
extern void func_0029F338(u8 *);
extern void func_L02_0031F858(s32, s32);

/* The part of the object's state this function reads: the id of its first entity, three group
   words, four mark words (-1 means none). */
typedef struct {
    s32 first;
    s32 groups[3];
    u8 pad[0x10];
    s32 marks[4];
} GrelbinState;

/* Leaves at once when byte 0xBC is clear, func_002B38B8 returns zero, the entity of state word 0
   is in neither state 0xFE nor 0xFD and the table byte of the object lacks bit 7; otherwise hands
   every entity of the three groups to func_0029F338, releases the four marks, counts one nibble of
   the table byte at 0xB2 up (saturating at 7) and releases the object. */
void func_L19_00422810(u8 *a0)
{
    GrelbinState *state = *(GrelbinState **)(a0 + 0x68);
    u16 *p;
    u8 *e;
    u8 *first;
    s32 i;
    s32 k;
    u16 f;

    if (a0[0xBC] == 0) {
        if (func_002B38B8(a0) == 0) {
            if (state->first != -1) {
                first = (u8 *)((state->first << 8) + (int)D_L19_001B2A1C[0]);
                if (first[0x20] != 0xFE) {
                    if (first[0x20] != 0xFD) {
                        if ((D_0019B2E8[a0[0xB0] + D_001A79F0 * 16] & 0x80) == 0)
                            return;
                    }
                }
            }
        }
    }
    for (i = 0; i < 3; i++) {
        if (state->groups[i] == -1)
            continue;
        for (p = D_L19_001FB5A0[state->groups[i]];
             (state->groups[i] & 0xFF) != 0xFF && state->groups[i] <= D_L19_001B2A38[0] &&
             p != 0 && ((s16)p[-1] >= 0 || p == D_L19_001FB5A0[state->groups[i]]);
             p++) {
            e = D_L19_001B2A1C[0] + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            func_0029F338(e);
        }
    }
    for (k = 0; k < 4; k++) {
        if (state->marks[k] != -1)
            func_L02_0031F858(state->marks[k], 1);
    }
    f = *(u16 *)(a0 + 0xB2);
    if (f & 1) {
        u8 *q = (u8 *)(((s16)f >> 1) + (D_001A79F0 << 10)) + (int)D_0019B4A8;
        u8 c = *q;

        if (((c >> 4) & 7) != 7)
            *q = c + 0x10;
    } else {
        u8 *q = (u8 *)(((s16)f >> 1) + (D_001A79F0 << 10)) + (int)D_0019B4A8;
        u8 c = *q;

        if ((c & 7) != 7)
            *q = c + 1;
    }
    func_0029F338(a0);
}

/* func_L19_00422A98 is defined in L19_00422A98-g8.c. */

INCLUDE_ASM("asm/levels", func_L19_00423270);

INCLUDE_ASM("asm/levels", func_L19_00423548);

/* func_L19_00423A98 is in L19_003E9400-g8.c. */

INCLUDE_ASM("asm/levels", func_L19_00423CC0);

INCLUDE_ASM("asm/levels", func_L19_00423EC0);
