#include "include_asm.h"

#include "common.h"
typedef struct {
    unsigned char pad0[0x30];
    float f30;
    float f34;
    unsigned char pad1[0x48];
} Rec_42550;
extern float D_L20_001B2124 __attribute__((sda));
extern float D_L20_001B2134 __attribute__((sda));
extern char g_hero_state[];
extern Rec_42550 *D_L20_001B308C;
extern float ApproachValue(float *, float, float);
extern void StepAngleTowardTarget(char *, int, float, float);
extern float vec_distance_xy(char *, char *);
extern float coll_probe_ground_height_below(void *, int, float);
extern float mat_fast_helper_a(float, float);
extern int moby_start_effect_from_entry(char *, float);
extern int PlayMobySound(int, int, char *);

int func_PAL_L20_00447F88(char *arg0) {
    char *s0 = arg0;
    char *s2 = *(char **)(arg0 + 0x68);
    char *s1;
    char *s3;
    float f0;
    int v0;
    Rec_42550 *p;

    ApproachValue((float *)(s0 + 0x48), 1.0f, 0.040000003f);

    if (*(u8 *)(s0 + 0x94) == 2) {
        StepAngleTowardTarget(s2 + 0x1804, 1, 0.0f, D_L20_001B2124 * 0.00017453295f);
    }
    f0 = *(float *)(s2 + 0xF8);
    s1 = g_hero_state;
    *(float *)(s0 + 0x18) += f0;

    *(float *)(s2 + 0xF8) -= *(float *)(s2 + 0x7C);

    if (*(int *)(s1 + 0x2294) == 0x8C) {
        float f0;
        s3 = s1 + 0x80;
        f0 = vec_distance_xy(s3, s0 + 0x10);
        if (f0 <= 4.0f) {
            f0 = *(float *)(s1 + 0x88);
            f0 += 5.0f;
            *(float *)(s1 + 0x88) = f0;
            f0 = coll_probe_ground_height_below(s3, 0, 0.5f);
            *(float *)(s1 + 0x88) = f0;
            *(unsigned short *)(s1 + 0x1E0) = 5;
            *(unsigned short *)(s1 + 0x1F0) = 5;
        }
        v0 = *(int *)(s2 + 0x230);
        p = (Rec_42550 *)((v0 << 7) + (unsigned int)D_L20_001B308C);
        f0 = mat_fast_helper_a(p->f30 - *(float *)(s0 + 0x10), p->f34 - *(float *)(s0 + 0x14));
        moby_start_effect_from_entry(s0, f0);

    } else {
        moby_start_effect_from_entry(s0, mat_fast_helper_a(
            *(float *)(s1 + 0x80) - *(float *)(s0 + 0x10),
            *(float *)(s1 + 0x84) - *(float *)(s0 + 0x14)));
    }

    if (*(float *)(s0 + 0x18) <= *(float *)(s2 + 0xE0)) {
        float velocity;
        *(float *)(s0 + 0x18) = *(float *)(s2 + 0xE0);
        PlayMobySound(0, 0, s0);
        velocity = *(float *)(s2 + 0xF8) * -D_L20_001B2134;
        *(float *)(s2 + 0xF8) = velocity;
        if (velocity < 0.020000001f) {
            *(int *)(s2 + 0xF8) = 0;
            return 1;
        }
    }
    return 0;
}

extern float D_L20_001B212C __attribute__((sda));
extern float D_L20_001B2130 __attribute__((sda));
extern float D_L20_001B2138 __attribute__((sda));
extern float D_L20_001B2128 __attribute__((sda));
extern void moby_set_controller_speed_limits(unsigned char *, float, float, float, float);
extern float square_root(float);

void func_PAL_L20_00447ED8(char *actor)
{
    char *state = *(char **)(actor + 0x68);
    moby_set_controller_speed_limits((unsigned char *)actor, 0.0f, 0.0f,
                 D_L20_001B212C * 6.981318e-06f,
                 D_L20_001B2130 * 0.0003490659f);
    *(float *)(state + 0x7C) = D_L20_001B2138 * 0.00040000002f;
    *(float *)(state + 0xE0) = coll_probe_ground_height_below(actor + 0x10, 0, 0.5f);
    qzero(state + 0xF0);
    *(float *)(state + 0xF8) = square_root(*(float *)(state + 0x7C) * 2.0f * D_L20_001B2128);
}
