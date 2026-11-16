#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;
typedef float f32;
extern u8 *g_moby_l04_group_lists[];
extern u8 *g_moby_l04_pool __attribute__((sda));
extern s32 g_screen_width __attribute__((sda));
extern s32 g_screen_height;
extern f32 g_race_float_extra __attribute__((sda));
typedef int TI128 __attribute__((mode(TI)));
extern u16 **g_light_id_lists;
extern u8 *g_light_record_table;
extern u8 g_barlow_burst_scatter_a[8] __attribute__((sda));
extern u8 g_barlow_burst_scatter_b[8] __attribute__((sda));
extern u8 g_barlow_burst_scatter_c[8] __attribute__((sda));
extern s32 g_barlow_burst_scatter_param __attribute__((sda));
extern void moby_set_state(void *moby, s32 a1, s32 a2);
extern void *part_find_owned_effect_slot(void *moby, s32 a1, s32 a2);
extern void ScatterObjectPieces_pal(void *moby, void *a1, void *a2, void *a3, s32 a4, s32 a5, s32 a6,
                              s32 a7, s32 a8, s32 a9, s32 a10);
extern void part_spawn_scaled_bolts_pal(void *moby, s32 a1, f32 f12);
extern void vec_local_offset_to_world(void *moby, void *a1, f32 f12, f32 f13, f32 f14);
extern void SpawnExplosionEffects_pal(void *o, void *a, void *b, f32 f0, f32 f1, s32 i0, s32 i1, s32 i2,
                          f32 f2, f32 f3, f32 f4, f32 f5, s32 i3, f32 f6, s32 i4, s32 i5, s32 i6,
                          s32 i7, s32 i8);
extern void moby_mark_spawned(void *moby);
extern s32 g_game_l04_mode;
extern u8 g_unlocked_item_flags;
extern u8 g_effect_reset_byte_a;
extern u8 g_effect_reset_byte_b;
extern f32 g_effect_scale_x;
extern f32 g_effect_scale_y;
extern f32 g_effect_scale_z;

/* State 0 arms the object and moves it to vars 1; vars 1 moves to vars 2 once func_002A9640
   finds a match while the vars word is clear; vars 2 makes the three func_PAL_002AC718 calls,
   sets bit 2 of byte +0x1E of every entity of the group at +4 and calls func_0029F338. */
void barlow_effect_burst_update_pal(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    f32 origin[4] __attribute__((aligned(16)));
    f32 offset[4] __attribute__((aligned(16)));
    u16 *light_ids;
    u8 *light;

    switch (moby[0x20]) {
    case 0:
        moby[0x31] = 0;
        *(u16 *)(moby + 0x34) |= 1;
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(moby, 0x4010000, 0) != 0) {
            if (*(s32 *)vars == 0)
                moby_set_state(moby, 2, -1);
        }
        moby[0xA8] = 0xFF;
        break;
    case 2:
        ScatterObjectPieces_pal(moby, g_barlow_burst_scatter_a, g_barlow_burst_scatter_b, g_barlow_burst_scatter_c, 0x7F, 0,
                          g_barlow_burst_scatter_param, 1, 0xFFFF, 0xFF, 0);
        part_spawn_scaled_bolts_pal(moby, 5, 0.0f);
        *(TI128 *)origin = 0;
        origin[2] = 0.20000002f;
        vec_local_offset_to_world(moby, offset, 0.0f, 0.0f, 4.0f);
        SpawnExplosionEffects_pal(moby, origin, offset, 0.0f, 0.0f, 50, 10, 10, 3.0f, 1.0f, 9.0f, 2.25f, -1, 15.0f, 1, 7,
                      -1, 0, 0x810001);
        SpawnExplosionEffects_pal(moby, origin, offset, 0.0f, 0.0f, 5, 1, 1, 0.0f, 0.0f, 9.0f, 2.25f, -1, 0.0f, 0, 0, -1,
                      1, 0x810001);
        SpawnExplosionEffects_pal(moby, origin, offset, 0.0f, 0.0f, 5, 1, 1, 0.0f, 0.0f, 9.0f, 2.25f, -1, 0.0f, 0, 0, -1,
                      2, 0x810001);
        if (*(s32 *)(vars + 4) != 0) {
            for (light_ids = g_light_id_lists[*(s32 *)(vars + 4)];
                 light_ids != 0 &&
                 ((light_ids != 0 && (s16)light_ids[-1] >= 0) || light_ids == g_light_id_lists[*(s32 *)(vars + 4)]);
                 light_ids++) {
                light = g_light_record_table + ((*light_ids & 0x7FFF) << 5);
                if (light == 0)
                    break;
                light[0x1E] |= 4;
            }
        }
        moby_mark_spawned(moby);
        break;
    }
}
