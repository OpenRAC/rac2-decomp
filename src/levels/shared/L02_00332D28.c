#include "names.h"
/* func_L02_00332D28 in its own unit (flags in config/cflags.txt: -O2 -G0 -ffunction-sections). */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
extern void FastVecAdd(void *, void *, void *);
extern int coll_check_sphere_hit(void *, void *);
extern void FastVecSub(void *, void *, void *);
/* Canonical pointer inputs and float return are explicit. */
extern float vec_get_horizontal_offset_length(char *, char *, char *);
extern void vec_transform_and_scale(char *, char *, char *, float, char *);
extern float gravity_get_center_distance(char *);
extern void vec_add_transformed_point(char *, char *, float, float, float);
extern void vec_transform_and_set_height(char *, char *, char *, float, char *);
extern int math_fast_float_d(void *);

/* Moves an object by its velocity and pushes it out of any walls it touched, trying up to 8 times. It slows the object, keeps it above the ground and counts how long it has been touching. */
void coll_move_resolve_collisions(char *object, char *data, void *originalPosition, void *scratch, char *transform) {
    TI128 before;
    int hit, i;
    float speed, height;
    FastVecAdd(object + 0x10, object + 0x10, data + 0xA0);
    qcopy(&before, object + 0x10);
    *(int *)(data + 0x84) = 0;
    qzero(data + 0x60);
    {
        int changed = 0;
        for (i = 0; i < 8; i++) {
            hit = coll_check_sphere_hit(object, data);
            changed |= hit;
            if (!hit)
                break;
        }
        if (changed) {
            FastVecSub(data + 0xA0, object + 0x10, originalPosition);
            speed = vec_get_horizontal_offset_length(object, data + 0xA0, transform);
            if (*(float *)(data + 0xB0) < speed)
                vec_transform_and_scale(object, data + 0xA0, data + 0xA0, *(float *)(data + 0xB0), transform);
            else
                *(float *)(data + 0xB0) = speed;
            height = gravity_get_center_distance(object + 0x10);
            if (height <= *(float *)(data + 0x90)) {
                float zero = 0.0f;
                vec_add_transformed_point(object, object + 0x10, zero, zero, *(float *)(data + 0x90) - height);
                vec_transform_and_set_height(object, data + 0xA0, data + 0xA0, zero, transform);
            }
            if (*(float *)(data + 0xB0) < *(float *)(data + 0x28) * 0.5f)
                *(int *)(data + 0x80) += 1;
            else
                math_fast_float_d(data + 0x80);
        } else {
            math_fast_float_d(data + 0x80);
        }
        FastVecSub(data + 0x70, object + 0x10, &before);
    }
}
