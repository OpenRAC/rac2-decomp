#include "include_asm.h"

#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI)));
extern char *part_spawn_object_following_effect(void *, void *, unsigned int, int, int, int, int, float, float, int);
extern void moby_set_state(char *, int, int);
extern int part_find_owned_effect_slot(char *, int, int);
extern void moby_mark_spawned(char *);
extern void func_PAL_L00_0032C328(char *, void *, void *, void *, int, int, int, int, int, int, int);
extern void moby_compute_local_point(char *, void *, float, float, float);
extern void func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void func_PAL_L00_00328480(char *, void *, int, float, int, void *, float, unsigned int, float, float, int);
extern float D_L06_001B1CB8 __attribute__((sda));
extern float D_L06_001B1CB0 __attribute__((sda));
extern float D_L06_001B1CC0 __attribute__((sda));
extern float D_L06_001B1CE0 __attribute__((sda));
extern float D_L06_001B1CE4, D_L06_001B1CE8;

void func_PAL_L06_00468998(char *a0) {
    float pos[4], vel[4];
    char *state = *(char **)(a0 + 0x68);
    int i;
    switch (*(unsigned char *)(a0 + 0x20)) {
    case 0: {
        float scale;
        *(u128 *)pos = 0;
        pos[2] = 3.75f;
        scale = *(float *)(a0 + 0x2C) / *(float *)(*(char **)(a0 + 0x24) + 0x24);
        pos[2] *= scale;
        part_spawn_object_following_effect(pos, a0, 0x300033FF, -1, 1, -1, 0, scale * 525000.0f, 0.75f, -1);
        part_spawn_object_following_effect(pos, a0, 0x280033FF, -1, 0, -1, 0, scale * 525000.0f, 0.75f, -1);
        *(int *)(a0 + 0x78) = -16192;
        moby_set_state(a0, 1, -1);
        /* fall through */
    }
    case 1:
        if (part_find_owned_effect_slot(a0, 0x4010000, 0) && *(int *)state == 0) moby_set_state(a0, 2, -1);
        *(unsigned char *)(a0 + 0xA8) = 0xFF;
        break;
    case 2:
        func_PAL_L00_0032C328(a0, &D_L06_001B1CC0, &D_L06_001B1CB8, &D_L06_001B1CB0, 0xFFFF, 0, -1, 6, 0xFF, 0xFF, 0);
        moby_compute_local_point(a0, pos, D_L06_001B1CE0, D_L06_001B1CE4, D_L06_001B1CE8);
        func_PAL_L00_003FB330(pos, 0, 5, 5, 5, 20, 5, 0, 1, 1, 1, 0, 1.0f, 20.0f);
        for (i = 0; i < 4; i++) {
            vel[0] = (i / 2 * 2 - 1) * 0.060000002f;
            vel[1] = (i % 2 * 2 - 1) * 0.060000002f;
            vel[2] = 0.14000002f;
            matrix_mul_vec3(vel, vel, a0 + 0xC0);
            func_PAL_L00_00328480(a0, pos, 3, 0.2f, 1, vel, 5.0f, 0x7F40FFFF, 1.45f, 2.2f, 0);
        }
        moby_mark_spawned(a0);
        break;
    }
}
