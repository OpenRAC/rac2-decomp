#include "common.h"
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_001163B0(void);
extern char D_00189EA0[];
extern char *D_L08_001FE7BC;
extern char *D_L08_001B29DC[] __attribute__((sda));
extern void func_L01_00337A60(void *, void *, void *, int);
extern int func_L01_003165E8(void *, int, int, int, int);

void func_L08_003D8AB0(char *object)
{
    char *state = *(char **)(object + 0x68);
    if (*(int *)(state + 0x428) == -1) {
        func_L01_00337A60(state + 0x3F0, state + 0x3F0, D_L08_001FE7BC + 0x10, *(int *)D_L08_001FE7BC);
        return;
    }
    {
        char *pos = state + 0x3F0;
        char *target = pos;
        if (func_L01_003165E8(state + 0x3F0, *(int *)(state + 0x428), -1, -1, -1)) return;
        if ((func_001163B0() & 1) || *(int *)(state + 0x254) == 2 || *(int *)(state + 0x44C)) {
            if (*(int *)(state + 0x404) == -1 || (func_001163B0() & 1)) {
                qcopy(target, state + 0x3E0);
            } else {
                *(float *)(state + 0x3F0) = func_00283180(func_002A7878(-3.1415927f, 3.1415927f)) * 3.0f;
                {
                    float y = func_00283198(func_002A7878(-3.1415927f, 3.1415927f)) * 3.0f;
                    int handle = *(int *)(state + 0x404);
                    char *entry = D_L08_001B29DC[0];
                    *(float *)(state + 0x3F8) = 0;
                    *(float *)(state + 0x3F4) = y;
                    FastVecAdd(target, target, entry + (handle << 8) + 0x10);
                }
            }
        } else {
            *(float *)(state + 0x3F0) = func_00283180(func_002A7878(-3.1415927f, 3.1415927f)) * 3.0f;
            *(float *)(state + 0x3F4) = func_00283198(func_002A7878(-3.1415927f, 3.1415927f)) * 3.0f;
            *(float *)(state + 0x3F8) = 0;
            FastVecAdd(pos, pos, D_00189EA0);
        }
    }
}
