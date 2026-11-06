#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void func_L16_00410CC0(u8 *, u8 *);

extern void func_2E74B8(void *, void *, void *);

extern float func_2E7590(void *, void *);

extern s32 func_313EA0(s32);

extern void func_30AD48(void *, s32, void *);

extern float func_313F38(float, float);

extern void func_41F1F0(void *, void *, void *, s32, float, float);

extern void func_00282DD8(void *, void *, void *);

extern void func_002ACE78(void *, void *, float);

extern void func_002A7750(void *, s32, s32);

extern void func_0029FCC0(void *, s32, void *);

extern void func_0029FC20(void *, s32, void *);

extern void func_002A0F48(void *);

extern void func_00283678(void *, void *);

extern void func_002A7470(void *, s32, s32, s32);

extern void func_00282CF0(void *, void *, void *);

extern void func_00282F20(void *, void *, float);

extern float func_00282E48(void *, void *);

extern float func_00282E80(void *, void *);

extern int func_L07_00321D68(void *, void *);

extern void func_L02_00327350(s32, s32);

extern void func_L01_00323310(s32, s32);
extern u8 *D_L16_001B2C0C[] __attribute__((sda));
extern u8 D_0013963B;

extern void func_L00_003294F0(void *, s32);

extern void func_002DF3F8(void *, void *);

extern void func_0029F338(void *);

extern void func_0029B3E0(s32, s32);

extern void func_L16_00412C58(u8 *, s32, s32);
extern void func_L16_00412BA8(u8 *, s32);

extern void func_L16_004117A8(u8 *);

extern void func_L16_00411F80(u8 *, s32);

extern void func_L16_0041ECF8(void *, float);

extern void func_002AD7B8(s32);

extern s32 func_00282948(void *);

extern void func_L16_004050D8(u8 *);

extern void func_0029F978(u8 *, s32, void *);

extern void func_00283898(void *, s32, float);

extern float func_00283BE0(float, float);

extern void func_002A8C00(void *, u8 *, s32, void *, float);

extern void func_00282CC0(void *, void *, void *);

extern float func_00282C48(float);

extern void func_002A8E20(s32, void *);

/* func_L16_00403900 is in L16_00403900-update-g8.c. */

/* func_L16_00404A60 is in the sibling file L16_00403900-g8.c: its body
   reaches the level's small-data floats through $gp. */

extern u8 *D_L16_001FE7C0[];

/* Steers the object toward the next point of its path (the state's table and cursor at
   0x294/0x2A4); advances the cursor once within half a unit, and returns 1 when the path is done. */
s32 func_L16_00404E40(u8 *moby)
{
    float point[4] __attribute__((aligned(16)));
    float step[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *path = D_L16_001FE7C0[*(s32 *)(state + 0x294)];

    if (*(s32 *)(state + 0x2A4) >= *(s32 *)path)
        return 1;
    qcopy(point, path + 16 + *(s32 *)(state + 0x2A4) * 16);
    func_00282CF0(step, point, moby + 0x10);
    func_00282F20(step, step, 0.20000002f);
    func_L07_00321D68(moby, step);
    if (*(s32 *)(state + 0x2AC) != 0) {
        if (func_00282E48(moby + 0x10, point) < 0.5f)
            (*(s32 *)(state + 0x2A4))++;
    } else {
        if (func_00282E80(moby + 0x10, point) < 0.5f)
            (*(s32 *)(state + 0x2A4))++;
    }
    return 0;
}

/* func_L16_00404F50 is defined in L16_00404F50.c. */

/* func_L16_004050D8 is defined in L16_004050D8-helpers.c. */

/* func_L16_00405488 is in L16_00405488-g8.c. */


/* func_L16_0040C840 is in L16_0040C840-g8.c. */

extern void func_002B60B0(void *, float, float, float, float);
extern s32 func_00283CF0(float);
extern s32 D_L16_001B2648 MACRO_ADDR;
extern float func_00283198(float);
extern void func_002AA548(void *, void *, float, float, float, float);
extern void func_L16_00412F48(u8 *);
extern void func_002A93B0(void *);
extern s32 func_002B0ED8(void *, void *, s32);
extern void func_L16_0040D188(u8 *);
extern s32 func_002B3BA8(void *, s32, float, float, s32, s32);
extern float D_L16_001B9B00[];

/* Object update: on the first frame (+0x20 still zero) sets the state's defaults and
   rates; then, with +0x31 set and the object within 32 units of D_L16_001B9B00, runs
   func_002A93B0 and sets +0x6F to 30; marks the group when func_002B0ED8 reports, and
   runs func_002B3BA8 on the state's two slots, keeping the object's +0x18 across them. */
void func_L16_0040CD88(u8 *arg)
{
    u8 *state;

    state = *(u8 **)(arg + 0x68);
    if (arg[0x20] == 0) {
        *(s32 *)(state + 0x54) = 0;
        *(s32 *)(state + 0x7C) = 0;
        state[0x150] = 5;
        *(s32 *)(state + 0x188) = 3;
        *(float *)(state + 0x17C) = 0.15f;
        *(float *)(state + 0x50) = 1.868f;
        *(float *)(state + 0x170) = 0.5f;
        *(float *)(state + 0x174) = 0.5f;
        *(float *)(state + 0x58) = 0.5f;
        *(float *)(state + 0x5C) = 0.5f;
        *(float *)(state + 0x60) = 3.141593f;
        *(float *)(state + 0x80) = 0.52359885f;
        func_002B60B0(arg, 0.0022222223f, 0.06666667f, 0.00043633237f, 0.034906592f);
        *(s32 *)(state + 0x88) |= 2;
        if (*(s16 *)(state + 0x24) == 0) {
            *(s16 *)(state + 0x24) = 1;
            *(float *)(state + 0x20) = 1.0f;
        }
        func_002A7750(arg, 1, 0);
        if (arg[0x43])
            func_002A7470(arg, 0, 0, 0);
        state[0x48] = func_00283CF0(18.0f);
        state[0x4A] = func_00283CF0(16.0f);
        *(float *)(state + 0x358) = *(float *)(arg + 0x18);
    }
    if (arg[0x31] && func_00282E48(arg + 0x10, D_L16_001B9B00) < 32.0f) {
        func_002A93B0(arg);
        arg[0x6F] = 30;
    }
    if (func_002B0ED8(arg, state + 0x140, 0))
        func_L16_0040D188(arg);
    *(s32 *)(state + 0x240) = func_002B3BA8(arg, *(s32 *)(state + 0x230), *(float *)(state + 0x234), 0.0f, 0, 0);
    *(s32 *)(state + 0x354) = func_002B3BA8(arg, *(s32 *)(state + 0x350), 0.0f, 0.0f, 0, 0);
    *(float *)(arg + 0x18) = *(float *)(state + 0x358);
}

/* func_L16_0040CF98 is defined in L16_00403900-g8.c. */

extern u16 *D_L16_001FB660[];

/* `sda` on an array of unknown size: cc1 emits the one-instruction load, which the assembler
   expands absolute (`lui $r` / `lw $r,%lo($r)`), as retail has it in this -G0 unit. */
extern u8 *D_L16_001B2B1C[] __attribute__((sda));
extern s32 D_L16_001B2B38[] __attribute__((sda));

/* Sets a flag word in the state record (+0x68) of every entity of the object's group, stopping
   at the first id with no entity: +0x244 for class 0xF35, +0x24C for class 0xEA3. */
void func_L16_0040D188(u8 *arg0)
{
    u16 *p;
    u8 *e;

    if (arg0[0x21] == 0xFF)
        return;
    p = D_L16_001FB660[arg0[0x21]];
    while (arg0[0x21] != 0xFF && arg0[0x21] <= D_L16_001B2B38[0] && p != 0 &&
           ((p != 0 && (s16)p[-1] >= 0) || p == D_L16_001FB660[arg0[0x21]])) {
        e = D_L16_001B2B1C[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (*(s16 *)(e + 0xAA) == 0xF35)
            *(s32 *)(*(u8 **)(e + 0x68) + 0x244) = 1;
        else if (*(s16 *)(e + 0xAA) == 0xEA3)
            *(s32 *)(*(u8 **)(e + 0x68) + 0x24C) = 1;
        p++;
    }
}


/* func_L16_0040D4E8 is compiled from L16_0040D4E8-g16.c. */



/* func_L16_00410618 is in L16_00410618-g8.c. */

/* func_L16_00410B88 is defined in L16_00403900-g8.c (this unit has no $gp access for it). */

/* Copies the measured 32-bit field pair of the handle reached at 0x68 onto the second
   pair after the helper has prepared the object's second half. */
void func_L16_00410C80(u8 *arg)
{
    u8 *s0;

    s0 = *(u8 **)(arg + 0x68);
    func_L16_00410CC0(arg, arg + 0x10);
    *(s32 *)(s0 + 0x220) = *(s32 *)(s0 + 0x1F4);
    *(s32 *)(s0 + 0x224) = *(s32 *)(s0 + 0x1F8);
}

/* func_L16_00410CC0 is defined in L16_00410CC0.c. */

extern s32 func_L16_00417788(void *);
extern s32 func_002ACBC8(void *, s32);
extern s32 func_002A77E0(s32);

/* Picks the row of the level's table that is closest to the handle, then, from a random
   start, the first other usable row, and copies it into the state's slot at 0x200. */
void func_L16_00410E40(u8 *arg0)
{
    u8 **base;
    u8 *state;
    u8 *table;
    u8 *slot;
    s32 target;
    u8 *p;
    s32 i;
    s32 best;
    s32 found;
    s32 start;
    s32 rem;
    s32 result;
    f32 bestf;
    f32 f;

    base = D_L16_001FE7C0;
    i = 0;
    best = -1;
    state = *(u8 **)(arg0 + 0x68);
    bestf = 1024.0f;
    table = base[*(s32 *)(state + 0x170)];
    target = func_L16_00417788(*(void **)(state + 0x24C));
    p = table + 0x10;
    do {
        f = func_00282E80(arg0 + 0x10, p);
        if (f < bestf) {
            bestf = f;
            best = i;
        }
        i++;
        p += 0x10;
    } while (i < 8);
    found = -1;
    start = func_002A77E0(8);
    i = 0;
    while (i < 8) {
        /* Never read: the invariant also computed after the loop is what makes gcse insert
           it on the loop's entry path, which keeps loop.c off this loop (phony). */
        slot = state + 0x200;
        rem = (i + start) % 8;
        result = func_002ACBC8(table + (rem * 16 + 0x10), target);
        if (result == 0) {
            i++;
            continue;
        }
        if (rem != best) {
            found = rem;
            break;
        }
        i++;
    }
    qcopy(state + 0x200, table + (found * 16 + 0x10));
    func_L16_00410CC0(arg0, state + 0x200);
}

/* func_L16_00410FA8 is in L16_00410CC0.c. */

/* func_L16_004110D0 is compiled from L16_004110D0-g8.c. */

void func_L16_00411368(u8 *arg)
{
    u8 *s0;
    u8 *s1;
    float f20;
    float period = 120.0f;

    s0 = arg;
    s1 = *(u8 **)(arg + 0x68);
    f20 = 10.0f;
    if (s0[0x20] == 0xD || s0[0x20] == 0xF || s0[0x20] == 0xE || s0[0x20] == 0x11)
        f20 = 25.0f;
    f20 = f20 + func_00283198((float)(D_L16_001B2648 % func_00283CF0(120.0f)) / period * 6.2831855f - 3.1415927f);
    func_002AA548(s0 + 0x18, s1 + 0x268, *(float *)(s1 + 0x264) + f20,
                  0.0083333338f, 0.0027777778f, 0.16666667f);
    func_L16_00412F48(s0);
}

/* func_L16_00411480 is defined in L16_00403900-g8.c. */

/* func_L16_00411600 is in L16_00411600-qcopy.c. */

/* Routes one transition request to the handle itself or to its first child, depending on
   the state word and on which of the two animation slots is current. */
void func_L16_004116C8(u8 *arg0, s32 arg1, s32 duration, float f)
{
    u8 *s2;

    s2 = *(u8 **)(arg0 + 0x68);
    if (*(s32 *)(s2 + 0x26C) == 0) {
        if (*(u8 *)(arg0 + 0x43) != arg1)
            func_002A7470(arg0, arg1, (s32)f, duration);
    } else {
        if (*(u8 *)(arg0 + 0x43) != 0x16)
            func_002A7470(arg0, 0x16, (s32)f, duration);
        if (arg1 == 0xA)
            arg1 = 0x16;
    }
    if (arg1 < 0x11)
        func_002A7470(*(u8 **)(s2 + 0x1F0), arg1, (s32)f, duration);
    else
        func_002A7470(*(u8 **)(s2 + 0x1F0), 0, (s32)f, duration);
}

/* func_L16_004117A8 is defined in L16_004117A8.c. */

/* func_L16_00411900 is defined in L16_00411900-g8.c. */

/* func_L16_00411B40 is defined in L16_00411B40-g16.c. */

/* func_L16_00411D00 is defined in L16_00411D00-g8.c. */

/* func_L16_00411F80 is defined in L16_00411F80.c. */

/* func_L16_00412560 is defined in L16_00412560-g32.c. */

/* func_L16_00412AF0 is defined in L16_00403900-g8.c (this unit has no $gp access for it). */

/* The voice-load state the level shares with the engine (see L03VoiceState in L03_003F09C0.c). */
typedef struct {
    u8 pad[0x24];
    s32 key;
    s32 selection;
    u8 pad2[0x3C];
    s32 active;
} L16VoiceState;

extern L16VoiceState D_001A63A8;
extern int D_L16_001B1888[];
extern void func_002A6170(void *);

/* Asks the engine to load voice line idx, from the first table below 20 and the second from 20 up,
   unless a load is active or pending or that line is already the current one. The arms are written
   out: cross-jump merges their stores after allocation, which leaves them before the shared tail. */
void func_L16_00412BA8(u8 *arg, s32 idx)
{
    L16VoiceState *voice = &D_001A63A8;
    u8 *s;

    s = *(u8 **)(arg + 0x68);
    if (voice->active == 0) {
        if (voice->key == -1 && idx != *(s32 *)(s + 0x354)) {
            if (idx < 20) {
                s32 v = *(s32 *)(s + (idx << 2) + 0x280);
                voice->selection = 0;
                voice->key = (v & 0x3FFF) + 0x7D0;
            } else {
                s32 v = *(s32 *)(s + ((idx - 20) << 2) + 0x2D0);
                voice->selection = 0;
                voice->key = (v & 0x3FFF) + 0x7D0;
            }
            func_002A6170(D_L16_001B1888);
            *(u8 *)(s + idx + 0x310) = 1;
            *(s32 *)(s + 0x350) = 0x384;
            *(s32 *)(s + 0x354) = idx;
        }
    }
}

/* Walks a rotating candidate index over the measured byte table until a free slot
   is found, arms it, and clears the whole window when none is. */
void func_L16_00412C58(u8 *arg, s32 start, s32 end)
{
    u8 *s3;
    s32 n;
    s32 i;
    s32 k;

    s3 = *(u8 **)(arg + 0x68);
    if (end < start)
        return;
    n = end - start + 1;
    k = func_313EA0(n);
    for (i = 0; i < n; i++) {
        u8 *tbl = s3 + 0x310;

        if (tbl[start + k] == 0) {
            func_L16_00412BA8(arg, start + k);
            return;
        }
        k = (k + 1) % n;
    }
    for (i = 0; i < n; i++)
        s3[0x310 + start + i] = 0;
    func_L16_00412BA8(arg, start + k);
}

/* Finishes the pending entry (its two saved vectors are copied back), then resets the
   level's handles. */
void func_L16_00412D48(u8 *arg)
{
    u8 *s0;
    s32 a0;
    u8 *tbl;

    s0 = *(u8 **)(arg + 0x68);
    if (*(s32 *)(s0 + 0x1BC) != 0) {
        s32 h = *(s32 *)(s0 + 0x1B0);
        s32 m = *(s32 *)(s0 + 0x1B4);

        *(s32 *)(s0 + 0x1BC) = 0;
        func_L02_00327350(h, m);
        a0 = *(s32 *)(s0 + 0x1B8) << 7;
        tbl = D_L16_001B2C0C[0];
        qcopy(arg + 0x10, tbl + 0x30 + a0);
        qcopy(arg + 0xF0, tbl + 0x70 + a0);
        func_L01_00323310(*(s32 *)(s0 + 0x1A4), -1);
    } else {
        func_L01_00323310(*(s32 *)(s0 + 0x1A4), *(s32 *)(s0 + 0x1AC));
    }
    D_0013963B = 1;
    func_L16_004117A8(arg);
    func_L16_00411F80(arg, 1);
    func_L00_003294F0(D_L16_001B2B1C[0] + (*(s32 *)(s0 + 0x190) << 8), 1);
    func_002DF3F8(D_L16_001B2C0C[0] + (*(s32 *)(s0 + 0x198) << 7) + 0x30,
                  D_L16_001B2C0C[0] + (*(s32 *)(s0 + 0x198) << 7) + 0x70);
    func_L16_00412C58(arg, 0, 2);
    func_0029B3E0(0, -1);
    func_002A7750(arg, 2, 1);
}

/* Level teardown: releases the handles the level state holds. */
extern char D_00189EA0[];

void func_L16_00412E70(char *arg0) {
    char *s0 = *(char **)(arg0 + 0x68);

    D_0013963B = 2;
    func_L16_0041ECF8(D_L16_001B2B1C[0] + (*(s32 *)(s0 + 0x190) << 8), 0.0f);
    func_L02_00327350(*(s32 *)(s0 + 0x188), *(s32 *)(s0 + 0x18C));
    func_002DF3F8(D_00189EA0, D_00189EA0 + 0x10);
    func_002AD7B8(0x11);
    if (*(s32 *)(s0 + 0x1F0) != 0)
        func_0029F338((void *)*(s32 *)(s0 + 0x1F0));
    if (*(s32 *)(s0 + 0x238) != 0)
        func_0029F338((void *)*(s32 *)(s0 + 0x238));
    if (*(s32 *)(s0 + 0x23C) != 0)
        func_0029F338((void *)*(s32 *)(s0 + 0x23C));
    func_L01_00323310(*(s32 *)(s0 + 0x1A0), -1);
    func_0029B3E0(0, -1);
    func_0029F338(arg0);
}


/* func_L16_00412F48 is in L16_00412F48-g8.c. */

/* func_L16_004130B0 is in L16_004130B0-qcopy.c. */

extern void func_00283958(void *, void *);
extern void func_00283738(void *, void *, void *);
extern s32 func_002A9640(void *, s32, s32);
extern s32 func_00277258(void *, s32, void *, float);
extern void func_0032DA58(void *, void *, void *, float);
extern void func_002A8C28(void *, void *, s32, s32, s32, s32, float, float, float);
extern void func_002AB6D8(void *, void *);
extern void func_002A7A00(void *, float, float);
extern float func_002A7878(float, float);
extern void func_00273730(void *, s32, s32, s32, void *, void *, void *, s32, float, float);

/* State 0: moves by the state's velocity and frees itself when the state's timer (+0x30)
   runs out, unless +0x31 is set. State 2: moves, lowers the velocity's third component by
   +0x34, turns its basis by the state's rotation and ages; on a collision record, or past
   90 frames when func_00277258 reports, it runs its impact effects toward D_L16_001B9B00,
   spawns six particles and frees itself. */
void func_L16_004133B0(u8 *arg)
{
    float rotation[12];
    float toward[4];
    float velocity[4];
    u8 *state;
    u8 *basis;
    u8 *angles;
    s32 hit;
    u32 old;
    u32 age;
    s32 i;
    s32 kind;
    float speed;
    float life;

    state = *(u8 **)(arg + 0x68);
    switch (arg[0x20]) {
    case 0:
        func_00282CC0(arg + 0x10, arg + 0x10, state);
        if (func_00282948(state + 0x30) && !arg[0x31])
            func_0029F338(arg);
        break;
    case 2:
        func_00282CC0(arg + 0x10, arg + 0x10, state);
        basis = arg + 0xC0;
        *(float *)(state + 8) -= *(float *)(state + 0x34);
        func_00283958(state + 0x20, rotation);
        func_00283738(basis, rotation, basis);
        hit = 0;
        if (func_002A9640(arg, 0x10000, 0))
            hit = 1;
        age = *(u16 *)(arg + 0x96);
        old = age++;
        *(u16 *)(arg + 0x96) = age;
        if (old > 90 && func_00277258(arg + 0x10, 0, arg, 1.0f))
            hit = 1;
        if (hit) {
            func_00282CF0(toward, D_L16_001B9B00, arg + 0x10);
            angles = arg + 0xF0;
            func_00282F20(toward, toward, 1.0f);
            func_0032DA58(arg, arg + 0x10, toward, 0.0f);
            func_002A8C28(arg, arg + 0x10, 0x10001, 0, 1, 0, 4.0f, 20.0f, 2.0f);
            func_002AB6D8(basis, angles);
            for (i = 0; i < 6; i++) {
                func_002A7A00(velocity, 0.0f, 0.33333334f);
                func_00282CC0(velocity, velocity, state);
                kind = *(s16 *)(arg + 0xAA);
                speed = func_002A7878(180.0f, 720.0f);
                life = func_002A7878(5.0f, 15.0f);
                func_00273730(arg, 2, kind, i, arg + 0x10, arg + 0xF0, velocity, 255, speed, life);
            }
            func_0029F338(arg);
        }
        break;
    }
}

/* Prepares a 16-byte record from the handle and reports one when the queried value
   does not exceed zero. */
s32 func_L16_00413638(u8 *arg)
{
    s32 buf[4];
    u8 *s0;

    s0 = *(u8 **)(arg + 0x68);
    func_2E74B8(buf, s0 + 0x10, arg + 0x10);
    if (func_2E7590(s0, buf) <= 0.0f)
        return 1;
    return 0;
}

/* func_L16_00413700 is in L16_00413700-qcopy.c. */

/* func_L16_00413D10 is in L16_00413D10-g8.c. */
