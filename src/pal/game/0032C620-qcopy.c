/* SPDX-License-Identifier: MIT */
#include "common.h"

typedef int TrailQuad __attribute__((mode(TI)));
extern unsigned char g_trail_nodes[];
extern void vec_clear_128(void *);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern float math_random_angle(void);
extern float math_random_signed_float_range(float, float);

/* func_PAL_0032C620, the PAL copy of func_0032AE30: the same C, where the lifetime is scaled to 50 Hz
 * and the angle factor 0.00029088824f becomes 0.0003490659f. */
void part_claim_trail_node_pal(char *owner, void *position, int value)
{
    unsigned char *base = g_trail_nodes;
    int scale = 6;
    int flag = 0x800000;
    int *count = *(int **)(owner + 0x68);
    unsigned char *position_field = base + 0x10;
    unsigned char *slot = base;
    unsigned char *end = slot + 0x2800;
    float angle;
    int lifetime;

    do {
        if (*(int *)(slot + 0x44) == 0) {
            *(char **)(slot + 0x44) = owner;
            *(int *)(slot + 0x30) = value;
            *(TrailQuad *)slot = *(TrailQuad *)position;
            vec_clear_128(position_field);
            *(int *)(slot + 0x38) = flag;
            *(float *)(slot + 0x20) = math_random_float_range(0.1f, 0.3f);
            *(float *)(slot + 0x24) = math_random_float_range(0.4f, 0.5f);
            lifetime = ((s32)math_random_int_range(0x19, 0x28) * 5 + 2) / scale;
            *(int *)(slot + 0x3C) = lifetime;
            *(int *)(slot + 0x40) = lifetime;
            *(float *)(slot + 0x2C) = math_random_angle();
            angle = math_random_signed_float_range(180.0f, 360.0f);
            *(float *)(slot + 0x28) = angle * 0.0003490659f;
            *count += 1;
            break;
        }
        slot += 0x50;
        position_field += 0x50;
    } while ((long)slot < (long)end);
}
