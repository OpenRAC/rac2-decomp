#include "include_asm.h"

typedef int Quadword89F80 __attribute__((mode(TI)));
extern float func_00282DB0(void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002A7750(void *, int, int);
extern int func_002AD0E0(void *, void *, void *, void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);
extern int func_L02_004127F8(char *);
extern char *ref_L12_00389F80_00 __attribute__((sda));
extern char *ref_L12_00389F80_01;
extern float ref_L12_00389F80_02 __attribute__((sda));
extern float ref_L12_00389F80_03 __attribute__((sda));

/* Per-state step of a homing object: state 0 starts it, state 1 steers it by the thing it
   follows (or just turns it) and then spins a short delay loop. */
void func_PAL_L12_0038CD10(char *object) {
    char *state = *(char **)(object + 0x68);
    float a[4];
    float b[4];
    float c[4];
    float dot;
    int i;

    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        *(unsigned int *)(state + 0x5C) |= 4;
        *(short *)(object + 0x7C) = 3;
        func_002A7750(object, 1, -1);
        break;
    case 1:
        if (*(int *)(state + 0xE0) == -1 ||
            func_L02_004127F8(ref_L12_00389F80_00 + (*(int *)(state + 0xE0) << 8)) == 0) {
            func_00282F20(state + 0x30, object + 0xD0, -(ref_L12_00389F80_02 * 0.020000001f));
            *(float *)(object + 0x48) = ref_L12_00389F80_03;
        } else {
            func_002AD0E0(object, ref_L12_00389F80_01 + (*(int *)(state + 0xE0) << 8), object + 0x10,
                          object + 0xF0, a, b);
            a[2] = 0.0f;
            func_00282CF0(c, a, object + 0x10);
            *(Quadword89F80 *)a = *(Quadword89F80 *)c;
            a[2] = 0.0f;
            b[0] = func_00283180(*(float *)(object + 0xF8) + 4.7123895f);
            b[1] = func_00283198(*(float *)(object + 0xF8) + 4.7123895f);
            b[2] = 0.0f;
            dot = func_00282DB0(a, b);
            c[0] = func_00283180(*(float *)(object + 0xF8)) * dot * 0.1f;
            c[1] = func_00283198(*(float *)(object + 0xF8)) * dot * 0.1f;
            c[2] = 0.0f;
            func_002AD6F0(state + 0x20, c, object + 0xF0, object + 0xF0);
            *(float *)(object + 0x48) = dot * 49.999996f;
        }
        i = 6;
        while (--i >= 0)
            ;
        break;
    }
}
