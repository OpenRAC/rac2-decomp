#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;

/* The measured table step is 0x80 bytes; count is unspecified. */
extern char *D_L14_001B268C __attribute__((sda));
extern char g_sound_state[];
extern void math_step_value_toward_target(void *, void *, float, float, float, float);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern float math_fabs(float);
extern int PlayMobySound(int, int, void *);
extern void snd_stop_voice(int);

/* Slides a platform toward its target height, moves whatever rides on it and keeps its motion sound playing. */
void elevator_platform_move_to_target(char *self) {
    struct { Vector argument, rotation; } scratch;
    char *vars = *(char **)(self + 0x68);
    float target;
    int sound_slot;
    if (*(int *)(vars + 0x7C))
        target = *(float *)(((char (*)[0x80])D_L14_001B268C)[*(int *)(vars + 0x60)] + 0x38);
    else
        target = *(float *)(vars + 0x70);
    math_step_value_toward_target(self + 0x18, vars + 0x74, target,
                 0.0011111111f, 0.0022222222f, 1.0f);
    scratch.rotation.q = 0;
    scratch.rotation.f[2] = *(float *)(vars + 0x74);
    scratch.argument.q = scratch.rotation.q;
    mat_combine_and_store(vars + 0x20, &scratch.argument, self + 0xF0, self + 0xF0);
    if (0.01f < math_fabs(*(float *)(vars + 0x74))) {
        char *sound_entry = g_sound_state + *(int *)(vars + 0x78) * 0x70;
        if (*(char **)(sound_entry + 0x88) != self || *(unsigned char *)(sound_entry + 0x74) == 0)
            *(int *)(vars + 0x78) = PlayMobySound(0, 4, self);
    } else {
        sound_slot = *(int *)(vars + 0x78);
        if (sound_slot != -1) {
            char *sound_entry = g_sound_state + sound_slot * 0x70;
            if (*(char **)(sound_entry + 0x88) == self && *(unsigned char *)(sound_entry + 0x74) != 0)
                snd_stop_voice(sound_slot);
        }
        *(int *)(vars + 0x78) = -1;
    }
}
