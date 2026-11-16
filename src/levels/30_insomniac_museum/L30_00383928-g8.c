#include "common.h"

typedef struct {
    float position[4][4];
    unsigned int color[4];
    float uv[4][2];
    unsigned long flags, texture, blend, alpha;
} GridQuad;

extern int g_museum_water_front_buffer __attribute__((sda));
extern float g_museum_water_height_raise __attribute__((sda));
extern int g_museum_water_alpha_high_word __attribute__((sda));
extern int g_museum_water_alpha_first __attribute__((sda));
extern int g_museum_water_alpha_second __attribute__((sda));
extern int g_museum_water_alpha_third __attribute__((sda));
extern int g_museum_water_alpha_fourth __attribute__((sda));
extern float g_museum_water_heights[][24][24];
extern float g_museum_water_grid_points[24][24][2];
extern float g_museum_water_refract_uv[24][24][2];
extern float g_museum_water_reflect_uv[24][24][2];
extern unsigned char g_museum_water_brightness[24][24];
extern unsigned long GetEffectTextureDescriptor(int);
extern void UpdateMuseumWaterGridOptics(void *);
extern void VU1_addGSregister(unsigned int, unsigned long);
extern void draw_world_quad(void *, int, int);

/* Draw the 24-by-24 grid twice as quads: once with the coordinates in D_L30_00236760 and once,
   raised by D_L30_001AEBF0 and blended by the packed GS ALPHA value, with those in D_L30_00237960. */
void DrawMuseumWaterGrid(char *obj)
{
    GridQuad q;
    unsigned int rgb;
    unsigned long tex0, tex1, alpha, alpha01, alpha012, alpha0123;
    int row, col;

    tex0 = GetEffectTextureDescriptor(0x47);
    tex1 = GetEffectTextureDescriptor(0x48);
    alpha01 = (unsigned long)g_museum_water_alpha_first | ((unsigned long)g_museum_water_alpha_second << 2);
    alpha012 = alpha01 | ((unsigned long)g_museum_water_alpha_third << 4);
    alpha0123 = alpha012 | ((unsigned long)g_museum_water_alpha_fourth << 6);
    alpha = alpha0123 | ((unsigned long)g_museum_water_alpha_high_word << 32);
    q.blend = 0xFF9000000260UL;
    q.flags = 0;
    UpdateMuseumWaterGridOptics(obj + 0x10);
    VU1_addGSregister(0x47, 0x53001);
    q.alpha = 0x80000000A8UL;
    q.texture = tex1;
    row = 0;
    rgb = 0x808080;
    for (; row < 23; row++) {
        for (col = 0; col < 23; col++) {
            q.color[0] = (g_museum_water_brightness[row][col] << 24) | rgb;
            q.position[0][0] = g_museum_water_grid_points[row][col][0] + *(float *)(obj + 0x10);
            q.position[0][1] = g_museum_water_grid_points[row][col][1] + *(float *)(obj + 0x14);
            q.position[0][2] = g_museum_water_heights[g_museum_water_front_buffer][row][col] + *(float *)(obj + 0x18);
            q.position[0][3] = 1.0f;
            q.color[1] = (g_museum_water_brightness[row + 1][col] << 24) | rgb;
            q.position[1][0] = g_museum_water_grid_points[row + 1][col][0] + *(float *)(obj + 0x10);
            q.position[1][1] = g_museum_water_grid_points[row + 1][col][1] + *(float *)(obj + 0x14);
            q.position[1][2] = g_museum_water_heights[g_museum_water_front_buffer][row + 1][col] + *(float *)(obj + 0x18);
            q.position[1][3] = 1.0f;
            q.color[2] = (g_museum_water_brightness[row][col + 1] << 24) | rgb;
            q.position[2][0] = g_museum_water_grid_points[row][col + 1][0] + *(float *)(obj + 0x10);
            q.position[2][1] = g_museum_water_grid_points[row][col + 1][1] + *(float *)(obj + 0x14);
            q.position[2][2] = g_museum_water_heights[g_museum_water_front_buffer][row][col + 1] + *(float *)(obj + 0x18);
            q.position[2][3] = 1.0f;
            q.color[3] = (g_museum_water_brightness[row + 1][col + 1] << 24) | rgb;
            q.position[3][0] = g_museum_water_grid_points[row + 1][col + 1][0] + *(float *)(obj + 0x10);
            q.position[3][1] = g_museum_water_grid_points[row + 1][col + 1][1] + *(float *)(obj + 0x14);
            q.position[3][2] = g_museum_water_heights[g_museum_water_front_buffer][row + 1][col + 1] + *(float *)(obj + 0x18);
            q.position[3][3] = 1.0f;
            q.uv[0][0] = g_museum_water_refract_uv[row][col][0];
            q.uv[0][1] = g_museum_water_refract_uv[row][col][1];
            q.uv[1][0] = g_museum_water_refract_uv[row + 1][col][0];
            q.uv[1][1] = g_museum_water_refract_uv[row + 1][col][1];
            q.uv[2][0] = g_museum_water_refract_uv[row][col + 1][0];
            q.uv[2][1] = g_museum_water_refract_uv[row][col + 1][1];
            q.uv[3][0] = g_museum_water_refract_uv[row + 1][col + 1][0];
            q.uv[3][1] = g_museum_water_refract_uv[row + 1][col + 1][1];
            draw_world_quad(&q, 0, 0);
        }
    }
    VU1_addGSregister(0x47, 0x5360B);
    q.alpha = alpha;
    q.texture = tex0;
    for (row = 0; row < 23; row++) {
        for (col = 0; col < 23; col++) {
            q.color[0] = (g_museum_water_brightness[row][col] << 24) | rgb;
            q.position[0][0] = g_museum_water_grid_points[row][col][0] + *(float *)(obj + 0x10);
            q.position[0][1] = g_museum_water_grid_points[row][col][1] + *(float *)(obj + 0x14);
            q.position[0][2] = g_museum_water_heights[g_museum_water_front_buffer][row][col] + *(float *)(obj + 0x18) + g_museum_water_height_raise;
            q.position[0][3] = 1.0f;
            q.color[1] = (g_museum_water_brightness[row + 1][col] << 24) | rgb;
            q.position[1][0] = g_museum_water_grid_points[row + 1][col][0] + *(float *)(obj + 0x10);
            q.position[1][1] = g_museum_water_grid_points[row + 1][col][1] + *(float *)(obj + 0x14);
            q.position[1][2] = g_museum_water_heights[g_museum_water_front_buffer][row + 1][col] + *(float *)(obj + 0x18) + g_museum_water_height_raise;
            q.position[1][3] = 1.0f;
            q.color[2] = (g_museum_water_brightness[row][col + 1] << 24) | rgb;
            q.position[2][0] = g_museum_water_grid_points[row][col + 1][0] + *(float *)(obj + 0x10);
            q.position[2][1] = g_museum_water_grid_points[row][col + 1][1] + *(float *)(obj + 0x14);
            q.position[2][2] = g_museum_water_heights[g_museum_water_front_buffer][row][col + 1] + *(float *)(obj + 0x18) + g_museum_water_height_raise;
            q.position[2][3] = 1.0f;
            q.color[3] = (g_museum_water_brightness[row + 1][col + 1] << 24) | rgb;
            q.position[3][0] = g_museum_water_grid_points[row + 1][col + 1][0] + *(float *)(obj + 0x10);
            q.position[3][1] = g_museum_water_grid_points[row + 1][col + 1][1] + *(float *)(obj + 0x14);
            q.position[3][2] = g_museum_water_heights[g_museum_water_front_buffer][row + 1][col + 1] + *(float *)(obj + 0x18) + g_museum_water_height_raise;
            q.position[3][3] = 1.0f;
            q.uv[0][0] = g_museum_water_reflect_uv[row][col][0];
            q.uv[0][1] = g_museum_water_reflect_uv[row][col][1];
            q.uv[1][0] = g_museum_water_reflect_uv[row + 1][col][0];
            q.uv[1][1] = g_museum_water_reflect_uv[row + 1][col][1];
            q.uv[2][0] = g_museum_water_reflect_uv[row][col + 1][0];
            q.uv[2][1] = g_museum_water_reflect_uv[row][col + 1][1];
            q.uv[3][0] = g_museum_water_reflect_uv[row + 1][col + 1][0];
            q.uv[3][1] = g_museum_water_reflect_uv[row + 1][col + 1][1];
            draw_world_quad(&q, 0, 0);
        }
    }
}
