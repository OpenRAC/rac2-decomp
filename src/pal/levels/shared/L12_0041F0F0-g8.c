#include "include_asm.h"

#include "common.h"
extern float D_L12_001B1C74 __attribute__((sda));
extern float D_L12_001B1C70 __attribute__((sda));
extern u8 D_L12_001B9E00[];
extern void func_002A7750(char *, int, int);
extern void func_PAL_002A7E68(char *, int, int, int);
extern void func_002B60B0(char *, float, float, float, float);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(char *);

void func_PAL_L12_0041F568(char *self) {
    char *state = *(char **)(self + 0x68);
    float rate;

    if (*(u8 *)(self + 0x20) == 0) {
        *(u8 *)(self + 0x30) = 0xC8;
        *(u16 *)(self + 0x32) = 0xC8;
        qcopy(state + 0x210, self + 0x10);
        *(float *)(state + 0x21C) = *(float *)(self + 0xF8);
        *(int *)(self + 0x98) = 0;
        *(u16 *)(self + 0x34) = (*(u16 *)(self + 0x34) | 0x41) & 0xEFFF;
        func_002A7750(self, 1, 0);
        if (*(u8 *)(self + 0x43) != 0) {
            func_PAL_002A7E68(self, 0, 0, 0);
        }
        {
            float half = 0.5f;
            float quarter = 0.25f;
            float fraction = 0.4f;
            float turn = 0.261799425f;
            float step = 0.008f;
            float pi = 3.14159012f;
            rate = D_L12_001B1C74 * 0.020000001f;
            *(float *)(state + 0x154) = quarter;
            *(float *)(state + 0x120) = fraction;
            *(float *)(state + 0x12C) = *(float *)(state + 0x128) = *(float *)(state + 0x124) = half;
            *(float *)(state + 0x150) = turn;
            *(float *)(state + 0x14C) = step;
            *(int *)(state + 0x15C) = -1;
            *(float *)(state + 0x130) = pi;
        }
        func_002B60B0(self, 0.012800001f, rate, 0.005026549f, 0.25132746f);
        *(int *)(state + 0x11C) = 0;
        *(int *)(state + 0x258) = 0;
    }
    *(float *)(self + 0x2C) = *(float *)(*(char **)(self + 0x24) + 0x24) * D_L12_001B1C70;
    if (*(u8 *)(self + 0x31) != 0) {
        if (func_00282E48(self + 0x10, D_L12_001B9E00) < 24.0f) {
            func_002A93B0(self);
            *(u8 *)(self + 0x6F) = 0x16;
        }
    }
}
