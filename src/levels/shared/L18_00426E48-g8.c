#include "names.h"
#include "moby_classes.h"
typedef short s16;
typedef int s32;
typedef float f32;
extern f32 D_L18_001B12A8 __attribute__((sda));
extern f32 D_L18_001B12AC __attribute__((sda));
extern f32 D_L18_001B12B0 __attribute__((sda));
extern f32 D_L18_001B12B4 __attribute__((sda));
extern f32 D_L18_001B12B8 __attribute__((sda));
extern f32 D_L18_001B12BC __attribute__((sda));
extern f32 vec_distance_xy(char *, char *);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 FastDiffRots(f32, f32);

/* Tests whether the target is close enough and inside this object's sight angle. */
s32 moby_is_target_in_sight(char *self, char *target) {
    f32 range = D_L18_001B12A8;
    f32 arc = D_L18_001B12AC;
    f32 distance, angle;
    s16 kind = *(s16 *)(self + 0xAA);
    if (kind == 0xED4 /* moby class 3796 */) goto special_range;
    if (kind < 0xED5) goto test_target;
    if (kind == MOBY_CLASS_RECEIVER_BOT) goto alternate_range;
    goto test_target;
special_range:
    range = D_L18_001B12B0;
    arc = D_L18_001B12B4;
    goto test_target;
alternate_range:
    range = D_L18_001B12B8;
    arc = D_L18_001B12BC;
test_target:
    distance = vec_distance_xy(self + 0x10, target + 0x10);
    angle = mat_fast_helper_a(*(f32 *)(target + 0x10) - *(f32 *)(self + 0x10),
                         *(f32 *)(target + 0x14) - *(f32 *)(self + 0x14));
    angle = FastDiffRots(*(f32 *)(self + 0xF8), angle);
    return distance < range && angle < arc;
}
