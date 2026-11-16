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

void feltzin_target_spawn_random_pal(u8 *arg0) {
    TI128 v[6];
    u8 *pw;
    u8 *px;
    u8 *p;
    s32 t;

    p = SpawnFreeLevelObjectById_pal(0x10F5, 1);
    *(TI128 *)&v[0] = 0;
    ((f32 *)&v[0])[2] = 1.0f;
    if (p == 0)
        return;
    t = math_random_int_range(0, 4);
    pw = (u8 *)&v[1];
    moby_transform_joint_to_world(arg0, t, pw);
    px = (u8 *)&v[2];
    moby_transform_joint_point(arg0, t, px);
    qcopy(p + 0x10, pw);
    qcopy(p + 0xC0, px);
    FastVecCross(p + 0xD0, p + 0xC0, (u8 *)&v[0]);
    vec_scale_to_length(p + 0xD0, p + 0xD0, 1.0f);
    FastVecCross(p + 0xE0, p + 0xD0, p + 0xC0);
    follower_start_random_push_pal(p);
}
