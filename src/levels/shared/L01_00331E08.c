#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern void FastVecAdd(void *out, void *a, void *b);
extern float coll_get_heightmap_height(void *position);
extern void part_kill(void *object);
extern float g_falling_l01_part_gravity[];
extern float g_falling_part_floor_height MACRO_ADDR;
extern float g_falling_part_height_offset MACRO_ADDR;

/* Moves a falling particle each frame and removes it when it leaves the map or sinks below the ground. */
void part_l01_update_falling(char *object)
{
    float offset[4] __attribute__((aligned(16)));
    float test1[4] __attribute__((aligned(16)));
    float test2[4] __attribute__((aligned(16)));
    float *velocity = (float *)(object + 0x20);
    float *position;
    float height = velocity[3];
    float measured;
    int x;
    int y;
    if (*(float *)(object + 0x10) < 0.0f || *(float *)(object + 0x14) < 0.0f || *(float *)(object + 0x10) > 512.0f || *(float *)(object + 0x14) > 512.0f || *(float *)(object + 0x18) < height) {
        part_kill(object);
        return;
    }
    position = (float *)(object + 0x10);
    *(Quad *)offset = *(Quad *)velocity;
    x = (int)*(float *)(object + 0x10);
    y = (int)*(float *)(object + 0x14);
    offset[3] = 0.0f;
    FastVecAdd(position, position, offset);
    FastVecAdd(position, position, g_falling_l01_part_gravity);
    if (x != (int)*(float *)(object + 0x10) || y != (int)*(float *)(object + 0x14)) {
        *(Quad *)test1 = *(Quad *)position;
        measured = coll_get_heightmap_height(test1);
        if (g_falling_part_floor_height <= measured) {
            *(Quad *)test2 = *(Quad *)position;
            height = coll_get_heightmap_height(test2);
        } else {
            height = g_falling_part_floor_height;
        }
        if (*(float *)(object + 0x18) < height) {
            part_kill(object);
            return;
        }
    }
    offset[0] = 0.0f;
    offset[1] = 0.0f;
    offset[2] = -0.00013888889225199819f;
    offset[3] = 0.0f;
    FastVecAdd(velocity, offset, velocity);
    velocity[3] = height + g_falling_part_height_offset;
}
