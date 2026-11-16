#include "include_asm.h"

#include "common.h"
extern int g_beam_color_start __attribute__((sda));
extern float g_beam_l05_width_start __attribute__((sda));
extern float g_beam_height_start __attribute__((sda));
extern float g_beam_length_start __attribute__((sda));
extern float g_beam_extent_start __attribute__((sda));
extern int g_beam_count_start __attribute__((sda));
extern int g_beam_color2_start __attribute__((sda));
extern float g_beam_width2_start __attribute__((sda));
extern float g_beam_height2_start __attribute__((sda));
extern float g_beam_length2_start __attribute__((sda));
extern float g_beam_extent2_start __attribute__((sda));
extern int g_beam_count2_start __attribute__((sda));
extern int g_beam_color_end __attribute__((sda));
extern float g_beam_l05_width_end __attribute__((sda));
extern float g_beam_height_end __attribute__((sda));
extern float g_beam_length_end __attribute__((sda));
extern float g_beam_extent_end __attribute__((sda));
extern int g_beam_count_end __attribute__((sda));
extern int g_beam_color2_end __attribute__((sda));
extern float g_beam_width2_end __attribute__((sda));
extern float g_beam_height2_end __attribute__((sda));
extern float g_beam_length2_end __attribute__((sda));
extern float g_beam_extent2_end __attribute__((sda));
extern int g_beam_count2_end __attribute__((sda));
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int FastTweenColor(int, int, float);
extern void part_spawn_sprite_line(void *, void *, int, float, float, float, int);
extern void UpdateBeamTrailParticles_pal(char *);
extern int hero_get_shield_value(void);
extern void gfx_draw_thruster_glow_pal(char *);
typedef int BeamVec __attribute__((mode(TI)));

/* Draws the beam layers of the thruster flame from sprite lines, widening them with the thruster level (more when an attachment is fitted), then the trail particles and, with a shield, the thruster glow. */
void DrawInterpolatedBeamLayers_pal(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *attachment = *(char **)(state + 0x4C);
    float pos[4], direction[4], offset[4], offset2[4], offset3[4];
    float offsetX, offsetZ;

    if (attachment && *(short *)(attachment + 0xAA) == 0x10D9) {
        float factor, length, length2, width, height, width2, height2, extent, extent2;
        int count, count2, color, color2;

        offsetX = -0.135f;
        offsetZ = 0.1f;
        *(BeamVec *)offset = 0;
        offset[1] = 0.045f;
        offset[0] = offsetX;
        offset[2] = offsetZ;
        offset[3] = 1.0f;
        matrix_mul_vec3(pos, offset, object + 0xC0);
        FastVecAdd(pos, pos, object + 0x10);
        factor = IntToFloat(*(int *)(state + 0x34)) / IntToFloat(7);
        factor *= 0.5f;
        length = g_beam_length_start + (g_beam_length_end - g_beam_length_start) * factor;
        length2 = g_beam_length2_start + (g_beam_length2_end - g_beam_length2_start) * factor;
        count = FloatToInt((float)g_beam_count_start + (float)(g_beam_count_end - g_beam_count_start) * factor);
        length = -length;
        length2 = -length2;
        count2 = FloatToInt((float)g_beam_count2_start + (float)(g_beam_count2_end - g_beam_count2_start) * factor);
        width = (g_beam_l05_width_start + (g_beam_l05_width_end - g_beam_l05_width_start) * factor) * 0.5f;
        width2 = (g_beam_width2_start + (g_beam_width2_end - g_beam_width2_start) * factor) * 0.5f;
        height = (g_beam_height_start + (g_beam_height_end - g_beam_height_start) * factor) * 0.5f;
        height2 = (g_beam_height2_start + (g_beam_height2_end - g_beam_height2_start) * factor) * 0.5f;
        extent = g_beam_extent_start + (g_beam_extent_end - g_beam_extent_start) * factor;
        extent2 = g_beam_extent2_start + (g_beam_extent2_end - g_beam_extent2_start) * factor;

        color = FastTweenColor(g_beam_color_start, g_beam_color_end, factor);
        color2 = FastTweenColor(g_beam_color2_start, g_beam_color2_end, factor);
        FastVecScale(direction, object + 0xC0, length);
        part_spawn_sprite_line(pos, direction, count, width, height, extent, color);
        FastVecScale(direction, object + 0xC0, length2);
        part_spawn_sprite_line(pos, direction, count2, width2, height2, extent2, color2);
        *(BeamVec *)offset2 = 0;
        offset2[1] = -0.045f;
        offset2[0] = offsetX;
        offset2[2] = offsetZ;
        offset2[3] = 1.0f;
        matrix_mul_vec3(pos, offset2, object + 0xC0);
        FastVecAdd(pos, pos, object + 0x10);
        FastVecScale(direction, object + 0xC0, length);
        part_spawn_sprite_line(pos, direction, count, width, height, extent, color);
        FastVecScale(direction, object + 0xC0, length2);
        part_spawn_sprite_line(pos, direction, count2, width2, height2, extent2, color2);
        *(BeamVec *)offset3 = 0;
        offset3[2] = 0.07f;
        offset3[0] = offsetX;
        offset3[3] = 1.0f;
        matrix_mul_vec3(pos, offset3, object + 0xC0);
        FastVecAdd(pos, pos, object + 0x10);
        FastVecScale(direction, object + 0xC0, length);
        part_spawn_sprite_line(pos, direction, count, width + width, height + height, extent, color);
        FastVecScale(direction, object + 0xC0, length2);
        part_spawn_sprite_line(pos, direction, count2, width2 + width2, height2 + height2, extent2, color2);
    } else {
        float factor, length, length2, width, height, width2, height2, extent, extent2;
        int count, count2, color, color2;

        *(BeamVec *)offset = 0;
        offset[0] = -0.135f;
        offset[2] = 0.07f;
        offset[3] = 1.0f;
        matrix_mul_vec3(pos, offset, object + 0xC0);
        FastVecAdd(pos, pos, object + 0x10);
        factor = IntToFloat(*(int *)(state + 0x34)) / IntToFloat(7);
        length = g_beam_length_start + (g_beam_length_end - g_beam_length_start) * factor;
        length2 = g_beam_length2_start + (g_beam_length2_end - g_beam_length2_start) * factor;
        count = FloatToInt((float)g_beam_count_start + (float)(g_beam_count_end - g_beam_count_start) * factor);
        count2 = FloatToInt((float)g_beam_count2_start + (float)(g_beam_count2_end - g_beam_count2_start) * factor);
        width = g_beam_l05_width_start + (g_beam_l05_width_end - g_beam_l05_width_start) * factor;
        width2 = g_beam_width2_start + (g_beam_width2_end - g_beam_width2_start) * factor;
        height = g_beam_height_start + (g_beam_height_end - g_beam_height_start) * factor;
        height2 = g_beam_height2_start + (g_beam_height2_end - g_beam_height2_start) * factor;
        extent = g_beam_extent_start + (g_beam_extent_end - g_beam_extent_start) * factor;
        extent2 = g_beam_extent2_start + (g_beam_extent2_end - g_beam_extent2_start) * factor;
        color = FastTweenColor(g_beam_color_start, g_beam_color_end, factor);
        color2 = FastTweenColor(g_beam_color2_start, g_beam_color2_end, factor);
        FastVecScale(direction, object + 0xC0, -length);
        part_spawn_sprite_line(pos, direction, count, width, height, extent, color);
        FastVecScale(direction, object + 0xC0, -length2);
        part_spawn_sprite_line(pos, direction, count2, width2, height2, extent2, color2);
    }
    UpdateBeamTrailParticles_pal(object);
    if (hero_get_shield_value())
        gfx_draw_thruster_glow_pal(object);
}
