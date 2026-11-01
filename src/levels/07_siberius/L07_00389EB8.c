#include "common.h"
#include "include_asm.h"


/* func_L07_003B72E8 is in L07_003B72E8-g8.c. */

/* func_L07_003E4BD0 is in L07_003E4BD0-g8.c. */

/* func_L07_003E5070 is in L07_003E5070-g8.c. */

/* func_L07_003E5198 is in L07_003E5198-g8.c. */

/* func_L07_003E56B8 is in L07_003E56B8-g8.c. */


extern void func_00282978(char *);

/* Clear the two resource slots and step the state counter while it has room. */
void func_L07_003E5A70(char *arg)
{
    char *o = *(char **)(arg + 104);
    unsigned short v;

    func_00282978(o + 0x240);
    func_00282978(o + 0x242);
    v = *(unsigned short *)(arg + 0x96);
    if (v <= 0xFFFE)
        *(unsigned short *)(arg + 0x96) = v + 1;
}

extern unsigned short *D_L07_001FAD60[];

/* `sda` on an array of unknown size: cc1 emits the one-instruction load, which the assembler
   expands absolute (`lui $r` / `lw $r,%lo($r)`), as retail has it in this -G0 unit. */
extern unsigned char *D_L07_001B22DC[] __attribute__((sda));
extern int D_L07_001B22F8[] __attribute__((sda));

/* Sets the +0x244 word of every entity of the object's group state to 1. */
void func_L07_003E5AC8(unsigned char *arg0)
{
    unsigned short *p;
    unsigned char *e;

    if (arg0[0x21] == 0xFF)
        return;
    p = D_L07_001FAD60[arg0[0x21]];
    while (arg0[0x21] != 0xFF && arg0[0x21] <= D_L07_001B22F8[0] && p != 0 &&
           ((p != 0 && (short)p[-1] >= 0) || p == D_L07_001FAD60[arg0[0x21]])) {
        e = D_L07_001B22DC[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        *(int *)(*(char **)(e + 0x68) + 0x244) = 1;
        p++;
    }
}

/* Counts the entities of the group whose class is 0xD1D and whose state byte is neither 0xFE nor
   0xFD into *count; returns the last entity of the group in state 8, or 0. */
unsigned char *func_L07_003E5B70(int group, int *count)
{
    unsigned short *p;
    unsigned char *e;
    unsigned char *result;

    *count = 0;
    if (group == -1)
        return 0;
    result = 0;
    for (p = D_L07_001FAD60[group];
         (unsigned char)group != 0xFF && group <= D_L07_001B22F8[0] && p != 0 &&
         ((short)p[-1] >= 0 || p == D_L07_001FAD60[group]);
         p++) {
        e = D_L07_001B22DC[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (*(short *)(e + 0xAA) == 0xD1D && e[0x20] != 0xFE && e[0x20] != 0xFD)
            (*count)++;
        if (e[0x20] == 8)
            result = e;
    }
    return result;
}

/* func_L07_003E5C78 is defined in L07_003E5C78-helpers.c. */

/* func_L07_003E5FA8 is in L07_003E5FA8-g8.c. */

extern void func_002AD0E0(char *, int, char *, char *, char *, char *);

/* Run the shared pass on both halves of the object, then again on the
   secondary half with a stack buffer when the state byte reads nine. */
void func_L07_003E6148(char *arg)
{
    char *o = *(char **)(arg + 104);
    char tmp[16];

    func_002AD0E0(arg, *(int *)(o + 0x260), arg + 0x10, arg + 0xF0, arg + 0x10, arg + 0xF0);
    if (*(unsigned char *)(arg + 0x20) == 9)
        func_002AD0E0(arg, *(int *)(o + 0x260), o + 0x230, tmp, o + 0x230, tmp);
}

/* func_L07_003E61B8 is in the sibling file L07_00389EB8-g8.c: its body
   reaches a small-data global through $gp. */

/* func_L07_003E61E0 is in L07_003E61E0-g8.c. */

/* func_L07_003E69B8 is in L07_003E69B8-g8.c. */

/* func_L07_003E6E00 is in the sibling file L07_00389EB8-qcopy.c: its body
   copies a 16-byte vector, which needs the grouped-copy profile. */

/* Sets the +0x2D0 word of every entity of the object's group state to 1. */
void func_L07_003E6F40(unsigned char *arg0)
{
    unsigned short *p;
    unsigned char *e;

    if (arg0[0x21] == 0xFF)
        return;
    p = D_L07_001FAD60[arg0[0x21]];
    while (arg0[0x21] != 0xFF && arg0[0x21] <= D_L07_001B22F8[0] && p != 0 &&
           ((p != 0 && (short)p[-1] >= 0) || p == D_L07_001FAD60[arg0[0x21]])) {
        e = D_L07_001B22DC[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        *(int *)(*(char **)(e + 0x68) + 0x2D0) = 1;
        p++;
    }
}

extern int func_002761F8(void *,void *,int,void *,int);
extern char *func_002AD0B0(char *);
extern void func_00282CF0(void *,void *,void *);
extern void func_002AFDD8(void *,void *,void *,int);
extern int func_002AD5F8(void *,void *,void *,void *,void *,void *);
extern int func_002AD470(void *,void *,void *,void *,void *,void *);
extern void func_002833F0(void *,void *);
extern void func_002B0408(void *,void *,int);
extern void func_002AB6D8(void *,void *);
extern void func_00282D30(void *,void *,float);
typedef int Quad128 __attribute__((mode(TI)));
extern void func_00283098(Quad128 *, Quad128 *, char *);
typedef struct { char pad[24]; char *object; } Collision;
extern Collision D_L07_001BF640;

/* With no platform attached, probe below the object and attach to the object hit when it is
   a platform (flag 2), recording the relative offset; otherwise carry the object along with
   the attached platform and rebuild its orientation. */
void func_L07_003E6FE8(char *arg)
{
    char *state = *(char **)(arg + 0x68);
    float rayStart[4] __attribute__((aligned(16)));
    float rayEnd[4] __attribute__((aligned(16)));
    float localOffset[4] __attribute__((aligned(16)));
    char *pos, *platform;

    platform = *(char **)(state + 0x338);
    if (platform == 0) {
        pos = arg + 0x10;
        qcopy(rayStart, pos);
        qcopy(rayEnd, pos);
        rayStart[2] += 2.0f;
        rayEnd[2] -= 3.0f;
        if (func_002761F8(rayStart, rayEnd, 0, arg, 0) && D_L07_001BF640.object != 0) {
            if (*(int *)(func_002AD0B0(D_L07_001BF640.object) + 0x3C) & 2) {
                *(char **)(state + 0x338) = D_L07_001BF640.object;
                func_00282CF0(localOffset, pos, *(char **)(state + 0x338) + 0x10);
                func_002AFDD8(*(char **)(state + 0x338), localOffset, localOffset, 0);
                *(float *)(state + 0x33C) = localOffset[2] - 1.0f;
                func_002AD5F8(arg, *(char **)(state + 0x338), pos, arg + 0xF0,
                             state + 0x310, state + 0x320);
            }
            *(int *)(state + 0x88) |= 0x100;
        }
    } else {
        if (*(unsigned char *)(arg + 0x20) == 9 || *(unsigned char *)(arg + 0x20) == 11) {
            func_002AD470(arg, platform, state + 0x310, state + 0x320, arg + 0x10, arg + 0xF0);
        } else {
            func_002AD0E0(arg, (int)platform, arg + 0x10, arg + 0xF0, arg + 0x10, arg + 0xF0);
        }
        func_002833F0(arg + 0xC0, arg + 0xF0);
        func_002B0408(arg + 0xC0, *(char **)(state + 0x338) + 0xE0, 0);
        func_002AB6D8(arg + 0xC0, arg + 0xF0);
        if (*(unsigned short *)(arg + 0x34) & 0x8000)
            func_00282D30(arg + 0xD0, arg + 0xD0, -1.0f);
        if (*(unsigned char *)(arg + 0x95) == 3) {
            func_00282CF0(rayStart, arg + 0x10, *(char **)(state + 0x338) + 0x10);
            func_002AFDD8(*(char **)(state + 0x338), rayStart, rayStart, 0);
            rayStart[2] = *(float *)(state + 0x33C);
            func_00283098((Quad128 *)rayStart, (Quad128 *)rayStart, *(char **)(state + 0x338) + 0xC0);
            *(float *)(state + 0x180) = rayStart[2] + *(float *)(*(char **)(state + 0x338) + 0x18);
        }
    }
}

/* The 16-byte vector the object keeps. */
typedef int TI128 __attribute__((mode(TI)));

extern void func_00325D30(char *, char *);

extern void func_002A6C58(char *, int, int);

extern void func_00283098(TI128 *, TI128 *, char *);

extern void func_00282CC0(TI128 *, TI128 *, char *);

extern void func_0032C700(TI128 *, int, int, int, int, int, int, int, float, float, int, int, int,
                          int);

extern void func_002E5CF8(int, int, char *);

extern void func_00282F20(TI128 *, TI128 *, float);

extern void func_002B0A68(char *, int, TI128 *, float, float, float, float, int);

/* Arm the object's mode, then set up its position and hand it to the launcher.
   func_002B0A68's integer mask is its last parameter, and this compiler sets the
   arguments up in parameter order: the mask's store then comes after the four
   float copies, in the call's delay slot, as the retail has it. */
void func_L07_003E7240(char *arg)
{
    char *o;
    TI128 v[1];
    TI128 w;

    o = *(char **)(arg + 0x68);
    *(unsigned short *)(arg + 0x34) = (*(unsigned short *)(arg + 0x34) | 0x41) & 0xEFFF;
    *(int *)(arg + 0x98) = 0;
    func_00325D30(arg, o + 0x330);
    func_002A6C58(arg, 0, 3);
    v[0] = 0;
    ((float *)v)[2] = 0.75f;
    func_00283098(v, v, arg + 0xC0);
    func_00282CC0(v, v, arg + 0x10);
    func_0032C700(v, 0, 25, 20, 20, 20, 45, 1, 0.6f, 20.0f, 1, 0, 0, *(int *)(o + 0x338));
    func_002E5CF8(6, 0, arg);
    func_00282F20(&w, o + 0x1C0, 0.05000000447034836f);
    func_002B0A68(arg, 1016, &w, 3.0f, 6.0f, 3.0f, 6.0f, 255);
}

extern void func_002A7750(int, int, int);

extern int func_002A7820(int, int);

extern void func_L07_002E2090(char *, int, int, char *, int, int, int);

/* Arm the object's mode ten and hand it to the shared launcher. */
void func_L07_003E7380(char *arg, int a1, int a2, int a3, int a4)
{
    int r;

    func_002A7750(arg, 10, -1);
    *(unsigned short *)(arg + 0x34) = (*(unsigned short *)(arg + 0x34) & 0xFFBE) | 0x1000;
    *(int *)(arg + 0x98) = *(int *)(*(char **)(arg + 0x24) + 0x10);
    r = func_002A7820(0x2D, 0x4B);
    func_L07_002E2090(arg, a1, a2, arg + 0xF0, r, a3, a4);
}

/* func_L07_003EA900 is in L07_003EA900-g8.c. */

/* func_L07_003EB2C0 is in L07_003EB2C0-g8.c. */

extern void func_00282948(char *);

extern void func_002B0990(char *, char *, int, int, float);

extern int D_L07_001C9780;

void func_L07_003EB700(char *arg)
{
    char *o = *(char **)(arg + 104);
    unsigned short v;

    func_00282948(o + 0x2D4);
    func_00282948(o + 0x2D8);
    v = *(unsigned short *)(arg + 0x96);
    if (v <= 0xFFFE)
        *(unsigned short *)(arg + 0x96) = v + 1;
    if (D_L07_001C9780 != 0)
        func_L07_003EB838(arg);
    func_002B0990(arg, o + 0x230, 5, 1, 2.5f);
}

/* Twin of func_L07_003E6F40. */
void func_L07_003EB790(unsigned char *arg0)
{
    unsigned short *p;
    unsigned char *e;

    if (arg0[0x21] == 0xFF)
        return;
    p = D_L07_001FAD60[arg0[0x21]];
    while (arg0[0x21] != 0xFF && arg0[0x21] <= D_L07_001B22F8[0] && p != 0 &&
           ((p != 0 && (short)p[-1] >= 0) || p == D_L07_001FAD60[arg0[0x21]])) {
        e = D_L07_001B22DC[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        *(int *)(*(char **)(e + 0x68) + 0x2D0) = 1;
        p++;
    }
}

/* func_L07_003EB838 is in L07_003EB838.c. */

void func_L07_003EBAB8(char *actor)
{
    float position[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    char *state = *(char **)(actor + 0x68);
    *(int *)(actor + 0x98) = 0;
    *(unsigned short *)(actor + 0x34) = (*(unsigned short *)(actor + 0x34) | 0x41) & 0xefff;
    func_002A6C58(actor, 0, 3);
    *(TI128 *)position = 0;
    position[2] = 0.75f;
    func_00283098((TI128 *)position, (TI128 *)position, actor + 0xc0);
    func_00282CC0((TI128 *)position, (TI128 *)position, actor + 0x10);
    func_0032C700((TI128 *)position, 0, 25, 20, 20, 20, 45, 1, 0.6f, 20.0f,
                 1, 0, 0, *(int *)(state + 0x314));
    func_002E5CF8(9, 0, actor);
    func_00282F20((TI128 *)direction, (TI128 *)(state + 0x1c0), 0.0500000045f);
    func_002B0A68(actor, 0x7f8, (TI128 *)direction, 3.0f, 6.0f, 3.0f, 6.0f, 0xff);
}


/* Twin of func_L07_003E7380 with the mode eight instead of ten. */
void func_L07_003EBBE8(char *arg, int a1, int a2, int a3, int a4)
{
    int r;

    func_002A7750(arg, 8, -1);
    *(unsigned short *)(arg + 0x34) = (*(unsigned short *)(arg + 0x34) & 0xFFBE) | 0x1000;
    *(int *)(arg + 0x98) = *(int *)(*(char **)(arg + 0x24) + 0x10);
    r = func_002A7820(0x2D, 0x4B);
    func_L07_002E2090(arg, a1, a2, arg + 0xF0, r, a3, a4);
}

/* func_L07_003EE3B0 is in L07_003EE3B0-g8.c. */

extern void func_002A7750(int, int, int);

extern int func_002ACBC8(int, int);

extern void func_L02_0031F858(int, int);

extern char D_00189EA0[];

void func_L07_003EE640(char *arg)
{
    int *o = *(int **)(arg + 104);
    int *p;
    int *q;
    int i;

    switch (*(unsigned char *)(arg + 0x20)) {
    case 0:
        func_002A7750(arg, 1, -1);
        break;
    case 1:
        q = o;
        p = o + 8;
        for (i = 0; i < 8; i++) {
            if (p[i] != -1) {
                if (func_002ACBC8((int)D_00189EA0, *q) != 0) {
                    func_L02_0031F858(p[i], 1);
                    p[i] = -1;
                }
            }
            q++;
        }
        break;
    }
}

/* func_L07_003EE708 is matched in L07_003EE708-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

void func_L07_003EEBF8(char *arg, char *a1, TI128 *a2, TI128 *a3)
{
    TI128 v[2];
    TI128 *second = &v[1];
    char *s1;
    unsigned short w;

    v[0] = *a2;
    *second = *a3;

    w = *(unsigned short *)(arg + 0x34);
    *(unsigned short *)(arg + 0x34) = (w & 0xFFBE) | 0x1000;

    s1 = *(char **)(arg + 0x68);
    *(int *)(arg + 0x98) = *(int *)(*(int *)(arg + 0x24) + 0x10);
    func_002A7750((unsigned char *)arg, 2, -1);

    *(unsigned char *)(arg + 0x30) = 0xFF;
    *(short *)(arg + 0x32) = 0xFF;

    *(int *)(s1 + 0x110) = (int)a1;

    func_00283098((TI128 *)(arg + 0x10), &v[0], a1 + 0xC0);
    func_00282CC0((TI128 *)(arg + 0x10), (TI128 *)(arg + 0x10),
                  (char *)(*(int *)(s1 + 0x110) + 0x10));

    w = *(unsigned short *)(arg + 0x34);
    *(unsigned short *)(arg + 0x34) = w & 0xEFFF;

    qcopy(s1 + 0xF0, arg + 0x10);
    qcopy(s1 + 0xD0, second);
}


/* func_L07_003EECE0 is in L07_003EECE0.c. */

/* Play the fixed mode/value pair for this object. */
void func_L07_003EEE08(char *arg)
{
    func_002A7750(arg, 5, -1);
}

/* func_L07_003EEE28 is defined in L07_003EEE28-g8.c. */

extern float func_002E5460(int);

extern void func_003109C8(char *, int, int);

/* Store the mode value and the inverse of the launch factor. */
/* func_L07_003EF1E0 is matched in L07_003EF1E0.c (built with -g). */

INCLUDE_ASM("asm/levels", func_L07_003F3E80);

/* func_L07_003F43E0 is in the sibling file L07_00389EB8-g8.c: its body
   reads small-data globals through $gp. */
