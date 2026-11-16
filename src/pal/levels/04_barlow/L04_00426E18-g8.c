#include "include_asm.h"
#include "names.h"

extern int g_tether_l04_hit_result __attribute__((nosda));
extern int g_hero_moby __attribute__((nosda));
extern char g_effect_default_params[1];
extern int g_barlow_hit_countdown __attribute__((sda));
extern int coll_sweep_from_object(void *, void *, int, int, float, float, float, int, int);
extern int coll_test_point(void *, int, float, void *);
extern void func_PAL_002ABCB8(void *owner, char *offset, void *filter);
extern int math_fast_float_d(void *);

void func_PAL_L04_00426E18(char *a0)
{
    char *s0 = a0;
    char *s1 = s0 + 0x10;

    coll_sweep_from_object(s0, s1, 0x10001, 5, 1.0f, 1.0f, 1.0f, 1, 0);
    if (coll_test_point(s1, 1, 1.0f, s0) != 0) {
        if (g_tether_l04_hit_result != 0 && g_tether_l04_hit_result == g_hero_moby) {
            if (g_barlow_hit_countdown <= 0) {
                g_barlow_hit_countdown = 0x32;
            }
        }
    }
    if (g_barlow_hit_countdown > 0) {
        func_PAL_002ABCB8(g_hero_moby, g_effect_default_params, 0xFFFF);
        math_fast_float_d(&g_barlow_hit_countdown);
    }
}
