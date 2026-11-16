#include "names.h"
/* func_PAL_0030E850, the PAL copy of func_0030D430: the same C, where wrap D_001AF000 (({e}) * 1.2f). */

/* Scrolls the sky layer's texture offset (wrapping it by 8) and draws its two layers
   with the current colours, the planet-specific colour pair and light set for planet
   20 in mode 2; planet 1 in mode 2 takes its own light set as well. Its own -G8 unit:
   the sky globals are $gp scalars. */
typedef struct {
    char pad0[0x38];
    short tex;
} SkyVars30D430;
typedef struct {
    char pad0[0x68];
    SkyVars30D430 *vars;
} SkyMoby30D430;
extern int g_current_map_index;
extern int g_current_game_mode;
extern SkyVars30D430 g_beam_level_params_first;
extern SkyVars30D430 g_beam_level_params_second;
extern float g_ribbon_uv_scroll __attribute__((sda));
extern float g_ribbon_scroll_step __attribute__((sda));
extern int g_ribbon_top_alpha __attribute__((sda));
extern int g_ribbon_bottom_alpha __attribute__((sda));
extern int g_ribbon_halo_color __attribute__((sda));
extern int g_ribbon_bottom_color __attribute__((sda));
extern float g_ribbon_normal_scale __attribute__((sda));
extern float g_ribbon_core_width __attribute__((sda));
extern float g_ribbon_halo_width __attribute__((sda));
extern float g_ribbon_outer_normal_scale __attribute__((sda));
extern float g_ribbon_outer_core_width __attribute__((sda));
extern float g_ribbon_outer_halo_width __attribute__((sda));
extern char g_beam_ribbon_points[];
extern void beam_draw_ribbon_with_halo(void *, int, int, int, float, float, float);
extern void beam_draw_anchor_glow_level(SkyMoby30D430 *);

void beam_draw_ribbons_level_pal(SkyMoby30D430 *moby)
{
    SkyVars30D430 *vars = moby->vars;
    float offset;
    int top;
    int bottom;
    int colour0;
    int colour1;

    if (g_current_map_index == 1 && g_current_game_mode == 2)
        vars = &g_beam_level_params_first;
    if (g_current_map_index == 20 && g_current_game_mode == 2)
        vars = &g_beam_level_params_second;
    offset = g_ribbon_uv_scroll - ((g_ribbon_scroll_step) * 1.2f);
    g_ribbon_uv_scroll = offset;
    if (offset <= -8.0f)
        g_ribbon_uv_scroll = offset + 8.0f;
    top = g_ribbon_top_alpha << 24;
    bottom = g_ribbon_bottom_alpha << 24;
    colour0 = top | g_ribbon_halo_color;
    colour1 = bottom | g_ribbon_bottom_color;
    if (g_current_map_index == 20 && g_current_game_mode == 2) {
        colour0 = top | 0xEFCD12;
        colour1 = bottom | 0xEF3212;
    }
    beam_draw_ribbon_with_halo(g_beam_ribbon_points, colour0, colour1, vars->tex, g_ribbon_normal_scale, g_ribbon_core_width, g_ribbon_halo_width);
    beam_draw_ribbon_with_halo(g_beam_ribbon_points + 0x140, colour0, colour1, vars->tex, g_ribbon_outer_normal_scale, g_ribbon_outer_core_width, g_ribbon_outer_halo_width);
    beam_draw_anchor_glow_level(moby);
}
