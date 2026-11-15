#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern s32 ref_L00_003F5870_00 MACRO_ADDR;
extern float ref_L00_003F5870_01 __attribute__((sda));
extern void cam_compute_view_direction(void *, void *, int);
extern float math_fabs(float);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void math_build_axis_angle_quat(void *, void *, float);
extern void vec_rotate_by_quaternion(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);

typedef struct {
    float offset[4];
    float position[4];
    float angle;
    float length;
    float f28;
    float f2c;
} L00Joint;

/* Sets one joint of a chain of 0x30-byte joints: its offset is the up axis (optionally
   transformed) or, past the first joint, the direction from the previous joint's position
   rotated by the joint's angle, scaled by the joint's length. */
void vaporizer_set_chain_joint_offset(L00Joint *joints, int index)
{
    float up[4] __attribute__((aligned(16)));
    float dir[4] __attribute__((aligned(16)));
    float diff[4] __attribute__((aligned(16)));
    float normal[4] __attribute__((aligned(16)));

    *(TI128 *)up = 0;
    up[2] = 1.0f;
    if (ref_L00_003F5870_00 != 0)
        cam_compute_view_direction(up, joints[index].position, 1);
    if ((float)index == 0.0f || math_fabs(joints[index].angle) < 0.00001f) {
        FastVecScale(dir, up, joints[index].length);
    } else {
        FastVecSub(diff, joints[index].position, joints[index - 1].position);
        vec_scale_to_length(normal, diff, 1.0f);
        math_build_axis_angle_quat(normal, normal, joints[index].angle);
        vec_rotate_by_quaternion(dir, up, normal);
        FastVecScale(dir, dir, joints[index].length);
    }
    FastVecAdd(joints[index].offset, joints[index].position, dir);
    joints[index].offset[3] = ref_L00_003F5870_01;
}
