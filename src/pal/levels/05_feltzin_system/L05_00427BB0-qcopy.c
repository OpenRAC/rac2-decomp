#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern u8 *SpawnFreeLevelObjectById_pal(s32 a0, s32 a1);
extern s32 math_random_int_range(s32 a0, s32 a1);
extern void moby_transform_joint_to_world(u8 *a0, s32 a1, u8 *a2);
extern void moby_transform_joint_point(u8 *a0, s32 a1, u8 *a2);
extern void FastVecCross(u8 *a0, u8 *a1, u8 *a2);
extern void vec_scale_to_length(u8 *a0, u8 *a1, f32 f12);
extern void follower_start_random_push_pal(u8 *a0);

/* Spawns a target moby at a random joint of the object and points it along that joint. */
void feltzin_target_spawn_random_pal(u8 *moby) {
    TI128 vecs[6];
    u8 *joint_world;
    u8 *joint_point;
    u8 *target;
    s32 joint;

    target = SpawnFreeLevelObjectById_pal(0x10F5, 1);
    *(TI128 *)&vecs[0] = 0;
    ((f32 *)&vecs[0])[2] = 1.0f;
    if (target == 0)
        return;
    joint = math_random_int_range(0, 4);
    joint_world = (u8 *)&vecs[1];
    moby_transform_joint_to_world(moby, joint, joint_world);
    joint_point = (u8 *)&vecs[2];
    moby_transform_joint_point(moby, joint, joint_point);
    qcopy(target + 0x10, joint_world);
    qcopy(target + 0xC0, joint_point);
    FastVecCross(target + 0xD0, target + 0xC0, (u8 *)&vecs[0]);
    vec_scale_to_length(target + 0xD0, target + 0xD0, 1.0f);
    FastVecCross(target + 0xE0, target + 0xD0, target + 0xC0);
    follower_start_random_push_pal(target);
}
