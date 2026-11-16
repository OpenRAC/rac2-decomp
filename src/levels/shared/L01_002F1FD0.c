#include "names.h"
/* func_L01_002F1FD0 (188 bytes; levels 01, 12): the nearest object of class 0xFA0 to a
   point, by func_002E3618's distance; 0 when none is nearer than 99999. The list start
   is read with the absolute macro (MACRO_ADDR), its end through $gp in the loop. */
/* flags: -O2 -G0 -ffunction-sections -frac2-zero-ti-por */
#include "common.h"

typedef int L01_1FD0TI __attribute__((mode(TI)));

extern u8 *g_moby_l01_table MACRO_ADDR;
extern u8 *g_moby_l01_table_end __attribute__((sda));
extern float func_002E3618(void *a0, void *a1);

/* Finds the TV Screens object nearest to a point. Returns it, or 0 if none is close enough. */
u8 *tv_screen_find_nearest(float x, float y, float z)
{
    float query_point[4] __attribute__((aligned(16)));
    u8 *closest;
    float nearest_distance;
    u8 *candidate;

    *(L01_1FD0TI *)query_point = 0;
    query_point[0] = x; query_point[1] = y; query_point[2] = z;
    nearest_distance = 99999.0f;
    closest = 0;
    for (candidate = g_moby_l01_table; candidate < g_moby_l01_table_end; candidate += 0x100) {
        if (*(s16 *)(candidate + 0xAA) == MOBY_CLASS_TV_SCREENS) {
            float dist = func_002E3618(query_point, candidate + 0x10);
            if (dist < nearest_distance) {
                nearest_distance = dist;
                closest = candidate;
            }
        }
    }
    return closest;
}
