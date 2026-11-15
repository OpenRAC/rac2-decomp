#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern float D_L02_001B04B0 __attribute__((sda));
extern float D_L02_001B04C8 __attribute__((sda));
extern float D_L02_001B04CC __attribute__((sda));
extern float D_L02_001B04D0 __attribute__((sda));
extern float D_L02_001B04D4 __attribute__((sda));
extern float D_L02_001B04D8 __attribute__((sda));
extern int g_moby_l02_pool;
extern float g_camera_l02_position[4];
extern void moby_transform_joint_to_world(char *, int, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void vec_add_random_offset(void *, float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern void *enemy_spawn_record(void *, void *, void *, int, int);

void func_PAL_L02_003DF388(char *arg0) {
    float a[4];
    float b[4];
    float c[4];

    *(TI128 *)a = 0;
    moby_transform_joint_to_world((char *)(g_moby_l02_pool + (*(int *)(*(char **)(arg0 + 0x68) + 0x244) << 8)), 4, b);
    b[2] = b[2] + D_L02_001B04D4;
    FastVecSub(c, g_camera_l02_position, b);
    c[2] = 0.0f;
    vec_scale_to_length(c, c, D_L02_001B04D8);
    FastVecAdd(b, b, c);
    vec_add_random_offset(b, D_L02_001B04C8);
    a[2] = math_random_float_range(D_L02_001B04CC, D_L02_001B04D0) * 0.020000001f;
    enemy_spawn_record(b, a, &D_L02_001B04B0, math_random_int_below(2), 1);
}
