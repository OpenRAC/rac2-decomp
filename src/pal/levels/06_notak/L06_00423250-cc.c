/* func_PAL_L06_00423250, the PAL copy of func_L06_0041EF08: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; rename func_002B0ED8 becomes func_PAL_002B1A50; rename func_002A6C58 becomes func_PAL_002A7650; rename func_002AC728 becomes func_PAL_002AD288. */
#include "common.h"

extern int func_00283CF0(float);
extern int func_002A7820(int, int);
/* EE argument banks preserve position/count/velocity/color/flags and four floats. */
/* The two flags the re-arm sets, at 0x001395B8. */
typedef struct {
    char pad_000[0x13];
    char flag_013;
    char flag_014;
} L06ArmFlags;

extern L06ArmFlags D_L06_001395B8;

extern void func_L06_00457C00(char *, int, void *, int, float, float, float, float);
extern int func_32E728(float);
extern int func_35A620(int);
extern void func_L06_004579C8(char *);

extern void func_00282CC0(void *, void *, void *);
void func_L06_004579C8(char *a0);

/* func_L06_0041DED8 is defined in L06_0041DED8-update.c. */

extern char D_L06_001B0820[];
extern char D_L06_001B9840[];
extern int func_L02_0032E508(void *, int, void *, int);
extern void func_0026FEB8(const char *, ...);
extern float func_002A78D8(float, float);
extern void func_002A7750(void *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern int func_PAL_002B1A50(void *, void *, int);
extern void func_L06_0041F798(u8 *);
extern s32 func_002B3BA8(void *, s32, float, float, s32, s32);
extern void func_PAL_002A7650(void *, int, int);
extern void func_PAL_002AD288(void *, void *, int, float, float);
extern void func_0029F338(void *);

/* A Notak enemy's update, the same shape as func_L06_00443A38: spawn-time setup, then the
   distance, target and ground checks. The fields are indexed through typed pointers (in-struct
   MEMs), and the setup's store order is the one that gives retail's schedule and registers.
   qzero_nc's bare volatile asm flushes cse, so the later `m[0x43] != 3` test builds a fresh 3
   rather than keeping the setup's 3 in a saved register across the calls, as retail does. */
#define B(o) (v[o])
#define H(o) (((short *)v)[(o) / 2])
#define I(o) (((int *)v)[(o) / 4])
#define F(o) (((float *)v)[(o) / 4])

void func_PAL_L06_00423250(u8 *m)
{
    u8 *v = *(u8 **)(m + 0x68);
    int hit;

    if (m[0x20] == 0) {
        I(0x480) = func_L02_0032E508(m, I(0x230), v + 0x260, 16);
        func_0026FEB8(D_L06_001B0820, I(0x480));
        qcopy(v + 0x460, m + 0x10);
        F(0x46C) = *(float *)(m + 0xF8);
        B(0x70) = 15;
        I(0xA8) = 3;
        B(0x71) = 12;
        F(0x90) = 0.5f;
        B(0x28) = 1;
        B(0xD4) = 0;
        H(0x26) = 0;
        B(0x72) = 16;
        B(0x76) = 14;
        B(0x77) = 15;
        F(0x7C) = 0.24000001f;
        F(0x80) = 0.15f;
        F(0x84) = 0.008f;
        F(0x88) = 0.014f;
        F(0x8C) = 0.006f;
        F(0x94) = 0.5f;
        F(0x9C) = 0.4f;
        B(0xCC) = 7;
        B(0xCD) = 12;
        B(0xCE) = 3;
        B(0xCF) = 5;
        B(0xD2) = 10;
        B(0xD3) = 17;
        F(0x5AC) = (float)B(0x34);
        B(0x29) = 1;
        F(0x30) = 0.75f;
        F(0x47C) = func_002A78D8(10.0f, 25.0f) * 0.0174532942f;
        I(0x478) = 0;
        H(0x24C) = func_002A7820(0, 0x5F);
        I(0x498) = -1;
        I(0x5A0) = H(0x490);
        qzero_nc(v + 0x5B0);
        func_002A7750(m, 1, 0);
        if (m[0x43] != 1)
            func_PAL_002A7E68(m, 1, 0, 0);
        B(0x48) = func_00283CF0(20.0f);
        B(0x4A) = func_00283CF0(8.0f);
        if (H(0x492) != 0) {
            if (m[0x43] != 3)
                func_PAL_002A7E68(m, 3, 0, 0);
            B(0x48) = func_00283CF0(20.0f);
            B(0x4A) = func_00283CF0(24.0f);
        }
    }
    if (m[0x31] != 0 && func_00282E48(m + 0x10, D_L06_001B9840) < 24.0f) {
        func_002A93B0(m);
        m[0x6F] = 0x16;
    }
    hit = func_PAL_002B1A50(m, v + 0x60, 0);
    if (hit != 0) {
        if (B(0x37) == 10)
            B(0xD7) = 1;
        if (hit == 5) {
            I(0xF0) = 0;
            F(0xF4) = 1.0053098f;
        }
        func_L06_0041F798(m);
        m[0xA8] = 0xFF;
    }
    I(0x228) = func_002B3BA8(m, I(0x220), F(0x240), 10.0f, 0, 0);
    I(0x22C) = func_002B3BA8(m, I(0x224), F(0x244), 10.0f, 0, 0);
    if (*(float *)(m + 0x18) < 48.0f) {
        func_PAL_002A7650(m, 0, 3);
        func_PAL_002AD288(m, m + 0x10, -1, 1.0f, 13.0f);
        func_0029F338(m);
    }
}

#undef B
#undef H
#undef I
#undef F

/* Turns the actor toward its target and keeps the two angles it stores at +0x470 and
   +0x474 of its state; returns 1 when the actor's state changed. */
/* func_L06_0041F558 is defined in L06_0041F558.c. */

extern char D_L06_001B9840[];
extern int func_35A620(int);
extern int func_32E728(float);
/* func_L06_0041FC58 is matched in its own unit, src/levels/06_notak/L06_0041FC58-qcopy.c (-frac2-qcopy -frac2-qcopy-barrier). */

/* func_L06_00420080 is defined in L06_00420080.c. */

/* func_L06_00420548 is defined in L06_00420548-g.c. */

/* func_L06_00420740 is defined in L06_00420740.c. */

/* func_L06_00420AE8 is defined in L06_00420AE8-g8.c. */

/* The object runs through five states. The dispatch reads the level's own jump table (five
   words in the level's data at 0x2E1F00); `cases` only keeps the labels alive. */
/* func_L06_00430318 is defined in L06_00430318-g8.c. */

/* func_L06_00443280 is defined in L06_00443280-g8.c. */

/* func_L06_00443A38 is defined in L06_0041DED8-g8.c. */

/* func_L06_00444168 and func_L06_00444300 live in L06_0041DED8-g8.c (func_L06_00444300 reaches
 * its constants through $gp; the pair is the level 6 twin of func_L14_00428A08/func_L14_00428BA0). */

/* The same re-arm, with two probe addresses and two flags. */
/* Re-arms the object when the shared probe accepts its live handle. */
/* The same re-arm, with the level's second probe address. */
/* The same re-arm, gated on the shared live-object probe. */
/* func_L06_00455BC0 is in L06_0041DED8-f7-g8.c. */

/* func_L06_00456278 is in L06_00456278.c. */

/* func_L06_00456F08 is defined in L06_00456F08.c. */

/* func_L06_00457270 is in L06_00457270.c: its zeroed vector is a por. */

/* func_L06_004573E8 is in L06_004573E8-g8.c. */

/* func_L06_004577B0 lives in L06_0041DED8-g8.c: it reads its first angle through $gp. */

extern void func_00282CC0(void *, void *, void *);

