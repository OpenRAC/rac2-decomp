#include "names.h"
/* func_PAL_L00_00430308, the PAL copy of func_L00_0042AD98: the same C with the seconds-to-frames
   factor 60 becomes 50. */
/* Clamp the listener position to the emitter box and update its sound slot. */
#include "common.h"
extern char D_L00_001B8C80_1[];
extern void FastVecSub(char *, char *, char *);
extern void func_00282CC0_4(char *, char *, char *);
extern float math_fabs(float);
extern void matrix_mul_vec3(char *, char *, char *);
extern int math_fast_float_d(char *);
extern int snd_start_from_table_entry(int, int, char *, int);
extern int math_random_int_below(int);
extern char g_sound_state[];
extern char (*g_slot_table)[32] __attribute__((section(".sdata")));
void snd_update_emitter_box_pal(char *emitter)
{
    float v[4] __attribute__((aligned(16)));
    float local[4] __attribute__((aligned(16)));
    int *state = *(int **)(emitter + 8);
    int kind = 8;
    char *sound;
    FastVecSub((char *)v, D_L00_001B8C80_1 + 0x140, emitter + 0x40);
    v[3] = 0;
    matrix_mul_vec3((char *)local, (char *)v, emitter + 0x50);
    if (math_fabs(local[0]) <= 1.0f && math_fabs(local[1]) <= 1.0f && math_fabs(local[2]) <= 1.0f) {
        qcopy(v, D_L00_001B8C80_1 + 0x140);
    } else {
        if (local[0] > 1.0f) local[0] = 1.0f;
        else if (local[0] < -1.0f) local[0] = -1.0f;
        if (local[1] > 1.0f) local[1] = 1.0f;
        else if (local[1] < -1.0f) local[1] = -1.0f;
        if (local[2] > 1.0f) local[2] = 1.0f;
        else if (local[2] < -1.0f) local[2] = -1.0f;
        matrix_mul_vec3((char *)v, (char *)local, emitter + 0x10);
        func_00282CC0_4((char *)v, (char *)v, emitter + 0x40);
    }
    sound = g_sound_state + state[4] * 0x70;
    if (*(unsigned char *)(g_slot_table[state[0]] + 0x18)) kind = 12;
    if (*(char **)(sound + 0x8C) != emitter || *(unsigned char *)(sound + 0x74) == 0) {
        if (math_fast_float_d((char *)&state[3])) {
            state[4] = snd_start_from_table_entry(state[0], kind, emitter, 0x400);
            if (state[2] > 0) state[3] = (int)((state[1] + math_random_int_below(state[2] - state[1])) * 50.0f);
        } else state[4] = -1;
    }
    if (state[4] != -1) qcopy(g_sound_state + 0x90 + state[4]*0x70, v);
}
