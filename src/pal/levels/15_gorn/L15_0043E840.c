#include "include_asm.h"


#include "common.h"
extern float func_00283198(float);
extern float func_002A7878(float, float);
extern float func_00283B98(float, float);
extern void func_0029F338(void *);
extern void func_002833F0(void *, void *);
extern f32 func_002A7878(f32 a, f32 b);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern float func_00283B98(float, float);
extern int D_L15_001A9018[] __attribute__((sda));
extern unsigned short **D_L15_001A9014[] __attribute__((sda));
extern unsigned char *D_L15_001B2C9C[] __attribute__((sda));
extern unsigned char *D_L15_001B2C94[] __attribute__((sda));
extern short D_L15_00227500[];
extern float func_00282E80(void *, void *);
extern float func_002A7940(void);
extern float func_00283198(float);
extern void func_002AEE70(void *, void *, void *, float, float, float);
extern void func_L00_00323448(void *, void *, int, int, int, int, int, int);
extern void func_L00_00323E48(void *, int, int, void *);
extern void func_L00_00323958(void *, void *);
extern void func_0029F338(void *);
extern void func_002833F0(void *, void *);

/* State 0 looks for the group of the level's id lists that holds the 64-byte record closest to
   the object (first walk, distances below 9999.0; the group index goes to the state's first word
   and the function ends when there is none), sets the object's aim from two random values
   (func_002A7878, func_002A7940) and the record list at state + 0x40, removes the object when the
   state's byte at +0x8A is zero, and otherwise walks the chosen group's 32-byte records
   (second walk): records of class 0xD34 and 0xD33 get their id written into the record list with
   the payload at state + 0x680 and state + 0x6A0 (func_L00_00323E48).  It then picks two random
   angular speeds (the second gets the sign opposite to the first) and goes to state 1, which
   keeps aiming and turns the two angles at +0x688 and +0x6A8.  Both walks keep the second
   `p != 0` guard before the `p[-1]` read and the second walk has a pointer variable of its own
   (one shared variable swaps two callee-saved registers).  Measured: a0 + 0xC0 and a0 + 0xF0
   formed in locals ahead of the second walk make loop.c hoist the two class constants out of it
   (two more saved registers); written at their use after the walk, as below, they stay in the
   loop.  The sign test is a store followed by a conditional store, which gives retail's
   `bc1f` with the first store in its slot and lets the constant 1 be shared by both stores. */
void func_PAL_L15_0043EDE0(unsigned char *a0)
{
    unsigned char *state = *(unsigned char **)(a0 + 0x68);
    unsigned short *p;
    unsigned short *q;
    unsigned char *e;
    int i;
    int best;
    short cls;
    float bestd;
    float d;
    float f2;

    switch (a0[0x20]) {
    case 0:
        best = -1;
        bestd = 9999.0f;
        for (i = 0; i < D_L15_001A9018[0]; i++) {
            for (p = D_L15_001A9014[0][i];
                 p != 0 && ((p != 0 && (short)p[-1] >= 0) || p == D_L15_001A9014[0][i]);
                 p++) {
                e = D_L15_001B2C9C[0] + ((*p & 0x7FFF) << 6);
                if (e == 0)
                    break;
                d = func_00282E80(e + 0x30, a0 + 0x10);
                if (d < bestd) {
                    bestd = d;
                    best = i;
                }
            }
        }
        *(int *)state = best;
        if (best == -1)
            return;
        *(float *)(state + 0x28) = 12.0f;
        *(float *)(state + 0x2C) = func_002A7878(30.0f, 37.0f);
        *(float *)(state + 0x1C) = func_002A7940();
        *(float *)(state + 0xC) = func_00283198(*(float *)(state + 0x1C)) * *(float *)(state + 0x28);
        func_002AEE70(a0, state + 0x1C, state + 0xC, *(float *)(state + 0x28),
                      *(float *)(state + 0x2C) * 0.0003490659f, -1.0f);
        a0[0x30] = 0xFF;
        func_L00_00323448(a0, state + 0x40, 20, *(int *)(state + 4), *(int *)state,
                          *(int *)(state + 8), 7, 0);
        if (state[0x8A] == 0) {
            func_0029F338(a0);
            return;
        }
        for (q = D_L15_001A9014[0][*(int *)state];
             q != 0 && ((q != 0 && (short)q[-1] >= 0) || q == D_L15_001A9014[0][*(int *)state]);
             q++) {
            e = D_L15_001B2C94[0] + ((*q & 0x7FFF) << 5);
            if (e == 0)
                break;
            cls = D_L15_00227500[e[0x1D]];
            if (cls == 0xD34)
                func_L00_00323E48(state + 0x40, 1, (short)*q, state + 0x680);
            if (cls == 0xD33)
                func_L00_00323E48(state + 0x40, 1, (short)*q, state + 0x6A0);
        }
        state[0x8D] = 1;
        *(unsigned short *)(a0 + 0x34) |= 0x104;
        func_002833F0(a0 + 0xC0, a0 + 0xF0);
        *(float *)(state + 0x38) = func_002A78D8(27.0f, 52.0f) * 0.0003490659f;
        f2 = func_002A78D8(25.0f, 37.0f) * 0.0003490659f;
        *(float *)(state + 0x3C) = f2;
        if (0.0f <= *(float *)(state + 0x38) * f2)
            *(float *)(state + 0x3C) = -f2;
        a0[0x20] = 1;
        break;
    case 1:
        func_002AEE70(a0, state + 0x1C, state + 0xC, *(float *)(state + 0x28),
                      *(float *)(state + 0x2C) * 0.0003490659f, -1.0f);
        *(float *)(state + 0x688) = func_00283B98(*(float *)(state + 0x688), *(float *)(state + 0x38));
        *(float *)(state + 0x6A8) = func_00283B98(*(float *)(state + 0x6A8), *(float *)(state + 0x3C));
        func_L00_00323958(a0, state + 0x40);
        break;
    }
}

