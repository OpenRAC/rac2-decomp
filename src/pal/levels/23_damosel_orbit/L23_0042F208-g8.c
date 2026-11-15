#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef short s16;
typedef int s32;
extern u8 *g_mothership_boss_moby __attribute__((sda));
extern u8 *D_L23_001B1484_2;
extern s32 g_enemy_charged_shot_moby __attribute__((sda));
extern s32 g_hero_charged_shot_moby __attribute__((sda));
extern s32 g_hero_moby __attribute__((nosda));
extern s32 D_L23_001B1430 __attribute__((sda));
extern s16 D_L23_001B1B94 __attribute__((sda));
extern s16 D_L23_001B1B96 __attribute__((sda));
extern void gfx_free_point_light(s32);
extern void gfx_add_draw_callback_first(void *, void *);
extern void effect_controller_init_link_table(void *);
extern void effect_controller_count_frame(void *);
extern void hero_spawn_trail_effect(void *);
extern void gfx_draw_spinning_star_quads(void *);
extern void hero_draw_trail_ribbons(void *);
extern s32 mothership_is_held(void);
extern s32 mothership_is_blast_timer_running(void);
extern s32 mothership_is_blast_cooling_down(void);
extern float D_L23_001B3930 __attribute__((sda));
extern s32 g_hero_charge_sound_handle __attribute__((sda));
extern s32 g_enemy_charge_sound_handle __attribute__((sda));
extern s32 D_L23_001A8AB0[4] __attribute__((sda));
extern s32 D_L23_001A8AC0[4] __attribute__((sda));
extern s32 D_L23_001B3714;
extern s32 D_L23_001B13E8 __attribute__((sda));
extern s32 math_random_int_below(s32);
typedef int TI16 __attribute__((mode(TI)));
extern s32 D_L23_001A8AB4[3] __attribute__((sda));
extern s32 D_L23_001A8AC4[3] __attribute__((sda));
extern s32 D_L23_001A8FF0;
extern s16 gfx_add_point_light(TI16 *, s32, float, float);
extern u8 *CreateMoby(s32);
extern s32 snd_start_in_slot(s32, s32, s32);
extern s32 D_L23_001B19C4 __attribute__((sda));
extern s32 D_L23_001B19C8 __attribute__((sda));
extern s32 D_L23_001B19D8 __attribute__((sda));

/* releases the measured handles and seeds the frame */
void func_PAL_L23_0042F208(u8 *arg0) {
    s32 *payload = *(s32 **)(arg0 + 0x68);

    effect_controller_init_link_table(arg0);
    if (D_L23_001B1484_2 != 0) {
        if (mothership_is_held() != 0) {
            gfx_add_draw_callback_first((void *)gfx_draw_spinning_star_quads, arg0);
        } else if (mothership_is_blast_timer_running() != 0) {
            gfx_add_draw_callback_first((void *)hero_draw_trail_ribbons, arg0);
        } else if (mothership_is_blast_cooling_down() != 0) {
            hero_spawn_trail_effect(arg0);
        } else {
            payload[1] = 0;
        }
        if (mothership_is_blast_timer_running() == 0) {
            s16 handle = D_L23_001B1B94;

            if (handle != -1) {
                D_L23_001B3930 = 0.02f;
                gfx_free_point_light(handle);
                D_L23_001B1B94 = -1;
            }
        }
        if (mothership_is_blast_cooling_down() == 0) {
            s16 handle = D_L23_001B1B96;

            if (handle != -1) {
                gfx_free_point_light(handle);
                D_L23_001B1B96 = -1;
            }
        }
    }
    effect_controller_count_frame(arg0);
}
