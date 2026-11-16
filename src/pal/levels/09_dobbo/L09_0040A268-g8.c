#include "include_asm.h"

#include "common.h"
extern f32 g_dobbo_fast_move_speed __attribute__((sda));
extern f32 g_dobbo_slow_move_speed __attribute__((sda));
extern s32 g_release_effect_state __attribute__((sda));
extern s32 g_release_busy_flag __attribute__((sda));
extern s32 func_323340(char *moby, char *a1, s32 a2);
extern s32 g_current_map_index;
extern s32 moby_apply_damage_to_object(char *moby, char *a1, s32 a2);
extern s32 weapon_select_aim_target(char *moby, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13);
extern s32 g_max_l09_group_id;
extern u8 *D_L09_001B285C_1;
extern u16 *g_track_entry_table[];
extern s32 g_dobbo_glow_colors[2];
extern s32 FastTweenColor(s32, s32, f32);
typedef struct {
    s32 a, b;
} ColorPair;
typedef struct {
    u8 pad[0x78];
    s32 colour;
} TintedObject;
extern ColorPair g_dobbo_tint_colors[2];
extern s32 g_frame_l09_counter;
extern f32 FastAddRotations(f32, f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern void moby_transform_joint_point(u8 *, s32, u8 *);
extern void gfx_add_draw_callback_first(void *, u8 *);
void dobbo_draw_pulsing_glows(u8 *moby);
extern u8 g_dobbo_spin_angle_base __attribute__((sda));
extern u8 g_moby_nibble_table[];
extern s32 g_game_mode __attribute__((nosda));
extern u8 g_level_progress_flags[];
extern u8 g_collection_progress_flags[] __attribute__((sda));

/* Steps the object's pulse: the angle at +0x348 advances by 2*pi/30 through the resident angle
   blend, its sine is mapped to 0..1 and kept at +0x34C, and the colour pair D_L09_001B1400 is
   blended by it into the object's word at +0x78. When the state's stamp (+0x350) differs from
   D_L09_001B2388, every visible class-0xD90 entity of the object's group that is not in state
   0xFE or 0xFD gets its point refreshed (func_0029FC20, selector 0) into its vector at +0x240
   and the same stamp; then func_L09_00405490 is registered as the object's callback. */
void dobbo_update_pulsing_tint_pal(u8 *moby) {
    u8 *state = *(u8 **)(moby + 0x68);
    ColorPair color = g_dobbo_tint_colors[0];
    u16 *track_ids;
    u8 *other;
    u8 *sub;
    f32 angle;
    f32 wave;

    angle = FastAddRotations(*(f32 *)(state + 0x348), 0.25132746f);
    *(f32 *)(state + 0x348) = angle;
    wave = math_fast_sin_or_cos_b(angle) * 0.5f + 0.5f;
    *(f32 *)(state + 0x34C) = wave;
    ((TintedObject *)moby)->colour = FastTweenColor(color.a, color.b, wave);
    if (*(s32 *)(state + 0x350) != g_frame_l09_counter) {
        for (track_ids = g_track_entry_table[moby[0x21]];
             moby[0x21] != 0xFF && moby[0x21] <= g_max_l09_group_id && track_ids != 0 &&
             ((track_ids != 0 && (s16)track_ids[-1] >= 0) || track_ids == g_track_entry_table[moby[0x21]]);
             track_ids++) {
            other = D_L09_001B285C_1 + ((*track_ids & 0x7FFF) << 8);
            if (other == 0)
                break;
            if (other[0x31] != 0 && *(s16 *)(other + 0xAA) == 0xD90) {
                if (other[0x20] != 0xFE) {
                    if (other[0x20] != 0xFD) {
                        sub = *(u8 **)(other + 0x68);
                        moby_transform_joint_point(other, 0, sub + 0x240);
                        *(s32 *)(sub + 0x350) = g_frame_l09_counter;
                    }
                }
            }
        }
        gfx_add_draw_callback_first((void *)dobbo_draw_pulsing_glows, moby);
    }
}
