#include "include_asm.h"


typedef int TI128 __attribute__((mode(TI)));
extern void func_002AA548(char *, char *, float, float, float, float);
extern void func_002AAA00(char *, char *, float, float, float, float, int);
extern void func_002AEE70(char *, char *, char *, float, float, float);

void func_PAL_L02_003D9090(char *arg0, TI128 *arg1, float arg2, float arg3) {
    char *state = *(char **)(arg0 + 0x68);
    TI128 vec = *arg1;
    float *v = (float *)&vec;

    func_002AA548(arg0 + 0x10, state + 0x1B0, v[0], 0.036000002f, 0.036000002f, 1.8000001f);
    func_002AA548(arg0 + 0x14, state + 0x1B4, v[1], 0.036000002f, 0.036000002f, 1.8000001f);
    func_002AA548(arg0 + 0x18, state + 0x1B8, v[2], 0.036000002f, 0.036000002f, 1.8000001f);
    func_002AAA00(arg0 + 0xF8, state + 0x1C4, arg2, 0.005026549f, 0.005026549f,
                0.26529008f, 0);
    func_002AAA00(arg0 + 0xF4, state + 0x2F0, arg3, *(float *)(state + 0x124),
                *(float *)(state + 0x128), *(float *)(state + 0x12C), 0);
    func_002AEE70(arg0, state + 0x2F4, state + 0x304, 0.5f, 0.10471977f, -1.0f);
}

