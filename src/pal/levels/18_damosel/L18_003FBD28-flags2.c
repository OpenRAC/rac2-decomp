#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
extern u8 *part_spawn_gravity_fade(void *, void *, int, unsigned, int, int, int,
                          float, float, float, int);
extern u8 g_explosion_effect_desc[] __attribute__((sda));
extern u8 *g_particle_template_table[];
extern u8 *fireball_spawn(void *, void *, void *, int, float, float);
extern void gfx_update_color_fade_pal(u8 *arg0, u8 *arg1);
extern void moby_update_eased_node(u8 *arg0, u8 *arg1, s32 arg2, float arg3, float arg4);
extern void value_set_and_smooth_pal(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, float arg4);
extern void moby_update_ground_check(u8 *arg0);
extern float fast_vec_dist();
extern u8 g_beam_target_vec[];
extern u16 *g_condition_target_lists[];
extern u8 *g_moby_l18_table[] __attribute__((sda));
extern s32 g_max_l18_group_index[] __attribute__((sda));
extern s32 g_current_map_index __attribute__((sda));
extern u8 g_moby_group_flags[];
extern s32 IsPointInCuboid(u8 *, s32);
extern s32 CollLine(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
extern u16 *g_condition_target_lists[];
extern u8 *g_moby_l18_table[] __attribute__((sda));
extern s32 g_max_l18_group_index[] __attribute__((sda));
extern u8 g_data_block_base[];

/* Updates the enemy's body each frame: runs its animation helpers, clears its hit flags, and switches it to a new state when the hero's spot is close. (PAL version) */
void enemy_update_body_parts_pal(u8 *moby) {
    u8 *obj = moby;
    u8 *vars = *(u8 **)(obj + 0x68);
    gfx_update_color_fade_pal(moby, vars + 0x50);
    moby_update_eased_node(obj, vars + 0x680, 1, 0.0432f,
                  0.43200004f);
    moby_update_eased_node(obj, vars + 0x600, 0, 0.0432f,
                  0.43200004f);
    value_set_and_smooth_pal(obj, vars + 0x770, 2, 1, 2.5f);
    if (*(u16 *)(obj + 0x96) <= 0xFFFEu) {
        *(u16 *)(obj + 0x96) = *(u16 *)(obj + 0x96) + 1;
    }
    *(u16 *)(vars + 0x766) = 0;
    *(u16 *)(vars + 0x768) = 0;
    *(u16 *)(vars + 0x76A) = 0;
    if (*(u8 *)(obj + 0x31) != 0) {
        if (fast_vec_dist(obj + 0x10, g_beam_target_vec) < 24.0f) {
            moby_update_ground_check(obj);
            *(u8 *)(obj + 0x6F) = 0x16;
        }
    }
}
