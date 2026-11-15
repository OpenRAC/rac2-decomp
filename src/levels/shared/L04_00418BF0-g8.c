#include "common.h"

typedef float Vector[4] __attribute__((aligned(16)));
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char prefix[0x108]; float stick; char pad[0xA4]; unsigned int held; } PadState;

extern struct { s32 pad; s32 flags; u8 rest[56]; } g_race_challenge_table[];
extern int g_current_race_index __attribute__((sda));
extern int D_L04_001B0938 __attribute__((sda));
extern PadState g_pad_state;
extern unsigned int D_00138330 NOT_SDA;
extern unsigned int D_00138334 NOT_SDA;
extern char D_L04_001B98C0[];
extern void level_clear_leftover_flag(void *);
/* The EE passes the float arguments in their own registers; listing the 0x22 ahead of the 0.0f
   keeps both banks in order and gives retail's argument setup. */
extern void hud_add_moby_marker(void *, unsigned int, float, void *, int, float, int, float, int);
extern float math_fabs(float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float FastVecDot(void *, void *);
extern float vec_distance_xy(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern int FastTweenColor(int, int, float);
extern float math_random_float_range(float, float);
extern float ApproachValue(float *, float, float);
extern float pad_read_float_history(int);
extern float ReadPadFloatHistory(int);
extern unsigned char *homing_rocket_spawn(unsigned char *, float *, unsigned char *, float, float, float, float, float);

#define I(o) (*(int *)(s + (o)))
#define F(o) (*(float *)(s + (o)))
#define P(o) (*(u8 **)(s + (o)))

/* The rail-grind trick on Barlow's hoverbike tracks: arms after a jump onto a rail, reads the
   stick for the trick direction, spins and leans the bike, and draws the trick ring whose
   colour climbs with the combo. */
void hoverbike_update_rail_grind_trick(u8 *self, u8 *s)
{
    Vector offset;
    Vector delta;
    Vector point;
    Vec rest;
    int limit;
    float height, stick, turn, spin, lean;

    if (!(g_race_challenge_table[g_current_race_index].flags & 2)) {
        return;
    }
    limit = 900;
    if (g_current_race_index == 4) {
        limit = 600;
    }
    if (I(0x720) != 0 && limit < I(0x738)) {
        height = F(0x310) - *(float *)(*(u8 **)(P(0x734) + 0x68) + 0x11C);
        if (1.0f < height && height < 15.0f) {
            if (I(0x724) == 0 && math_fabs(F(0x4A4)) < 1.5707964f && *(short *)(s + 0x274) == 0
                && I(0x4D8) == 0) {
                F(0x6A0) = 0.0f;
                I(0x754) = 0;
                I(0x728) = 0;
                F(0x740) = -999.0f;
                I(0x724) = 1;
                P(0x730) = P(0x734);
                if (math_random_float_range(F(0x6A0), 1.0f) < 0.5f) {
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
    FastVecSub(delta, self + 0x10, P(0x730) + 0x10);
    height = F(0x310) - *(float *)(*(u8 **)(P(0x730) + 0x68) + 0x11C);
    if (I(0x728) < 5
        && (height < 0.1f || FastVecDot(delta, delta) > 500.0f || math_fabs(F(0x6A4)) > 0.55f)) {
        if (math_fabs(F(0x6A4)) > 0.55f) {
            D_L04_001B0938 = 4;
        }
        I(0x724) = 0;
        return;
    }
    stick = pad_read_float_history(1);
    if (I(0x73C) == -1 && (0.9f < stick || (stick < 0.4f && (D_00138334 & 0xF000)))) {
        if (F(0x740) == -999.0f) {
            if (0.9f < stick) {
                F(0x740) = ReadPadFloatHistory(1);
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
        held = g_pad_state.held;
        if (held & 0x1000) {
            stick = -1.5707964f;
        } else if (held & 0x4000) {
            stick = 1.5707964f;
        } else if (held & 0x8000) {
            stick = 3.1415927f;
        } else if (held & 0x2000) {
            stick = 0.0f;
        } else if (I(0x758) == 0) {
            stick = ReadPadFloatHistory(1);
        }
        turn = FastDiffRots(F(0x740), stick);
        if (I(0x758) != 0 ? 1.3f < turn : 2.0f < turn) {
            F(0x740) = stick;
            if (I(0x728) >= 5) {
                if (I(0x744) == 0) {
                    if (math_random_float_range(0.0f, 1.0f) < 0.5f) {
                        I(0x744) = 2;
                    } else {
                        I(0x744) = 1;
                    }
                } else {
                    I(0x744) += 2;
                }
            } else {
                turn = math_fabs(F(0x6A0));
                if (I(0x758) != 0) {
                    spin = turn + 0.55f;
                } else {
                    spin = turn + 0.4f;
                }
                lean = spin;
                if (I(0x73C) < 15) {
                    lean += 0.1f;
                }
                F(0x6A0) = lean;
                if (math_fabs(lean) < 0.55f
                    && (g_pad_state.stick < 0.0f || (g_pad_state.held & 0x8000))) {
                    F(0x6A0) = -F(0x6A0);
                }
            }
            I(0x73C) = -1;
        }
        if (I(0x728) >= 5) {
            limit = I(0x758) != 0 ? 15 : 10;
        } else {
            limit = I(0x758) != 0 ? 35 : 30;
        }
        if (limit < I(0x73C)) {
            I(0x73C) = -1;
        }
    }
    ApproachValue((float *)(s + 0x6A0), 0.0f, 0.008333334f);
    if (F(0x6A0) != 0.0f) {
        ApproachValue((float *)(s + 0x6A4), F(0x6A0), 0.031666666f);
    } else {
        ApproachValue((float *)(s + 0x6A4), F(0x6A0), 0.008333334f);
    }
    if (I(0x728) >= 41) {
        float yaw, pitch;

        rest.q = 0;
        rest.f[0] = -5.0f;
        rest.f[2] = 3.5f;
        offset[1] = math_random_float_range(-0.75f, 0.75f);
        if (math_random_float_range(0.0f, 1.0f) < 0.5f) {
            offset[1] -= 2.0f;
        } else {
            offset[1] += 2.0f;
        }
        matrix_mul_vec3(point, rest.f, self + 0xC0);
        FastVecAdd(point, point, self + 0x10);
        yaw = mat_fast_helper_a(*(float *)(self + 0x10) - point[0], *(float *)(self + 0x14) - point[1]);
        pitch = -mat_fast_helper_a(vec_distance_xy(point, self + 0x10), *(float *)(self + 0x18) - point[2]);
        homing_rocket_spawn(P(0x730), point, self, yaw, pitch, 0.0f, yaw, pitch);
        I(0x724) = 2;
    }
    FastVecScale(offset, D_L04_001B98C0, F(0x6A4));
    FastVecAdd(offset, offset, self + 0x10);
    level_clear_leftover_flag(self);
    {
        int combo = I(0x728);

        if (combo < 10) {
            stick = (float)combo * 0.1f;
            if (1.0f < stick) stick = 1.0f;
            if (stick < 0.0f) stick = 0.0f;
            limit = FastTweenColor(0x500FFF0F, 0x500000EE, stick);
        } else if (combo < 20) {
            stick = (float)(combo - 10) * 0.1f;
            if (1.0f < stick) stick = 1.0f;
            if (stick < 0.0f) stick = 0.0f;
            limit = FastTweenColor(0x500000EE, 0x800000FF, stick);
        } else if (combo < 30) {
            stick = (float)(combo - 20) * 0.1f;
            if (1.0f < stick) stick = 1.0f;
            if (stick < 0.0f) stick = 0.0f;
            limit = FastTweenColor(0x800000FF, 0x50000033, stick);
        } else if (combo < 41) {
            stick = (float)(combo - 30) * 0.1f;
            if (1.0f < stick) stick = 1.0f;
            if (stick < 0.0f) stick = 0.0f;
            limit = FastTweenColor(0x50000033, 0x800000FF, stick);
        } else {
            limit = 0x800000FF;
        }
        hud_add_moby_marker(self, limit, 2.0f, offset, 0x22, 0.0f, -1, 90.0f, 4);
    }
    if (F(0x6A4) == 0.0f && F(0x6A0) == 0.0f) {
        I(0x728)++;
    } else {
        I(0x728) = 0;
    }
    I(0x738) = 0;
}
