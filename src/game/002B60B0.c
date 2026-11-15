#include "names.h"
typedef unsigned char u8;
extern void *func_002B5D28(u8 *);

/* Sets the speed and turning limits in an object's movement controller. */
void func_002B60B0(u8 *object, float x, float y, float z, float w)
{
    char *ctl = GetMovementController(object);
    if (ctl != 0) {
        *(float *)(ctl + 0x20) = x;
        *(float *)(ctl + 0x24) = x;
        *(float *)(ctl + 0x28) = y;
        *(float *)(ctl + 0x14) = z;
        *(float *)(ctl + 0x18) = z;
        *(float *)(ctl + 0x1C) = w;
    }
}
