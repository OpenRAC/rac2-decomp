#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern void matrix_mul_vec3(float *, float *, float *);
extern void FastVecAdd(float *, float *, float *);
extern char *cam_moby_create(char *, int, int, int, char *, char *, float *, int, float, float);
extern int moby_spawn_bolt_pickup(char *, float *, float *, int, int, int);
extern int D_L02_001B096C __attribute__((sda));

/* Spawns five particles at the actor (the ids 0xCA5 to 0xCA9, each with a random velocity in a
   0.0167-scaled box rotated by the matrix at +0xC0), then, while D_L02_001B096C stays above 0, up
   to five more (-5 each) through func_00302470 around a point near the actor. */
void part_spawn_slot_machine_debris(char *actor) {
    float vel[4] __attribute__((aligned(16)));
    float spawnPoint[4] __attribute__((aligned(16)));
    char *pos = actor + 0x10;
    char *mat = actor + 0xC0;
    int i;

    for (i = 0xCA5; i < 0xCAA; i++) {
        qzero(vel);
        vel[0] = math_random_float_range(1.0f, 4.0f) * 0.016666668f;
        vel[1] = math_random_signed_float_range(1.0f, 3.0f) * 0.016666668f;
        vel[2] = math_random_float_range(4.0f, 9.0f) * 0.016666668f;
        matrix_mul_vec3(vel, vel, (float *)(actor + 0xC0));
        cam_moby_create(actor, 0, i, -1, actor + 0x10, actor + 0xF0, vel, 0xFF,
                      math_random_float_range(90.0f, 180.0f), math_random_float_range(15.0f, 25.0f));
    }
    *(TI128 *)spawnPoint = 0;
    spawnPoint[2] = 1.5f;
    matrix_mul_vec3(spawnPoint, spawnPoint, (float *)mat);
    FastVecAdd(spawnPoint, spawnPoint, (float *)pos);
    for (i = 0; i < 5 && D_L02_001B096C > 0; i++) {
        qzero(vel);
        vel[0] = math_random_float_range(1.0f, 4.0f) * 0.016666668f;
        vel[1] = math_random_signed_float_range(1.0f, 3.0f) * 0.016666668f;
        vel[2] = math_random_float_range(4.0f, 9.0f) * 0.016666668f;
        matrix_mul_vec3(vel, vel, (float *)mat);
        moby_spawn_bolt_pickup(actor, spawnPoint, vel, 0, 5, 0);
        D_L02_001B096C -= 5;
    }
}
