#include "common.h"

typedef struct {
    u8 pad00[0x268];
    f32 phase;
} Vars_L10_0041EE00;

typedef struct {
    u8 pad00[0x10];
    f32 pos[4];
    u8 pad20[0x68 - 0x20];
    Vars_L10_0041EE00 *vars;
    u8 pad6C[0xC0 - 0x6C];
    f32 axis[4];
} Moby_L10_0041EE00;

extern u16 *g_group_moby_id_lists[];
extern char *g_moby_base_table[] __attribute__((sda));
extern void gfx_draw_billboard_quad(void *, s32, u32, s32, float, float, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float math_fast_sin_or_cos_a(float);
extern int FloatToInt(float);
extern float math_random_angle(void);
extern char *moby_get_motion_data(void *);

/* Draw a pulsing glow at every live moby of this moby's group. */
void pulsing_light_draw_group_glows(u8 *moby)
{
    f32 glow_pos[4] __attribute__((aligned(16)));
    u16 *first = g_group_moby_id_lists[moby[0x21]];
    u16 *list;
    Moby_L10_0041EE00 *target;
    Vars_L10_0041EE00 *vars;
    u32 color;

    if (first != 0) {
        list = first;
        do {
            target = (Moby_L10_0041EE00 *)(g_moby_base_table[0] + ((*list & 0x7FFF) << 8));
            if (*(s32 *)(moby_get_motion_data(target) + 0x110) != 0) {
                vars = target->vars;
                FastVecScale(glow_pos, target->axis, 0.25f);
                FastVecAdd(glow_pos, target->pos, glow_pos);
                color = (FloatToInt((math_fast_sin_or_cos_a(vars->phase) + 1.0f) * 0.5f * 64.0f) << 24) | 0x63B4FF;
                gfx_draw_billboard_quad(glow_pos, 0x31, color, 1, 7.5f, 2.0f, math_random_angle());
            }
        } while ((s16)*list++ >= 0);
    }
}
