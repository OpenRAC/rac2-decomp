#include "common.h"

/* func_PAL_L09_00415440, the PAL copy of func_L09_00410200: the same C, with the 50 Hz
   velocity scales, the scaled puff life and the renumbered messages. */

/* The spawn ranges of the dust puffs, read through $gp. */
extern int g_dust_life_min __attribute__((sda));
extern int g_dust_life_max __attribute__((sda));
extern float g_dust_radius_min __attribute__((sda));
extern float g_dust_radius_max __attribute__((sda));
extern float g_dust_rise_speed_min __attribute__((sda));
extern float g_dust_rise_speed_max __attribute__((sda));
extern float g_dust_drag_min __attribute__((sda));
extern float g_dust_drag_max __attribute__((sda));
extern float g_dust_spin_min __attribute__((sda));
extern float g_dust_spin_max __attribute__((sda));
extern float g_dust_size_min __attribute__((sda));
extern float g_dust_size_max __attribute__((sda));
extern int g_dust_color_start __attribute__((sda));
extern int g_dust_color_end __attribute__((sda));
extern int g_dust_count_min __attribute__((sda));
extern int g_dust_count_max __attribute__((sda));
extern float g_dust_height_offset __attribute__((sda));
extern int g_input_block_flag __attribute__((sda));
extern int g_current_map_index __attribute__((section(".sdata")));
extern int g_dobbo_setting_flags[] __attribute__((sda));
extern int g_pad_held_flags __attribute__((nosda));
extern char g_sound_state[];
typedef struct {
    char pad0[0x33C];
    u8 *standing;
    char pad340[0x34E - 0x340];
    short busy;
    char pad350[0x22B4 - 0x350];
    u8 help;
} Player10200;

extern Player10200 g_hero_state;
extern u8 g_game_flag_table[];
extern char g_request_l09_queue[];

extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void add_vectors(void *, void *, void *);
extern int math_random_int_range(int, int);
extern int FastTweenColor(int, int, float);
extern int func_001163B0(void);
extern void *part_spawn_ground_effect(void *, int, float, float, int, int, int, void *, int, float);
extern void moby_set_state(void *, int, int);
extern int PlayMobySound(int, int, void *);
extern int TryClaimNotice(int, int, int);
extern int req_push_queue(void *, int);
extern s32 req_launch_queued(void *);
extern void data_set_small_value_and_refresh(int, int);
extern int game_is_either_mode_two(void);

/* Throws one dust puff at a random point around the object, then runs its state: 0 arms it,
   1 keeps its sound slot and, while the player stands on it, shows a message on levels 9 and
   18 and moves on when bit 0x10 of D_00138324 is set and D_L00_001A8FB4 is 4; 2 waits for
   func_00288AA0 on D_L09_001BFC00; 3 and 4 finish it. The frame counter at +0x96 saturates.
   The vector clear is qzero_nc: retail clears through a register address. */
/* Updates the Giant Clank pad: throws dust puffs around it and runs its states, from waiting for the player to stand on it to starting the level request (PAL: 50 Hz timings). */
void giant_l09_clank_pad_update_pal_2(u8 *moby)
{
    float pos[4];
    float vel[4];
    float point[4];
    int *vars = *(int **)(moby + 0x68);
    float radius;
    float spin;
    float size;
    int life;
    int tex;
    int count;
    int dir;
    char *sound_slot;

    radius = math_random_float_range(g_dust_radius_min, g_dust_radius_max);
    pos[0] = math_fast_sin_or_cos_a(math_random_angle()) * radius;
    pos[1] = math_fast_sin_or_cos_b(math_random_angle()) * radius;
    pos[2] = 0.0f;
    add_vectors(point, pos, moby + 0x10);
    pos[2] -= g_dust_height_offset;
    qzero_nc(vel);
    vel[2] = math_random_float_range(g_dust_rise_speed_min, g_dust_rise_speed_max) * 0.020000001f;
    life = (math_random_int_range(g_dust_life_min, g_dust_life_max) * 5 + 2) / 6;
    spin = math_random_float_range(g_dust_spin_min, g_dust_spin_max);
    size = math_random_float_range(g_dust_size_min, g_dust_size_max);
    tex = FastTweenColor(g_dust_color_start, g_dust_color_end, math_random_float_range(0.0f, 1.0f));
    count = math_random_int_range(g_dust_count_min, g_dust_count_max);
    dir = (func_001163B0() & 1) ? -count : count;
    part_spawn_ground_effect(pos, life, spin, size, tex, 2, dir, vel, 0,
                  -(math_random_float_range(g_dust_drag_min, g_dust_drag_max) * 0.00040000002f));

    switch (moby[0x20]) {
    case 0:
        moby_set_state(moby, 1, -1);
        vars[2] = -1;
        break;
    case 1:
        sound_slot = g_sound_state + vars[2] * 0x70;
        if (*(u8 **)(sound_slot + 0x88) != moby || *(u8 *)(sound_slot + 0x74) == 0)
            vars[2] = PlayMobySound(0, 4, moby);
        if (g_hero_state.standing != moby || g_hero_state.busy != 0)
            break;
        if (g_hero_state.help == 0) {
            if (g_current_map_index == 9)
                TryClaimNotice(4, 0x1318, 1);
            else if (g_current_map_index == 18)
                TryClaimNotice(4, 0x133F, 1);
        } else if (g_hero_state.help == 2) {
            TryClaimNotice(4, 0x1306, 1);
        }
        if (!(g_pad_held_flags & 0x10) || g_input_block_flag != 4)
            break;
        if (g_current_map_index == 9 || g_current_map_index == 18)
            moby_set_state(moby, 2, -1);
        else
            moby_set_state(moby, 4, -1);
        break;
    case 2:
        if (g_current_map_index == 9) {
            if (req_push_queue(g_request_l09_queue, 100)) {
                req_launch_queued(g_request_l09_queue);
                moby_set_state(moby, 3, -1);
            }
        } else if (g_current_map_index == 18) {
            if (req_push_queue(g_request_l09_queue, 0x92)) {
                req_launch_queued(g_request_l09_queue);
                moby_set_state(moby, 3, -1);
            }
        }
        break;
    case 3:
        if (game_is_either_mode_two()) {
            g_dobbo_setting_flags[2] = 1;
            break;
        }
    case 4: {
        int lvl;

        g_dobbo_setting_flags[2] = 0;
        moby[0x31] = 1;
        lvl = g_current_map_index;
        *(u16 *)(moby + 0x34) &= ~1;
        if (lvl == 9) {
            g_game_flag_table[0x1D] = 1;
            g_game_flag_table[0x2D] = 1;
        } else if (lvl == 18) {
            g_game_flag_table[0x87] = 1;
            g_game_flag_table[0x9F] = 1;
        }
        data_set_small_value_and_refresh(vars[0], 1);
        break;
    }
    case 5:
    case 6:
        break;
    }
    if (*(u16 *)(moby + 0x96) < 0xFFFF)
        *(u16 *)(moby + 0x96) += 1;
}
