#include "include_asm.h"
#include "common.h"

extern void func_002A0F48(char *);

/* Sets up an object as a child of another: copies its position and rotation and links the two. */
void func_002B37E8(char *child, char *parent)
{
    *(unsigned char *)(child + 0x30) = 0xFF;
    *(short *)(child + 0x32) = 0xFF;
    *(unsigned char *)(child + 0x31) = 1;
    if (parent != 0) {
        *(char **)(child + 0xB8) = parent;
        qcopy(child + 0x10, parent + 0x10);
        qcopy(child + 0xF0, parent + 0xF0);
        *(long long *)(child + 0x38) = *(long long *)(parent + 0x38);
        func_002A0F48(child);
    }
    *(unsigned short *)(child + 0x34) &= 0xFFF8;
}
