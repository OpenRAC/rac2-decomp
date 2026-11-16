#include "include_asm.h"

#include "common.h"
typedef int Copy128 __attribute__((mode(TI)));
typedef union { Copy128 q; float f[4]; } Vector16;
extern void mat_get_euler_angles(void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern char g_hero_position[];
extern int g_tether_lock_active __attribute__((sda));
extern void SetDeathBits_pal(char *, int, int);
extern int PlayMobySound(int, int, char *);
extern void matrix_mul_vec3(void *, void *, void *);
extern unsigned char *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern void vec_transform_and_set_height(char *, void *, void *, float, void *);
extern int math_random_int_below(int);
extern void part_spawn_masked_debris_pal(char *, int, float *, unsigned char, float, float, float, float);
extern void moby_mark_spawned(void *);

/* Spawn the destruction burst and ground impulse, then remove the object. */
void moby_l02_explode_and_remove_pal(char *object)
{
    Vector16 position, offset;
    float impulse[4];
    char *origin;
    int colour;

    if (*(short *)(*(char **)(object + 0x68) + 0x338) != 0)
        mat_get_euler_angles(object + 0xC0, object + 0xF0);
    origin = object + 0x10;
    SetDeathBits_pal(object, 0, 3);
    PlayMobySound(1, 0, object);
    offset.q = 0;
    offset.f[2] = 1.0f;
    matrix_mul_vec3(&position, &offset, object + 0xC0);
    FastVecAdd(&position, &position, origin);
    SpawnExplosion_pal(origin, 0, 0, 0, 0, 10, 20, 0, 0.333f, 20.0f, 1, 0, 0, 0);
    FastVecSub(&impulse, origin, g_hero_position);
    vec_transform_and_set_height(object, &impulse, &impulse, 0.0f, 0);
    vec_scale_to_length(&impulse, &impulse, 0.120000005f);
    if (g_tether_lock_active)
        colour = math_random_int_below(255);
    else
        colour = 255;
    part_spawn_masked_debris_pal(object, colour & 0x1F, impulse, 255, 3.0f, 6.0f, 3.0f, 6.0f);
    moby_mark_spawned(object);
}

