#include "names.h"
/* Follows the attached target (two target kinds) and eases the object toward the computed position. */
#include "common.h"
typedef int OozlaQuad __attribute__((mode(TI)));
/* The object table pointer: $gp-relative in delay slots, lui/lw in ordinary flow. */
extern char *g_moby_l01_table MACRO_ADDR;
extern float vec_distance_xy(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void vec_fast_divide_helper(void *, void *, float);
extern void matrix_from_basis_rows(void *, void *);
extern void transform_vector(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
/* Keeps the object near the thing it is attached to, easing it toward a spot beside that target each frame. */
void moby_follow_attached_target(char *object)
{
    float position[4], offset[4], matrix[16];
    char *state = *(char **)(object + 0x68);
    char *target;
    int index = *(int *)(state + 0x384);
    if (index != -1) {
        target = g_moby_l01_table + (index << 8);
        if (target == 0) return;
        if (*(short *)(target + 0xAA) == 0xA56 /* moby class 2646 */) {
            if (vec_distance_xy(object + 0x10, target + 0x10) > 1.0f) {
                FastVecSub(offset, object + 0x10, target + 0x10);
                vec_scale_to_length(offset, offset, 1.0f);
                FastVecAdd(position, target + 0x10, offset);
            } else {
                qcopy(position, (object + 0x10));
            }
            if (position[2] < *(float *)(target + 0x18) + 0.01f)
                position[2] = *(float *)(target + 0x18) + 0.011f;
        } else if (*(short *)(target + 0xAA) == 0xA53 /* moby class 2643 */) {
            matrix_from_basis_rows(matrix, target + 0xC0);
            FastVecSub(offset, object + 0x10, target + 0x10);
            transform_vector(offset, offset, matrix);
            if (offset[0] > 2.0f) offset[0] = 2.0f;
            else if (offset[0] < -2.0f) offset[0] = -2.0f;
            if (offset[1] > 5.0f) offset[1] = 5.0f;
            else if (offset[1] < -5.0f) offset[1] = -5.0f;
            if (offset[2] < 0.01f) offset[2] = 0.01f;
            matrix_mul_vec3(offset, offset, target + 0xC0);
            FastVecAdd(position, target + 0x10, offset);
        } else {
            qcopy(position, (object + 0x10));
        }
        FastVecSub(offset, position, object + 0x10);
        vec_fast_divide_helper(offset, offset, 0.10000001f);
        FastVecAdd(object + 0x10, object + 0x10, offset);
    } else {
        char *attached = *(char **)(state + 0x198);
        if (attached && (*(short *)(attached + 0xAA) == 0xA56 /* moby class 2646 */ || *(short *)(attached + 0xAA) == 0xA53 /* moby class 2643 */))
            *(int *)(state + 0x384) = (attached - g_moby_l01_table) >> 8;
    }
}
