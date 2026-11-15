#include "include_asm.h"
#include "names.h"

extern int FastDecTimer(short *);
extern void FastVecAdd(char *, char *, char *);
extern void part_kill(void *);
extern unsigned char *D_001F2608[];
extern float D_001AA384 __attribute__((sda));

void func_PAL_002C2CD0(char *self)
{
    char *state = self + 32;
    if (FastDecTimer((short *)(self + 10)))
        *(float *)(state + 8) -= *(float *)(state + 24);
    FastVecAdd(self + 16, self + 16, state);
    self[8] = (unsigned char)self[8] + *(unsigned char *)(state + 20);
    if ((unsigned char)self[2] == D_001F2608[0][0])
        *(float *)(self + 12) += D_001AA384 * 4200.0005f;
    if (*(float *)(self + 24) < *(float *)(state + 16))
        part_kill(self);
}
