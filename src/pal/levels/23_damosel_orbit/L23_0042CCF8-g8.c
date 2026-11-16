#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;
extern u8 *g_mothership_boss_moby __attribute__((sda));
extern u8 *D_L23_001B1484_2;
extern s32 g_enemy_charged_shot_moby __attribute__((sda));
extern s32 g_hero_charged_shot_moby __attribute__((sda));
extern s32 g_hero_moby __attribute__((nosda));
extern s32 g_counter_effect_active __attribute__((sda));
extern s16 g_effect_sound_handle_a __attribute__((sda));
extern s16 g_effect_sound_handle_b __attribute__((sda));
extern s32 mothership_is_held(void);
extern s32 mothership_is_blast_timer_running(void);
extern s32 mothership_is_blast_cooling_down(void);
extern s32 g_hero_charge_sound_handle __attribute__((sda));
extern s32 g_enemy_charge_sound_handle __attribute__((sda));
extern s32 g_charged_shot_flag[4] __attribute__((sda));
extern s32 g_screen_effect[4] __attribute__((sda));
extern s32 g_boss_fight_timer;
extern s32 g_boss_fight_start_value __attribute__((sda));
extern s32 math_random_int_below(s32);
typedef int TI16 __attribute__((mode(TI)));
extern s32 g_charged_shot_color_a[3] __attribute__((sda));
extern s32 g_charged_shot_color_b[3] __attribute__((sda));
extern s32 g_hero_special_mode;
extern s16 gfx_add_point_light(TI16 *, s32, float, float);
extern u8 *CreateMoby(s32);
extern s32 snd_start_in_slot(s32, s32, s32);
extern void moby_set_state(void *, s32, s32);
extern void boss_part_handle_hit(u8 *);
extern float g_mothership_max_health __attribute__((sda));
extern s32 g_trail_ribbon_color_scale_a __attribute__((sda));
extern s32 g_trail_ribbon_color_scale_b __attribute__((sda));
extern s32 g_trail_ribbon_halo_value __attribute__((sda));

/* state 0 arms the draw distances and a 2000-tick timer and moves to state 1; state 1 copies the
   shared timer when it is set and moves to state 2; both then run the per-frame handler */
void boss_part_init_health_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 state = moby[0x20];

    if (state == 0) {
        *(u16 *)(moby + 0x32) = 0xFF;
        moby[0x30] = 0xFF;
        *(u16 *)(moby + 0x34) = *(u16 *)(moby + 0x34) | 0x100;
        *(float *)(vars + 0x20) = 2000.0f;
        *(s16 *)(vars + 0x24) = 2000;
        *(u16 *)(moby + 0x7C) = 0x3FF;
        moby_set_state(moby, 1, 0);
        *(u16 *)(moby + 0x34) = *(u16 *)(moby + 0x34) | 0x4000;
    } else if (state == 1) {
        float t = g_mothership_max_health;

        if (t != 0.0f) {
            *(float *)(vars + 0x20) = t;
            *(s16 *)(vars + 0x24) = (s16)t;
        }
        moby_set_state(moby, 2, 0);
    }
    boss_part_handle_hit(moby);
}
