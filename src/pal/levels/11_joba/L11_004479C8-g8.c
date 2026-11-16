#include "include_asm.h"
#include "names.h"

typedef int s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef float f32;
extern s32 g_arena_intro_script_handle_a __attribute__((sda));
extern s32 g_arena_intro_script_handle_b __attribute__((sda));
extern s32 g_arena_intro_script_handle_c __attribute__((sda));
extern s32 g_arena_intro_script_handle_d __attribute__((sda));
extern u8 g_hero_l11_position[];
extern u8 *g_moby_l11_table[3] __attribute__((sda));
extern u8 *g_group_id_lists[];
extern s32 g_tribe_group_limit __attribute__((sda));
extern u8 *D_L11_001B359C_abs[3] __attribute__((sda));
extern s32 arena_is_entity_far_in_direction(u8 *);
extern s32 moby_has_free_child_slot_state2(u8 *);
extern f32 g_arena_fighter_param_min __attribute__((sda));
extern f32 g_arena_fighter_param_max __attribute__((sda));
extern f32 g_arena_fighter_turn_step __attribute__((sda));
extern f32 g_arena_fighter_velocity_scale __attribute__((sda));
extern u8 *arena_get_center_point(u8 *);
extern s32 D_L11_001B35B8_1[] __attribute__((sda));
extern f32 g_arena_spawn_time_scale __attribute__((sda));
extern f32 g_arena_spawn_angle_scale __attribute__((sda));
extern s32 moby_is_state_six(u8 *);
extern s32 moby_is_state_one_cleared_vars(u8 *);
extern s32 math_random_int_below(s32);
extern const f32 g_arena_camera_guide_a_x __attribute__((sda));
extern const f32 g_arena_camera_guide_a_y __attribute__((sda));
extern const f32 g_arena_camera_guide_a_z __attribute__((sda));
extern const f32 g_arena_camera_guide_b_x __attribute__((sda));
extern const f32 g_arena_camera_guide_b_y __attribute__((sda));
extern const f32 g_arena_camera_guide_b_z __attribute__((sda));
extern const f32 g_arena_camera_guide_c_x __attribute__((sda));
extern const f32 g_arena_camera_guide_c_y __attribute__((sda));
extern const f32 g_arena_camera_guide_c_z __attribute__((sda));
extern const f32 g_arena_camera_guide_d_x __attribute__((sda));
extern const f32 g_arena_camera_guide_d_y __attribute__((sda));
extern const f32 g_arena_camera_guide_d_z __attribute__((sda));
extern const f32 g_arena_camera_guide_e_x __attribute__((sda));
extern const f32 g_arena_camera_guide_e_y __attribute__((sda));
extern const f32 g_arena_camera_guide_e_z __attribute__((sda));
extern u8 g_hero_state[];
extern void *cam_alloc_override_slot_pal(s32);
extern void cam_end_override(void *);
extern void cam_set_strength_and_steer_target(void *, f32, f32);
#define GUIDE (*(f32 **)(s + 0x170))
#define SET_GUIDE(x, y, z) (GUIDE[0] = (x), GUIDE[1] = (y), GUIDE[2] = (z))

void arena_update_camera_guide_pal(u8 *obj) {
    u8 *s = *(u8 **)(obj + 0x68);

    if (obj[0x20] == 8 || obj[0x20] == 9) {
        if (GUIDE == 0) {
            GUIDE = cam_alloc_override_slot_pal(5);
        } else if (*(void **)(s + 0x180) != 0) {
            if (*(u8 **)(s + 0x184) == 0) {
                SET_GUIDE(g_arena_camera_guide_a_x, g_arena_camera_guide_a_y, g_arena_camera_guide_a_z);
                return;
            }
            if (*(s16 *)(*(u8 **)(s + 0x184) + 0xAA) == 0xD4A)
                SET_GUIDE(g_arena_camera_guide_c_x, g_arena_camera_guide_c_y, g_arena_camera_guide_c_z);
            if (*(s16 *)(*(u8 **)(s + 0x184) + 0xAA) == 0xD4B)
                SET_GUIDE(g_arena_camera_guide_e_x, g_arena_camera_guide_e_y, g_arena_camera_guide_e_z);
            else if (*(s16 *)(*(u8 **)(s + 0x184) + 0xAA) == 0xB3A)
                SET_GUIDE(g_arena_camera_guide_d_x, g_arena_camera_guide_d_y, g_arena_camera_guide_d_z);
        } else if (obj[0x20] == 9) {
            u8 *player = g_hero_state;
            SET_GUIDE(g_arena_camera_guide_b_x, g_arena_camera_guide_b_y, g_arena_camera_guide_b_z);
            if (*(f32 *)(player + 0x88) > ((f32 *)arena_get_center_point(obj))[2] + 16.0f) {
                if (*(u16 *)(obj + 0x96) < 417)
                    cam_set_strength_and_steer_target(arena_get_center_point(obj), 0.17453295f, 0.0f);
                else
                    cam_set_strength_and_steer_target(arena_get_center_point(obj), 0.008726647f, 0.0f);
            }
        } else {
            SET_GUIDE(g_arena_camera_guide_a_x, g_arena_camera_guide_a_y, g_arena_camera_guide_a_z);
        }
    } else {
        cam_end_override(GUIDE);
        GUIDE = 0;
    }
}
