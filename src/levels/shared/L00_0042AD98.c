/* Clamp the listener position to the emitter box and update its sound slot. */
#include "common.h"
extern char D_L00_001B8C80_1[];
extern void func_00282CF0(char *, char *, char *);
extern void func_00282CC0_4(char *, char *, char *);
extern float func_00282C48(float);
extern void func_00283098(char *, char *, char *);
extern int func_00282948(char *);
extern int func_L00_0035F640(int, int, char *, int);
extern int func_002A77E0(int);
extern char D_00188660[];
extern char (*D_L00_001B19EC)[32] __attribute__((section(".sdata")));
void func_L00_0042AD98(char *emitter)
{
    float v[4] __attribute__((aligned(16)));
    float local[4] __attribute__((aligned(16)));
    int *state = *(int **)(emitter + 8);
    int kind = 8;
    char *sound;
    FastVecSub((char *)v, D_L00_001B8C80_1 + 0x140, emitter + 0x40);
    v[3] = 0;
    matrix_mul_vec3((char *)local, (char *)v, emitter + 0x50);
    if (FloatAbs(local[0]) <= 1.0f && FloatAbs(local[1]) <= 1.0f && FloatAbs(local[2]) <= 1.0f) {
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
    sound = gSoundState + state[4] * 0x70;
    if (*(unsigned char *)(D_L00_001B19EC[state[0]] + 0x18)) kind = 12;
    if (*(char **)(sound + 0x8C) != emitter || *(unsigned char *)(sound + 0x74) == 0) {
        if (FastFloatHelperD((char *)&state[3])) {
            state[4] = StartEffectFromTableEntry(state[0], kind, emitter, 0x400);
            if (state[2] > 0) state[3] = (int)((state[1] + RandomIntBelow(state[2] - state[1])) * 60.0f);
        } else state[4] = -1;
    }
    if (state[4] != -1) qcopy(gSoundState + 0x90 + state[4]*0x70, v);
}
