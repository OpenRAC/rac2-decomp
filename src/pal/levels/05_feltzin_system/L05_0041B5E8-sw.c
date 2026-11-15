#include "include_asm.h"

#include "common.h"
extern char *moby_get_motion_data(char *);
extern void donor_transform_copy(char *);
extern void FastVecSub(char *, char *, char *);
extern void FastVecAdd(char *, char *, char *);
extern void FastVecScale(char *, char *, float);
extern void vec_clear_128(char *);
extern void moby_transform_joint_to_world(char *, int, char *);
extern void feltzin_helper_clear_slot(int, int);
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern int math_fast_float_d(void *);
extern int moby_get_sub_object_stored_value(void *);
extern void euler_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void mat_transform_via_copy(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern float IntToFloat(int);
extern float math_square(float);
extern void vec_fast_normalize3(void *, void *, void *, float);
extern void quaternion_to_rotation_basis(void *, void *);
extern void object_step_along_direction(char *, int);
extern void func_PAL_L05_0041BC50(char *, char *);
extern void func_PAL_002AD288(void *, void *, int, float, float);
extern void moby_mark_spawned(void *);
extern int feltzin_helper_end_if_hit(char *);

void func_PAL_L05_0041B5E8(char *object)
{
    char matrix[0x30];
    char delta[0x10], rot0[0x10], rot1[0x10], rot2[0x10], point[0x10];
    Vec up;
    char *target, *position;
    char *sub = *(char **)(object + 0x68);
    target = moby_get_motion_data(*(char **)(sub + 0x50));
    up.q = 0;
    up.f[2] = 1.0f;
    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        *(int *)(object + 0x98) = 0;
        object[0x20] = 1;
        /* fall through */
    case 1:
        donor_transform_copy(object);
        if (!moby_get_sub_object_stored_value(*(char **)(sub + 0x50))) object[0x20] = 4;
        break;
    case 2: {
        char *forward = object + 0xC0;
        char *right;
        char *normal;
        char *velocity;
        char *drift;
        float fraction;
        qcopy(sub, forward);
        right = object + 0xD0;
        qcopy(sub + 0x10, right);
        normal = object + 0xE0;
        qcopy(sub + 0x20, normal);
        position = object + 0x10;
        velocity = sub + 0x40;
        euler_rotation_basis(matrix, velocity);
        multiply_matrix3x3(forward, forward, matrix);
        mat_transform_via_copy(rot0, forward);
        FastVecSub(delta, *(char **)(target + 0x120) + 0x10, position);
        vec_scale_to_length(forward, delta, 1.0f);
        FastVecCross(right, forward, &up);
        vec_scale_to_length(right, right, *(int *)(sub + 0x54) ? -1.0f : 1.0f);
        drift = sub + 0x30;
        FastVecCross(normal, right, forward);
        mat_transform_via_copy(rot1, forward);
        fraction = IntToFloat(*(int *)(sub + 0x58));
        fraction /= IntToFloat(150);
        vec_fast_normalize3(rot2, rot0, rot1, math_square(1.0f - fraction));
        quaternion_to_rotation_basis(rot2, forward);
        object_step_along_direction(object, 0);
        FastVecAdd(position, drift, position);
        FastVecScale(drift, drift, .99f);
        FastVecScale(velocity, velocity, .99f);
        if (*(int *)(sub + 0x58) < 45) *(int *)(object + 0x98) = *(int *)(*(char **)(object + 0x24) + 0x10);
        if (math_fast_float_d(sub + 0x58)) {
            object[0x20] = 3;
            vec_clear_128(velocity);
            *(int *)(sub + 0x5C) = 0;
        }
        break;
    }
    case 3: {
        char *forward = object + 0xC0;
        char *right;
        char *normal;
        char *drift;
        if (!*(unsigned char *)(object + 0x31)) object[0x20] = 4;
        qcopy(sub, forward);
        right = object + 0xD0;
        qcopy(sub + 0x10, right);
        normal = object + 0xE0;
        qcopy(sub + 0x20, normal);
        moby_transform_joint_to_world(object, 0, delta);
        FastVecSub(delta, *(char **)(target + 0x120) + 0x10, delta);
        vec_scale_to_length(forward, delta, 1.0f);
        FastVecCross(right, forward, &up);
        vec_scale_to_length(right, right, *(int *)(sub + 0x54) ? -1.0f : 1.0f);
        drift = sub + 0x30;
        FastVecCross(normal, right, forward);
        *(int *)(object + 0xCC) = 0;
        *(int *)(object + 0xDC) = 0;
        *(int *)(object + 0xEC) = 0;
        vec_scale_to_length(delta, delta, *(float *)(sub + 0x5C));
        FastVecAdd(delta, delta, drift);
        object_step_along_direction(object, 0);
        moby_transform_joint_to_world(object, 0, point);
        FastVecAdd(object + 0x10, delta, object + 0x10);
        FastVecScale(drift, drift, .99f);
        *(float *)(sub + 0x5C) += 0.14f;
        func_PAL_L05_0041BC50(object, point);
        break;
    }
    case 4:
        func_PAL_002AD288(object, object + 0x10, -1, 3.0f, 13.0f);
        feltzin_helper_clear_slot(*(int *)(sub + 0x50), *(int *)(sub + 0x54));
        moby_mark_spawned(object);
        return;
    }
    feltzin_helper_end_if_hit(object);
}
