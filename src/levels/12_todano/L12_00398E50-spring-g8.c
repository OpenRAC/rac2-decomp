#include "common.h"
extern float math_random_angle(void);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern int FloatToInt(float);
extern void moby_set_state(char *, int, int);
extern void part_spawn_object_following_effect(void *, char *, int, float, int, int, float, int, int, int);
extern int flag_is_third_pending_set(char *);
extern int PlayMobySound(int, int, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern char *D_0018A15C[3] __attribute__((sda));
typedef struct { unsigned short value; } Flag3D4110;
extern Flag3D4110 D_0018CA54 NOT_SDA;
extern float D_L12_001B0598 __attribute__((sda));
extern float D_L12_001B059C __attribute__((sda));
extern float D_L12_001B05A0 __attribute__((sda));
extern float D_L12_001B05A4 __attribute__((sda));
typedef struct { char pad[0x78]; int color; } Actor3D4110;
typedef int Quad3D4110 __attribute__((mode(TI)));
typedef struct { float origin[4]; float position, velocity, angle; } State3D4110;

/* Todano's copy of func_L02_003EA180: the same pulsing actor and spring-driven slide. */
/* Moby class 2731 and 2732 update: a glowing block that pulses, then slides out on a spring
   once the hero hits it. */
void pulsing_sliding_block_update(char *actor) {
    State3D4110 *vars = *(State3D4110 **)(actor + 0x68);
    Quad3D4110 offsetVec;
    int brightness;
    float slideDir;

    switch (*(u8 *)(actor + 0x20)) {
    case 0:
        vars->angle = math_random_angle();
        qcopy(vars, actor + 0x10);
        moby_set_state(actor, 1, -1);
        break;
    case 1:
        offsetVec = 0;
        ((float *)&offsetVec)[1] = -1.25f;
        ((float *)&offsetVec)[2] = -2.0f;
        vars->angle = FastAddRotations(vars->angle, 0.05235988646745682f);
        brightness = FloatToInt((math_fast_sin_or_cos_b(vars->angle) * 4.0f - 3.0f) * 208.0f);
        if (brightness > 208) brightness = 208;
        else if (brightness < 80) brightness = 80;
        if (D_0018A15C[0] != 0 && *(short *)(D_0018A15C[0] + 0xAA) == 0xA61 /* moby class 2657 */ && brightness >= 101) {
            part_spawn_object_following_effect(&offsetVec, actor, 0x20000012, 315000.0f, -1, 0, 0.0f, 15, 0, -1);
            part_spawn_object_following_effect(&offsetVec, actor, 0x20000012, 315000.0f, -1, 1, 0.0f, 15, 0, -1);
        }
        ((Actor3D4110 *)actor)->color = brightness | 0x800C0C00;
        if (flag_is_third_pending_set(actor)) {
            PlayMobySound(0, 0, actor);
            moby_set_state(actor, 2, -1);
        }
        break;
    case 2: {
        float pull, springPull;
        ((Actor3D4110 *)actor)->color = 0xFF0CFF0C;
        pull = D_L12_001B059C * 0.00027777778450399637f;
        springPull = vars->position * 0.00027777778450399637f * D_L12_001B05A0;
        pull += springPull;
        vars->velocity += pull;
        vars->position += vars->velocity;
        D_0018CA54.value = -1;
        if (vars->position > D_L12_001B0598) {
            vars->position = D_L12_001B0598;
            if (vars->velocity > 0.01666666753590107f) {
                vars->velocity *= D_L12_001B05A4;
            } else {
                vars->velocity = 0;
                moby_set_state(actor, 3, -1);
            }
        }
        slideDir = -1.0f;
        if (*(short *)(actor + 0xAA) == 0xAAC /* moby class 2732 */) slideDir = 1.0f;
        vec_scale_to_length(actor + 0x10, actor + 0xC0, slideDir * vars->position);
        FastVecAdd(actor + 0x10, actor + 0x10, vars);
        break;
    }
    }
    return;
}
