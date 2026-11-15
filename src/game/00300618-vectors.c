#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad bits; float f[4]; } Vector;
extern char *slot_get_by_index(int);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void mat_transform_via_copy(void *, void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);



/* Builds a local axis frame from the input direction and places the owner's linked part there. */
void moby_build_linked_frame(char *owner, Quad *input)
{
    Vector local[7];
    char *transform = slot_get_by_index(*(int *)(*(char **)(owner + 0x68) + 0x48));
    qcopy(&local[3], input);
    qcopy(&local[0], &local[3]);
    local[4].bits = 0;
    local[4].f[2] = 1.0f;
    FastVecCross(&local[1], &local[0], &local[4]);
    vec_scale_to_length(&local[1], &local[1], 1.0f);
    FastVecCross(&local[2], &local[1], &local[0]);
    mat_transform_via_copy(transform + 0x10, &local[0]);
    moby_transform_joint_to_world(owner, 0, &local[5]);
    matrix_mul_vec3(&local[3], input, owner + 0xC0);
    FastVecAdd(&local[6], &local[3], &local[5]);
}

/* Same as func_00305310: builds a local axis frame from the input direction and places the linked part. */
void moby_build_linked_frame_copy(char *owner, Quad *input)
{
    Vector local[7];
    char *transform = slot_get_by_index(*(int *)(*(char **)(owner + 0x68) + 0x48));
    qcopy(&local[3], input);
    qcopy(&local[0], &local[3]);
    local[4].bits = 0;
    local[4].f[2] = 1.0f;
    FastVecCross(&local[1], &local[0], &local[4]);
    vec_scale_to_length(&local[1], &local[1], 1.0f);
    FastVecCross(&local[2], &local[1], &local[0]);
    mat_transform_via_copy(transform + 0x10, &local[0]);
    moby_transform_joint_to_world(owner, 0, &local[5]);
    matrix_mul_vec3(&local[3], input, owner + 0xC0);
    FastVecAdd(&local[6], &local[3], &local[5]);
}
