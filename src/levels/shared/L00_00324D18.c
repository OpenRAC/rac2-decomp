#include "names.h"
typedef unsigned char u8;
typedef struct { float x, y, z; } V3;
extern u8 D_00189E20[];
extern V3 D_L00_001AA300 __attribute__((aligned(1)));
extern float *func_002AB1F0(u8 *);
extern u8 *func_002AF580(void *, void *, float, float, float, float, float, void *, int, int, int, void *, void *);
/* Returns the player's current target if it is still alive, otherwise searches for a new one. */
u8 *func_L00_00324D18(void *a, void *b, float d, float e, float f, float g, float h, void *c)
{
    V3 point;
    float scratch[4];
    u8 *resident = gHeroState;
    u8 *object = *(u8 **)(resident + 0x1450);
    float *health;
    if (object != 0 && object[0x20] != 0xfe && object[0x20] != 0xfd) {
        health = GetMobyPrivateValue0(object);
        if (health != 0 && *health > 0.0f)
            return *(u8 **)(resident + 0x1450);
    }
    point = D_L00_001AA300;
    return SelectBestTargetInCone(a, b, d, e, f, g, h, scratch, 0, 0, 0, c, &point);
}
