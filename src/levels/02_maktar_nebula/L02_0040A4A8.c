#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;

extern void func_00335870(void);
extern void func_002A7750();
extern char D_L02_001BE200[];
extern void func_L02_003DAE60(void *, int);
extern void func_L02_003DB158(void *, int);
extern void func_L02_003DAF90(void *);
extern void func_L02_003DB030(void *);
extern void func_002AB8C0(void *, void *);
extern void func_002A0488(void *, void *, void *, void *);
extern void func_002B0990(void *, void *, int, int, float);
extern void func_002A8C28(void *, void *, int, float, float, float, int, int, int);
extern void func_L00_003D7250(void *, void *, float, int, int, int);
extern void func_002B60B0(u8 *, float, float, float, float);
extern void func_002A7470(void *, int, int, int);
extern float func_002A7878(float, float);
extern float func_00283248(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_31E6A0(void *, int, int);
extern char D_L02_00188660[];
extern void func_41F230(void *, int, int, int, int, int, int, int, int, int,
                        int, int, float, float);
extern void func_366BD8(int, int, void *, int);
extern void func_31EA58(void *, float, float);
extern void func_2F1F70(void *, void *, void *);
extern void func_32B068(void *, int, void *, int, float, float, float, float);
extern void func_31E3C0(void *, int, int, int);
extern void func_316220(void *);
extern void func_366830(int);
extern void func_3FC1B0(int, int);
extern void func_0032C700(void *, int, int, int, int, int, int, int, float, float,
                          int, int, int, int);
extern void func_002E5DA0(int, int, void *, int);
extern void func_002A7A00(void *, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002B0A68(void *, int, void *, float, float, float, float, int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A05A8(void *);
extern int func_002E59F8(int);
extern int func_L02_003FC1B0(void *, int);
extern int func_L02_003FC0D0(void *, int);
extern int func_002B3BA8(void *, u32, float, float, int, int);

typedef int TI128 __attribute__((mode(TI)));


extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern void func_0029FCC0(void *, int, void *);
extern void func_0029FC20(void *, int, void *);
extern void func_00282C88(void *);
extern void func_002830C0(void *, void *, void *);
extern void *func_002A9640(void *, int, int);
extern int func_002B0ED8(void *, void *, int);
extern char D_L02_001BA500[];
extern void func_L02_0040B980(u8 *);
extern void func_002B60B0_1(void *, float, float, float, float);

/* Sets up the actor and refreshes its three effect tracks. In state 0 it points the sub-object's
   record at +0x100, draws two byte values and a turn rate (15 to 40 degrees, negated half of the
   time) for +0x2D8, may set bit 0x8000 of the halfword at +0x34, fills the sub-object's tuning
   floats and arms it (func_L02_0040B980). In every state it then, when the actor is shown (+0x31)
   and within 24.0 of D_L02_001BA500, starts func_002A93B0, rebuilds the tracks at +0x290, +0x2A0
   and +0x2B0 from the matrix func_0029FC20 returns, and, from state 3 on, clears the carried
   record's word at +0x2C filtering by class, tests func_002B0ED8 against 5 and refreshes the
   +0x2E0 handle. Retail passes the actor to func_002B60B0 (a0 is reloaded before the call), which
   the four-float declaration at the top of the file leaves out: the second name carries the
   five-argument prototype. */
void func_L02_0040B0F8(u8 *a0) {
    u8 *s1 = *(u8 **)(a0 + 0x68);
    float m[16];
    float f;
    u8 *p;
    u8 *rec;
    u8 *other;
    short cls;

    if (a0[0x20] == 0) {
        *(u8 **)(s1 + 0x18) = s1 + 0x100;
        s1[0x48] = func_00283CF0(15.0f);
        s1[0x4A] = func_00283CF0(12.0f);
        f = func_002A7878(15.0f, 40.0f) * 0.01745329424738884f;
        if (func_002A77E0(2) != 0)
            f = -f;
        *(float *)(s1 + 0x2D8) = f;
        if (func_002A77E0(2) == 1)
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) | 0x8000;
        s1[0x60] = 8;
        *(float *)(s1 + 0x80) = 0.5f;
        *(float *)(s1 + 0x84) = 0.5f;
        *(float *)(s1 + 0x8C) = 0.4f;
        *(int *)(s1 + 0x98) = 4;
        *(float *)(s1 + 0x100) = 0.8f;
        *(float *)(s1 + 0x104) = 0.5f;
        *(float *)(s1 + 0x108) = 0.4f;
        *(float *)(s1 + 0x10C) = 0.4f;
        *(float *)(s1 + 0x110) = 1.5707965f;
        *(float *)(s1 + 0x130) = 0.52359885f;
        *(float *)(s1 + 0x12C) = 0.0055555557f;
        func_002B60B0_1(a0, 0.004444444552063942f, 0.13333334028720856f,
                        0.0011635529808700085f, 0.10471977293491364f);
        s1[0x28] = 3;
        func_L02_0040B980(a0);
    }
    if (a0[0x31] != 0) {
        if (func_00282E48(a0 + 0x10, D_L02_001BA500) < 24.0f) {
            func_002A93B0(a0);
            a0[0x6F] = 0x16;
        }
    }
    func_0029FCC0(a0, 1, s1 + 0x290);
    p = s1 + 0x2B0;
    func_0029FCC0(a0, 2, s1 + 0x2A0);
    func_0029FC20(a0, 3, m);
    func_00282C88(p);
    *(float *)(s1 + 0x2B0) = 0.25f;
    *(int *)(s1 + 0x2B8) = 0;
    func_002830C0(p, p, m);
    func_00282CC0(p, p, m + 12);
    if (a0[0x31] != 0 && a0[0x20] >= 3) {
        rec = func_002A9640(a0, 0x10000, 1);
        if (rec != 0) {
            other = *(u8 **)(rec + 0x20);
            if (other != 0 && a0[0x31] == 0) {
                cls = *(short *)(other + 0xAA);
                if (cls == 0xA03 || cls == 0xB89)
                    *(int *)(rec + 0x2C) = 0;
            }
        }
        if (func_002B0ED8(a0, s1 + 0x50, 0) == 5) {
            *(int *)(s1 + 0xE0) = 0;
            *(float *)(s1 + 0xE4) = 0.8377582f;
        }
        if (a0[0x20] >= 2 && s1[0x2E] == 2)
            func_L02_0040B980(a0);
        *(s16 *)(s1 + 0x2E0) = func_002B3BA8(a0, *(u32 *)(s1 + 0x2DC), 100.0f, 100.0f, 0, 0);
        *(int *)(s1 + 0x2D4) = *(int *)(s1 + 0x200);
    }
}

/* arms one actor: raises its counter, then two setup calls */
void func_L02_0040B420(u8 *a0) {
    u8 *q = *(u8 **)(a0 + 0x68);

    if (*(u16 *)(a0 + 0x96) <= 0xFFFE)
        *(u16 *)(a0 + 0x96) = *(u16 *)(a0 + 0x96) + 1;
    func_002B0990(a0, q + 0x210, 5, 1, 2.5f);
    func_002A8C28(a0, a0 + 0x10, 0x4000000, 1.3f, 1.0f, 1.0f, 0, 1, 0);
}

/* starts the three effect tracks of the actor */
void func_L02_0040B4B0(u8 *a0) {
    u8 *s1 = *(u8 **)(a0 + 0x68);

    if (a0[0x95] != 0) {
        func_L00_003D7250(a0, s1 + 0x290, 0.125f, 0x36F6, 0x20000000, 0x20000000);
        func_L00_003D7250(a0, s1 + 0x2A0, 0.15f, 0x1050B0, 0x30000000, 0x20000000);
        func_L00_003D7250(a0, s1 + 0x2B0, 0.15f, 0x1050B0, 0x10000000, 0x30000000);
    }
}

/* brings the actor into its armed state */
void func_L02_0040B868(u8 *a0, int a1) {
    u8 *s0 = *(u8 **)(a0 + 0x68);
    int one = 1;
    u32 v;

    *(float *)(s0 + 0x20) = (float)*(s16 *)(s0 + 0x24);
    *(u16 *)(s0 + 0x2E2) = one;
    func_002B60B0(a0, 0.004444444552063942f, 0.13333334028720856f,
                  0.0011635529808700085f, 0.10471977293491364f);
    func_002A7750(a0, 3, 1);
    if (*(u8 *)(a0 + 0x43) != 2)
        func_002A7470(a0, 2, 0, 0);
    *(u32 *)(a0 + 0x98) = *(u32 *)(*(u32 *)(a0 + 0x24) + 0x10);
    *(u8 *)(s0 + 0x6A) = 0;
    *(u8 *)(s0 + 0x2E) = one;
    *(u8 *)(a0 + 0x31) = one;
    v = *(u16 *)(a0 + 0x34);
    *(u8 *)(a0 + 0x7F) = 0;
    *(u16 *)(a0 + 0x34) = (v | 0x1000) & 0xFFB8;
    *(u16 *)(s0 + 0x2E8) = a1;
    *(u16 *)(s0 + 0x88) = 0;
    if (*(s16 *)(s0 + 0x50) != 0) {
        *(u16 *)(s0 + 0x50) = 0;
        func_002A0488(a0, *(u8 *)(s0 + 0x54), *(u8 *)(s0 + 0x55), *(u8 *)(s0 + 0x56));
        *(u16 *)(s0 + 0x52) = one;
    }
}

/* arms the actor: its two effect tracks, then the shared state resets */
void func_L02_0040B980(u8 *a0) {
    u8 *s1 = *(u8 **)(a0 + 0x68);
    float buf[3];

    *(u16 *)(s1 + 0x2E2) = 0;
    *(u32 *)(s1 + 0x2D4) = 0;
    if (a0[0x31]) {
        func_0032C700(a0 + 0x10, 0, 5, 5, 0x19, 0x14, 0xA, 1, 0.5f, 0.0f,
                      1, 0, 0, 0);
        func_002E5DA0(0, 0, a0, 0xC3E);
        func_002A7A00(buf, 0.083333335816860199f, 0.11666667461395264f);
        func_00282CC0(buf, buf, s1 + 0xD0);
        func_002B0A68(a0, 0xFF, buf, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    }
    func_002A7470(a0, 0, 0, 3);
    func_002A05A8(a0);
    func_002A7750(a0, 1, 0);
    *(u8 *)(a0 + 0x31) = 0;
    *(u32 *)(a0 + 0x98) = 0;
    *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) & 0xEFFF) | 0x47;
}

/* sweeps the two effect tracks of the actor relative to a head position */
/* func_L02_0040BAB8 is defined in L02_0040BAB8.c. */

/* records the actor's two shot counters, then arms it */
void func_L02_0040BBA0(u8 *a0) {
    u8 *t = *(u8 **)(a0 + 0x68);

    *(u16 *)(t + 0x2E4) = *(u8 *)(a0 + 0x20);
    *(u16 *)(t + 0x2E6) = *(u8 *)(a0 + 0x95);
    func_31E6A0(a0, 6, 3);
}

/* func_L02_0040BE08 is defined in L02_0040BE08-g8.c. */

/* func_L02_0040CAF0 is defined in L02_0040CAF0-g8.c. */

/* steps the actor's state machine, then raises its counter */
void func_L02_0040CEE8(u8 *a0) {
    u8 *s0 = *(u8 **)(a0 + 0x68);

    func_002AB8C0(a0, s0 + 0x50);
    if (*(s16 *)(s0 + 0x50) == 0) {
        if (*(u32 *)(s0 + 0x1AC) == 0) {
            func_002A0488(a0, *(u32 *)(s0 + 0x1A0), *(u32 *)(s0 + 0x1A4),
                          *(u32 *)(s0 + 0x1A8));
            *(u32 *)(s0 + 0x1AC) = 1;
        }
    } else {
        *(u32 *)(s0 + 0x1AC) = 0;
    }
    if (*(u16 *)(a0 + 0x96) <= 0xFFFE)
        *(u16 *)(a0 + 0x96) = *(u16 *)(a0 + 0x96) + 1;
}

/* Updates the actor's halfword at +0x1B8: below kind 4 it only clears it and the word at +0x184;
   while it is 1, or when the flag at +0x31 is set and func_L02_003FC0D0 agrees, it keeps it at 1
   and calls func_002B3BA8 on the slot at +0x1B0; otherwise it clears it and, for kinds 8 and 0xB,
   picks one of two states by the word at +0x180. */
void func_L02_0040CF68(u8 *a0) {
    u8 *s1 = *(u8 **)(a0 + 0x68);

    if (a0[0x20] < 4) {
        *(u16 *)(s1 + 0x1B8) = 0;
        *(s32 *)(s1 + 0x184) = 0;
    } else {
        if (*(s16 *)(s1 + 0x1B8) == 1) {
            *(s16 *)(s1 + 0x1B6) = func_002B3BA8(a0, *(u32 *)(s1 + 0x1B0), 100.0f, 100.0f, 0, 0);
            *(s32 *)(s1 + 0x184) = *(s32 *)(s1 + 0x160);
        } else {
            if (a0[0x31] != 0 && func_L02_003FC0D0(*(void **)(a0 + 0xB8), *(s16 *)(a0 + 0xAA)) != 0) {
                *(u16 *)(s1 + 0x1B8) = 1;
                *(s16 *)(s1 + 0x1B6) = func_002B3BA8(a0, *(u32 *)(s1 + 0x1B0), 100.0f, 100.0f, 0, 0);
                *(s32 *)(s1 + 0x184) = *(s32 *)(s1 + 0x160);
            } else {
                *(u16 *)(s1 + 0x1B8) = 0;
                if (a0[0x20] == 0xB || a0[0x20] == 8) {
                    if (*(s32 *)(s1 + 0x180) != -1)
                        func_002A7750(a0, 7, 3);
                    else
                        func_002A7750(a0, 5, 2);
                }
            }
        }
    }
}

/* resets the actor's aim: three records and the two shared limits */
void func_L02_0040D080(u8 *a0, int a1) {
    u8 *s0 = *(u8 **)(a0 + 0x68);

    *(u16 *)(s0 + 0x1B8) = 0;
    *(float *)(s0 + 0x20) = (float)*(s16 *)(s0 + 0x24);
    func_002A7750(a0, 3, 1);
    if (*(u8 *)(a0 + 0x43) != 0)
        func_002A7470(a0, 0, 0, 10);
    *(u32 *)(a0 + 0x98) = *(u32 *)(*(u32 *)(a0 + 0x24) + 0x10);
    *(u8 *)(s0 + 0x2E) = 1;
    *(u8 *)(a0 + 0x7F) = 0;
    *(u8 *)(a0 + 0x31) = 1;
    *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) | 0x1000) & 0xFFB8;
    *(float *)(s0 + 0x18C) = func_002A7878(0.0f, 90.0f) * 0.01745329424738884f;
    *(u16 *)(s0 + 0x1BA) = a1;
    *(u16 *)(s0 + 0x3C) = 0;
    *(u32 *)(s0 + 0x38) = 0;
    if (*(s16 *)(s0 + 0x50) != 0) {
        *(u16 *)(s0 + 0x50) = 0;
        func_002A0488(a0, *(u32 *)(s0 + 0x1A0), *(u32 *)(s0 + 0x1A4),
                      *(u32 *)(s0 + 0x1A8));
        *(u16 *)(s0 + 0x52) = 1;
    }
}

/* Lets go of the slot the actor holds (+0x19C) when that slot's record still names it and is live,
   ends the state at +0x1B8 when it is 1 (func_L02_003FC1B0), starts the effect pair when the actor
   is shown (+0x31), then clears the state and the shared fields as func_L02_0040B980 does. */
void func_L02_0040D180(u8 *a0) {
    u8 *s1 = *(u8 **)(a0 + 0x68);
    s32 slot = *(s32 *)(s1 + 0x19C);

    if (slot != -1) {
        u8 *rec = (u8 *)D_L02_00188660 + slot * 0x70;

        if (*(u8 **)(rec + 0x88) == a0 && rec[0x74] != 0)
            func_002E59F8(slot);
    }
    *(s32 *)(s1 + 0x19C) = -1;
    if (*(s16 *)(s1 + 0x1B8) == 1) {
        *(u16 *)(s1 + 0x1B8) = 0;
        func_L02_003FC1B0(*(void **)(a0 + 0xB8), *(s16 *)(a0 + 0xAA));
    }
    if (a0[0x31] != 0) {
        func_0032C700(a0 + 0x10, 0, 0xA, 0x1E, 0, 0xA, 0x2D, 1, 0.3f, 0.0f, 0, 0, 0, 0);
        func_002E5DA0(0, 0, a0, 0xC3E);
    }
    *(u16 *)(s1 + 0x1B8) = 0;
    *(s32 *)(s1 + 0x184) = 0;
    func_002A7470(a0, 0, 0, 3);
    func_002A05A8(a0);
    func_002A7750(a0, 1, 0);
    a0[0x31] = 0;
    *(u32 *)(a0 + 0x98) = 0;
    *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) & 0xEFFF) | 0x47;
}

/* sda in this -G0 unit gives retail's bare-symbol load (`lui $r` / `lbu $r,%lo($r)`, one register);
   a plain declaration splits it into two registers. */
extern u8 D_001A7BCB __attribute__((sda));
extern u8 D_L02_001395B8[];
extern u8 D_L02_001C0700[];
extern char D_00189EA0[];
extern int func_002ACBC8(void *, int);
extern s32 func_00288AA0(u8 *, s32);
extern s32 func_00288BE8(u8 *);
extern int func_002F5D10(void);
extern void func_002AD7B8(int);
extern void func_002AF0A8(int);
extern void func_0029F338(u8 *);

/* Steps the actor by its kind byte (+0x20). Kind 0 hands it to func_0029F338 when it holds no
   record at +0x68 and calls func_002A7750 with 1 otherwise. Kind 1 waits for D_001A7BCB and the
   byte D_L02_001395B8[4] to be clear and func_002ACBC8 to accept the index at +0xC of the
   record, then queues the messages 0x2D, 3 and 0x2E on D_L02_001C0700, sets the byte and calls
   func_002A7750 with 2. Kind 2 runs func_002AD7B8 and func_002AF0A8 with 3 and calls
   func_002A7750 with 3, unless func_002F5D10 answers yes. */
void func_L02_0040FB80(u8 *a0) {
    u8 *state = *(u8 **)(a0 + 0x68);

    switch (a0[0x20]) {
    case 0:
        if (state == 0)
            func_0029F338(a0);
        else
            func_002A7750(a0, 1, -1);
        break;
    case 1:
        if (D_001A7BCB == 0 && D_L02_001395B8[4] == 0 &&
            func_002ACBC8(D_00189EA0, *(s32 *)(state + 0xC)) != 0 &&
            func_00288AA0(D_L02_001C0700, 0x2D) != 0) {
            func_00288AA0(D_L02_001C0700, 3);
            func_00288AA0(D_L02_001C0700, 0x2E);
            func_00288BE8(D_L02_001C0700);
            D_L02_001395B8[4] = 1;
            func_002A7750(a0, 2, -1);
        }
        break;
    case 2:
        if (func_002F5D10() == 0) {
            func_002AD7B8(3);
            func_002AF0A8(3);
            func_002A7750(a0, 3, -1);
        }
        break;
    }
}

/* func_L02_00411750 is defined in L02_00411750-g8.c. */

INCLUDE_ASM("asm/levels", func_L02_00411D18);

extern s32 D_001A79F0 __attribute__((sda));
extern u8 D_0019B2E8[];
extern u16 D_0018CFDC;
extern int func_002A77E0(int);
extern float func_002A7940(void);
extern float func_002AA2E8(float *, float, float);
extern float func_00282E80(void *, void *);
extern float func_00282E48(void *, void *);
extern float func_00283B98(float, float);
extern void *func_002A9640(void *, int, int);
extern int func_002E5CF8(int, int, void *);
extern void func_L00_002E6CF0(void *, void *);
extern void func_L02_00412808(u8 *);
extern void func_L02_004129D0(u8 *);

/* Steps the actor by its kind byte (+0x20). Kind 0 releases it (func_0029F338) when the table byte
   of its owner (D_0019B2E8, indexed by the byte at +0xB0 and D_001A79F0) has bit 7 set; otherwise
   it takes twice the size at +0x24 of its type record, sets or clears bit 15 of its flags at +0x34
   by func_002A77E0(2), starts state 1 and draws the block's two phases (+4 and +0x14) with
   func_002A7940. Kind 1 keeps its slot record (the index at +0x18 of the block) alive, eases the
   block's float at +0xC to 0 or 1 by whether func_00282E80 puts the actor farther than 64.0 from
   D_L02_001BA500, registers func_L02_004129D0 while it is nonzero, and when the entity found by
   func_002A9640 (a record whose halfword at +0xAA is 0x9C8) is within 5.0 starts state 2 and gives
   the slot up. Kind 2 only runs the common tail, which steps the two phases (func_00283B98), puts
   0.5 * sin(phase) + the base at +8 into the actor's float at +0x18 and runs the counter at +0x10
   down by 1/15, wrapping it into [-1, 1]. The first slot lookup is a separate block-local pointer
   from the one in the state-2 arm (retail keeps them in different registers). */
void func_L02_004124A0(u8 *a0) {
    u8 *s1 = *(u8 **)(a0 + 0x68);
    u8 *p;
    u8 *q;
    s32 slot;
    float f;

    switch (a0[0x20]) {
    case 0:
        if (D_0019B2E8[a0[0xB0] + D_001A79F0 * 16] & 0x80) {
            func_0029F338(a0);
            return;
        }
        *(float *)(a0 + 0x2C) = *(float *)(*(u8 **)(a0 + 0x24) + 0x24) * 2.0f;
        if (func_002A77E0(2))
            *(u16 *)(a0 + 0x34) |= 0x8000;
        else
            *(u16 *)(a0 + 0x34) &= 0x7FFF;
        func_002A7750(a0, 1, -1);
        *(float *)(s1 + 8) = *(float *)(a0 + 0x18);
        *(float *)(s1 + 4) = func_002A7940();
        *(float *)(s1 + 0x14) = func_002A7940();
        break;
    case 1:
        if (a0[0x31] != 0)
            func_L02_00412808(a0);
        {
            u8 *r = (u8 *)D_L02_00188660 + *(s32 *)(s1 + 0x18) * 0x70;

            if (*(u8 **)(r + 0x88) != a0 || r[0x74] == 0)
                *(s32 *)(s1 + 0x18) = func_002E5CF8(0, 4, a0);
        }
        f = func_00282E80(a0 + 0x10, D_L02_001BA500);
        if (f > 64.0f)
            func_002AA2E8((float *)(s1 + 0xC), 0.0f, 0.016666668f);
        else
            func_002AA2E8((float *)(s1 + 0xC), 1.0f, 0.016666668f);
        if (*(float *)(s1 + 0xC) != 0.0f)
            func_L00_002E6CF0((void *)func_L02_004129D0, a0);
        p = func_002A9640(a0, 0x10000, 0);
        if (p != 0) {
            q = *(u8 **)(p + 0x20);
            if (q != 0 && *(s16 *)(q + 0xAA) == 0x9C8 &&
                func_00282E48(a0 + 0x10, q + 0x10) < 5.0f) {
                D_0018CFDC = 0xFFFF;
                func_002A7750(a0, 2, -1);
                *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) | 0x41) & 0xEFFF;
                *(u32 *)(a0 + 0x98) = 0;
                slot = *(s32 *)(s1 + 0x18);
                if (slot != -1) {
                    u8 *rec = (u8 *)D_L02_00188660 + slot * 0x70;

                    if (*(u8 **)(rec + 0x88) == a0 && rec[0x74] != 0)
                        func_002E59F8(slot);
                }
                *(s32 *)(s1 + 0x18) = -1;
            }
        }
        a0[0xA8] = 0xFF;
        break;
    case 2:
        break;
    }
    *(float *)(s1 + 4) = func_00283B98(*(float *)(s1 + 4), 0.05817765f);
    *(float *)(s1 + 0x14) = func_00283B98(*(float *)(s1 + 0x14), -0.10471977f);
    *(float *)(a0 + 0x18) = func_00283198(*(float *)(s1 + 4)) * 0.5f + *(float *)(s1 + 8);
    f = *(float *)(s1 + 0x10) + -0.06666667f;
    *(float *)(s1 + 0x10) = f;
    if (f > 1.0f)
        *(float *)(s1 + 0x10) = f - 1.0f;
    else if (f < -1.0f)
        *(float *)(s1 + 0x10) = f + 1.0f;
}

/* The effect's tuning, four resident tables copied onto the stack: the spread and fall speed of
   the sparks, the two sizes, the two colours and the two byte ranges of the kind. */
typedef struct { float f[4]; } SparkRange;
typedef struct { float f[2]; } SparkSizes;
typedef struct { int i[2]; } SparkColours;
typedef struct { u8 b[4]; } SparkKinds;
extern SparkRange D_L02_001B1C10;
extern SparkSizes D_L02_001B1C20;
extern SparkColours D_L02_001B1C28;
extern SparkKinds D_L02_001B1C30;
extern void func_00283098(void *, void *, void *);
extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern void *func_002C3150(void *, void *, int, int, int, int, float);
extern void func_00282C88(void *);

/* Throws two sparks from a point 1.5 in front of the actor (carried by the matrix at +0xC0, then
   moved to the position at +0x10): the first with a velocity drawn between the first two range
   words per frame (no spread in this level's table), the second from a random point within 1.5
   of the first, falling at a speed drawn between the last two. */
void func_L02_00412808(u8 *a0) {
    SparkRange range = D_L02_001B1C10;
    SparkSizes sizes = D_L02_001B1C20;
    SparkColours colours = D_L02_001B1C28;
    SparkKinds kinds = D_L02_001B1C30;
    float vel[4];
    float front[4];
    float spot[4];

    *(TI128 *)front = 0;
    front[2] = 1.5f;
    func_00283098(front, front, a0 + 0xC0);
    func_00282CC0(front, front, a0 + 0x10);
    func_002A7A00(vel, range.f[0] * 0.016666668f, range.f[1] * 0.016666668f);
    func_002C3150(front, vel, colours.i[0], (u8)func_002A7820(kinds.b[0], kinds.b[1]),
                  (u8)func_002A77E0(0xFF), 0, sizes.f[0]);
    func_00282C88(vel);
    func_002A7A00(spot, 0.0f, 1.5f);
    func_00282CC0(spot, spot, front);
    vel[2] = -(func_002A7878(range.f[2], range.f[3]) * 0.016666668f);
    func_002C3150(spot, vel, colours.i[1], (u8)func_002A7820(kinds.b[2], kinds.b[3]),
                  (u8)func_002A77E0(0xFF), 0, sizes.f[1]);
}

/* func_L02_004129D0 is defined in L02_004129D0.c. */

INCLUDE_ASM("asm/levels", func_L02_00412D50);

/* func_L02_00413730 is defined in L02_00413730-g8.c. */

/* func_L02_004216F0 is matched in L02_004216F0-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier -g). */

/* func_L02_00423520 is matched in L02_00423520-g8.c (built with -frac2-zero-ti-por). */

extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern int func_00283D38(int, int, float);
extern void *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);
extern int D_L02_001B2050[2] __attribute__((sda));
extern int D_L02_001B2058[2] __attribute__((sda));

/* Throws twenty sparks from a point built from the actor's transform (+0x10) and its vectors at
   +0xC0 and +0xE0. Each one flies along a random mix of the vectors at +0xC0, +0xD0 and +0xE0 at
   a speed drawn between lo and hi, with a random size, two colours blended from the level's two
   colour pairs and a small downward pull. Retail negates its constant at run time (neg.s), so k
   stays a variable. */
void func_L02_00423838(u8 *a0, float lo, float hi) {
    float v10[4];
    float v20[4];
    float v30[4];
    float v40[4];
    float v50[4];
    float v60[4];
    int i;
    float r;
    int a, b, c;
    int c0, c1;
    float k = 0.0013888889f;

    func_00282D30(v10, a0 + 0xE0, 1.75f);
    func_00282CC0(v20, v10, a0 + 0x10);
    func_00282D30(v10, a0 + 0xC0, -0.5f);
    func_00282CC0(v20, v10, v20);
    i = 19;
    do {
        func_00282F20(v40, a0 + 0xD0, func_002A7878(-1.0f, 1.0f));
        func_00282F20(v30, a0 + 0xE0, func_002A7878(-0.15f, 1.0f));
        func_00282CC0(v50, a0 + 0xC0, v40);
        func_00282CC0(v50, v50, v30);
        func_00282F20(v50, v50, func_002A7878(lo, hi));
        r = func_002A7878(0.5f, 1.5f);
        a = func_00283CF0(r * 10.0f);
        b = func_00283CF0(r * 30.0f);
        c = func_00283CF0(r * 7.0f);
        v50[3] = func_002A7878(0.2f, 0.6f);
        func_00282C88(v60);
        v60[2] = -k * (float)(a + b + c);
        func_00282CC0(v60, v60, v50);
        v60[3] = 0.01f;
        c0 = func_00283D38(D_L02_001B2050[0], D_L02_001B2050[1], func_002A7878(0.0f, 1.0f));
        c1 = func_00283D38(D_L02_001B2058[0], D_L02_001B2058[1], func_002A7878(0.0f, 1.0f));
        func_002BAA28(v20, v50, v60, c0, c1, a, b, c, 0x1003C);
    } while (--i >= 0);
}

struct Pair42E2F8 {
    float a;
    float b;
};

extern const struct Pair42E2F8 D_L02_001B23E0;
extern const struct Pair42E2F8 D_L02_001B23E8;
extern const TI128 D_L02_001B23F0[2];
extern s32 D_L02_001AEC78 __attribute__((sda));
extern void func_L00_0032A258(void *, void *, void *, void *, s32, s32, s32, s32, s32, unsigned char, s32);
extern void *func_L00_0033E220(void *, void *, int, int, int, int, int, int, float, float);
extern void func_L00_00326110(void *, int, float);
extern void *func_00273730(void *, int, int, int, void *, void *, void *, int, float, float);
extern void func_L00_003263D0(void *,void *,int,int,void *,u32,void *,float,float,float,float);
extern void func_L02_0042E680(u8 *, float, float);

void func_L02_0042E2F8(u8 *a0) {
    u8 *state = *(u8 **)(a0 + 0x68);
    struct Pair42E2F8 a = D_L02_001B23E0;
    struct Pair42E2F8 b = D_L02_001B23E8;
    TI128 c[2];
    float d[4] __attribute__((aligned(16)));
    float e[4] __attribute__((aligned(16)));
    float f[4] __attribute__((aligned(16)));

    c[0] = D_L02_001B23F0[0];
    c[1] = D_L02_001B23F0[1];
    switch (a0[0x20]) {
    case 0:
        *(TI128 *)d = 0;
        d[2] = 4.0f;
        func_L00_0033E220(d, a0, 0x28208080, -1, 0, -1, 0, 0x60, 409500.0f, 0.0f);
        func_L00_0033E220(d, a0, 0x20208080, -1, 1, -1, 0, 0x60, 367500.0f, 0.75f);
        if (*(s32 *)state != 0)
            D_L02_001AEC78 = D_L02_001AEC78 - 1;
        func_002A7750(a0, 1, -1);
        break;
    case 1:
        if (func_002A9640(a0, 0x4010000, 0) != 0 && *(s32 *)state == 0) {
            D_L02_001AEC78 = D_L02_001AEC78 - 1;
            func_002A7750(a0, 2, -1);
        }
        a0[0xA8] = 0xFF;
        break;
    case 2:
        func_L00_0032A258(a0, c, &b, &a, 0xB, 0, 1, 5, 0xFFFF, 0xFF, 0);
        func_L00_00326110(a0, 1, 4.0f);
        *(TI128 *)d = 0;
        d[1] = -0.10000001f;
        d[2] = 0.050000004f;
        func_00283098(d, d, a0 + 0xC0);
        func_00273730(a0, 1, *(s16 *)(a0 + 0xAA), 1, a0 + 0x10, a0 + 0xF0, d, 0xFF, 0.0f, 15.0f);
        *(TI128 *)e = 0;
        e[1] = 0.2f;
        e[2] = 4.3f;
        func_00283098(e, e, a0 + 0xC0);
        func_00282CC0(e, e, a0 + 0x10);
        *(TI128 *)f = 0;
        f[1] = 0.050000004f;
        f[2] = 0.025000002f;
        func_00283098(f, f, a0 + 0xC0);
        func_L00_003263D0(a0,e,4,1,f,0x50404040,0,0.25f,5.0f,0.5f,1.0f);
        func_L02_0042E680(a0, 0.016666668f, 0.23333335f);
        func_0029F338(a0);
        break;
    }
}

/* func_L02_0042E680 is matched in L02_0042E680.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L02_0042E988 is defined in L02_0042E988-flags-g8.c. */


/* restarts the shared effect object the level keeps at 0x1BE200 */
void func_L02_00438B28(void) {
    char *p = D_L02_001BE200;

    func_L02_003DAE60(*(void **)(p + 0x198), 0);
    func_L02_003DAE60(*(void **)(p + 0x198), 1);
    func_L02_003DB158(*(void **)(p + 0x198), 5);
    func_L02_003DB158(*(void **)(p + 0x198), 6);
    func_L02_003DAF90(*(void **)(p + 0x198));
    func_L02_003DB030(*(void **)(p + 0x198));
}

extern void func_L02_004388A0(u8 *);
extern void func_L02_003FFDB0(u8 *);
extern int D_L02_001A8F00 __attribute__((sda));
extern char *D_L02_001B359C __attribute__((sda));
extern char D_L02_004004D8[];
extern int D_L02_00258800[];
extern void func_00282F20(void *, void *, float);
extern void func_L00_002E6CF0(void *, void *);

typedef struct { u8 pad00[0x78]; int w78; u8 pad7C[0xB8 - 0x7C]; int wB8; } L02_Part;
typedef struct { u8 pad00[0x30]; int mode; u8 pad34[0x198 - 0x34]; L02_Part *part; int w19C; } L02_Level;
typedef struct { u8 pad00[4]; int ent; int armed; int ent2; } L02_CtlState;
typedef struct { u8 pad00[0x6C]; float f6C; } L02_EntVars;
typedef struct {
    u8 pad00[0x10];
    float pos[4];
    u8 pad20[0x34 - 0x20];
    u16 flags;
    u8 pad36[0x43 - 0x36];
    u8 b43;
    u8 pad44[0x48 - 0x44];
    int w48;
    u8 pad4C[0x68 - 0x4C];
    L02_EntVars *vars;
    u8 pad6C[0xD0 - 0x6C];
    float dir[4];
    u8 padE0[0x100 - 0xE0];
} L02_Ent;

/* Controller of the level's moving entity (state byte at +0x20; the words at +0x4 and +0xC of
   its state name two entities of the table D_L02_001B359C). State 0 shows it (byte +0x30 = 0xFF),
   clears the armed word at +0x8 and goes to state 1. State 1 follows D_L02_001A8F00: when it is 2
   the mode of the level block D_L02_001BE200 decides. Mode 0 hands func_L02_003FFDB0 and the
   handler at D_L02_004004D8 to the second entity and func_L02_004388A0 to itself, and once
   (func_002A7470 resets the entity's mode first) pushes the first entity by -2 along its +0xD0
   axis. Mode 1 hands the two handlers to the second entity. Mode 6 does that too, then sets that
   entity's float at +0x6C to 100.0 and its flag 2, writes the colour 0x40FF00EA to three words of
   D_L02_00258800 and to the part at +0x198 of the block, and hands func_L02_00438B28 to itself.
   With D_L02_001A8F00 not 2 it undoes the push (+2 along the axis) and clears the armed word. */
void func_L02_00438B90(u8 *a0) {
    L02_CtlState *st = *(L02_CtlState **)(a0 + 0x68);
    L02_Level *lv;
    L02_Ent *e;
    float v[4];
    int c;

    switch (a0[0x20]) {
    case 0:
        a0[0x30] = 0xFF;
        a0[0x20] = 1;
        st->armed = 0;
        break;
    case 1:
        if (D_L02_001A8F00 != 2) {
            if (st->armed != 0) {
                e = (L02_Ent *)(D_L02_001B359C + (st->ent << 8));
                st->armed = 0;
                if (e->b43 != 0) {
                    func_002A7470(e, 0, 0, 0);
                    e->w48 = 0;
                }
                func_00282F20(v, e->dir, 2.0f);
                func_00282CC0(e->pos, e->pos, v);
            }
        } else {
            lv = (L02_Level *)D_L02_001BE200;
            if (lv->mode == 0) {
                func_L00_002E6CF0(func_L02_003FFDB0, D_L02_001B359C + (st->ent2 << 8));
                func_L00_002E6CF0(D_L02_004004D8, D_L02_001B359C + (st->ent2 << 8));
                func_L00_002E6CF0(func_L02_004388A0, a0);
                if (st->armed == 0) {
                    e = (L02_Ent *)(D_L02_001B359C + (st->ent << 8));
                    st->armed = 1;
                    if (e->b43 != 1) {
                        func_002A7470(e, 1, 7, 0);
                        e->w48 = 0;
                    }
                    func_00282F20(v, e->dir, -2.0f);
                    func_00282CC0(e->pos, e->pos, v);
                }
            } else if (lv->mode == 1) {
                func_L00_002E6CF0(func_L02_003FFDB0, D_L02_001B359C + (st->ent2 << 8));
                func_L00_002E6CF0(D_L02_004004D8, D_L02_001B359C + (st->ent2 << 8));
            } else if (lv->mode == 6) {
                c = 0x40FF00EA;
                func_L00_002E6CF0(func_L02_003FFDB0, D_L02_001B359C + (st->ent2 << 8));
                func_L00_002E6CF0(D_L02_004004D8, D_L02_001B359C + (st->ent2 << 8));
                /* indexed, not `base + (n << 8)`: retail adds the shifted index first */
                ((L02_Ent *)D_L02_001B359C)[st->ent2].vars->f6C = 100.0f;
                ((L02_Ent *)D_L02_001B359C)[st->ent2].flags |= 2;
                D_L02_00258800[0x250 / 4] = c;
                D_L02_00258800[0x258 / 4] = c;
                D_L02_00258800[0x254 / 4] = c;
                lv->part->wB8 = lv->w19C;
                func_L00_002E6CF0(func_L02_00438B28, a0);
                lv->part->w78 = c;
            }
        }
        break;
    }
}

/* func_L02_00439CD8 is in L02_0040A4A8-f7-g8.c. */


typedef struct { u8 pad[0x464]; u8 spent[1]; } L02_CellFlags;
extern L02_CellFlags D_L02_0021F4F0;
extern u8 D_0019B4A8[];
extern int D_001A79F0 __attribute__((sda));
/* sda in this -G0 unit keeps the address of the ring table one `la`, retail's adjacent `lui`/`addiu`
   in the last call's setup (a plain declaration splits it and the scheduler lifts the `lui`). */
extern char D_L02_001A8F20[] __attribute__((sda));
extern void *func_0029EFD0(int);
extern void func_002B37E8(void *, u8 *);
extern int func_002E5CF8(int, int, void *);

/* A breakable placed in the world, numbered by the halfword at +0xB2. Whether it was broken before
   is kept in D_0019B4A8 (one 1 KB table per planet, a 3-bit count in each nibble, the low bit of
   the number picking the nibble) and in a flag byte of its own. State 0 releases it when either
   says so, otherwise it goes to state 1. State 1 asks func_002A9640 what touches it: an actor of
   kind 0x9C8 breaks it (effect object 0xE43 started on it, the burst and the 0x3FFF ring, the
   count raised up to 7, the object released); with nothing there it only sets byte +0xA8 to 0xFF. */
void func_L02_00445200(u8 *a0) {
    u8 *p;
    u8 *q;
    void *fx;
    int id;
    int id2;    /* state 1 reads the number again into a register of its own, as retail does */
    int v;

    switch (a0[0x20]) {
    case 0:
        id = *(u16 *)(a0 + 0xB2);
        if (D_L02_0021F4F0.spent[(s16)id] == 0) {
            v = D_0019B4A8[((s16)id >> 1) + (D_001A79F0 << 10)];
            if (id & 1)
                v = (v >> 4) & 7;
            else
                v = v & 7;
            if (v == 0) {
                func_002A7750(a0, 1, -1);
                break;
            }
        }
        func_0029F338(a0);
        break;
    case 1:
        p = func_002A9640(a0, 0x10000, 0);
        if (p != 0 && (q = *(u8 **)(p + 0x20)) != 0 && *(s16 *)(q + 0xAA) == 0x9C8) {
            fx = func_0029EFD0(0xE43);
            if (fx != 0)
                func_002B37E8(fx, a0);
            func_002B0A68(a0, 0x3FFF, D_L02_001A8F20, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
            func_002E5CF8(0, 0, a0);
            id2 = *(u16 *)(a0 + 0xB2);
            if (id2 & 1) {
                if (((D_0019B4A8[((s16)id2 >> 1) + (D_001A79F0 << 10)] >> 4) & 7) != 7)
                    D_0019B4A8[((s16)id2 >> 1) + (D_001A79F0 << 10)] += 0x10;
            } else {
                if ((D_0019B4A8[((s16)id2 >> 1) + (D_001A79F0 << 10)] & 7) != 7)
                    D_0019B4A8[((s16)id2 >> 1) + (D_001A79F0 << 10)] += 1;
            }
            func_0029F338(a0);
        } else {
            a0[0xA8] = 0xFF;
        }
        break;
    }
}

/* rac1-decomp src/core/00118A40.c: func_00119100 */
/* Takes an argument its callers pass (e.g. r1_func_00112468) and ignores
   it; an unused parameter costs no codegen. */
int func_L02_00456258(int arg0) {
    return -1;
}

extern void func_00335870(void);

void func_L02_00456AC0(void) {
    func_00335870();
}
