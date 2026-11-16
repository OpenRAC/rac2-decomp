#include "include_asm.h"


#include "common.h"
extern void func_002E6EF8(void (*f)(char *), char *arg);

/* shared native body of family af5b3bc3a678ed5c */
/* Sets the starting values of a new object the first time it runs. (PAL: 50 Hz values) */
void moby_init_first_frame_pal(char *object)
{
    char *o = object;
    int *vars = *(int **)(o + 104);

    if (*(unsigned char *)(o + 32))
        return;

    vars[2] = 53;
    vars[4] = 42;
    vars[0] = 0;
    vars[3] = -1;
    vars[5] = 0;
    *(unsigned char *)(o + 32) = 1;
    vars[6] = -1;

    *(float *)(o + 44) = *(float *)(*(int *)(o + 36) + 36) * 0.8f;
}

