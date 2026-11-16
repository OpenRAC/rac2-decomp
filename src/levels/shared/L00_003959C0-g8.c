#include "common.h"

extern f32 IntToFloat(int);
extern s32 FloatToInt(f32);
extern void gfx_l00_draw_ribbon_with_halo(void *, int, int, int, f32, f32, f32);
extern void gfx_l00_draw_billboard_flare(void *);

extern s16 g_arc_timers[] __attribute__((sda));
extern s16 g_arc_alphas[] __attribute__((sda));
extern f32 g_arc_fade_scale[] __attribute__((sda));
extern char g_arc_points[];
extern f32 g_ribbon_width_param_a __attribute__((sda));
extern f32 g_ribbon_width_param_b __attribute__((sda));

/* Updates ten 0x50-byte records using the paired halfword tables. */
void UpdateScaledRecords(char *object) {
    s16 *values = g_arc_alphas;
    s16 *enabled = g_arc_timers;
    char *record = g_arc_points;
    char *savedObject = object;
    int remaining = 9;

    do {
        if (*enabled != 0) {
            int scaled = FloatToInt(IntToFloat(*values) * g_arc_fade_scale[0]);

            gfx_l00_draw_ribbon_with_halo(record, scaled, scaled, 5, g_ribbon_width_param_a, g_ribbon_width_param_b, 0.2f);
        }
        record += 0x50;
        values++;
        enabled++;
    } while (--remaining >= 0);
    gfx_l00_draw_billboard_flare(savedObject);
}
