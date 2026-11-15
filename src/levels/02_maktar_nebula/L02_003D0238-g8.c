#include "common.h"

extern int D_L02_001B0138 __attribute__((sda));
extern int D_L02_001B013C NOT_SDA;
extern int func_L01_0031BC68(int, int, float);
extern void func_002A7750(char *, int, int);
extern void func_L00_003294F0(char *, int);
extern int func_L02_002EF388(void *, void *, void *, void *, int);

void func_L02_003D0238(char *self)
{
    char *state = *(char **)(self + 0x68);

    *(int *)(state + 0xD8) = 0;
    *(int *)(self + 0x78) = PulseColor(D_L02_001B0138, D_L02_001B013C, *(float *)(state + 0xD8));
    func_002A7750(self, 1, -1);
    qcopy(self + 0x10, state + 0xA0);
    qcopy(state + 0x60, state + 0xA0);
    qzero_nc(state + 0x50);
    self[0x31] = 1;
    *(unsigned short *)(self + 0x34) = (*(unsigned short *)(self + 0x34) & 0xFFFE) | 0x1000;
    func_L00_003294F0(self, 0);
    func_L02_002EF388(self, self + 0x10, self + 0xF0, 0, 0);
}
