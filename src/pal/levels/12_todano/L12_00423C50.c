#include "include_asm.h"

#include "common.h"
extern int g_current_map_index __attribute__((sda));
extern char g_moby_nibble_table[];
extern char g_hero_position[];
extern void FastVecSub(f32 *, const f32 *, const f32 *);
extern void vec_transform_and_set_height(char *, char *, char *, char *, f32);
extern void vec_scale_to_length(f32 *, f32 *, f32);
extern void part_spawn_masked_debris_pal(void *, s32, void *, f32, f32, f32, f32, s32);
extern s32 *g_path_zone_table[];
extern s32 *g_path_zone_table[];
extern s32 CollLine(void *from, void *to, s32 mode, void *self, s32 flags);
extern s32 *g_path_zone_table[];
extern char g_hero_position[];
extern f32 math_fabs(f32);
extern f32 vec_distance_xy(void *, void *);
extern s32 math_random_int_range(s32, s32);
extern s32 PlayMobySound(s32, s32, void *);
extern s32 g_spark_timer_min __attribute__((sda));
extern u8 g_zone_event_flag;
extern s32 math_random_int_below(s32);
extern s32 FloatToInt(f32);
extern u8 *SpawnSpinningSparkParticle(void *, f32, f32, f32, s32, void *, f32, u32, s32);

/* Sets off the moby: spawns a small burst, adds one to the saved progress counter and plays a sound (PAL: 50 Hz timings). */
void linked_moby_trigger_burst_pal(u8 *moby) {
    u8 *self = moby;
    f32 push_vec[4];
    u16 object_id;

    FastVecSub(push_vec, (f32 *)(self + 0x10), (f32 *)g_hero_position);
    vec_transform_and_set_height((char *)self, (char *)push_vec, (char *)push_vec, 0, 0.0f);
    vec_scale_to_length(push_vec, push_vec, 0.120000005f);
    part_spawn_masked_debris_pal(self, 31, push_vec, 6.0f, 12.0f, 6.0f, 12.0f, 255);

    object_id = *(u16 *)(self + 0xB2);
    if (object_id & 1) {
        u8 *counter = (u8 *)(((s16)object_id >> 1) + (g_current_map_index << 10)) + (int)g_moby_nibble_table;
        u8 packed = *counter;

        if (((packed >> 4) & 7) != 7)
            *counter = packed + 0x10;
    } else {
        u8 *counter = (u8 *)(((s16)object_id >> 1) + (g_current_map_index << 10)) + (int)g_moby_nibble_table;
        u8 packed = *counter;

        if ((packed & 7) != 7)
            *counter = packed + 1;
    }
    PlayMobySound(1, 0, self);
}





