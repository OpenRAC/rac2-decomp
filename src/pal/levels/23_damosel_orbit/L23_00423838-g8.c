#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef int s32;
extern u8 *g_mothership_boss_moby __attribute__((sda));
extern u8 *D_L23_001B1484_2;
extern s32 g_enemy_charged_shot_moby __attribute__((sda));
extern s32 g_hero_charged_shot_moby __attribute__((sda));
extern s32 g_hero_moby __attribute__((nosda));
extern s32 g_counter_effect_active __attribute__((sda));
extern s32 mothership_is_held(void);
extern s32 mothership_is_blast_timer_running(void);
extern s32 mothership_is_blast_cooling_down(void);
extern s32 g_hero_charge_sound_handle __attribute__((sda));
extern s32 g_enemy_charge_sound_handle __attribute__((sda));
extern s32 g_charged_shot_flag[4] __attribute__((sda));
extern s32 g_screen_effect[4] __attribute__((sda));
extern s32 g_boss_fight_timer;
extern s32 g_boss_fight_start_value __attribute__((sda));
extern int PlayMobySound(int, int, u8 *);
extern s32 math_random_int_below(s32);
extern s32 g_charged_shot_color_a[3] __attribute__((sda));
extern s32 g_charged_shot_color_b[3] __attribute__((sda));
extern s32 g_hero_special_mode;
extern u8 *CreateMoby(s32);
extern s32 snd_start_in_slot(s32, s32, s32);
extern s32 g_trail_ribbon_color_scale_a __attribute__((sda));
extern s32 g_trail_ribbon_color_scale_b __attribute__((sda));
extern s32 g_trail_ribbon_halo_value __attribute__((sda));

/* publishes the boot stamp once, seeding the shared state first */
void func_PAL_L23_00423838(void) {
    if (g_boss_fight_timer == 0) {
        u8 *state = g_mothership_boss_moby;

        if (state != 0) {
            PlayMobySound(0x10, 0, state);
        }
    }
    g_boss_fight_timer = ((s32)(g_boss_fight_start_value) * 5 + 2) / 6;
}
