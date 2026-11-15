#include "names.h"
typedef unsigned char u8;
extern void *moby_get_controller(u8 *);

/* Sets the speed and turning limits in an object's movement controller. */
void moby_set_controller_speed_limits(u8 *object, float x, float y, float z, float w)
{
    char *ctl = moby_get_controller(object);
    if (ctl != 0) {
        *(float *)(ctl + 0x20) = x;
        *(float *)(ctl + 0x24) = x;
        *(float *)(ctl + 0x28) = y;
        *(float *)(ctl + 0x14) = z;
        *(float *)(ctl + 0x18) = z;
        *(float *)(ctl + 0x1C) = w;
    }
}
