#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef int s32;
extern u8 *g_mothership_boss_moby __attribute__((sda));
extern u8 *D_L23_001B1484_2;
extern s32 g_enemy_charged_shot_moby __attribute__((sda));
extern s32 g_hero_charged_shot_moby __attribute__((sda));
extern s32 g_hero_moby __attribute__((nosda));
extern s32 D_L23_001B1430 __attribute__((sda));
extern s32 mothership_is_held(void);
extern s32 mothership_is_blast_timer_running(void);
extern s32 mothership_is_blast_cooling_down(void);
extern s32 g_hero_charge_sound_handle __attribute__((sda));
extern s32 g_enemy_charge_sound_handle __attribute__((sda));
extern s32 D_L23_001A8AB0[4] __attribute__((sda));
extern s32 D_L23_001A8AC0[4] __attribute__((sda));
extern s32 D_L23_001B3714;
extern s32 D_L23_001B13E8 __attribute__((sda));
extern int PlayMobySound(int, int, u8 *);
extern s32 math_random_int_below(s32);
extern s32 D_L23_001A8AB4[3] __attribute__((sda));
extern s32 D_L23_001A8AC4[3] __attribute__((sda));
extern s32 D_L23_001A8FF0;
extern u8 *CreateMoby(s32);
extern s32 snd_start_in_slot(s32, s32, s32);
extern s32 D_L23_001B19C4 __attribute__((sda));
extern s32 D_L23_001B19C8 __attribute__((sda));
extern s32 D_L23_001B19D8 __attribute__((sda));

/* publishes the boot stamp once, seeding the shared state first */
void func_PAL_L23_00423838(void) {
    if (D_L23_001B3714 == 0) {
        u8 *state = g_mothership_boss_moby;

        if (state != 0) {
            PlayMobySound(0x10, 0, state);
        }
    }
    D_L23_001B3714 = ((s32)(D_L23_001B13E8) * 5 + 2) / 6;
}
