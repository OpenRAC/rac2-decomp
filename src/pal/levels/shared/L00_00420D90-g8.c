#include "include_asm.h"

#include "common.h"
extern char *g_lava_gun_beam_slots __attribute__((sda));
extern void vec_transform_or_copy(void *, void *);
extern float math_spring_float_to_goal(float *, float, float *, float, float, float);
extern int math_fast_float_d(int *);

/* Walks the ten 0x530-byte records: spins the two direction vectors, then steps the fade state. */
void part_l00_update_effect_slots_2_pal(void)
{
    int index, axis;
    char *record;
    float *position, *velocity, value;

    for (index = 0; index < 10; index++) {
        record = (char *)(index * 0x530 + (int)g_lava_gun_beam_slots);
        if (*(int *)(record + 0x514) != 1)
            continue;
        velocity = (float *)(record + 0x4f0);
        position = (float *)(record + 0x500);
        for (axis = 0; axis < 2; axis++) {
            vec_transform_or_copy(record + 0x20 + axis * 16, record + 0x20 + axis * 16);
            value = position[axis] + velocity[axis];
            position[axis] = value;
            if (value <= -8.0f)
                position[axis] = value + 8.0f;
        }
        if (*(int *)(record + 0x518) == 0) {
            math_spring_float_to_goal((float *)(record + 0x510), 0.5f, (float *)(record + 0x51C), 0.0024f, 0.00024000001f, 0.024f);
            if (*(float *)(record + 0x510) == 0.5f) {
                *(int *)(record + 0x518) = 2;
                *(int *)(record + 0x520) = 50;
            }
        } else if (*(int *)(record + 0x518) == 1) {
            math_spring_float_to_goal((float *)(record + 0x510), 0.0f, (float *)(record + 0x51C), 0.0024f, 0.00024000001f, 0.024f);
            if (*(float *)(record + 0x510) == 0.0f)
                *(int *)(record + 0x514) = 0;
        } else if (math_fast_float_d((int *)(record + 0x520))) {
            *(int *)(record + 0x518) = 1;
        }
    }
}
