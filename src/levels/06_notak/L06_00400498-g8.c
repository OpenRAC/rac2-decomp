#include "names.h"
/* Update a rising platform and retire it near either endpoint. */
extern void anim_start_immediate(char *, int, int);
extern float FastDiffRots(float, float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern int PlayMobySound(int, int, char *);
extern char *D_L06_001B281C __attribute__((nosda));
extern float D_L06_001AFE40 __attribute__((sda));

void oscillating_height_update(char *object)
{
    char *state = *(char **)(object + 0x68);
    int advance;
    char *parent;
    float wave;
    if (state == 0)
        return;
    if (*(unsigned char *)(object + 0x20) == 0) {
        anim_start_immediate(object, 0, 0);
        *(int *)(object + 0x48) = 0;
        *(float *)(state + 0xc) = *(float *)(state + 4);
        *(unsigned char *)(object + 0x20) = 1;
        *(float *)(state + 8) = *(float *)(object + 0x18);
    }
    advance = 1;
    if (*(int *)state > 0) {
        parent = D_L06_001B281C + (*(int *)state << 8);
        if (parent != 0 && *(unsigned char *)(*(char **)(parent + 0x68) + 0x14) != 0)
            advance = 0;
    }
    if (FastDiffRots(*(float *)(state + 0xc), 0.0f) < D_L06_001AFE40 * 0.00029088824521750211716f ||
        FastDiffRots(*(float *)(state + 0xc), 3.14159297943115234375f) < D_L06_001AFE40 * 0.00029088824521750211716f)
        PlayMobySound(0, 0, object);
    if (advance)
        *(float *)(state + 0xc) = FastAddRotations(*(float *)(state + 0xc), D_L06_001AFE40 * 0.00029088824521750211716f);
    wave = math_fast_sin_or_cos_b(*(float *)(state + 0xc));
    *(float *)(object + 0x18) = (*(float *)(state + 8) - 2.0f) + (wave + wave);
}
