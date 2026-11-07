/* func_PAL_L04_0041D788, the PAL copy of func_L04_00418BF0: the same C, where rename func_L04_003FA5A8 becomes func_PAL_L04_003FE7B0; lit 0.010000001f becomes 0.008333334f. */
#include "common.h"

typedef float Vector[4] __attribute__((aligned(16)));
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char prefix[0x108]; float stick; char pad[0xA4]; unsigned int held; } PadState;

extern struct { s32 pad; s32 flags; u8 rest[56]; } D_L04_002C63C0[];
extern int D_L04_001B090C __attribute__((sda));
extern int D_L04_001B0938 __attribute__((sda));
extern PadState D_00138180;
extern unsigned int D_00138330 NOT_SDA;
extern unsigned int D_00138334 NOT_SDA;
extern char D_L04_001B98C0[];
extern void func_L04_002FB920(void *);
/* The EE passes the float arguments in their own registers; listing the 0x22 ahead of the 0.0f
   keeps both banks in order and gives retail's argument setup. */
extern void func_00273318(void *, unsigned int, float, void *, int, float, int, float, int);
extern float func_00282C48(float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern float func_00282E80(void *, void *);
extern void func_00283098(void *, void *, void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern int func_00283D38(int, int, float);
extern float func_002A7878(float, float);
extern float func_002AA2E8(float *, float, float);
extern float func_L04_003524D0(int);
extern float func_L00_0032F038(int);
extern unsigned char *func_PAL_L04_003FE7B0(unsigned char *, float *, unsigned char *, float, float, float, float, float);

#define I(o) (*(int *)(s + (o)))
#define F(o) (*(float *)(s + (o)))
#define P(o) (*(u8 **)(s + (o)))

/* The rail-grind trick on Barlow's hoverbike tracks: arms after a jump onto a rail, reads the
   stick for the trick direction, spins and leans the bike, and draws the trick ring whose
   colour climbs with the combo. */
void func_PAL_L04_0041D788(u8 *self, u8 *s)
{
    Vector offset;
    Vector delta;
    Vector point;
    Vec rest;
    int limit;
    float height, stick, turn, spin, lean;

    if (!(D_L04_002C63C0[D_L04_001B090C].flags & 2)) {
        return;
    }
    limit = 750;
    if (D_L04_001B090C == 4) {
        limit = 500;
    }
    if (I(0x720) != 0 && limit < I(0x738)) {
        height = F(0x310) - *(float *)(*(u8 **)(P(0x734) + 0x68) + 0x11C);
        if (1.0f < height && height < 15.0f) {
            if (I(0x724) == 0 && func_00282C48(F(0x4A4)) < 1.5707964f && *(short *)(s + 0x274) == 0
                && I(0x4D8) == 0) {
                F(0x6A0) = 0.0f;
                I(0x754) = 0;
                I(0x728) = 0;
                F(0x740) = -999.0f;
                I(0x724) = 1;
                P(0x730) = P(0x734);
                if (func_002A7878(F(0x6A0), 1.0f) < 0.5f) {
                    F(0x6A4) = -0.5f;
                } else {
                    F(0x6A4) = 0.5f;
                }
            }
        }
        I(0x720) = 0;
        I(0x73C) = -1;
        I(0x744) = 0;
    }
    I(0x738)++;
    if (I(0x724) != 1) {
        return;
    }
    func_00282CF0(delta, self + 0x10, P(0x730) + 0x10);
    height = F(0x310) - *(float *)(*(u8 **)(P(0x730) + 0x68) + 0x11C);
    if (I(0x728) < 4
        && (height < 0.1f || func_00282DB0(delta, delta) > 500.0f || func_00282C48(F(0x6A4)) > 0.55f)) {
        if (func_00282C48(F(0x6A4)) > 0.55f) {
            D_L04_001B0938 = 4;
        }
        I(0x724) = 0;
        return;
    }
    stick = func_L04_003524D0(1);
    if (I(0x73C) == -1 && (0.9f < stick || (stick < 0.4f && (D_00138334 & 0xF000)))) {
        if (F(0x740) == -999.0f) {
            if (0.9f < stick) {
                F(0x740) = func_L00_0032F038(1);
                I(0x758) = 0;
            } else {
                unsigned int pressed = D_00138330;

                if (pressed & 0x1000) {
                    F(0x740) = -1.5707964f;
                } else if (pressed & 0x4000) {
                    F(0x740) = 1.5707964f;
                } else if (pressed & 0x8000) {
                    F(0x740) = 3.1415927f;
                } else {
                    F(0x740) = 0.0f;
                }
                I(0x758) = 1;
            }
        }
        I(0x73C) = 0;
    }
    if (I(0x73C) >= 0) {
        unsigned int held;

        I(0x73C)++;
        held = D_00138180.held;
        if (held & 0x1000) {
            stick = -1.5707964f;
        } else if (held & 0x4000) {
            stick = 1.5707964f;
        } else if (held & 0x8000) {
            stick = 3.1415927f;
        } else if (held & 0x2000) {
            stick = 0.0f;
        } else if (I(0x758) == 0) {
            stick = func_L00_0032F038(1);
        }
        turn = func_00283C80(F(0x740), stick);
        if (I(0x758) != 0 ? 1.3f < turn : 2.0f < turn) {
            F(0x740) = stick;
            if (I(0x728) >= 4) {
                if (I(0x744) == 0) {
                    if (func_002A7878(0.0f, 1.0f) < 0.5f) {
                        I(0x744) = 2;
                    } else {
                        I(0x744) = 1;
                    }
                } else {
                    I(0x744) += 2;
                }
            } else {
                turn = func_00282C48(F(0x6A0));
                if (I(0x758) != 0) {
                    spin = turn + 0.55f;
                } else {
                    spin = turn + 0.4f;
                }
                lean = spin;
                if (I(0x73C) < 12) {
                    lean += 0.1f;
                }
                F(0x6A0) = lean;
                if (func_00282C48(lean) < 0.55f
                    && (D_00138180.stick < 0.0f || (D_00138180.held & 0x8000))) {
                    F(0x6A0) = -F(0x6A0);
                }
            }
            I(0x73C) = -1;
        }
        if (I(0x728) >= 4) {
            limit = I(0x758) != 0 ? 12 : 8;
        } else {
            limit = I(0x758) != 0 ? 29 : 25;
        }
        if (limit < I(0x73C)) {
            I(0x73C) = -1;
        }
    }
    func_002AA2E8((float *)(s + 0x6A0), 0.0f, 0.010000001f);
    if (F(0x6A0) != 0.0f) {
        func_002AA2E8((float *)(s + 0x6A4), F(0x6A0), 0.038000003f);
    } else {
        func_002AA2E8((float *)(s + 0x6A4), F(0x6A0), 0.010000001f);
    }
    if (I(0x728) >= 34) {
        float yaw, pitch;

        rest.q = 0;
        rest.f[0] = -5.0f;
        rest.f[2] = 3.5f;
        offset[1] = func_002A7878(-0.75f, 0.75f);
        if (func_002A7878(0.0f, 1.0f) < 0.5f) {
            offset[1] -= 2.0f;
        } else {
            offset[1] += 2.0f;
        }
        func_00283098(point, rest.f, self + 0xC0);
        func_00282CC0(point, point, self + 0x10);
        yaw = func_00283248(*(float *)(self + 0x10) - point[0], *(float *)(self + 0x14) - point[1]);
        pitch = -func_00283248(func_00282E80(point, self + 0x10), *(float *)(self + 0x18) - point[2]);
        func_PAL_L04_003FE7B0(P(0x730), point, self, yaw, pitch, 0.0f, yaw, pitch);
        I(0x724) = 2;
    }
    func_00282D30(offset, D_L04_001B98C0, F(0x6A4));
    func_00282CC0(offset, offset, self + 0x10);
    func_L04_002FB920(self);
    {
        int combo = I(0x728);

        if (combo < 8) {
            stick = (float)combo * 0.125f;
            if (1.0f < stick) stick = 1.0f;
            if (stick < 0.0f) stick = 0.0f;
            limit = func_00283D38(0x500FFF0F, 0x500000EE, stick);
        } else if (combo < 17) {
            stick = (float)(combo - 8) * 0.125f;
            if (1.0f < stick) stick = 1.0f;
            if (stick < 0.0f) stick = 0.0f;
            limit = func_00283D38(0x500000EE, 0x800000FF, stick);
        } else if (combo < 25) {
            stick = (float)(combo - 17) * 0.125f;
            if (1.0f < stick) stick = 1.0f;
            if (stick < 0.0f) stick = 0.0f;
            limit = func_00283D38(0x800000FF, 0x50000033, stick);
        } else if (combo < 34) {
            stick = (float)(combo - 25) * 0.125f;
            if (1.0f < stick) stick = 1.0f;
            if (stick < 0.0f) stick = 0.0f;
            limit = func_00283D38(0x50000033, 0x800000FF, stick);
        } else {
            limit = 0x800000FF;
        }
        func_00273318(self, limit, 2.0f, offset, 0x22, 0.0f, -1, 90.0f, 4);
    }
    if (F(0x6A4) == 0.0f && F(0x6A0) == 0.0f) {
        I(0x728)++;
    } else {
        I(0x728) = 0;
    }
    I(0x738) = 0;
}
