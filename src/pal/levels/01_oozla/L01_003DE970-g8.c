#include "include_asm.h"

#include "common.h"
extern f32 g_falling_object_target_scale __attribute__((sda));
extern f32 g_falling_object_scale_blend __attribute__((sda));
extern f32 g_falling_object_spin_rate __attribute__((sda));
extern f32 g_falling_object_collision_radius __attribute__((sda));
extern u8 *g_hit_l01_result __attribute__((nosda));
typedef struct { u8 pad[0x2290]; s32 collision; } CameraAB;
extern CameraAB g_hero_state;
extern void FastVecAdd(void *, void *, void *);
extern void part_spawn_debris_burst_pal(void *);
extern void anim_start_blended_pal(void *, s32, s32, s32);
extern f32 level_get_water_height_pal(void);
extern s32 coll_test_point(void *, s32, f32, s32);
extern void part_l01_spawn_explosion_particles_pal(void *, void *);
extern int coll_cast_object_line(s32, void *, void *, f32, f32, s32, s32, s32, s32);
extern void vec_scale_to_length(void *, void *, f32);
extern void moby_mark_spawned(void *);
extern void part_queue_ground_shadow(void *, f32);

/* Updates a falling object. It drifts down while spinning and casts a shadow, then bursts into particles when it hits the ground or the water (PAL: 50 Hz rates). */
void falling_l01_object_update_pal(u8 *moby) {
    f32 pos[4] __attribute__((aligned(16)));
    f32 bottom[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(moby + 0x68);
    f32 height;
    *(f32 *)(moby + 0x2C) += (*(f32 *)(*(u8 **)(moby + 0x24) + 0x24) * g_falling_object_target_scale - *(f32 *)(moby + 0x2C)) * g_falling_object_scale_blend;
    qcopy(pos, moby + 0x10);
    FastVecAdd(moby + 0x10, moby + 0x10, state);
    part_spawn_debris_burst_pal(moby);
    if ((moby[0x60] & 2) && moby[0x43] != 1) anim_start_blended_pal(moby, 1, 0, 10);
    height = level_get_water_height_pal();
    if ((coll_test_point(moby + 0x10, 0, g_falling_object_collision_radius, *(s32 *)(state + 0x10)) &&
          (!g_hit_l01_result || *(s16 *)(g_hit_l01_result + 0xAA) != 0x660)) || *(f32 *)(moby + 0x18) < height) {
        part_l01_spawn_explosion_particles_pal(moby, state);
        qcopy(bottom, moby + 0x10);
        bottom[2] -= 6.0f;
        coll_cast_object_line(g_hero_state.collision, moby + 0x10, bottom, 0.0001f, 1.0f, 1, 0, 1, 0);
        vec_scale_to_length(state, state, g_falling_object_collision_radius);
        *(s32 *)(state + 8) = 0;
        FastVecAdd(moby + 0x10, moby + 0x10, state);
        FastVecAdd(bottom, bottom, state);
        coll_cast_object_line(g_hero_state.collision, moby + 0x10, bottom, 0.0001f, 1.0f, 1, 0, 1, 0);
        moby_mark_spawned(moby);
    } else {
        *(f32 *)(state + 8) -= g_falling_object_spin_rate * 0.00040000002f;
        if (*(f32 *)(moby + 0x10) < 2.0f || *(f32 *)(moby + 0x10) > 1021.0f ||
            *(f32 *)(moby + 0x14) < 2.0f || *(f32 *)(moby + 0x14) > 1021.0f ||
            *(f32 *)(moby + 0x18) < 2.0f || *(f32 *)(moby + 0x18) > 1021.0f) { moby_mark_spawned(moby); return; }
        part_queue_ground_shadow(moby, *(f32 *)(moby + 0x2C) / *(f32 *)(*(u8 **)(moby + 0x24) + 0x24));
    }
}
