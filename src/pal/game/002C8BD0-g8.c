#include "include_asm.h"

extern int func_00282978(short *);
extern void func_00282CC0(char *, char *, char *);
extern void func_002B9180(void *);
extern unsigned char *D_001F26D0[];
extern float D_001AA384 __attribute__((sda));

void func_PAL_002C9058(char *self)
{
    char *state = self + 32;
    char *pos;

    if (func_00282978((short *)(self + 10)))
        *(float *)(state + 8) -= *(float *)(state + 24);
    pos = self + 16;
    func_00282CC0(pos, pos, state);
    func_00282CC0(pos, pos, *(char **)(state + 28));
    self[8] = (unsigned char)self[8] + *(unsigned char *)(state + 20);
    if ((unsigned char)self[2] == D_001F26D0[0][0])
        *(float *)(self + 12) += D_001AA384 * 4200.0005f;
    if (*(float *)(self + 24) < *(float *)(state + 16))
        func_002B9180(self);
}
