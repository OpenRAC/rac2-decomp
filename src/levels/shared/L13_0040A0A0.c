#include "common.h"
extern void moby_probe_ground(char *, char *);
extern float fast_vec_dist(void *, void *);
extern float math_facing_angle_from_vector(char *, float *, const void *);
extern float vec_get_vertical_offset(char *, char *, char *);
extern void vec_add_transformed_point(float, float, float, char *, char *);
extern char D_L13_001B2590[] MACRO_ADDR;

void creature_resolve_ground_coll(char *object, char *state, char *target,
                       char *old_position, char *transform)
{
    int blocked = 0;
    char *position;
    float height;
    moby_probe_ground(object, state);
    height = fast_vec_dist(object + 0x10, D_L13_001B2590);
    if (height < *(float *)(state + 0x90) - *(float *)(state + 8)) {
        *(int *)(state + 0x94) |= 2;
        blocked = 1;
    }
    if (((*(int *)(state + 0x38) ^ 1) & 1) && *(short *)(state + 0xc2) < 5) {
        if (*(float *)(state + 0x90) + *(float *)(state + 0xc) < height) {
            *(int *)(state + 0x94) |= 1;
            blocked = 1;
        }
    }
    if (*(short *)(state + 0xc0) != 0) {
        if (*(float *)(state + 0x10) < math_facing_angle_from_vector(object, (float *)(state + 0x50), 0)) {
            *(int *)(state + 0x94) |= 4;
            blocked = 1;
        }
    }
    position = object + 0x10;
    if (blocked) {
        qcopy(position, old_position);
        moby_probe_ground(object, state);
        height = fast_vec_dist(position, D_L13_001B2590);
    }
    if (height <= *(float *)(state + 0x90) + 0.005f) {
        vec_get_vertical_offset(object, state + 0xa0, 0);
        if (transform != 0)
            vec_add_transformed_point(0.0f, 0.0f, *(float *)(state + 0x90) - height, object, position);
        *(short *)(state + 0xc2) = 0;
        *(short *)(state + 0xc0) += 1;
    } else if (*(float *)(state + 0x90) + *(float *)(state + 0xc) <= height) {
        *(short *)(state + 0xc0) = 0;
        *(short *)(state + 0xc2) += 1;
    }
    {
        float distance = fast_vec_dist(position, target);
        *(float *)(state + 0xcc) = distance;
        if (distance <= *(float *)(state + 0x34))
            *(int *)(state + 0x94) |= 0x80;
    }
}
