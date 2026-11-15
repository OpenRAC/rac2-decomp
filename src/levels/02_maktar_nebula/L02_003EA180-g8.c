#include "common.h"
extern float math_random_angle(void);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern int FloatToInt(float);
extern void moby_set_state(char *, int, int);
extern void *part_spawn_object_following_effect(void *, char *, int, float, int, int, float, int, int, int);
extern int flag_is_third_pending_set(char *);
extern int PlayMobySound(int, int, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern char *D_0018A15C[3] __attribute__((sda));
typedef struct { unsigned short value; } FlagA180;
extern FlagA180 D_0018CA54 NOT_SDA;
extern float D_L02_001B0D40 __attribute__((sda));
extern float D_L02_001B0D44 __attribute__((sda));
extern float D_L02_001B0D48 __attribute__((sda));
extern float D_L02_001B0D4C __attribute__((sda));
typedef struct { char pad[0x78]; int color; } ActorA180;
typedef int QuadA180 __attribute__((mode(TI)));
typedef struct { float origin[4]; float position, velocity, angle; } StateA180;
/* Pulses the part's color, then springs it in and out along its axis until it
   settles. */
void tether_anchor_update(char *actor) {
    StateA180 *vars = *(StateA180 **)(actor + 0x68);
    QuadA180 offset;
    int brightness;
    float direction;

    switch (*(u8 *)(actor + 0x20)) {
    case 0:
        vars->angle = math_random_angle();
        qcopy(vars, actor + 0x10);
        moby_set_state(actor, 1, -1);
        break;
    case 1:
        offset = 0;
        ((float *)&offset)[1] = -1.25f;
        ((float *)&offset)[2] = -2.0f;
        vars->angle = FastAddRotations(vars->angle, 0.05235988646745682f);
        brightness = FloatToInt((math_fast_sin_or_cos_b(vars->angle) * 4.0f - 3.0f) * 208.0f);
        if (brightness > 208) brightness = 208;
        else if (brightness < 80) brightness = 80;
        if (D_0018A15C[0] != 0 && *(short *)(D_0018A15C[0] + 0xAA) == 0xA61 /* moby class 2657 */ && brightness >= 101) {
            part_spawn_object_following_effect(&offset, actor, 0x20000012, 315000.0f, -1, 0, 0.0f, 15, 0, -1);
            part_spawn_object_following_effect(&offset, actor, 0x20000012, 315000.0f, -1, 1, 0.0f, 15, 0, -1);
        }
        ((ActorA180 *)actor)->color = brightness | 0x800C0C00;
        if (flag_is_third_pending_set(actor)) {
            PlayMobySound(0, 0, actor);
            moby_set_state(actor, 2, -1);
        }
        break;
    case 2: {
        float force, spring;
        ((ActorA180 *)actor)->color = 0xFF0CFF0C;
        force = D_L02_001B0D44 * 0.00027777778450399637f;
        spring = vars->position * 0.00027777778450399637f * D_L02_001B0D48;
        force += spring;
        vars->velocity += force;
        vars->position += vars->velocity;
        D_0018CA54.value = -1;
        if (vars->position > D_L02_001B0D40) {
            vars->position = D_L02_001B0D40;
            if (vars->velocity > 0.01666666753590107f) {
                vars->velocity *= D_L02_001B0D4C;
            } else {
                vars->velocity = 0;
                moby_set_state(actor, 3, -1);
            }
        }
        direction = -1.0f;
        if (*(short *)(actor + 0xAA) == 0xAAC /* moby class 2732 */) direction = 1.0f;
        vec_scale_to_length(actor + 0x10, actor + 0xC0, direction * vars->position);
        FastVecAdd(actor + 0x10, actor + 0x10, vars);
        break;
    }
    }
    return;
}
