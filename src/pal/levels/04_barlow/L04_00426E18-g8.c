#include "include_asm.h"
#include "names.h"

extern int g_tether_l04_hit_result __attribute__((nosda));
extern int g_hero_moby __attribute__((nosda));
extern char g_effect_default_params[1];
extern int g_barlow_hit_countdown __attribute__((sda));
extern int coll_sweep_from_object(void *, void *, int, int, float, float, float, int, int);
extern int coll_test_point(void *, int, float, void *);
extern void part_spawn_sparks_around_moby_pal(void *owner, char *offset, void *filter);
extern int math_fast_float_d(void *);

/* Checks if the object is hit and starts a 50 frame countdown, while it runs the countdown it keeps the effect going (PAL). */
void barlow_hit_countdown_update_pal(char *moby_arg)
{
    char *moby = moby_arg;
    char *position = moby + 0x10;

    coll_sweep_from_object(moby, position, 0x10001, 5, 1.0f, 1.0f, 1.0f, 1, 0);
    if (coll_test_point(position, 1, 1.0f, moby) != 0) {
        if (g_tether_l04_hit_result != 0 && g_tether_l04_hit_result == g_hero_moby) {
            if (g_barlow_hit_countdown <= 0) {
                g_barlow_hit_countdown = 0x32;
            }
        }
    }
    if (g_barlow_hit_countdown > 0) {
        part_spawn_sparks_around_moby_pal(g_hero_moby, g_effect_default_params, 0xFFFF);
        math_fast_float_d(&g_barlow_hit_countdown);
    }
}
