#include "include_asm.h"
#include "names.h"

/* func_PAL_00317768, the PAL copy of func_00316248: the same C, where the angle step 0.125f
   becomes 0.15f and the callee func_003169D0 is the PAL copy func_PAL_00317EF8. */
extern float g_lock_on_sprite_angle __attribute__((sda));
extern char g_emitter_origin[] __attribute__((sda));
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern int FastTweenColor(int, int, float);
extern void gfx_draw_owner_effect_slots_pal(void *);
extern void gfx_draw_billboard_quad(char *, int, unsigned int, int, float, float, float);

void func_PAL_00317768(void *object)
{
    float angle = FastAddRotations(g_lock_on_sprite_angle, 0.15f);
    float scale;
    float size_a;
    float size_b;
    float size_c;
    int colour_a;
    int colour_b;
    int colour_c;

    g_lock_on_sprite_angle = angle;
    scale = math_fast_sin_or_cos_a(angle);
    scale = (scale + 1.0f) * 0.5f;
    size_b = scale * 0.0625f + 0.0625f;
    size_c = scale * 0.19999999f + 0.15f;
    size_a = scale * 0.125f + 0.125f;

    colour_a = FastTweenColor(0x2F007F00, 0x3F007F00, scale);
    colour_b = FastTweenColor(0x2F7F7F7F, 0x5F7F7F7F, scale);
    colour_c = FastTweenColor(0x10003F00, 0x10003F00, scale);

    gfx_draw_owner_effect_slots_pal(object);
    gfx_draw_billboard_quad(g_emitter_origin, 0x31, colour_a, 1, size_a, 0.125f, 0.0f);
    gfx_draw_billboard_quad(g_emitter_origin, 0x31, colour_b, 1, size_b, 0.124f, 0.0f);
    gfx_draw_billboard_quad(g_emitter_origin, 0x0B, colour_c, 1, size_c, 0.123f, 0.0f);
}
