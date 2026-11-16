#include "common.h"
extern float g_surface_grid_points[][4];
extern float math_random_float_range(float, float);
extern float FloatFraction(float);
/* Picks a random point on the surface grid and returns its position. */
void surface_grid_random_point(char *obj, float *out)
{
    char *rec = *(char **)(obj + 0x68);
    float x = math_random_float_range(0.0f, 6.99f);
    int ix = (int)x;
    float y = math_random_float_range(0.0f, 6.99f);
    int iy = (int)y;
    int base = *(int *)(rec + 0x40) * 64;
    int index = base + iy * 8 + ix;
    float f, dx, dy;
    out[0] = g_surface_grid_points[index][0];
    out[1] = g_surface_grid_points[index][1];
    f = FloatFraction(x);
    dx = g_surface_grid_points[index + 1][0] - g_surface_grid_points[index][0];
    dy = g_surface_grid_points[index + 1][1] - g_surface_grid_points[index][1];
    out[0] += dx * f;
    out[1] += dy * f;
    f = FloatFraction(y);
    dx = g_surface_grid_points[base + (iy + 1) * 8 + ix][0] - g_surface_grid_points[index][0];
    dy = g_surface_grid_points[base + (iy + 1) * 8 + ix][1] - g_surface_grid_points[index][1];
    out[0] += dx * f;
    out[1] += dy * f;
    out[2] = g_surface_grid_points[index][2];
    out[3] = 1.0f;
}
