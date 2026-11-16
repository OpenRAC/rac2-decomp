#include "include_asm.h"
#include "names.h"


extern void SpawnExplosionEffects_pal(char *, char *, int, float, float, int, int, int,
                          float, float, float, float, int, float, int, int, int, int, int);
extern void vec_random_direction(float *, float, float);
extern float math_fabs(float);
extern void func_PAL_002B15D8(char *, int, float *, float, float, float, float, int);
extern char *part_find_owned_effect_slot(char *, int, int);
extern int PlayMobySound(int, int, char *);
extern void moby_mark_spawned(char *);
extern void FastVecAdd(char *, char *, char *);
extern char g_effect_vector[] __attribute__((sda));

void func_PAL_L06_0045B390(char *obj)
{
    float v[4];
    char *hit = (char *)part_find_owned_effect_slot(obj, 0x4010000, 0);
    if (hit && *(short *)(*(char **)(hit + 0x20) + 0xAA) != 0xFE5) {
        PlayMobySound(0, 0, obj);
        SpawnExplosionEffects_pal(obj, obj + 0x10, 0, 0.0f, 0.0f, 10, 3, 9,
                      4.0f, 2.0f, 9.0f, 0.0f, -1, 15.0f, 1, 1, -1, 0, 0x810001);
        vec_random_direction(v, 0.080000006f, 0.120000005f);
        v[2] = math_fabs(v[2]) * 1.5f;
        FastVecAdd((char *)v, (char *)v, g_effect_vector);
        func_PAL_002B15D8(obj, 1, v, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        vec_random_direction(v, 0.080000006f, 0.120000005f);
        v[2] = math_fabs(v[2]) * 1.5f;
        FastVecAdd((char *)v, (char *)v, g_effect_vector);
        func_PAL_002B15D8(obj, 4, v, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        vec_random_direction(v, 0.080000006f, 0.120000005f);
        v[2] = math_fabs(v[2]) * 1.5f;
        FastVecAdd((char *)v, (char *)v, g_effect_vector);
        func_PAL_002B15D8(obj, 8, v, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        vec_random_direction(v, 0.080000006f, 0.120000005f);
        v[2] = math_fabs(v[2]) * 1.5f;
        FastVecAdd((char *)v, (char *)v, g_effect_vector);
        func_PAL_002B15D8(obj, 16, v, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        vec_random_direction(v, 0.080000006f, 0.120000005f);
        v[2] = math_fabs(v[2]) * 1.5f;
        FastVecAdd((char *)v, (char *)v, g_effect_vector);
        func_PAL_002B15D8(obj, 32, v, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        vec_random_direction(v, 0.080000006f, 0.120000005f);
        v[2] = math_fabs(v[2]) * 1.5f;
        FastVecAdd((char *)v, (char *)v, g_effect_vector);
        func_PAL_002B15D8(obj, 64, v, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        moby_mark_spawned(obj);
    }
    *(unsigned char *)(obj + 0xA8) = 255;
}


