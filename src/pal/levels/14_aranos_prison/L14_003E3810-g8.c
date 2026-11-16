#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;
extern char *g_platform_projection_table __attribute__((sda));
extern char g_sound_state[];
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern float math_fabs(float);
extern int PlayMobySound(int, int, void *);
extern void snd_stop_voice(int);

/* Slides a platform toward its target height, moves whatever rides on it and keeps its motion sound playing. (PAL) */
void elevator_platform_move_to_target_pal(char *self) {
    struct { Vector argument, rotation; } work;
    char *state = *(char **)(self + 0x68);
    float target;
    int index;
    if (*(int *)(state + 0x7C))
        target = *(float *)(((char (*)[0x80])g_platform_projection_table)[*(int *)(state + 0x60)] + 0x38);
    else
        target = *(float *)(state + 0x70);
    math_step_value_toward_target(self + 0x18, state + 0x74, target,
                 0.0016000001f, 0.0032000002f, 1.0f);
    work.rotation.q = 0;
    work.rotation.f[2] = *(float *)(state + 0x74);
    work.argument.q = work.rotation.q;
    mat_combine_and_store(state + 0x20, &work.argument, self + 0xF0, self + 0xF0);
    if (0.01f < math_fabs(*(float *)(state + 0x74))) {
        char *entry = g_sound_state + *(int *)(state + 0x78) * 0x70;
        if (*(char **)(entry + 0x88) != self || *(unsigned char *)(entry + 0x74) == 0)
            *(int *)(state + 0x78) = PlayMobySound(0, 4, self);
    } else {
        index = *(int *)(state + 0x78);
        if (index != -1) {
            char *entry = g_sound_state + index * 0x70;
            if (*(char **)(entry + 0x88) == self && *(unsigned char *)(entry + 0x74) != 0)
                snd_stop_voice(index);
        }
        *(int *)(state + 0x78) = -1;
    }
}
