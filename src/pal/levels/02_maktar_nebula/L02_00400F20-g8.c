#include "include_asm.h"
#include "names.h"
#include "moby_classes.h"

typedef unsigned char u8;
typedef short s16;
typedef int s32;
typedef float f32;
extern s32 g_group_max_index[] __attribute__((sda));
extern f32 g_cutscene_camera_time __attribute__((sda));
extern f32 g_cutscene_camera_angle __attribute__((sda));
extern s32 moby_is_state_six(char *);
extern s32 moby_is_state_one_cleared_vars(char *);
extern s32 math_random_int_below(s32);
extern s32 moby_has_free_child_slot_state2(char *);
extern s32 arena_is_entity_far_from_hero(char *);
extern f32 vec_distance_xy(char *, char *);
extern unsigned char g_game_flag_table[0x100];
extern int arena_get_challenge_save_index(int);
extern int arena_start_announcer_message(char *, int);
extern s32 g_frame_l02_counter;
extern s32 math_random_int_range(s32, s32);
extern s32 g_request_enabled_flag __attribute__((nosda));
extern s32 arena_start_announcer_message(char *, s32);
extern s32 g_game_mode __attribute__((nosda));
extern u8 g_game_flag_table[];
extern u8 g_item_slot_to_record[];
extern s32 PadPressedWithin(s32, s32, s32 *);
extern s32 arena_get_challenge_save_index(s32);
extern s32 flag_is_byte_set(void);
extern const s32 g_actor_idle_message_count_limit __attribute__((sda));
extern s32 g_actor_message_delay_base __attribute__((sda));
extern s32 g_player_stats;
extern s32 math_fast_float_d(void *);
extern void *cam_alloc_override_slot_pal(s32);
extern void cam_end_override(void *);
extern f32 g_helper_offset_a_x __attribute__((sda));
extern f32 g_helper_offset_a_y __attribute__((sda));
extern f32 g_helper_offset_a_z __attribute__((sda));
extern f32 g_helper_offset_b_x __attribute__((sda));
extern f32 g_helper_offset_b_y __attribute__((sda));
extern f32 g_helper_offset_b_z __attribute__((sda));
extern f32 g_helper_offset_c_x __attribute__((sda));
extern f32 g_helper_offset_c_y __attribute__((sda));
extern f32 g_helper_offset_c_z __attribute__((sda));
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} L02_003FC9C0_Vec3;

/* In state 8 the actor's 0xC0 object is created through func_PAL_L00_002D7850(5) when missing,
   otherwise it gets one of three float triples: by the class (+0xAA, MOBY_CLASS_CHAINBLADE or MOBY_CLASS_B2_BRAWLER_LEGS) of the
   0xD0 object, or the default one when there is none. In any other state the object is
   released through func_L00_002D7140 and the slot cleared.
   Each branch writes its own triple; the y and z stores (re-reading 0xC0) come out as one tail
   through cross-jumping after reload, which is why z keeps its own register ($f2). The stores
   are struct fields so the sda loads are not ordered behind them. */
void actor_update_helper_offsets_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);

    if (*(u8 *)(moby + 0x20) == 8) {
        L02_003FC9C0_Vec3 *cam_slot = *(L02_003FC9C0_Vec3 **)(vars + 0xC0);

        if (cam_slot == 0) {
            *(L02_003FC9C0_Vec3 **)(vars + 0xC0) = cam_alloc_override_slot_pal(5);
        } else {
            u8 *target_moby = *(u8 **)(vars + 0xD0);

            if (target_moby != 0) {
                if (*(s16 *)(target_moby + 0xAA) == MOBY_CLASS_CHAINBLADE) {
                    cam_slot->x = g_helper_offset_b_x;
                    (*(L02_003FC9C0_Vec3 **)(vars + 0xC0))->y = g_helper_offset_b_y;
                    (*(L02_003FC9C0_Vec3 **)(vars + 0xC0))->z = g_helper_offset_b_z;
                } else if (*(s16 *)(target_moby + 0xAA) == MOBY_CLASS_B2_BRAWLER_LEGS) {
                    cam_slot->x = g_helper_offset_c_x;
                    (*(L02_003FC9C0_Vec3 **)(vars + 0xC0))->y = g_helper_offset_c_y;
                    (*(L02_003FC9C0_Vec3 **)(vars + 0xC0))->z = g_helper_offset_c_z;
                }
            } else {
                cam_slot->x = g_helper_offset_a_x;
                (*(L02_003FC9C0_Vec3 **)(vars + 0xC0))->y = g_helper_offset_a_y;
                (*(L02_003FC9C0_Vec3 **)(vars + 0xC0))->z = g_helper_offset_a_z;
            }
        }
    } else {
        cam_end_override(*(L02_003FC9C0_Vec3 **)(vars + 0xC0));
        *(L02_003FC9C0_Vec3 **)(vars + 0xC0) = 0;
    }
}
