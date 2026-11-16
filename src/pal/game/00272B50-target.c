#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad[0x1450];
    char *requested;
    char gap[0x2C];
    char *current;
    float fade;
    float angle;
} TargetReticleState;
extern TargetReticleState g_hero_state;
extern char g_camera_eye_state[];
extern int g_reticle_screen_params[] __attribute__((sda));
extern float g_target_scale_factor SDATA(D_001A85C0);
extern float g_target_scale_max SDATA(D_001A85C4);
extern float g_target_scale_min SDATA(D_001A85C8);
extern float g_target_fade_speed SDATA(D_001A85CC);
extern unsigned int g_target_colors_active[] SDATA(D_001A85D0);
extern unsigned int g_target_colors_idle[] SDATA(D_001A85E0);
extern float g_target_size_table[] SDATA(D_001A85F0);
extern float g_target_angle_degrees SDATA(D_001A85FC);
extern float g_target_spin_speed SDATA(D_001A8600);
extern int g_target_arc_param SDATA(D_001A8604);
extern unsigned int g_target_uv_table[] SDATA(D_001A8608);
extern int g_target_width SDATA(D_001A8618);
extern int g_target_height SDATA(D_001A861C);
extern unsigned int g_target_color_a SDATA(D_001A8620);
extern unsigned int g_target_color_b SDATA(D_001A8624);
extern float g_target_bar_scale_a SDATA(D_001A8628);
extern float g_target_bar_scale_b SDATA(D_001A862C);
extern float ApproachValue(float *, float, float);
extern float FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float);
extern char *moby_get_private_value_0(char *);
extern void vec_scale_to_length(float *, void *, float);
extern void FastVecAdd(float *, float *, void *);
extern void gfx_project_world_point_to_screen(float *, float *);
extern float IntToFloat(int);
extern float fast_vec_dist(void *, void *);
extern float mat_fast_helper_a(float, float);
extern long GetEffectTextureDescriptor(int);
extern int FastTweenColor(unsigned int, unsigned int, float);
extern int FloatToInt(float);
extern void AppendRotatedSpriteQuad(float, float, float, float, float, int, int, long, int, int,
                          unsigned char, unsigned char, float, float);
extern void DrawTexturedArc(int, int, int, int, unsigned int *, unsigned int *, int, int, float, float);

/* Fades the reticle in on the requested target and out when the target changes, spins it, then
   draws it at the target's projected position: three layers of four rotated quads, with a
   health arc under them when the target's info gives a maximum health. */
void DrawTargetReticle_pal(void)
{
    float screen[4];
    float offset[4];
    float position[4];
    unsigned int colors[4];
    unsigned int uv[4];
    char *obj;
    char *info;
    float *pos;
    float health;
    float max_health;
    float radius;
    float scale;
    float angle;
    float size;
    float bar;
    float edge;
    int i;
    int color;
    int width;
    int height;
    int width2;
    int height2;
    long texture;
    long x;
    long y;

    if (!g_hero_state.requested && g_hero_state.fade == 0.0f) {
        return;
    }
    if (g_hero_state.requested != g_hero_state.current) {
        ApproachValue(&g_hero_state.fade, 0.0f, g_target_fade_speed * (0.020000001f));
        if (g_hero_state.fade <= 0.0f) {
            g_hero_state.current = g_hero_state.requested;
        }
    } else if (g_hero_state.requested && g_hero_state.fade < 1.0f) {
        ApproachValue(&g_hero_state.fade, 1.0f, g_target_fade_speed * (0.020000001f));
        g_hero_state.angle = FastAddRotations(g_hero_state.angle, g_target_spin_speed * 0.0003490659f);
    }
    g_hero_state.angle = FastAddRotations(g_hero_state.angle, g_target_spin_speed * 0.0003490659f);
    obj = g_hero_state.current;
    if (!obj || g_hero_state.fade == 0.0f) {
        return;
    }
    health = 0.0f;
    max_health = health;
    info = moby_get_private_value_0(obj);
    if (info) {
        vec_scale_to_length(position, obj + 0xE0, *(float *)(info + 0x10));
        FastVecAdd(position, position, obj + 0x10);
        max_health = *(short *)(info + 4);
        health = *(float *)info;
        pos = position;
    } else {
        qcopy(position, obj + 0x10);
        pos = position;
    }
    gfx_project_world_point_to_screen(screen, pos);
    offset[0] = (screen[0] - IntToFloat(g_reticle_screen_params[2])) * 0.0625f;
    offset[1] = (screen[1] - IntToFloat(g_reticle_screen_params[3])) * 0.0625f;
    radius = *(float *)(info + 0x10);
    if (radius > 2.0f) {
        radius = 2.0f;
    }
    scale = mat_fast_helper_a(fast_vec_dist(g_camera_eye_state, obj + 0x10), radius) * g_target_scale_factor;
    if (scale > g_target_scale_max) {
        scale = g_target_scale_max;
    } else if (scale < g_target_scale_min) {
        scale = g_target_scale_min;
    }
    for (i = 0; i < 3; i++) {
        switch (i) {
        case 0:
            angle = g_hero_state.angle;
            break;
        case 1:
            angle = -g_hero_state.angle;
            break;
        case 2:
        default:
            angle = g_target_angle_degrees * 0.01745329424738884f;
            break;
        }
        texture = GetEffectTextureDescriptor(i + 0x33);
        color = FastTweenColor(g_target_colors_idle[i], g_target_colors_active[i], g_hero_state.fade);
        size = ((g_target_size_table[i] - 1.0f) * (1.0f - g_hero_state.fade) + 1.0f) * scale;
        AppendRotatedSpriteQuad(offset[0], offset[1], size, size, angle, 64, 64, texture, 0xFFFFF3, color,
                      0, 0, 0.0f, 0.0f);
        AppendRotatedSpriteQuad(offset[0], offset[1], size, size, FastAddRotations(angle, 1.57079637f), 64, 64,
                      texture, 0xFFFFF3, color, 0, 0, 0.0f, 0.0f);
        AppendRotatedSpriteQuad(offset[0], offset[1], size, size, FastAddRotations(angle, 3.14159274f), 64, 64,
                      texture, 0xFFFFF3, color, 0, 0, 0.0f, 0.0f);
        AppendRotatedSpriteQuad(offset[0], offset[1], size, size, fast_subtract_rotations(angle, 1.57079637f), 64, 64,
                      texture, 0xFFFFF3, color, 0, 0, 0.0f, 0.0f);
    }
    if (max_health != 0.0f) {
        uv[0] = g_target_uv_table[0];
        uv[1] = g_target_uv_table[1];
        uv[2] = g_target_uv_table[2];
        uv[3] = g_target_uv_table[3];
        colors[0] = colors[1] = colors[2] = colors[3] =
            FastTweenColor(g_target_color_a & 0xFFFFFF, g_target_color_a, g_hero_state.fade);
        x = FloatToInt(screen[0]);
        y = FloatToInt(screen[1]);
        bar = g_target_bar_scale_b * mat_fast_helper_a(g_target_bar_scale_a, max_health);
        edge = -bar;
        width = FloatToInt(scale * (float)g_target_width);
        height = FloatToInt(scale * (float)g_target_height);
        DrawTexturedArc(x, y, width, height, colors, uv, g_target_arc_param, 16, bar, edge);
        colors[0] = colors[1] = colors[2] = colors[3] =
            FastTweenColor(g_target_color_b & 0xFFFFFF, g_target_color_b, g_hero_state.fade);
        edge = bar - (bar + bar) * (health / max_health);
        width2 = FloatToInt(scale * (float)g_target_width);
        height2 = FloatToInt(scale * (float)g_target_height);
        DrawTexturedArc(x, y, width2, height2, colors, uv, g_target_arc_param, 16, bar, edge);
    }
}
