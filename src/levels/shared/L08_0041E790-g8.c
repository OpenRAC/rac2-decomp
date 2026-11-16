#include "common.h"


extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void matrix_mul_vec3(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int FloatToInt(float);
extern char *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);
extern int func_001163B0(void);



extern int GetCollHitMaterial(void);
extern int g_ring_l08_color_start SDATA(D_L08_001B1ADC);
extern int g_ring_l08_color_end SDATA(D_L08_001B1AE0);
extern int g_ring_l08_color_start_2 SDATA(D_L08_001B1B74);
extern int g_ring_l08_color_end_2 SDATA(D_L08_001B1B78);
extern float g_ring_speed_min_divisor SDATA(D_L08_001B1B14);
extern float g_ring_rise_min_divisor SDATA(D_L08_001B1B18);
extern float g_ring_boost_scale SDATA(D_L08_001B1B68);
extern float g_ring_height_offset SDATA(D_L08_001B1B6C);
extern float g_ring_red_min SDATA(D_L08_001B1AE4);
extern float g_ring_red_max SDATA(D_L08_001B1AE8);
extern float g_ring_green_min SDATA(D_L08_001B1AEC);
extern float g_ring_green_max SDATA(D_L08_001B1AF0);
extern float g_ring_blue_min SDATA(D_L08_001B1AF4);
extern float g_ring_blue_max SDATA(D_L08_001B1AF8);

/* Spawns a burst of small particles that fly outward from a point in a ring, rising and
   shrinking as they go. */
void part_spawn_ring(char *moby, void *position, int count,
                      float speed, float rise, float maxRadius, float minRadius,
                      float size, float endSize)
{
    float offset[4], velocity[4], accel[4], boost[4];
    char *vars = *(char **)(moby + 0x68);
    int color_start = g_ring_l08_color_start;
    int color_end = g_ring_l08_color_end;
    if (!GetCollHitMaterial()) {
        color_start = g_ring_l08_color_start_2;
        color_end = g_ring_l08_color_end_2;
    }
    { int i;
    for (i = 0; i < count; i++) {
        int red,green,blue;
        char *particle;
        float cos_part,sin_part,speed_range;
        cos_part = math_fast_sin_or_cos_a(math_random_float_range(-3.1415927410125732f,3.1415927410125732f));
        offset[0] = cos_part * math_random_float_range(minRadius,maxRadius);
        sin_part = math_fast_sin_or_cos_b(math_random_float_range(-3.1415927410125732f,3.1415927410125732f));
        sin_part *= math_random_float_range(minRadius,maxRadius);
        offset[1] = sin_part;
        offset[2] = 0;
        matrix_mul_vec3(offset,offset,moby+0xC0);
        speed_range = (speed * ((maxRadius-FastVecLength(offset))*0.01666666753590107f))/maxRadius;
        vec_scale_to_length(velocity,offset,math_random_float_range(speed_range / g_ring_speed_min_divisor,speed_range));
        qcopy(boost,vars);
        boost[2] *= g_ring_boost_scale;
        FastVecAdd(velocity,velocity,boost);
        {
            velocity[2] += math_random_float_range(rise / g_ring_rise_min_divisor,rise)*0.01666666753590107f;
        }
        qzero_nc(accel);
        FastVecAdd(offset,offset,position);
        offset[2] += g_ring_height_offset;
        velocity[3] = size;
        accel[3] = endSize;
        red = FloatToInt(math_random_float_range(g_ring_red_min,g_ring_red_max));
        green = FloatToInt(math_random_float_range(g_ring_green_min,g_ring_green_max));
        blue = FloatToInt(math_random_float_range(g_ring_blue_min,g_ring_blue_max));
        particle = part_spawn_trail(offset,velocity,accel,color_start,color_end,red,green,blue,-1);
        if (particle && (func_001163B0() & 1)) particle[3] = 0x48;
    }
    }
}
