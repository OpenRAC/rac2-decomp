#include "include_asm.h"

extern void func_002A7398(char *, int, int);
extern float func_00283C80(float, float);
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern int func_002E5CF8(int, int, char *);
extern char *D_L06_001B281C __attribute__((nosda));
extern float D_L06_001AFE40 __attribute__((sda));

void func_PAL_L06_00404194(char *object)
{
    char *state = *(char **)(object + 0x68);
    int advance;
    char *parent;
    float wave;
    if (state == 0)
        return;
    if (*(unsigned char *)(object + 0x20) == 0) {
        func_002A7398(object, 0, 0);
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
    if (func_00283C80(*(float *)(state + 0xc), 0.0f) < D_L06_001AFE40 * 0.0003490659f ||
        func_00283C80(*(float *)(state + 0xc), 3.14159297943115234375f) < D_L06_001AFE40 * 0.0003490659f)
        func_002E5CF8(0, 0, object);
    if (advance)
        *(float *)(state + 0xc) = func_00283B98(*(float *)(state + 0xc), D_L06_001AFE40 * 0.0003490659f);
    wave = func_00283198(*(float *)(state + 0xc));
    *(float *)(object + 0x18) = (*(float *)(state + 8) - 2.0f) + (wave + wave);
}
