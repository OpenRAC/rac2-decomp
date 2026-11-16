#include "names.h"
typedef unsigned char u8;
typedef struct { float x, y, z; } V3;
extern u8 g_hero_state[];
extern V3 g_target_point __attribute__((aligned(1)));
extern float *moby_get_private_value_0(u8 *);
extern u8 *SelectBestTargetInCone(void *, void *, float, float, float, float, float, void *, int, int, int, void *, void *);
/* Returns the player's current target if it is still alive, otherwise searches for a new one. */
u8 *moby_get_or_find_target(void *a, void *b, float d, float e, float f, float g, float h, void *c)
{
    V3 point;
    float scratch[4];
    u8 *resident = g_hero_state;
    u8 *object = *(u8 **)(resident + 0x1450);
    float *health;
    if (object != 0 && object[0x20] != 0xfe && object[0x20] != 0xfd) {
        health = moby_get_private_value_0(object);
        if (health != 0 && *health > 0.0f)
            return *(u8 **)(resident + 0x1450);
    }
    point = g_target_point;
    return SelectBestTargetInCone(a, b, d, e, f, g, h, scratch, 0, 0, 0, c, &point);
}
