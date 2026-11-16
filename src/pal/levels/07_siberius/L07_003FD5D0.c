#include "include_asm.h"
#include "names.h"

typedef int Q128 __attribute__((mode(TI)));
extern void moby_transform_joint_to_world(void *entity, int a, void *out);
extern void vec_scale_to_length(void *, void *, float);
extern void *level_build_spawn_record(void *, void *, void *, void *, void *, void *, int, int, int);
extern void turret_start_swinging(char *);
extern char *group_pick_random_active_entity(int);

/* Launches every member of the object's group away from it at a fixed speed. */
void group_launch_members_pal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float origin[4];
    float velocity[4];
    float extra[4];
    char *member;

    moby_transform_joint_to_world(moby, 0, origin);
    *(Q128 *)extra = 0;
    extra[2] = 5.0f;
    vec_scale_to_length(velocity, moby + 0xC0, 2.0f);
    for (;;) {
        member = group_pick_random_active_entity(*(int *)(vars + 0x180));
        if (member == 0) break;
        turret_start_swinging(member);
        level_build_spawn_record(member, origin, velocity, member + 0x10, extra, member + 0xF0, 0x4B, 0, 0);
    }
}



#include "common.h"
extern u8 g_flag_block __attribute__((sda));
extern u8 *g_moby_l07_array[] __attribute__((sda));
extern s32 g_entity_group_count[] __attribute__((sda));
extern s32 math_random_int_below(s32 n);
extern s32 math_fast_float_d(s32 *counter);
extern u8 *moby_find_active_in_group(u8 *a);
extern void anim_start_blended(u8 *a0, s32 a1, s32 a2, s32 a3);
extern u8 g_moby_update_inhibit_flag __attribute__((sda));

/* Picks the boss's idle animation (one set while no attack mode is active, another while one is) and changes it only if it differs. */
void boss_select_idle_anim_pal(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);

    if (*(u32 *)(vars + 0x420) == 0) {
        if (*(u8 *)(moby + 0x43) != 2) {
            anim_start_blended(moby, 2, 0, 8);
        }
        return;
    }
    if (*(u8 *)(moby + 0x43) != 8) {
        anim_start_blended(moby, 8, 0, 8);
    }
}

/* Picks the boss's attack animation (one set while no attack mode is active, another while one is) and changes it only if it differs. */
void boss_select_attack_anim_pal(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);

    if (*(u32 *)(vars + 0x420) == 0) {
        if (*(u8 *)(moby + 0x43) != 3) {
            anim_start_blended(moby, 3, 0, 8);
        }
        return;
    }
    if (*(u8 *)(moby + 0x43) != 9) {
        anim_start_blended(moby, 9, 0, 8);
    }
}

