#include "include_asm.h"
#include "names.h"

typedef int Copy128 __attribute__((mode(TI)));

extern char *func_0029EFD0(int);
extern void func_002A0F48(void *);

/* Creates a child object of the given kind at the parent's position and rotation, scaled like the parent, and starts it in the given state. */
char *func_L00_00326620(char *parent, int kind, int state)
{
    char *child = CreateMoby(kind);
    if (child != 0) {
        *(unsigned short *)(child + 0x32) = 255;
        child[0x31] = 1;
        *(float *)(child + 0x2C) *= *(float *)(parent + 0x2C) /
            *(float *)(*(char **)(parent + 0x24) + 0x24);
        *(Copy128 *)(child + 0x10) = *(Copy128 *)(parent + 0x10);
        *(Copy128 *)(child + 0xF0) = *(Copy128 *)(parent + 0xF0);
        *(unsigned long *)(child + 0x38) = *(unsigned long *)(parent + 0x38);
        child[0x30] = state;
        *(unsigned short *)(child + 0x34) = 0;
        func_002A0F48(child);
        return child;
    } else {
        return 0;
    }
}
