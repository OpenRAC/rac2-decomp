#include "include_asm.h"

#include "common.h"
extern u8 *g_mothership_boss_moby __attribute__((sda));
extern s32 g_charged_l23_blast_timer __attribute__((sda));
extern s32 g_hero_moby __attribute__((nosda));
extern float g_mothership_max_health;
extern char g_hero_l23_state_block[];
extern u8 *part_find_owned_effect_slot(u8 *, s32, s32);
extern int FastDecTimer(u8 *);
extern s32 mothership_is_attack_state(void);
extern s32 mothership_is_held(void);
extern void boss_start_fight_once_pal(void);
extern void gfx_start_color_fade_pal(u8 *, u8 *);
extern void gfx_update_color_fade_pal(u8 *, u8 *);
extern void part_l23_spawn_hit_sparks_pal(u8 *);
extern float math_random_signed_float_range(float, float);
extern float FastAddRotations(float, float);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern u8 *cam_moby_create_pal(u8 *, s32, s32, s32, u8 *, u8 *, float *, float, float, s32);
extern void moby_fade_out_update_pal(void);

/* Hit handler of the object: takes the damage of the object that hit it (unless the shield state
   or the hit filter rejects the hit), then spawns one particle per set bit of the mask word, at
   most ten, fewer the more of the timer is left. */
void boss_part_handle_hit_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *hit;
    s32 spark_count;
    s32 i;
    float spark_vel[3];

    hit = part_find_owned_effect_slot(moby, 0x30000, 1);
    moby[0xA8] = 0xFF;
    FastDecTimer(vars + 0x26);
    if (hit != 0) {
        if (mothership_is_attack_state() == 0 || *(s16 *)(vars + 0x26) != 0 ||
            (g_mothership_boss_moby != 0 && mothership_is_held() != 0) ||
            (*(s32 *)(hit + 0x20) == g_hero_moby && g_charged_l23_blast_timer < 0)) {
            if (mothership_is_held() != 0)
                boss_start_fight_once_pal();
            hit = 0;
        }
    }
    if (hit != 0) {
        *(float *)(vars + 0x20) = *(float *)(vars + 0x20) - *(float *)(hit + 0x2C);
        if (*(float *)(vars + 0x20) > 0.0f) {
            vars[0x147] = 0xFF;
            gfx_start_color_fade_pal(moby, vars + 0x140);
            part_l23_spawn_hit_sparks_pal(*(u8 **)(hit + 0x20));
            if (*(s16 *)(*(u8 **)(hit + 0x20) + 0xAA) != 0x118F)
                *(s16 *)(vars + 0x26) = 0x11;
            if (*(u16 *)(moby + 0x7C) != 0) {
                float health_ratio;

                health_ratio = *(float *)(vars + 0x20) / g_mothership_max_health;
                spark_count = 10 - (s32)(health_ratio * 10.0f);
                for (i = 0; i < spark_count; i++) {
                    s32 mask = *(u16 *)(moby + 0x7C);

                    if ((mask >> i) & 1) {
                        float angle, speed;
                        u8 *spark;
                        u8 *hero_block = (u8 *)g_hero_l23_state_block;
                        float spread = 90.0f;
                        float per_tick = 0.020000001f;
                        float to_rad = 0.017453294f;

                        *(u16 *)(moby + 0x7C) = mask & ~(1 << i);
                        angle = FastAddRotations(math_random_signed_float_range(spread, 120.0f) * to_rad,
                                              *(float *)(hero_block + 0x158));
                        speed = math_random_float_range(2.0f, 4.0f) * per_tick;
                        spark_vel[0] = math_fast_sin_or_cos_a(angle) * speed;
                        spark_vel[1] = math_fast_sin_or_cos_b(angle) * speed;
                        spark_vel[2] = 0.0f;
                        spark_vel[2] = math_random_float_range(5.0f, 8.0f) * per_tick;
                        spark = cam_moby_create_pal(moby, 1, *(s16 *)(moby + 0xAA), i, moby + 0x10, moby + 0xF0,
                                          spark_vel, spread, 15.0f, 0xFF);
                        if (spark != 0)
                            *(void (**)(void))(spark + 0x64) = moby_fade_out_update_pal;
                    }
                }
            }
        }
    }
    gfx_update_color_fade_pal(moby, vars + 0x140);
}
