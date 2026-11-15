#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef struct { Vector128 normal, quaternion, matrix[3]; } GroundRotation;
extern void vec_transform_by_object_or_given(char *,char *,char *,char *);
extern char g_hero_state[];
extern float mat_fast_helper_a(float,float);
extern float math_fabs(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern void vec_scale_to_length(void *,void *,float);
extern void quaternion_to_rotation_basis(void *,void *);
extern void multiply_matrix3x3(void *,void *,void *);
/* Tilts the object to follow the slope of the ground under it, within a small angle limit. */
void moby_tilt_to_ground_slope(char *object)
{
    GroundRotation local;
    char *state=*(char **)(object+0x68);
    vec_transform_by_object_or_given(object,(char *)&local.normal,g_hero_state,0);
    *(float *)(state+0x38)=-mat_fast_helper_a(((float *)&local.normal)[0],((float *)&local.normal)[1]);
    if (*(float *)(state+0x38)>0.2094395459f) {
        *(float *)(state+0x38)=0.2094395459f;
    } else if (*(float *)(state+0x38)<-0.2094395459f) *(float *)(state+0x38)=-0.2094395459f;
    if (math_fabs(*(float *)(state+0x38)) <= 0.00174532947f) return;
    vec_scale_to_length(&local.quaternion,object+0xe0,math_fast_sin_or_cos_b(*(float *)(state+0x38)*0.5f));
    ((float *)&local.quaternion)[3]=math_fast_sin_or_cos_a(*(float *)(state+0x38)*0.5f);
    quaternion_to_rotation_basis(&local.quaternion,local.matrix);
    multiply_matrix3x3(object+0xc0,local.matrix,object+0xc0);
}
