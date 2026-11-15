#include "common.h"

extern unsigned char *ref_L00_00329DC0_01[];
extern char ref_L00_00329DC0_00[];
extern void *D_0018C0B0;
extern int func_002761F8(void *, void *, int, void *, int);

/* The twin of func_003286D0 that also mirrors the placed vector into its state block. */
int func_00329DC0(char *self, void *arg)
{
    char *state = *(char **)(self + 0x68);
    char *object;

    if (CollLine(arg, self + 0x10, 0, self, 0) != 0) {
        object = (char *)ref_L00_00329DC0_01[0];
        if (object != 0 && (*(short *)(object + 0xAA) == 0xFB0 || object == (char *)D_0018C0B0))
            return 0;
        qcopy(self + 0x10, ref_L00_00329DC0_00);
        qcopy(state + 0x20, self + 0x10);
        return 1;
    }
    return 0;
}
