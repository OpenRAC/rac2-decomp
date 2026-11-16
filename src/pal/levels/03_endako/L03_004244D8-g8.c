#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;
typedef float f32;
extern u8 *g_moby_record_base __attribute__((sda));
extern s32 g_endako_boss_forced_behaviour __attribute__((sda));
extern u32 g_endako_boss_initial_timer __attribute__((sda));
extern u8 *SpawnSpinningSparkParticle(void *p, float f0, float f1, float f2, int z, void *local,
                         float f3, int v, int t);
extern f32 g_robot_speed_scale __attribute__((sda));
extern f32 g_robot_turn_scale __attribute__((sda));
extern void hero_copy_field_to_moby(u8 *a0);
extern s32 flag_is_third_pending_set();
extern void moby_set_flag_bit(unsigned char *entity, int enabled);
extern u8 *g_entity_id_lists[];
extern s32 g_hero_l03_mode __attribute__((sda));
extern s32 func_3240F0(u8 *a0);

/* Sets the entity up for a shot: the state's own counter, its two blend rates and the
 * frame the shot was prepared on. */
s32 entity_prepare_shot_pal(u8 *moby) {
    u8 *state = *(u8 **)(moby + 0x68);
    f32 turn_scale;
    f32 speed_scale;
    s32 frame;

    if (*(s32 *)(state + 0x284) == -1) return 0;
    if (moby[0x20] != 9) return 0;

    if (flag_is_third_pending_set() == 0) {
        moby[0xA8] = 0xFF;
        speed_scale = g_robot_speed_scale * 0.00040000002f;
        turn_scale = g_robot_turn_scale * 0.020000001f;
        frame = *(s16 *)(state + 0x24);
        *(u16 *)(state + 0x98) = 0;
        *(f32 *)(state + 0x138) = turn_scale;
        *(f32 *)(state + 0x33C) = 6.0f;
        *(f32 *)(state + 0x134) = speed_scale;
        *(f32 *)(state + 0x130) = speed_scale;
        *(f32 *)(state + 0x20) = (f32)frame;
        moby[0xA8] = 0xFF;
        *(u32 *)(moby + 0x98) = *(u32 *)(*(u8 **)(moby + 0x24) + 0x10);
        hero_copy_field_to_moby(moby);
        moby_set_flag_bit(moby, 1);
        return 1;
    }
    return 0;
}
