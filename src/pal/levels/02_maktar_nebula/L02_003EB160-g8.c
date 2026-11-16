#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern void matrix_mul_vec3(float *, float *, float *);
extern void FastVecAdd(float *, float *, float *);
extern char *cam_moby_create_pal(char *, int, int, int, char *, char *, float *, int, float, float);
extern void *moby_spawn_bolt_pickup_pal(char *, float *, float *, int, int, int);
extern int g_slot_machine_debris_budget __attribute__((sda));

/* Spawns five particles at the actor (the ids 0xCA5 to 0xCA9, each with a random velocity in a
   0.0167-scaled box rotated by the matrix at +0xC0), then, while D_L02_001B096C stays above 0, up
   to five more (-5 each) through func_PAL_00303578 around a point near the actor. */
void part_spawn_slot_machine_debris_pal(char *moby) {
    float velocity[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    char *pos = moby + 0x10;
    char *mat = moby + 0xC0;
    int i;

    for (i = 0xCA5; i < 0xCAA; i++) {
        qzero(velocity);
        velocity[0] = math_random_float_range(1.0f, 4.0f) * 0.020000001f;
        velocity[1] = math_random_signed_float_range(1.0f, 3.0f) * 0.020000001f;
        velocity[2] = math_random_float_range(4.0f, 9.0f) * 0.020000001f;
        matrix_mul_vec3(velocity, velocity, (float *)(moby + 0xC0));
        cam_moby_create_pal(moby, 0, i, -1, moby + 0x10, moby + 0xF0, velocity, 0xFF,
                      math_random_float_range(90.0f, 180.0f), math_random_float_range(15.0f, 25.0f));
    }
    *(TI128 *)point = 0;
    point[2] = 1.5f;
    matrix_mul_vec3(point, point, (float *)mat);
    FastVecAdd(point, point, (float *)pos);
    for (i = 0; i < 5 && g_slot_machine_debris_budget > 0; i++) {
        qzero(velocity);
        velocity[0] = math_random_float_range(1.0f, 4.0f) * 0.020000001f;
        velocity[1] = math_random_signed_float_range(1.0f, 3.0f) * 0.020000001f;
        velocity[2] = math_random_float_range(4.0f, 9.0f) * 0.020000001f;
        matrix_mul_vec3(velocity, velocity, (float *)mat);
        moby_spawn_bolt_pickup_pal(moby, point, velocity, 0, 5, 0);
        g_slot_machine_debris_budget -= 5;
    }
}
