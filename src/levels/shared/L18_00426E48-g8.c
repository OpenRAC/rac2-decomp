#include "names.h"
#include "moby_classes.h"
typedef short s16;
typedef int s32;
typedef float f32;
extern f32 g_sight_range_near __attribute__((sda));
extern f32 g_sight_arc_near __attribute__((sda));
extern f32 g_sight_range_mid __attribute__((sda));
extern f32 g_sight_arc_mid __attribute__((sda));
extern f32 g_sight_range_far __attribute__((sda));
extern f32 g_sight_arc_far __attribute__((sda));
extern f32 vec_distance_xy(char *, char *);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 FastDiffRots(f32, f32);

/* Tests whether the target is close enough and inside this object's sight angle. */
s32 moby_is_target_in_sight(char *self, char *target) {
    f32 range = g_sight_range_near;
    f32 arc = g_sight_arc_near;
    f32 distance, angle;
    s16 kind = *(s16 *)(self + 0xAA);
    if (kind == 0xED4 /* moby class 3796 */) goto special_range;
    if (kind < 0xED5) goto test_target;
    if (kind == MOBY_CLASS_RECEIVER_BOT) goto alternate_range;
    goto test_target;
special_range:
    range = g_sight_range_mid;
    arc = g_sight_arc_mid;
    goto test_target;
alternate_range:
    range = g_sight_range_far;
    arc = g_sight_arc_far;
test_target:
    distance = vec_distance_xy(self + 0x10, target + 0x10);
    angle = mat_fast_helper_a(*(f32 *)(target + 0x10) - *(f32 *)(self + 0x10),
                         *(f32 *)(target + 0x14) - *(f32 *)(self + 0x14));
    angle = FastDiffRots(*(f32 *)(self + 0xF8), angle);
    return distance < range && angle < arc;
}
