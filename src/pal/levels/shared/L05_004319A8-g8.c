#include "include_asm.h"

#include "common.h"
extern int g_current_map_index MACRO_ADDR;
extern int D_001A79F0_gp SDATA(D_001A79F0);
extern u8 g_level_progress_flags[];
extern float g_collectible_speed_scale __attribute__((sda));
extern float g_collectible_bob_base __attribute__((sda));
extern float g_collectible_bob_amplitude __attribute__((sda));
extern float g_collectible_spin_x __attribute__((sda));
extern float g_collectible_spin_y __attribute__((sda));
extern float g_collectible_spin_z __attribute__((sda));
extern float g_collectible_spin_phase __attribute__((sda));
extern int g_collectible_sparkle_chance __attribute__((sda));
extern int g_collectible_update_count __attribute__((sda));
extern u8 *g_pickup_first_moby __attribute__((sda));
extern int g_collectible_spin_timer __attribute__((sda));
extern int g_collectible_state_word __attribute__((sda));
extern int g_collectible_flags[] __attribute__((sda));
extern u8 g_hero_position[];
extern u8 g_hero_state[];
extern float math_random_angle(void);
extern void moby_init_randomized_vars_pal(void *);
extern float math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float, float);
extern void gold_bolt_glow_rings_update_pal(void *);
extern int math_random_int_below(int);
extern void part_spawn_sparkle_drift_pal(void *);
extern float fast_vec_dist(void *, void *);
extern void value_set_entry_by_index_pal(int, int);
extern int MemcardSave(int, int);
extern int PlayMobySound(int, int, void *);
extern void moby_mark_spawned(void *);
extern void cam_blend_moby_update(void *);
extern void gold_bolt_update_pal(void *);
extern void anim_start_blended_pal(void *, int, int, int);
extern void set_hero_animation_pal(int, int, float);
extern int math_fast_float_d(void *);
extern void hero_reset_position_and_direction_pal(void *, void *, int, int);
extern void cam_set_mode_state(int);
typedef union { float f[0x40]; int i[0x40]; s16 h[0x80]; u16 uh[0x80]; } Fields;

/* Updates a spinning collectible: bobs and spins in place, sparkles, and when the hero touches it, records it as taken and saves (PAL). */
void spinning_collectible_update_pal(u8 *actor)
{
    u8 *state = *(u8 **)(actor + 0x68);
    int i;
    u8 *hero;
    switch (actor[0x20]) {
    case 0:
        if (((Fields *)state)->i[0] == -1 || g_level_progress_flags[((Fields *)state)->i[0] + (D_001A79F0_gp << 2)] != 0) {
            moby_mark_spawned(actor);
            return;
        }
        qcopy(state + 0x10, actor + 0x10);
        ((Fields *)state)->f[0x1C / 4] = ((Fields *)actor)->f[0xF8 / 4];
        ((Fields *)actor)->f[0xF0 / 4] = math_random_angle();
        ((Fields *)actor)->f[0xF4 / 4] = math_random_angle();
        ((Fields *)actor)->f[0xF8 / 4] = math_random_angle();
        ((Fields *)actor)->f[0xFC / 4] = math_random_angle();
        ((Fields *)state)->f[0x68 / 4] = g_collectible_spin_x * 0.0003490659f;
        ((Fields *)state)->f[0x64 / 4] = g_collectible_spin_y * 0.0003490659f;
        ((Fields *)state)->f[0x60 / 4] = g_collectible_spin_z * 0.0003490659f;
        if (((Fields *)actor)->h[0x32 / 2] < 64)
            ((Fields *)actor)->h[0x32 / 2] = 64;
        actor[0x20] = 1;
        moby_init_randomized_vars_pal(actor);
        return;
    case 1:
        ((Fields *)actor)->f[0x2C / 4] = *(float *)(*(char **)(actor + 0x24) + 0x24) * g_collectible_speed_scale;
        ((Fields *)actor)->f[0x18 / 4] = ((Fields *)state)->f[0x18 / 4] + g_collectible_bob_base +
                                  g_collectible_bob_amplitude * math_fast_sin_or_cos_b(((Fields *)actor)->f[0xFC / 4]);
        ((Fields *)actor)->f[0xF0 / 4] = FastAddRotations(((Fields *)actor)->f[0xF0 / 4], g_collectible_spin_x * 0.0003490659f);
        ((Fields *)actor)->f[0xF4 / 4] = FastAddRotations(((Fields *)actor)->f[0xF4 / 4], g_collectible_spin_y * 0.0003490659f);
        ((Fields *)actor)->f[0xF8 / 4] = FastAddRotations(((Fields *)actor)->f[0xF8 / 4], g_collectible_spin_z * 0.0003490659f);
        ((Fields *)actor)->f[0xFC / 4] = FastAddRotations(((Fields *)actor)->f[0xFC / 4], g_collectible_spin_phase * 0.0003490659f);
        gold_bolt_glow_rings_update_pal(actor);
        if (math_random_int_below(g_collectible_sparkle_chance) == 0)
            part_spawn_sparkle_drift_pal(actor);
        if (fast_vec_dist(g_pickup_first_moby + 0x10, actor + 0x10) < 1.5f) {
            g_collectible_spin_timer = 150;
            value_set_entry_by_index_pal(0x124B, -1);
            g_level_progress_flags[((Fields *)state)->i[0] + (g_current_map_index << 2)] = 1;
            g_collectible_update_count++;
            MemcardSave(0, -1);
            PlayMobySound(1, 0, actor);
            moby_mark_spawned(actor);
        }
        return;
    case 2:
        g_collectible_flags[1] = 1;
        cam_blend_moby_update(actor);
        qcopy(actor + 0x10, g_hero_position);
        qcopy(actor + 0xF0, g_hero_position + 0x10);
        if (actor[0x42] == 1) {
            gold_bolt_update_pal(actor);
            if (math_random_int_below(10) == 0)
                part_spawn_sparkle_drift_pal(actor);
            if (actor[0x60] & 2) {
                if (actor[0x43] != 0)
                    anim_start_blended_pal(actor, 0, 0, 0);
                actor[0x31] = 0;
                ((Fields *)actor)->uh[0x34 / 2] |= 1;
                for (i = 3; i >= 0; i--)
                    part_spawn_sparkle_drift_pal(actor);
            }
        }
        hero = g_hero_state;
        if (*(int *)(hero + 0xC28) & 2)
            set_hero_animation_pal(0, 0, 25.0f);
        if (actor[0x42] == 0 && math_fast_float_d(state + 0x6C) != 0) {
            g_collectible_spin_timer = 150;
            value_set_entry_by_index_pal(0x1234, -1);
            g_level_progress_flags[((Fields *)state)->i[0] + (g_current_map_index << 2)] = 1;
            g_collectible_update_count++;
            g_collectible_state_word = 0;
            hero_reset_position_and_direction_pal(hero + 0x80, hero + 0x90, 0, 0);
            cam_set_mode_state(0);
            MemcardSave(0, -1);
            moby_mark_spawned(actor);
        }
        break;
    }
}
