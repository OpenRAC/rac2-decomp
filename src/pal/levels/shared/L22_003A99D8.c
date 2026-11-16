#include "include_asm.h"
#include "names.h"


typedef unsigned char u8;
typedef float f32;
extern u8 D_001A63A8_4[];
extern u8 g_hero_state[];
extern f32 fast_vec_dist(void *a0, void *a1);
extern void hero_restart_in_mode(int a0, int a1, void *a2);
extern f32 math_random_float_range(f32 low, f32 high);

/* Per-frame update for moby class 637: when the player is close, it starts an effect on this object. */
void proximity_effect_update_pal(u8 *moby) {
    if (g_hero_state[0x22B4] != 0) return;
    if (fast_vec_dist(g_hero_state + 0x80, moby + 0x10) < 4.0f) {
        hero_restart_in_mode(2, 0x56, moby);
    }
}
