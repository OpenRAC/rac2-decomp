#include "include_asm.h"

#include "common.h"
extern void vec_build_spherical_offset(void *, float, float, float);
extern int g_feltzin_challenge_state[];
extern float math_random_float_range(float, float);
extern char *moby_get_motion_data(char *);
extern void FastVecAdd(void *, void *, void *);
extern int g_feltzin_challenge_state[];
extern char *g_feltzin_enemy_table __attribute__((sda));
extern void moby_init_spawned_sub_object_pal(char *, int);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(void *, float, float, float);

/* func_L05_003D1368 is in L05_003D1368-g8.c. */

/* func_L05_003D15E8 is in L05_003D15E8.c. */

/* Sets the object up in its second mode (mode 5) and places it at a random point in the cone of the current challenge record (PAL). */
void moby_init_state_and_position_pal(char *obj)
{
    char *sub = *(char **)(obj + 0x68);
    char *table;
    float radius, yaw, pitch;

    *(unsigned char *)(obj + 0x20) = 1;
    *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
    *(int *)(moby_get_motion_data(obj) + 0x148) = 5;
    moby_init_spawned_sub_object_pal(obj, 1);
    table = g_feltzin_enemy_table + g_feltzin_challenge_state[0] * 128;
    *(float *)(sub + 0x180) = 5.0f;
    *(int *)(sub + 0x2F0) = -1;
    *(int *)(sub + 0x2F4) = -1;
    *(int *)(sub + 0x268) = 0;
    *(float *)(obj + 0x2C) = 0.04f;
    radius = math_random_float_range(0.0f, *(float *)table);
    yaw = math_random_angle();
    pitch = math_random_angle();
    vec_build_spherical_offset(obj + 0x10, radius, yaw, pitch);
    FastVecAdd(obj + 0x10, table + 0x30, obj + 0x10);
    *(int *)(sub + 0x26C) = 0;
}
