#include "include_asm.h"

extern int func_00282978(short *);
extern void func_00282CC0(char *, char *, char *);
extern void func_002B9180(void *);
extern unsigned char *D_001F2608[];
extern float D_001AA384 __attribute__((sda));

void func_PAL_002C2CD0(char *self)
{
    char *state = self + 32;
    if (func_00282978((short *)(self + 10)))
        *(float *)(state + 8) -= *(float *)(state + 24);
    func_00282CC0(self + 16, self + 16, state);
    self[8] = (unsigned char)self[8] + *(unsigned char *)(state + 20);
    if ((unsigned char)self[2] == D_001F2608[0][0])
        *(float *)(self + 12) += D_001AA384 * 4200.0005f;
    if (*(float *)(self + 24) < *(float *)(state + 16))
        func_002B9180(self);
}
