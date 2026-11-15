#include "names.h"
/* Second spawner state machine: waits for the player, then emits while its target is alive and
   the level counter (D_L08_001B3AA0) is below 10. */

#include "common.h"


extern s32 D_L08_001B29DC __attribute__((sda));
extern f32 D_L08_001B250C __attribute__((sda));
extern s32 g_active_emitter_count __attribute__((sda));
extern char D_L08_001A8F20[] MACRO_ADDR;
extern char *part_find_owned_effect_slot(s32 a, s32 b, s32 c);
extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern void part_spawn_masked_debris(char *a0, f32 f12, f32 f13, s32 a1, char *a2,
                        f32 f14, f32 f15, s32 a3);
extern void part_spawn_scaled_bolts(char *a0, s32 a1, f32 f12);
extern void PlayMobySound(s32 a0, s32 a1, char *a2);
extern s32 flag_set_first_pending(char *a0);
extern s32 math_fast_float_d(char *a0);
extern void moby_mark_spawned(char *a0);

extern void vec_local_offset_to_world(char *,void *,float,float,float);
extern void SpawnExplosionEffects(char *,float,float,float,float,float,float,float,char *,void *,int,int,int,int,int,int,int,int,int);
/* Waits for the player, then fires its burst of particles and counts itself in the level counter
   until its timer runs out. */
void emitter_burst_update(char *spawner) {
    char *vars = *(char **)(spawner + 0x68);
    u8 state = *(u8 *)(spawner + 0x20);
    char *hit;
    s32 childIndex;
    u8 childState;

    switch (state) {
    case 0:
        g_active_emitter_count = 0;
        moby_set_state(spawner, 1, -1);
        return;
    case 1:
        hit = part_find_owned_effect_slot((s32)spawner, 0x04010000, 0);
        if (hit != 0 && *(s32 *)vars == 0) {
            moby_set_state(spawner, 2, -1);
            return;
        }
        *(u8 *)(spawner + 0xA8) = 0xFF;
        childIndex = *(s32 *)(vars + 4);
        if (childIndex > 0) {
            char *child = (char *)(D_L08_001B29DC + (childIndex << 8));

            if (child == 0) {
                return;
            }
            childState = *(u8 *)(child + 0x20);
            if (childState == 0xFE || (childState == 0xFD || childState == 3)) {
                moby_set_state(spawner, 2, -1);
            }
        }
        return;
    case 2:
        { float v[4];
        vec_local_offset_to_world(spawner,v,0.0f,0.0f,3.0f);
        if (*(u8 *)(spawner + 0x31) != 0 && D_L08_001B250C < 0.9f &&
            g_active_emitter_count < 10) {
            SpawnExplosionEffects(spawner,0.0f,0.0f,1.0f,0.5f,9.0f,*(float *)(spawner+0x2C)*1.3f,15.0f,
                         D_L08_001A8F20,v,10,3,16,-1,0,1,-1,0,0);
            part_spawn_masked_debris(spawner, 3.0f, 6.0f, 15, D_L08_001A8F20, 3.0f, 6.0f, 0xFF);
        } else {
            part_spawn_masked_debris(spawner, 3.0f, 6.0f, 1, D_L08_001A8F20, 3.0f, 6.0f, 0xFF);
        }
        part_spawn_scaled_bolts(spawner, 1, 0.0f);
        PlayMobySound(0, 0, spawner);
        moby_set_state(spawner, 3, -1);
        return; }
    case 3:
        if (flag_set_first_pending(spawner) != 0) {
            s32 count;
            *(u8 *)(spawner + 0x31) = 0;
            count = g_active_emitter_count;
            *(u16 *)(spawner + 0x34) |= 1;
            *(s32 *)(spawner + 0x98) = 0;
            g_active_emitter_count = count + 1;
            *(s32 *)(vars + 8) = 0x78;
        }
        if (math_fast_float_d(vars + 8) != 0) {
            g_active_emitter_count = g_active_emitter_count - 1;
            moby_mark_spawned(spawner);
        }
        return;
    }
}
