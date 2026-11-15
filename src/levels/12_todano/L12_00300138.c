#include "names.h"
/* Refresh the two tuning factors, or zero them on the two states that ask for it.
   The factors are two adjacent floats: the second is written as element 1 of the first's
   small-data array, which keeps its store out of the return's delay slot. */
extern char D_L12_001BDB00[];
extern float D_L12_001AD230[] __attribute__((sda));

void todano_refresh_scene_tuning(void)
{
    char *p = D_L12_001BDB00;

    if (*(int *)(p + 0x58) != 0) {
        D_L12_001AD230[0] = 0.1f;
        D_L12_001AD230[1] = 0.02f;
        return;
    }
    if ((unsigned int)(*(int *)(p + 0x30) - 3) < 2) {
        D_L12_001AD230[0] = 0.0f;
        D_L12_001AD230[1] = 0.0f;
    }
}
