#include "names.h"
extern void *moby_get_private_value_4(void *);
extern float gravity_get_center_distance(void *);
extern int D_001A8CA0 __attribute__((sda));

/* Compares the object's float at 0x18 with the partner's float at 0x90 and, when the
   object is still smaller, with the found object's float at 0x40 less half; the
   float that is compared comes from the helper at 0x10 when the resident flag is
   set and from the object itself otherwise. */
/* Tells whether the object is well above the ground it is standing over. */
int coll_is_object_well_above_ground(void *self, void *ctl)
{
    void *ground;
    int result;
    float f;

    if (*(float *)((char *)self + 0x18) <= *(float *)((char *)ctl + 0x90)) {
        return 0;
    }
    ground = moby_get_private_value_4(self);
    if (ground == 0) {
        return 0;
    }
    result = 0;
    if (D_001A8CA0 != 0) {
        f = gravity_get_center_distance((char *)self + 0x10);
        if (f < *(float *)((char *)ground + 0x40) - 0.5f) {
            result = 1;
        }
    } else {
        f = *(float *)((char *)self + 0x18);
        if (f < *(float *)((char *)ground + 0x40) - 0.5f) {
            result = 1;
        }
    }
    return result;
}
