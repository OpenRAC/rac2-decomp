#include "include_asm.h"
#include "names.h"

extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float mat_fast_helper_a(float, float);
extern int FloatToInt(float);
extern void armed_enemy_setup(char *, int);
extern void actor_revive(char *, int);
extern void flamethrower_robot_wake(char *, int);
extern void blade_ball_wake(char *, int);
typedef struct {
    char pad0[0x80];
    float x;
    float y;
} L02_003D7900_Hero;
extern L02_003D7900_Hero g_hero_state;

/* Builds a four-float vector and hands it to the two vector helpers, tints the three colour
   records of the actor's state from it, then walks the three actors the state points at:
   each gets the angle to the hero written at 0xF8 and the behaviour its type selects. */
void chainblade_release_held_actors_pal(char *self) {
    float anchor[4];
    char *state = *(char **)(self + 0x68);
    char *held;
    int i;
    int count;

    anchor[0] = 0.0f;
    anchor[1] = -9.0f;
    anchor[2] = -3.3f;
    anchor[3] = 0.0f;
    matrix_mul_vec3(anchor, anchor, self + 0xC0);
    FastVecAdd(anchor, anchor, self + 0x10);
    if (*(char **)(state + 0x10) != 0) {
        *(float *)(*(char **)(state + 0x10) + 0x10) = anchor[0] - 2.0f;
        *(float *)(*(char **)(state + 0x10) + 0x14) = anchor[1];
        *(float *)(*(char **)(state + 0x10) + 0x18) = anchor[2];
        *(float *)(*(char **)(state + 0x10) + 0x1C) = anchor[3];
    }
    if (*(char **)(state + 0x14) != 0) {
        *(float *)(*(char **)(state + 0x14) + 0x10) = anchor[0];
        *(float *)(*(char **)(state + 0x14) + 0x14) = anchor[1] + 1.0f;
        *(float *)(*(char **)(state + 0x14) + 0x18) = anchor[2];
        *(float *)(*(char **)(state + 0x14) + 0x1C) = anchor[3];
    }
    if (*(char **)(state + 0x18) != 0) {
        *(float *)(*(char **)(state + 0x18) + 0x10) = anchor[0];
        *(float *)(*(char **)(state + 0x18) + 0x14) = anchor[1] - 1.0f;
        *(float *)(*(char **)(state + 0x18) + 0x18) = anchor[2];
        *(float *)(*(char **)(state + 0x18) + 0x1C) = anchor[3];
    }
    held = *(char **)(state + 0x10);
    for (count = 0, i = 0; i < 3; i++) {
        L02_003D7900_Hero *hero = &g_hero_state;

        if (i == 1) {
            held = *(char **)(state + 0x14);
        }
        if (i == 2) {
            held = *(char **)(state + 0x18);
        }
        if (held == 0) {
            continue;
        }
        *(int *)(held + 0xF0) = 0;
        *(int *)(held + 0xF4) = 0;
        *(float *)(held + 0xF8) =
            mat_fast_helper_a(hero->x - *(float *)(held + 0x10),
                          hero->y - *(float *)(held + 0x14));
        *(int *)(held + 0xFC) = 0;
        switch (*(short *)(held + 0xAA)) {
        case 0x9CA:
            armed_enemy_setup(held, 0);
            break;
        case 0xB22:
            actor_revive(held, 0);
            break;
        case 0xC3B:
            flamethrower_robot_wake(held, 0);
            break;
        case 0xC3E:
            *(float *)(held + 0x18) = *(float *)(held + 0x18) + 0.5f;
            blade_ball_wake(held, FloatToInt((float)count * 0.16666667f));
            break;
        }
    }
    *(int *)(state + 0x10) = 0;
    *(int *)(state + 0x14) = 0;
    *(int *)(state + 0x18) = 0;
}

