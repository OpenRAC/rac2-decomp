#include "names.h"
extern char *D_L08_001B29E8;
extern float D_L08_001AFA18 __attribute__((sda));
extern float vec_distance_xy(void *, void *);
extern int FloatToInt(float);

/* Marks nearby sandfly and dune monster mobys so they are drawn or updated, and widens their range to cover this object. */
void moby_mark_nearby_creatures_active(char *actor)
{
    char *item = D_L08_001B29E8;
    for (; item != 0; item = *(char **)(item + 0x28)) {
        int kind = *(short *)(item + 0xAA);
        if (kind == 0x942 || kind == 0x962 || kind == 0xFFF /* Mutant Sandfly */ || kind == 0x1002 /* Desert Dune Monster */) {
            float distance = vec_distance_xy(actor + 0x10, item + 0x10);
            if (distance < D_L08_001AFA18) {
                *(unsigned char *)(item + 0xBC) |= 2;
                if ((float)*(unsigned char *)(item + 0x30) < distance)
                    *(unsigned char *)(item + 0x30) = FloatToInt(distance + 5.0f);
                if ((float)*(short *)(item + 0x32) < distance)
                    *(short *)(item + 0x32) = FloatToInt(distance + 5.0f);
            }
        }
    }
}
