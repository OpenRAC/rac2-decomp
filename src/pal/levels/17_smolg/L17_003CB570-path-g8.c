/* func_PAL_L17_003CB570, the PAL copy of func_L17_003C7498: the same C, where the 60 Hz duration becomes (d * 300 + 2) / 6. */
#include "common.h"
extern char D_00189EA0[];
extern char *D_L17_001B2D0C;
extern float D_L17_001B03B0 __attribute__((sda));
extern int func_003221C8(void *, int);
extern float func_002EF0B0(void *, void *);
extern float func_002EF4C8(float);
extern float func_002F00B0(int);
extern int func_002F00C0(float);
extern void func_002EEEE8(void *, void *, void *);
extern void func_002EEF40(void *, void *, float);
extern void func_002EEEB8(void *, void *, void *);
void func_PAL_L17_003CB570(char *self, int *path, float duration) {
    char *data = *(char **)(self + 0x68);
    float weight, part, phase;
    int index;
    float delta[4];
    if (*(int *)(data + 0xCC) != -1 && *(int *)(data + 0xAC) == 1 &&
        func_003221C8(D_00189EA0, *(int *)(data + 0xCC)) &&
        *(float *)(D_00189EA0 + 8) <= *(float *)(self + 0x18) + 0.05f &&
        func_002EF0B0(self + 0x10, D_L17_001B2D0C + *(int *)(data + 0xCC) * 128 + 0x30) <= D_L17_001B03B0) {
        *(float *)(data + 0x9C) -= 1.0f;
        goto done;
    }
    phase = (*(float *)(data + 0x9C) * 3.141593f) / ((duration * 300.0f + 2.0f) * 0.16666667f);
    weight = (1.0f - func_002EF4C8(phase)) * 0.5f;
    index = func_002F00C0(func_002F00B0(path[0] - 1) * weight);
    part = func_002F00B0(path[0] - 1) * weight - func_002F00B0(index);
    if (index == path[0] - 1) {
        qcopy(self + 0x10, (char *)path + index * 16 + 0x10);
    } else {
        func_002EEEE8(delta, (char *)path + (index * 16 + 0x20), (char *)path + (index * 16 + 0x10));
        func_002EEF40(delta, delta, part);
        func_002EEEB8(self + 0x10, delta, (char *)path + (index * 16 + 0x10));
    }
done:;
}
