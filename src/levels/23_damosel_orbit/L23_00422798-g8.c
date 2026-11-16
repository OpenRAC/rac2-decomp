#include "include_asm.h"
#include "names.h"

/* func_L23_00422798 is a unit of its own: retail clears its local direction as plain C, with the
   zero materialised (`por $v0,$zero,$zero` ... `sq $v0,0($sp)`), which -frac2-zero-ti-por keeps
   (config/cflags.txt). */

typedef unsigned char u8;

typedef unsigned int u32;

typedef int s32;

typedef int TI128 __attribute__((mode(TI)));

extern float g_energy_effect_base_size __attribute__((sda));

extern float g_energy_effect_length_scale __attribute__((sda));

extern float g_energy_effect_scroll_limit __attribute__((sda));

extern u32 g_energy_effect_tex_a __attribute__((sda));

extern u32 g_energy_effect_tex_b __attribute__((sda));

extern u32 g_energy_effect_tex_c __attribute__((sda));

extern u32 g_energy_effect_quad_a_color __attribute__((sda));

extern s32 g_energy_effect_quad_a_texture __attribute__((sda));

extern u32 g_energy_effect_quad_b_color __attribute__((sda));

extern s32 g_energy_effect_quad_b_texture __attribute__((sda));

extern u32 g_energy_effect_quad_c_color __attribute__((sda));

extern s32 g_energy_effect_quad_c_texture __attribute__((sda));

extern float FastVecLength(void *);

extern float math_random_angle(void);

extern void gfx_draw_billboard_quad(void *, s32, u32, s32, float, float, float);

extern void DrawOrientedQuadsAtPoints(void *, void *, s32, u32, s32, s32, float, float, float);

/* scrolls the effect's phase, spawns three particles around it, and once the phase passes the
   limit emits three more through the shared emitter with the local direction {0, 0, 0, 1} */
/* Per-frame update of a scrolling energy effect. It spawns a few glowing particles and,
   once the effect has built up, shoots out three more. */
void energy_effect_update_scrolling(u8 *obj) {
    float direction[4];
    u8 *vars = *(u8 **)(obj + 0x68);
    float phase;
    float scrollStep;
    float size;

    *(TI128 *)direction = 0;
    direction[3] = 1.0f;
    phase = *(float *)(vars + 0x14) - 0.1f;
    *(float *)(vars + 0x14) = phase;
    if (phase <= -8.0f) {
        *(float *)(vars + 0x14) = phase + 8.0f;
    }
    scrollStep = FastVecLength(vars);
    size = g_energy_effect_base_size * 0.2f;
    *(float *)(vars + 0x18) = *(float *)(vars + 0x18) + scrollStep;
    gfx_draw_billboard_quad(obj + 0x10, 0x31, g_energy_effect_tex_a, 1, size, 0.0f, math_random_angle());
    gfx_draw_billboard_quad(obj + 0x10, 0x31, g_energy_effect_tex_b, 1, g_energy_effect_base_size * 0.1f, 0.0f, math_random_angle());
    gfx_draw_billboard_quad(obj + 0x10, 0x2F, g_energy_effect_tex_c, 1, g_energy_effect_base_size * 0.05f, 0.0f, math_random_angle());
    if (*(float *)(vars + 0x18) > g_energy_effect_scroll_limit) {
        DrawOrientedQuadsAtPoints(obj, direction, 1, g_energy_effect_quad_a_color, g_energy_effect_quad_a_texture, 0x17, g_energy_effect_base_size * 0.02f,
                          g_energy_effect_length_scale * g_energy_effect_base_size, *(float *)(vars + 0x14));
        DrawOrientedQuadsAtPoints(obj, direction, 1, g_energy_effect_quad_b_color, g_energy_effect_quad_b_texture, 0x17, g_energy_effect_base_size * 0.07f,
                          g_energy_effect_length_scale * g_energy_effect_base_size, *(float *)(vars + 0x14));
        DrawOrientedQuadsAtPoints(obj, direction, 1, g_energy_effect_quad_c_color, g_energy_effect_quad_c_texture, 0x17, g_energy_effect_base_size * 0.07f,
                          g_energy_effect_length_scale * g_energy_effect_base_size, *(float *)(vars + 0x14));
    }
}
