#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
extern void gfx_draw_animated_water_background(void), gfx_finish_wave_grid_packet(void);
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float), FastAddRotations(float, float);
extern void FastVecCross(float *, float *, float *), vec_scale_to_length(float *, float *, float);
extern float FastVecDot(float *, float *);
extern u32 FastTweenColor(unsigned int, unsigned int, float);
extern int g_oozla_intro_stage;
extern float g_water_phase_scale_a __attribute__((sda)), g_water_phase_scale_b __attribute__((sda));
extern int g_water_phase_period_a __attribute__((sda)), g_water_phase_period_b __attribute__((sda));
extern float g_water_axis_value __attribute__((sda)), g_water_light_heading __attribute__((sda));
extern float g_water_light_elevation __attribute__((sda)), g_water_palette_blend __attribute__((sda));
extern short g_water_height_grid[];
extern unsigned int g_water_color_grid[];
extern unsigned char *g_water_bg_palette_ptr __attribute__((sda));
/* This routine uses absolute accesses to the real packet cursor. */
extern unsigned char *g_water_packet_headers[] __attribute__((sda));
extern unsigned char *D_L01_001B2CC8_gp __asm__("D_L01_001B2CC8") MACRO_ADDR;
/* All are complete 16-byte constants; their observed address forms differ. The MACRO_ADDR ones
   load through an unsplit la: split HIGH/LO_SUM insns would lengthen the packet base's life and
   lower its local-alloc priority below the cursor values, moving it from $a0 to $a1. */
extern Quad g_water_quad_a __attribute__((sda));
extern Quad g_water_quad_b MACRO_ADDR, g_water_quad_c MACRO_ADDR, g_water_quad_d MACRO_ADDR;
extern Quad g_water_quad_e __attribute__((sda)), g_water_quad_f __attribute__((sda));
extern Quad g_water_quad_g __attribute__((sda)), g_water_quad_h __attribute__((sda));
#define APPEND_QUAD(value) { cursor[offset] = (value); offset += 1; D_L01_001B2CC8[0] = (unsigned char *)(cursor + offset); }
/* Builds the animated water wave grid. It works out the height and shading of each grid point, then writes the draw packet. */
void BuildWaveGridPacket(void)
{
    gfx_draw_animated_water_background();
    {
        int i;
        int firstPhase[8], secondPhase[8];
        float firstAngle = (float)(g_oozla_intro_stage % (g_water_phase_period_a * 2) - g_water_phase_period_a)
            * (3.14159274f / (float)g_water_phase_period_a);
        float secondAngle = (float)(g_oozla_intro_stage % (g_water_phase_period_b * 2) - g_water_phase_period_b)
            * (3.14159274f / (float)g_water_phase_period_b);
        for (i = 0; i < 8; i++) {
            firstPhase[i] = (int)((math_fast_sin_or_cos_a(firstAngle) + 1.0f) * g_water_phase_scale_a);
            secondPhase[i] = (int)((math_fast_sin_or_cos_a(secondAngle) + 1.0f) * g_water_phase_scale_b);
            firstAngle = FastAddRotations(firstAngle, 0.785398006f);
            secondAngle = FastAddRotations(secondAngle, 0.785398006f);
        }
        { int row, col;
        for (row = 0; row < 8; row++)
            for (col = 0; col < 8; col++)
                g_water_height_grid[(row*9+col)*4+2] = (unsigned short)firstPhase[(col + row) & 7]
                    + (unsigned short)secondPhase[(-row) & 7];
        }
        { int j; for (j = 0; j < 36; j += 4) { int index = j + 2; short *p = g_water_height_grid + index; p[288] = *p; } }
        { int j; for (j = 0; j < 324; j += 36) { int index = j + 2; short *p = g_water_height_grid + index; p[32] = *p; } }
    }
    {
        int i, j;
        float direction[4] __attribute__((aligned(16)));
        float horizontal[4] __attribute__((aligned(16)));
        float vertical[4] __attribute__((aligned(16)));
        float normal[4] __attribute__((aligned(16)));
        unsigned int shade, target;
        direction[0] = math_fast_sin_or_cos_a(g_water_light_heading) * math_fast_sin_or_cos_a(g_water_light_elevation);
        direction[1] = math_fast_sin_or_cos_b(g_water_light_heading) * math_fast_sin_or_cos_a(g_water_light_elevation);
        direction[2] = math_fast_sin_or_cos_b(g_water_light_elevation);
        for (i = 0; i < 8; i++) {
            int palette = ((i + 2) * 128) | 8;
            for (j = 0; j < 8; j++) {
                int k = (i * 9 + j) * 4;
                horizontal[0] = g_water_axis_value;
                horizontal[1] = 0.0f;
                horizontal[2] = (float)(g_water_height_grid[k + 6] - g_water_height_grid[k + 2]) * 0.0009765625f;
                vertical[0] = 0.0f;
                vertical[1] = g_water_axis_value;
                vertical[2] = (float)(g_water_height_grid[k + 38] - g_water_height_grid[k + 2]) * 0.0009765625f;
                FastVecCross(normal, vertical, horizontal);
                vec_scale_to_length(normal, normal, 1.0f);
                shade = (int)(FastVecDot(normal, direction) * 128.0f);
                {
                    unsigned int green = (shade << 8) | 0x80000000;
                    unsigned int red = shade << 16;
                    target = red | green;
                    target |= shade;
                }
                g_water_color_grid[(i) * 9 + (j)] = FastTweenColor(
                    *(unsigned int *)(palette + (unsigned int)g_water_bg_palette_ptr), target, g_water_palette_blend);
                palette += 4;
            }
        }
        { int k; for (k = 0; k < 9; k++) g_water_color_grid[k + 72] = g_water_color_grid[k]; }
        { int k; for (k = 0; k < 81; k += 9) { unsigned int *p = g_water_color_grid + k; p[8] = *p; } }
    }
    { Quad *cursor = (Quad *)g_water_packet_headers[0]; int offset = 0;
    APPEND_QUAD(g_water_quad_e);
    APPEND_QUAD(g_water_quad_a);
    APPEND_QUAD(g_water_quad_f);
    APPEND_QUAD(g_water_quad_g);
    APPEND_QUAD(g_water_quad_h);
    APPEND_QUAD(g_water_quad_e);
    APPEND_QUAD(g_water_quad_b);
    APPEND_QUAD(g_water_quad_f);
    APPEND_QUAD(g_water_quad_g);
    APPEND_QUAD(g_water_quad_h);
    APPEND_QUAD(g_water_quad_e);
    APPEND_QUAD(g_water_quad_c);
    APPEND_QUAD(g_water_quad_f);
    APPEND_QUAD(g_water_quad_g);
    APPEND_QUAD(g_water_quad_h);
    APPEND_QUAD(g_water_quad_e);
    APPEND_QUAD(g_water_quad_d);
    APPEND_QUAD(g_water_quad_f);
    APPEND_QUAD(g_water_quad_g);
    cursor[offset] = g_water_quad_h; offset += 1;
    D_L01_001B2CC8_gp = (unsigned char *)(cursor + offset);
    }
    gfx_finish_wave_grid_packet();
}
