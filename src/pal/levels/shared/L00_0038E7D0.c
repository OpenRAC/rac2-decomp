#include "include_asm.h"

extern char D_00189E20[];
extern void func_0029F390(void *);
extern void func_PAL_002A7E68(void *, int, int, int);

void func_PAL_L00_0038E7D0(unsigned char *target)
{
    char *globals = D_00189E20;
    int state;
    unsigned char *source;
    int oldState;
    if (*(int *)(globals + 0x2294) == 0x37) {
        source = *(unsigned char **)(globals + 0x2290);
        oldState = source[0x43];
        state = 0xB;
        if (oldState == 0x40) state = 0x13;
        if (oldState == 0x41) state = 0x12;
        if ((unsigned int)(state - 0x12) < 2) {
            unsigned char flag;
            target[0x42] = state;
            target[0x43] = state;
            *(float *)(target + 0x44) = *(float *)(*(char **)(globals + 0x2290) + 0x44);
            target[0x40] = (*(unsigned char **)(globals + 0x2290))[0x40];
            flag = (*(unsigned char **)(globals + 0x2290))[0x41];
            target[0x41] = flag;
            if ((*(unsigned char **)(globals + 0x2290))[0x42] != (*(unsigned char **)(globals + 0x2290))[0x43])
                target[0x40] = flag;
            func_0029F390(target);
        } else func_PAL_002A7E68(target, state, 0, 6);
    } else {
        int old = target[0x43];
        if (old == 0xB || old == 0x13 || old == 0x12)
            func_PAL_002A7E68(target, 1, 0, 0xE);
    }
}

