#include "names.h"
/* func_003076F0: the motion pointer is a byte pointer (its scale is at +0x10), the child's
 * entity is read once for the copy and the +0xE0 argument, and the copy is
 * qcopy(), so the buffer address is set up before the motion is saved. */
#include "common.h"


extern char *moby_get_private_value_0(char *);
extern void moby_get_facing_direction(void *object, float *out);
extern void FastVecScale(char *local, void *value, float scale);
extern void FastVecAdd(void *out, void *a, void *b);
extern void moby_transform_joint_to_world(void *entity, int a, void *out);
extern void FastVecSub(void *out, void *a, void *b);
extern void mat_fast_helper_c(float *out, float *in);
extern void matrix_mul_vec3(void *out, void *a, void *b);

/* Aims the Megaturret at its locked target. Drops the target and goes idle when the target is gone. */
void megaturret_aim_at_target(char *object)
{
    float vec[28];
    char *vars = *(char **)(object + 0x68);
    char *target_info = moby_get_private_value_0(*(char **)(vars + 0x64));
    char *target;

    moby_get_facing_direction(object + 0x10, &vec[4]);
    target = *(char **)(vars + 0x64);
    qcopy(&vec[0], target + 0x10);
    if (target_info != 0) {
        FastVecScale((char *)&vec[12], target + 0xE0, *(float *)(target_info + 0x10));
        FastVecAdd(&vec[0], &vec[0], &vec[12]);
    }
    if (*(char **)(vars + 0x64) == 0
            || *(unsigned char *)(*(char **)(vars + 0x64) + 0x20) == 0xFE
            || *(unsigned char *)(*(char **)(vars + 0x64) + 0x20) == 0xFD
            || !(*(unsigned short *)(*(char **)(vars + 0x64) + 0x34) & 0x1000)) {
        *(unsigned char *)(object + 0x20) = 3;
        *(char **)(vars + 0x64) = 0;
        return;
    }
    moby_transform_joint_to_world(object, 0, &vec[8]);
    FastVecSub(&vec[12], &vec[0], &vec[8]);
    mat_fast_helper_c(&vec[16], (float *)(object + 0xC0));
    matrix_mul_vec3(vars + 0x20, &vec[12], &vec[16]);
}
