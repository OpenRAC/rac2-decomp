#include "include_asm.h"

#include "common.h"
extern float g_water_level_threshold;
extern int g_particle_spin_counter[] __attribute__((sda));
extern int D_001B1DD4_sda __attribute__((sda));
extern int g_game_time[] __attribute__((sda));
extern char g_particle_spin_vector[] __attribute__((sda));
extern char g_sway_vector[];
extern int FastDecTimer(void *);
extern void part_kill(void *);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);

/* Spinning particle that fades out below the water level and otherwise fades in, then drifts
   and sways. */
void part_update_fading_spin_pal(char *obj)
{
    float v[4];
    char *p = obj + 0x20;
    char *q;
    int n;
    int top;

    if (*(float *)(obj + 0x18) - g_water_level_threshold < -7.0f ||
        (*(int *)(p + 0x14) != 0 && FastDecTimer(obj + 0xA) != 0)) {
        n = *(int *)(p + 0x10) - 1;
        *(int *)(p + 0x10) = n;
        if (n <= 0) {
            part_kill(obj);
            D_001B1DD4_sda = g_particle_spin_counter[0] - 1;
            return;
        }
        *(int *)(obj + 4) = (*(int *)(obj + 4) & 0xFFFFFF) + (n << 24);
    } else {
        top = *(int *)(obj + 4);
        if ((top >> 24) < *(int *)(p + 0x10))
            *(int *)(obj + 4) = top + 0x1000000;
    }
    if (((int)obj & 0x80) == 0)
        *(unsigned char *)(obj + 8) += 2;
    else
        *(unsigned char *)(obj + 8) -= 2;
    q = obj + 0x10;
    FastVecAdd(q, q, p);
    FastVecAdd(q, q, g_particle_spin_vector);
    if (*(int *)(p + 0x14) == 0) {
        short h = *(short *)(obj + 0xA);
        float f = math_fast_sin_or_cos_b((float)(g_game_time[0] & (h - 1)) / (float)h * 6.2831855f);
        FastVecScale(v, g_sway_vector, f * 0.020000001f);
        FastVecAdd(q, v, q);
    }
}

