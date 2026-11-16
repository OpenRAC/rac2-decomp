#include "include_asm.h"

#include "common.h"
extern int PlayMobySound(int, int, char *);
extern void *SpawnExplosion_pal(float, float, void *, int, int, int, int, int, int, int, int, int, int, void *);
extern void moby_get_facing_direction(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern void vec_build_spherical_offset(float *, float, float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern char *tumbling_debris_create_pal(void *, void *, int, int);
extern void table_clear_entry_flag(int);
extern void *g_active_tether_object MACRO_ADDR;
extern int g_shot_fragment_count __attribute__((sda));

/* Build a surface-aligned frame, then launch the configured number of fragments. */

void shot_spawn_fragments_pal(char *object) {
    float basis[3][4];
    float perpendicular[4];
    float direction[4];
    char *state = *(char **)(object + 0x68);
    char *position = object + 0x10;
    char *fragment;
    float strength = 0.7f;
    float heading;
    float elevation;
    float speed;
    int i;
    int j;

    PlayMobySound(0, 0, object);
    for (j = 1; j >= 0; j--) {
        SpawnExplosion_pal(strength, 20.0f, object + 0x10, 1, 14, 10, 15, 10, 20, 1,
                       0, 1, 0, g_active_tether_object);
        strength += 0.3f;
    }
    moby_get_facing_direction(position, basis[2]);
    perpendicular[0] = basis[2][2];
    perpendicular[1] = basis[2][2];
    perpendicular[2] = -(basis[2][0] + basis[2][1]);
    vec_scale_to_length(basis[0], perpendicular, 1.0f);
    FastVecCross(basis[1], basis[0], basis[2]);
    basis[0][3] = basis[1][3] = basis[2][3] = 0.0f;
    for (i = 0; i < g_shot_fragment_count; i++) {
        heading = math_random_angle();
        if (*(int *)(state + 0x2C) != 0) {
            elevation = math_random_float_range(0.698131799697876f, 1.3089970350265503f);
            speed = math_random_float_range(4.0f, 12.0f) * 0.020000001f;
        } else {
            elevation = math_random_float_range(0.8726646900177002f, 1.5707964897155762f);
            speed = math_random_float_range(4.0f, 9.0f) * 0.020000001f;
        }
        vec_build_spherical_offset(direction, speed, heading, elevation);
        direction[3] = 0.0f;
        matrix_mul_vec3(direction, direction, basis);
        fragment = tumbling_debris_create_pal(position, direction, i, *(int *)(state + 0x2C));
        if (fragment != 0) *(int *)(fragment + 0xB8) = *(int *)(object + 0xB8);
    }
    table_clear_entry_flag(*(int *)(state + 0x30));
}
