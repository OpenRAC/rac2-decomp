#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef int s32;
typedef int Quadword __attribute__((mode(TI)));
extern char *CreateMoby(short);
extern void moby_init_child_from_parent(char *, char *);
extern float fast_subtract_rotations(float, float);
extern void moby_set_state(char *, s32, s32);
extern int flag_is_third_pending_set(u8 *);
extern int flag_set_first_pending(u8 *);
extern void PlayMobySound(s32, s32, char *);
extern void moby_mark_spawned(char *);
extern float math_step_value_toward_target(float *, float *, float, float, float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);

typedef struct { char *child; float velocity; } ChildMotion;

/* Swings a lever-like part up and down in steps and keeps its child object attached. */
void swinging_l16_arm_update(char *object)
{
    ChildMotion *vars = *(ChildMotion **)(object + 0x68);
    union { Quadword q; float f[4]; } offset;
    if (vars == 0) {
        moby_init_child_from_parent(CreateMoby(0xe7f), object);
        moby_mark_spawned(object);
        return;
    }
    switch (*(u8 *)(object + 0x20)) {
    case 0: {
        float size;
        *(float *)(object + 0xf0) = fast_subtract_rotations(*(float *)(object + 0xf8), 1.5707964897155762f);
        moby_init_child_from_parent((vars->child = CreateMoby(0x99d)), object);
        size = *(float *)(*(char **)(vars->child + 0x24) + 0x24);
        *(float *)(vars->child + 0x2c) = size + size;
        moby_set_state(object, 1, -1);
        break;
    }
    case 1:
        if (flag_is_third_pending_set((u8 *)vars->child)) {
            PlayMobySound(0, 0, object);
            moby_set_state(object, 2, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending((u8 *)object)) PlayMobySound(0, 0, object);
        math_step_value_toward_target((float *)(object + 0xf0), &vars->velocity, 0.0f, 0.0005332950968295336f, 174.53294372558594f, 290.8882751464844f);
        if (*(float *)(object + 0xf0) <= 0.0f) {
            *&vars->velocity = 0.0f;
            PlayMobySound(1, 0, object);
            moby_set_state(object, 7, -1);
        }
        break;
    case 3:
        if (flag_set_first_pending((u8 *)object)) PlayMobySound(1, 0, object);
        math_step_value_toward_target((float *)(object + 0xf0), &vars->velocity, 0.4363323450088501f, 0.01745329424738884f, 0.0004363323678262532f, 0.872664749622345f);
        if (0.4363323450088501f <= *(float *)(object + 0xf0)) {
            *&vars->velocity = 0.0f;
            moby_set_state(object, 4, -1);
        }
        break;
    case 4:
        math_step_value_toward_target((float *)(object + 0xf0), &vars->velocity, 0.0f, 0.0004363323678262532f, 0.174532949924469f, 2.9088826179504395f);
        if (*(float *)(object + 0xf0) <= 0.0f) {
            *&vars->velocity = 0.0f;
            PlayMobySound(1, 0, object);
            moby_set_state(object, 5, -1);
        }
        break;
    case 5:
        if (flag_set_first_pending((u8 *)object)) PlayMobySound(1, 0, object);
        math_step_value_toward_target((float *)(object + 0xf0), &vars->velocity, 0.2617994248867035f, 0.01745329424738884f, 0.0004363323678262532f, 0.872664749622345f);
        if (0.2617994248867035f <= *(float *)(object + 0xf0)) {
            *&vars->velocity = 0.0f;
            moby_set_state(object, 6, -1);
        }
        break;
    case 6:
        math_step_value_toward_target((float *)(object + 0xf0), &vars->velocity, 0.0f, 0.0004363323678262532f, 0.174532949924469f, 2.9088826179504395f);
        if (*(float *)(object + 0xf0) <= 0.0f) {
            *&vars->velocity = 0.0f;
            PlayMobySound(1, 0, object);
            moby_set_state(object, 7, -1);
        }
        break;
    case 7:
        if (flag_set_first_pending((u8 *)object)) PlayMobySound(1, 0, object);
        math_step_value_toward_target((float *)(object + 0xf0), &vars->velocity, 0.0872664749622345f, 0.01745329424738884f, 0.0004363323678262532f, 0.872664749622345f);
        if (0.0872664749622345f <= *(float *)(object + 0xf0)) {
            *&vars->velocity = 0.0f;
            moby_set_state(object, 8, -1);
        }
        break;
    case 8:
        math_step_value_toward_target((float *)(object + 0xf0), &vars->velocity, 0.0f, 0.0004363323678262532f, 0.174532949924469f, 2.9088826179504395f);
        if (*(float *)(object + 0xf0) <= 0.0f) {
            *&vars->velocity = 0.0f;
            PlayMobySound(1, 0, object);
            moby_set_state(object, 9, -1);
        }
        break;
    case 9:
        if (flag_set_first_pending((u8 *)object)) PlayMobySound(1, 0, object);
        math_step_value_toward_target((float *)(object + 0xf0), &vars->velocity, 0.03490658849477768f, 0.01745329424738884f, 0.0004363323678262532f, 0.872664749622345f);
        if (0.03490658849477768f <= *(float *)(object + 0xf0)) {
            *&vars->velocity = 0.0f;
            moby_set_state(object, 10, -1);
        }
        break;
    case 10:
        math_step_value_toward_target((float *)(object + 0xf0), &vars->velocity, 0.0f, 0.0004363323678262532f, 0.174532949924469f, 2.9088826179504395f);
        break;
    }
    *(Quadword *)(vars->child + 0x10) = *(Quadword *)(object + 0x10);
    offset.q = 0;
    offset.f[1] = 8.0f;
    offset.f[2] = -0.5f;
    matrix_mul_vec3(&offset, &offset, object + 0xc0);
    FastVecAdd(vars->child + 0x10, vars->child + 0x10, &offset);
}
