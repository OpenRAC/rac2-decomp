/* Nonmatching: 332/328 bytes.
 * Profile: -O2 -G8 -ffunction-sections.
 * Placement checks: US: 0/1; US2: 0/1; PAL: 0/1.
 * 332/328 bytes. The complete prefix and count-up copy loop agree until an additional NOP at +0x10c shifts the back edge and epilogue. The reviewed qcopy emits two words but is counted as one instruction by post-DBR loop padding (MATCHING-BLOCKERS section30). The subtraction scratch now reserves the full16 bytes written by the callee.
 * Reopen with an independently qualified loop-padding/compiler profile or meaningful loop source change. Indexed helpers and the grouped TI/barrier profile retain this extra NOP; no dummy padding is added.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void *func_0029EFD0(int);
extern void func_002B37E8(void *, void *);
extern void func_00282CF0(float *, void *, void *);
extern float func_00282E20(float *);
extern float func_00283248(float, float);
extern float func_002A7878(float, float);
extern float D_L20_001B1F98 __attribute__((sda));


char *func_L20_0043F318(char *arg0, char *arg1, int arg2, int arg3, int arg4, float f) {
    char *obj = (char *)CreateMoby(0x119D);
    char *state;
    float v[4] __attribute__((aligned(16)));
    float r;
    float timer;
    int i;

    if (obj == 0) {
        goto out;
    }
    func_002B37E8(obj, arg0);
    qcopy(obj + 0x10, arg1);
    FastVecSub(v, (void *)(obj + 0x10), arg0 + 0x10);
    state = *(char **)(obj + 0x68);
    *(float *)(state + 0x40) = vec_length_xy(v);
    *(float *)(state + 0x44) = func_00283248(v[0], v[1]);
    *(float *)(state + 0x5C) = *(float *)(arg0 + 0x18);
    r = func_002A7878(1.0f, 4.0f);
    *(float *)(state + 0x4C) = *(float *)(state + 0x5C) + r;
    r = func_002A7878(0.0f, 1.0f);
    timer = D_L20_001B1F98 + r;
    *(int *)(state + 0x64) = arg2;
    *(int *)(state + 0x68) = arg3;
    *(int *)(state + 0x6C) = arg4;
    *(float *)(state + 0x70) = f;
    *(float *)(state + 0x48) = timer;
    for (i = 0; i < 3; i++) {
        qcopy(state + 0x10 + i * 0x10, arg1);
    }
out:
    return obj;
}
