#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L16_004176B0);

#include "common.h"
extern s32 func_313EA0(s32);
extern u8 *D_L16_001B2C0C[] __attribute__((sda));
extern u8 D_0013963B;
extern void func_L16_00412BA8(u8 *, s32);
extern s32 func_00282948(void *);
extern u8 *D_L16_001FE7C0[];
extern s32 func_00283CF0(float);
extern s32 func_002B0ED8(void *, void *, s32);
extern s32 func_002B3BA8(void *, s32, float, float, s32, s32);
extern u8 *D_L16_001B2B1C[] __attribute__((sda));
extern s32 D_L16_001B2B38[] __attribute__((sda));
typedef struct {
    u8 pad[0x24];
    s32 key;
    s32 selection;
    u8 pad2[0x3C];
    s32 active;
} L16VoiceState;
extern L16VoiceState D_001A63A8;
extern int D_L16_001B1888[];
extern void func_0026FEB8(void *);
extern s32 func_002A9640(void *, s32, s32);
extern s32 func_00277258(void *, s32, void *, float);

/* Asks the engine to load voice line idx, from the first table below 20 and the second from 20 up,
   unless a load is active or pending or that line is already the current one. The arms are written
   out: cross-jump merges their stores after allocation, which leaves them before the shared tail. */
void func_PAL_L16_00417D10(u8 *arg, s32 idx)
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
            func_0026FEB8(D_L16_001B1888);
            *(u8 *)(s + idx + 0x310) = 1;
            *(s32 *)(s + 0x350) = 0x2EE;
            *(s32 *)(s + 0x354) = idx;
        }
    }
}


extern s32 func_002A77E0(s32);
extern void func_L16_00412C58(u8 *, s32, s32);
extern void func_PAL_L16_00417D10(u8 *, s32);

/* Walks a rotating candidate index over the measured byte table until a free slot
   is found, arms it, and clears the whole window when none is. */
void func_PAL_L16_00417DC0(u8 *arg, s32 start, s32 end)
{
    u8 *s3;
    s32 n;
    s32 i;
    s32 k;

    s3 = *(u8 **)(arg + 0x68);
    if (end < start)
        return;
    n = end - start + 1;
    k = func_002A77E0(n);
    for (i = 0; i < n; i++) {
        u8 *tbl = s3 + 0x310;

        if (tbl[start + k] == 0) {
            func_PAL_L16_00417D10(arg, start + k);
            return;
        }
        k = (k + 1) % n;
    }
    for (i = 0; i < n; i++)
        s3[0x310 + start + i] = 0;
    func_PAL_L16_00417D10(arg, start + k);
}


extern void func_002A7750(void *, s32, s32);
extern void func_PAL_L02_003294D8(s32, s32);
extern void func_L01_00323310(s32, s32);
extern void func_L00_003294F0(void *, s32);
extern void func_002DF3F8(void *, void *);
extern void func_0029B3E0(s32, s32);
extern void func_PAL_L16_00417DC0(u8 *, s32, s32);
extern void func_L16_004117A8(u8 *);
extern void func_L16_00411F80(u8 *, s32);

/* Finishes the pending entry (its two saved vectors are copied back), then resets the
   level's handles. */
void func_PAL_L16_00417EB0(u8 *arg)
{
    u8 *s0;
    s32 a0;
    u8 *tbl;

    s0 = *(u8 **)(arg + 0x68);
    if (*(s32 *)(s0 + 0x1BC) != 0) {
        s32 h = *(s32 *)(s0 + 0x1B0);
        s32 m = *(s32 *)(s0 + 0x1B4);

        *(s32 *)(s0 + 0x1BC) = 0;
        func_PAL_L02_003294D8(h, m);
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
    func_PAL_L16_00417DC0(arg, 0, 2);
    func_0029B3E0(0, -1);
    func_002A7750(arg, 2, 1);
}


extern void func_0029F338(void *);
extern void func_L16_0041ECF8(void *, float);
extern void func_002AD7B8(s32);
extern char D_00189EA0[];

void func_PAL_L16_00417FD8(char *arg0) {
    char *s0 = *(char **)(arg0 + 0x68);

    D_0013963B = 2;
    func_L16_0041ECF8(D_L16_001B2B1C[0] + (*(s32 *)(s0 + 0x190) << 8), 0.0f);
    func_PAL_L02_003294D8(*(s32 *)(s0 + 0x188), *(s32 *)(s0 + 0x18C));
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


INCLUDE_ASM("asm/pal/levels", func_PAL_L16_004180B0);


extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float D_L16_001B9B00[];
extern u16 *D_L16_001FB660[];
extern void func_00283958(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_PAL_0032F3B8(void *, void *, void *, float);
extern void func_002A8C28(void *, void *, s32, s32, s32, s32, float, float, float);
extern void func_002AB6D8(void *, void *);
extern void func_002A7A00(void *, float, float);
extern float func_002A7878(float, float);
extern void func_PAL_002735D0(void *, s32, s32, s32, void *, void *, void *, s32, float, float);

/* State 0: moves by the state's velocity and frees itself when the state's timer (+0x30)
   runs out, unless +0x31 is set. State 2: moves, lowers the velocity's third component by
   +0x34, turns its basis by the state's rotation and ages; on a collision record, or past
   90 frames when func_00277258 reports, it runs its impact effects toward D_L16_001B9B00,
   spawns six particles and frees itself. */
void func_PAL_L16_00418580(u8 *arg)
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
        if (old > 75 && func_00277258(arg + 0x10, 0, arg, 1.0f))
            hit = 1;
        if (hit) {
            func_00282CF0(toward, D_L16_001B9B00, arg + 0x10);
            angles = arg + 0xF0;
            func_00282F20(toward, toward, 1.0f);
            func_PAL_0032F3B8(arg, arg + 0x10, toward, 0.0f);
            func_002A8C28(arg, arg + 0x10, 0x10001, 0, 1, 0, 4.0f, 20.0f, 2.0f);
            func_002AB6D8(basis, angles);
            for (i = 0; i < 6; i++) {
                func_002A7A00(velocity, 0.0f, 0.40000004f);
                func_00282CC0(velocity, velocity, state);
                kind = *(s16 *)(arg + 0xAA);
                speed = func_002A7878(180.0f, 720.0f);
                life = func_002A7878(5.0f, 15.0f);
                func_PAL_002735D0(arg, 2, kind, i, arg + 0x10, arg + 0xF0, velocity, 255, speed, life);
            }
            func_0029F338(arg);
        }
        break;
    }
}

