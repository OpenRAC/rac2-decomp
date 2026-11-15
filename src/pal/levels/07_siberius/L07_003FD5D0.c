#include "include_asm.h"
#include "names.h"

typedef int Q128 __attribute__((mode(TI)));
extern void moby_transform_joint_to_world(void *entity, int a, void *out);
extern void vec_scale_to_length(void *, void *, float);
extern void level_build_spawn_record(void *, void *, void *, void *, void *, void *, int, int, int);
extern void turret_start_swinging(char *);
extern char *group_pick_random_active_entity(int);

void func_PAL_L07_003FD5D0(char *obj)
{
    char *s2 = *(char **)(obj + 0x68);
    float v10[4];
    float v20[4];
    float v30[4];
    char *p;

    moby_transform_joint_to_world(obj, 0, v10);
    *(Q128 *)v30 = 0;
    v30[2] = 5.0f;
    vec_scale_to_length(v20, obj + 0xC0, 2.0f);
    for (;;) {
        p = group_pick_random_active_entity(*(int *)(s2 + 0x180));
        if (p == 0) break;
        turret_start_swinging(p);
        level_build_spawn_record(p, v10, v20, p + 0x10, v30, p + 0xF0, 0x4B, 0, 0);
    }
}



#include "common.h"
extern u8 D_L07_001B31AF __attribute__((sda));
extern u8 *g_moby_l07_array[] __attribute__((sda));
extern s32 D_L07_001B22F8[] __attribute__((sda));
extern s32 math_random_int_below(s32 n);
extern s32 math_fast_float_d(s32 *counter);
extern u8 *moby_find_active_in_group(u8 *a);
extern void anim_start_blended(u8 *a0, s32 a1, s32 a2, s32 a3);
extern u8 D_001A7BD0 __attribute__((sda));

void func_PAL_L07_003FD928(u8 *a0)
{
    u8 *p = *(u8 **)(a0 + 0x68);

    if (*(u32 *)(p + 0x420) == 0) {
        if (*(u8 *)(a0 + 0x43) != 2) {
            anim_start_blended(a0, 2, 0, 8);
        }
        return;
    }
    if (*(u8 *)(a0 + 0x43) != 8) {
        anim_start_blended(a0, 8, 0, 8);
    }
}

void func_PAL_L07_003FD988(u8 *a0)
{
    u8 *p = *(u8 **)(a0 + 0x68);

    if (*(u32 *)(p + 0x420) == 0) {
        if (*(u8 *)(a0 + 0x43) != 3) {
            anim_start_blended(a0, 3, 0, 8);
        }
        return;
    }
    if (*(u8 *)(a0 + 0x43) != 9) {
        anim_start_blended(a0, 9, 0, 8);
    }
}

