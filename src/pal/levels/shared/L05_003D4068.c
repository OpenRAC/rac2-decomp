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

/* Gives the object its reach: the table's entry for the object's id picks the record, and
 * the record takes the cone the object was given. */
void moby_init_reach_and_position_pal(char *obj)
{
    char *sub = *(char **)(obj + 0x68);
    char *table;
    float radius, yaw, pitch;

    *(unsigned char *)(obj + 0x20) = 1;
    *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
    *(int *)(moby_get_motion_data(obj) + 0x148) = 1;
    moby_init_spawned_sub_object_pal(obj, 1);
    table = g_feltzin_enemy_table + g_feltzin_challenge_state[0] * 128;
    *(int *)(sub + 0x1BC) = -1;
    *(int *)(sub + 0x1C0) = -1;
    *(float *)(sub + 0x180) = 1.0f;
    *(int *)(sub + 0x1B8) = 0;
    *(float *)(obj + 0x2C) = 0.06f;
    radius = math_random_float_range(0.0f, *(float *)table);
    yaw = math_random_angle();
    pitch = math_random_angle();
    vec_build_spherical_offset(obj + 0x10, radius, yaw, pitch);
    FastVecAdd(obj + 0x10, table + 0x30, obj + 0x10);
}


