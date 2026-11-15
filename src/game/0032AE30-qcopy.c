/* SPDX-License-Identifier: MIT */
#include "common.h"

typedef int TrailQuad __attribute__((mode(TI)));
extern unsigned char g_trail_nodes[];
extern void vec_clear_128(void *);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern float math_random_angle(void);
extern float math_random_signed_float_range(float, float);

/* Initializes a free resident trail node and increments its owner's count. */
void part_claim_trail_node(char *owner, void *position, int value)
{
    unsigned char *base = g_trail_nodes;
    int flag = 0x800000;
    int *trail_count = *(int **)(owner + 0x68);
    unsigned char *velocity_field = base + 0x10;
    unsigned char *node = base;
    unsigned char *end = node + 0x2800;
    float angle;
    int lifetime;

    do {
        if (*(int *)(node + 0x44) == 0) {
            *(char **)(node + 0x44) = owner;
            *(int *)(node + 0x30) = value;
            *(TrailQuad *)node = *(TrailQuad *)position;
            vec_clear_128(velocity_field);
            *(int *)(node + 0x38) = flag;
            *(float *)(node + 0x20) = math_random_float_range(0.1f, 0.3f);
            *(float *)(node + 0x24) = math_random_float_range(0.4f, 0.5f);
            lifetime = math_random_int_range(0x19, 0x28);
            *(int *)(node + 0x3C) = lifetime;
            *(int *)(node + 0x40) = lifetime;
            *(float *)(node + 0x2C) = math_random_angle();
            angle = math_random_signed_float_range(180.0f, 360.0f);
            *(float *)(node + 0x28) = angle * 0.00029088824f;
            *trail_count += 1;
            break;
        }
        node += 0x50;
        velocity_field += 0x50;
    } while ((long)node < (long)end);
}
