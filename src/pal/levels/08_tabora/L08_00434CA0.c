#include "include_asm.h"

#include "common.h"
extern s32 g_moby_array __attribute__((sda));
extern f32 g_emitter_spawn_fraction __attribute__((sda));
extern s32 g_active_emitter_count __attribute__((sda));
extern char g_str_effect_name[] MACRO_ADDR;
extern char *part_find_owned_effect_slot(s32 a, s32 b, s32 c);
extern void moby_set_state(char *moby, s32 a1, s32 a2);
extern void part_spawn_masked_debris_pal(char *moby, f32 f12, f32 f13, s32 a1, char *a2,
                        f32 f14, f32 f15, s32 a3);
extern void part_spawn_scaled_bolts_pal(char *moby, s32 a1, f32 f12);
extern int PlayMobySound(s32 moby, s32 a1, char *a2);
extern s32 flag_set_first_pending(char *moby);
extern s32 math_fast_float_d(char *moby);
extern void moby_mark_spawned(char *moby);

/* Waits for the player, then fires its burst of particles and counts itself in the level counter
   until its timer runs out (PAL version). */
void emitter_update_pal(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    u8 state = *(u8 *)(moby + 0x20);
    char *effect_slot;
    s32 target_id;
    u8 target_state;

    switch (state) {
    case 0:
        moby_set_state(moby, 1, -1);
        return;
    case 1:
        effect_slot = part_find_owned_effect_slot((s32)moby, 0x04010000, 0);
        if (effect_slot != 0 && *(s32 *)vars == 0) {
            moby_set_state(moby, 2, -1);
            return;
        }
        *(u8 *)(moby + 0xA8) = 0xFF;
        target_id = *(s32 *)(vars + 4);
        if (target_id > 0) {
            char *target = (char *)(g_moby_array + (target_id << 8));

            if (target == 0) {
                return;
            }
            target_state = *(u8 *)(target + 0x20);
            if (target_state == 0xFE || (target_state == 0xFD || target_state == 3)) {
                moby_set_state(moby, 2, -1);
            }
        }
        return;
    case 2:
        if (*(u8 *)(moby + 0x31) != 0 && g_emitter_spawn_fraction < 0.9f &&
            g_active_emitter_count < 10) {
            part_spawn_masked_debris_pal(moby, 3.0f, 6.0f, 15, g_str_effect_name, 3.0f, 6.0f, 0xFF);
        } else {
            part_spawn_masked_debris_pal(moby, 3.0f, 6.0f, 9, g_str_effect_name, 3.0f, 6.0f, 0xFF);
        }
        part_spawn_scaled_bolts_pal(moby, 1, 0.0f);
        PlayMobySound(0, 0, moby);
        moby_set_state(moby, 3, -1);
        return;
    case 3:
        if (flag_set_first_pending(moby) != 0) {
            s32 count;
            *(u8 *)(moby + 0x31) = 0;
            count = g_active_emitter_count;
            *(u16 *)(moby + 0x34) |= 1;
            *(s32 *)(moby + 0x98) = 0;
            g_active_emitter_count = count + 1;
            *(s32 *)(vars + 8) = 0x64;
        }
        if (math_fast_float_d(vars + 8) != 0) {
            g_active_emitter_count = g_active_emitter_count - 1;
            moby_mark_spawned(moby);
        }
        return;
    }
}


extern void vec_local_offset_to_world(char *,void *,float,float,float);
extern void SpawnExplosionEffects_pal(char *,float,float,float,float,float,float,float,char *,void *,int,int,int,int,int,int,int,int,int);

/* Waits for the player, then fires its burst of particles and counts itself in the level counter
   until its timer runs out (PAL version). */
void emitter_burst_update_pal(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    u8 state = *(u8 *)(moby + 0x20);
    char *effect_slot;
    s32 target_id;
    u8 target_state;

    switch (state) {
    case 0:
        g_active_emitter_count = 0;
        moby_set_state(moby, 1, -1);
        return;
    case 1:
        effect_slot = part_find_owned_effect_slot((s32)moby, 0x04010000, 0);
        if (effect_slot != 0 && *(s32 *)vars == 0) {
            moby_set_state(moby, 2, -1);
            return;
        }
        *(u8 *)(moby + 0xA8) = 0xFF;
        target_id = *(s32 *)(vars + 4);
        if (target_id > 0) {
            char *target = (char *)(g_moby_array + (target_id << 8));

            if (target == 0) {
                return;
            }
            target_state = *(u8 *)(target + 0x20);
            if (target_state == 0xFE || (target_state == 0xFD || target_state == 3)) {
                moby_set_state(moby, 2, -1);
            }
        }
        return;
    case 2:
        { float v[4];
        vec_local_offset_to_world(moby,v,0.0f,0.0f,3.0f);
        if (*(u8 *)(moby + 0x31) != 0 && g_emitter_spawn_fraction < 0.9f &&
            g_active_emitter_count < 10) {
            SpawnExplosionEffects_pal(moby,0.0f,0.0f,1.0f,0.5f,9.0f,*(float *)(moby+0x2C)*1.3f,15.0f,
                         g_str_effect_name,v,10,3,16,-1,0,1,-1,0,0);
            part_spawn_masked_debris_pal(moby, 3.0f, 6.0f, 15, g_str_effect_name, 3.0f, 6.0f, 0xFF);
        } else {
            part_spawn_masked_debris_pal(moby, 3.0f, 6.0f, 1, g_str_effect_name, 3.0f, 6.0f, 0xFF);
        }
        part_spawn_scaled_bolts_pal(moby, 1, 0.0f);
        PlayMobySound(0, 0, moby);
        moby_set_state(moby, 3, -1);
        return; }
    case 3:
        if (flag_set_first_pending(moby) != 0) {
            s32 count;
            *(u8 *)(moby + 0x31) = 0;
            count = g_active_emitter_count;
            *(u16 *)(moby + 0x34) |= 1;
            *(s32 *)(moby + 0x98) = 0;
            g_active_emitter_count = count + 1;
            *(s32 *)(vars + 8) = 0x64;
        }
        if (math_fast_float_d(vars + 8) != 0) {
            g_active_emitter_count = g_active_emitter_count - 1;
            moby_mark_spawned(moby);
        }
        return;
    }
}



/* Waits for the player, then fires its burst of particles and counts itself in the level counter
   until its timer runs out (PAL version). */
void emitter_alt_update_pal(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    u8 state = *(u8 *)(moby + 0x20);
    char *effect_slot;
    s32 target_id;
    u8 target_state;

    switch (state) {
    case 0:
        moby_set_state(moby, 1, -1);
        return;
    case 1:
        effect_slot = part_find_owned_effect_slot((s32)moby, 0x04010000, 0);
        if (effect_slot != 0 && *(s32 *)vars == 0) {
            moby_set_state(moby, 2, -1);
            return;
        }
        *(u8 *)(moby + 0xA8) = 0xFF;
        target_id = *(s32 *)(vars + 4);
        if (target_id > 0) {
            char *target = (char *)(g_moby_array + (target_id << 8));

            if (target == 0) {
                return;
            }
            target_state = *(u8 *)(target + 0x20);
            if (target_state == 0xFE || (target_state == 0xFD || target_state == 3)) {
                moby_set_state(moby, 2, -1);
            }
        }
        return;
    case 2:
        if (*(u8 *)(moby + 0x31) != 0 && g_emitter_spawn_fraction < 0.9f &&
            g_active_emitter_count < 10) {
            part_spawn_masked_debris_pal(moby, 3.0f, 6.0f, 15, g_str_effect_name, 3.0f, 6.0f, 0xFF);
        } else {
            part_spawn_masked_debris_pal(moby, 3.0f, 6.0f, 1, g_str_effect_name, 3.0f, 6.0f, 0xFF);
        }
        part_spawn_scaled_bolts_pal(moby, 1, 0.0f);
        PlayMobySound(0, 0, moby);
        moby_set_state(moby, 3, -1);
        return;
    case 3:
        if (flag_set_first_pending(moby) != 0) {
            s32 count;
            *(u8 *)(moby + 0x31) = 0;
            count = g_active_emitter_count;
            *(u16 *)(moby + 0x34) |= 1;
            *(s32 *)(moby + 0x98) = 0;
            g_active_emitter_count = count + 1;
            *(s32 *)(vars + 8) = 0x64;
        }
        if (math_fast_float_d(vars + 8) != 0) {
            g_active_emitter_count = g_active_emitter_count - 1;
            moby_mark_spawned(moby);
        }
        return;
    }
}


