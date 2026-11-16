#include "names.h"
/* func_PAL_L19_00428CC0, the PAL copy of func_L19_00423548: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; rename func_L19_00423270 becomes func_PAL_L19_004289C0; rename func_002B0A18 becomes func_PAL_002B1588; wrap *(float *)(*(u8 **)(object + 0x24) + 0x24) (({e}) * 1.2. */
#include "common.h"

extern int g_current_map_index[] __attribute__((sda));
extern char g_hero_position[];
extern float g_warp_trigger_radius __attribute__((sda)), g_warp_trigger_speed_in __attribute__((sda));
extern float g_warp_trigger_speed_out __attribute__((sda)), g_warp_trigger_blend_rate __attribute__((sda));
extern float g_warp_trigger_height_range __attribute__((sda)), g_warp_trigger_reset_value __attribute__((sda));
extern float g_warp_trigger_lift_rate __attribute__((sda));
/* The hero: its state word and another mode word. */
typedef struct {
    char pad0[0x2294];
    int state;
    int pad2298;
    int mode;
} HeroModes;
extern HeroModes g_hero_state;
extern u8 g_moby_nibble_table[];
/* Player stats: the pending bolt credit at +0x1C. */
typedef struct { u8 pad0[0x1C]; int pending_bolts; } PlayerStats;
extern PlayerStats g_player_stats MACRO_ADDR;
extern u8 g_item_enabled_flags[] MACRO_ADDR;
extern int g_warp_triggered_flags[] MACRO_ADDR;
extern void anim_start_blended_pal(void *, int, int, int);
extern void EmitGrelbinGlowSprites_pal(void *);
extern float vec_distance_xy(void *, void *);
extern float math_fabs(float);
extern float vec_length_xy(void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_fast_divide_helper(void *, void *, float);
extern void moby_mark_spawned(void *);
extern int snd_play_from_class_bank(int, int, void *, int);
extern int snd_play_from_global_bank(int, int, void *);
extern int text_sum_subtitle_lengths(void);
extern void value_set_entry_by_index_pal(int, int);

/* A pickup that floats until the hero is close, then flies to the hero, shrinks, and adds a bolt when it arrives. (PAL version) */
void UpdateHomingCollectible_pal(u8 *moby)
{
    float direction[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(moby + 0x68);
    float distance, movement, threshold;
    switch (moby[0x20]) {
    case 0:
        moby[0x23] = 0x80;
        *(u32 *)(moby + 0x78) = 0xFFAAAAAA;
        *(u16 *)(moby + 0x34) |= 0x800;
        moby[0x20] = 1;
        if (moby[0x43]) anim_start_blended_pal(moby, 0, 0, 0);
        break;
    case 1:
        if (vec_distance_xy(moby + 0x10, g_hero_position) < g_warp_trigger_radius &&
            math_fabs(*(float *)(moby + 0x18) - *(float *)(g_hero_position + 8)) < g_warp_trigger_height_range) {
            *(float *)vars = g_warp_trigger_reset_value;
            if (moby[0x43] != 1) anim_start_blended_pal(moby, 1, 0, 20);
            *(float *)(moby + 0x48) = *(float *)vars + *(float *)vars;
            moby[0x20] = 2;
        }
        if (moby[0x31]) EmitGrelbinGlowSprites_pal(moby);
        break;
    case 2:
        if (moby[0x43] != 1) anim_start_blended_pal(moby, 1, 0, 20);
        *(float *)vars += (1.0f - *(float *)vars) * g_warp_trigger_blend_rate;
        *(float *)(moby + 0x48) = *(float *)vars + *(float *)vars;
        FastVecSub(direction, g_hero_position, moby + 0x10);
        direction[2] += 0.6f;
        distance = vec_length_xy(direction);
        threshold = 0.12f;
        if (*(int *)(g_hero_position + 0x2214) != 0x31)
            movement = g_warp_trigger_speed_in * (*(float *)vars * 0.020000001f);
        else {
            movement = g_warp_trigger_speed_out * (*(float *)vars * 0.020000001f);
            threshold = 0.8f;
        }
        vec_fast_divide_helper(direction, direction, movement);
        FastVecAdd(moby + 0x10, moby + 0x10, direction);
        if (*(float *)(moby + 0x2C) > 0.1f || distance < threshold || distance < movement)
            *(float *)(moby + 0x2C) -= g_warp_trigger_lift_rate * ((*(float *)(*(u8 **)(moby + 0x24) + 0x24)) * 1.2f);
        if ((distance < movement &&
             *(float *)(moby + 0x2C) < *(float *)(*(u8 **)(moby + 0x24) + 0x24) * 0.01f) ||
            g_hero_state.mode == 0x14 || g_hero_state.mode == 0x19 ||
            g_hero_state.state == 0x39 || g_hero_state.state == 0x6F) {
            if (*(u8 **)(vars + 4)) {
                u8 *linked = *(u8 **)(vars + 4);
                int uid = *(unsigned short *)(linked + 0xB2);
                if (uid & 1) {
                    unsigned char *nibble_ptr = &g_moby_nibble_table[((short)uid >> 1) + (g_current_map_index[0] << 10)];
                    if (((*nibble_ptr >> 4) & 7) != 7) {
                        *nibble_ptr += 0x10;
                    }
                } else {
                    unsigned char *nibble_ptr = &g_moby_nibble_table[((short)uid >> 1) + (g_current_map_index[0] << 10)];
                    if ((*nibble_ptr & 7) != 7) {
                        *nibble_ptr += 1;
                    }
                }
                moby_mark_spawned(*(u8 **)(vars + 4));
            }
            g_player_stats.pending_bolts++;
            snd_play_from_class_bank(3, 0, moby, 0x11C7);
            moby_mark_spawned(moby);
            if (!text_sum_subtitle_lengths() && !g_item_enabled_flags[6]) {
                g_item_enabled_flags[6] = 1;
                snd_play_from_global_bank(1, 0, 0);
                value_set_entry_by_index_pal(0x1233, -1);
                g_warp_triggered_flags[0] = 1;
            }
            moby_mark_spawned(moby);
        } else EmitGrelbinGlowSprites_pal(moby);
        break;
    }
}
