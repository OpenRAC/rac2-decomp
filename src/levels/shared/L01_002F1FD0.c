/* func_L01_002F1FD0 (188 bytes; levels 01, 12): the nearest object of class 0xFA0 to a
   point, by func_002E3618's distance; 0 when none is nearer than 99999. The list start
   is read with the absolute macro (MACRO_ADDR), its end through $gp in the loop. */
/* flags: -O2 -G0 -ffunction-sections -frac2-zero-ti-por */
#include "common.h"

typedef int L01_1FD0TI __attribute__((mode(TI)));

extern u8 *D_L01_001B255C MACRO_ADDR;
extern u8 *D_L01_001B2560 __attribute__((sda));
extern float func_002E3618(void *a0, void *a1);

/* Finds the TV Screens object nearest to a point. Returns it, or 0 if none is close enough. */
u8 *func_L01_002F1FD0(float x, float y, float z)
{
    float queryPoint[4] __attribute__((aligned(16)));
    u8 *closest;
    float nearestDistance;
    u8 *candidate;

    *(L01_1FD0TI *)queryPoint = 0;
    queryPoint[0] = x; queryPoint[1] = y; queryPoint[2] = z;
    nearestDistance = 99999.0f;
    closest = 0;
    for (candidate = gMobyTable_L01; candidate < D_L01_001B2560; candidate += 0x100) {
        if (*(s16 *)(candidate + 0xAA) == 0xFA0 /* TV Screens */) {
            float dist = func_002E3618(queryPoint, candidate + 0x10);
            if (dist < nearestDistance) {
                nearestDistance = dist;
                closest = candidate;
            }
        }
    }
    return closest;
}
