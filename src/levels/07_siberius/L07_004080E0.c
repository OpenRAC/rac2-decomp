#include "common.h"
extern void moby_set_state(void *, s32, s32);
extern u8 *part_find_owned_effect_slot(void *, s32, s32);
extern f32 fast_vec_dist(void *, void *);
extern s32 CollLine(void *, void *, s32, void *, s32);
extern int PlayMobySound(s32, s32, void *);
extern void part_explode_object_into_pieces(void *, void *, void *, void *, s32, s32, s32, s32, s32, s32, s32);
extern void part_l07_spawn_spark_burst(void *);
extern int snd_play_from_global_bank(s32, s32, s32);
extern void value_set_entry_by_index(s32, s32);
extern s32 math_fast_float_d(void *);
extern void moby_mark_spawned(void *);
extern u8 g_trigger_explode_part_bytes_a[16] __attribute__((sda));
extern u8 g_trigger_explode_part_bytes_b[8] __attribute__((sda));
extern u8 g_trigger_explode_part_bytes_c[8] __attribute__((sda));
extern s32 g_trigger_explode_sound_slot __attribute__((sda));
/* The byte is read through an absolute macro and written through a split address. */
extern u8 g_hero_event_flags __attribute__((nosda));
extern u8 D_001A7A70_read[] __asm__("D_001A7A70") __attribute__((sda));
extern s32 g_siberius_trigger_flags[] __attribute__((sda));
extern f32 g_spark_burst_saved_value __attribute__((sda));
extern f32 g_spark_burst_scale __attribute__((sda));

/* Updates a Siberius trigger object (moby class 3943): waits for a touch, plays an effect and sound once, then removes itself after a timer. */
void siberius_trigger_update(u8 *moby)
{
    f32 my_pos[4], target_pos[4];
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *target;
    s32 blocked;
    switch (moby[0x20]) {
    case 0:
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (!*(s32 *)vars) {
            target = part_find_owned_effect_slot(moby, 0x4010000, 0);
            if (target) {
                qcopy(my_pos, moby + 0x10);
                my_pos[2] += 0.5f;
                blocked = 1;
                if (*(u8 **)(target + 0x20)) {
                    qcopy(target_pos, *(u8 **)(target + 0x20) + 0x10);
                    target_pos[2] += 0.5f;
                    if (fast_vec_dist(target_pos, my_pos) < 64.0f) {
                        blocked = 0;
                        if (!CollLine(target_pos, my_pos, 2, moby, 0)) blocked = 1;
                    }
                }
                if (blocked) moby_set_state(moby, 2, -1);
            }
        }
        moby[0xA8] = 0xFF;
        break;
    case 2:
        PlayMobySound(0, 0, moby);
        part_explode_object_into_pieces(moby, g_trigger_explode_part_bytes_a, g_trigger_explode_part_bytes_b, g_trigger_explode_part_bytes_c, 0xFFF, -1, g_trigger_explode_sound_slot, 16, 0xFFFF, 0xFF, 0);
        part_l07_spawn_spark_burst(moby);
        *(s32 *)(vars + 4) = 480;
        if (!D_001A7A70_read[0]) {
            g_hero_event_flags = 1;
            snd_play_from_global_bank(1, 0, 0);
            value_set_entry_by_index(0x1233, -1);
            g_siberius_trigger_flags[0] = 1;
        }
        if (g_trigger_explode_sound_slot >= 0) *(u16 *)(moby + 0x7C) = (1 << g_trigger_explode_sound_slot) | 0x8000;
        else *(u16 *)(moby + 0x34) |= 0x41;
        moby_set_state(moby, 3, -1);
        break;
    case 3:
        if (math_fast_float_d(vars + 4)) {
            g_spark_burst_scale = g_spark_burst_saved_value;
            moby_mark_spawned(moby);
        }
        break;
    }
}
