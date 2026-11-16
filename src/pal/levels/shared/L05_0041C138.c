#include "include_asm.h"

#include "common.h"
extern char *g_feltzin_enemy_table __attribute__((sda));
extern int g_feltzin_challenge_state[];
extern char *moby_get_motion_data(char *object);
extern void moby_init_spawned_sub_object_pal(char *object, int flag);
extern float math_random_float_range(float a, float b);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(char *dst, float a, float b, float c);
extern void FastVecAdd(char *dst, char *src, char *src2);

/* Spawns the object's effect: marks the object, takes one record of the shared
   128-byte table by the global index and gives it a random position. */
void func_PAL_L05_0041C138(char *object)
{
    char *sub = *(char **)(object + 0x68);
    char *table;
    float a, b, c;

    *(unsigned char *)(object + 0x20) = 1;
    *(unsigned short *)(object + 0x34) = *(unsigned short *)(object + 0x34) | 0x100;
    *(int *)(moby_get_motion_data(object) + 0x148) = 1;
    moby_init_spawned_sub_object_pal(object, 1);
    table = g_feltzin_enemy_table + g_feltzin_challenge_state[0] * 128;
    *(int *)(sub + 0x1C8) = 0x64;
    *(int *)(sub + 0x1C0) = -1;
    *(int *)(sub + 0x1C4) = -1;
    *(float *)(sub + 0x180) = 1.0f;
    a = math_random_float_range(0.0f, *(float *)table);
    b = math_random_angle();
    c = math_random_angle();
    vec_build_spherical_offset(object + 0x10, a, b, c);
    FastVecAdd(object + 0x10, table + 0x30, object + 0x10);
    *(int *)(sub + 0x1B8) = 0;
    *(float *)(object + 0x2C) = 0.02f;
}


