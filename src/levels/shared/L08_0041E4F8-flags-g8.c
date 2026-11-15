#include "names.h"
#include "moby_classes.h"

extern char *D_L08_001B29E8;
extern float D_L08_001AFA18 __attribute__((sda));
extern float vec_distance_xy(void *, void *);
extern int FloatToInt(float);

/* Same body as func_L08_003C63F0, with this function's own callees. */
extern float ref_L08_0041E4F8_00 __attribute__((sda));
/* Marks nearby objects of four classes as in range of the actor and grows their stored range values. */
void moby_mark_in_range(char *actor)
{
    char *item = D_L08_001B29E8;
    for (; item != 0; item = *(char **)(item + 0x28)) {
        int kind = *(short *)(item + 0xAA);
        if (kind == 0x942 /* moby class 2370 */ || kind == 0x962 /* moby class 2402 */ || kind == MOBY_CLASS_MUTANT_SANDFLY || kind == MOBY_CLASS_DESERT_DUNE_MONSTER) {
            float distance = vec_distance_xy(actor + 0x10, item + 0x10);
            if (distance < ref_L08_0041E4F8_00) {
                *(unsigned char *)(item + 0xBC) |= 2;
                if ((float)*(unsigned char *)(item + 0x30) < distance)
                    *(unsigned char *)(item + 0x30) = FloatToInt(distance + 5.0f);
                if ((float)*(short *)(item + 0x32) < distance)
                    *(short *)(item + 0x32) = FloatToInt(distance + 5.0f);
            }
        }
    }
}
