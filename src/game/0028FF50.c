#include "names.h"
/* Clamps the object's current value to its limit, then either raises the first of two
   byte counters below 8 (when the 0x7C level is 5 or more) or lowers the second, then the
   first, setting the 0x6C state to 1, or to -6 once both are 0. Its entry is eight bytes
   into the catalogued row, after a leftover store and a nop of the previous body. */
typedef struct {
    char pad00[0x08];
    int current;
    int *limit;
    char pad10[0x5C];
    int state;
    unsigned char counter[4];
    int clamped;
    char pad78[4];
    int level;
} Gauge;

/* Updates the fade counters of a HUD gauge: they grow while the level is full and shrink back otherwise. */
void gauge_update_fade_counters(Gauge *gauge)
{
    unsigned char *fades = gauge->counter;
    int limitValue = *gauge->limit;
    int currentValue = gauge->current;

    gauge->clamped = limitValue;
    if (currentValue < limitValue)
        gauge->clamped = currentValue;
    else if (limitValue < 0)
        gauge->clamped = 0;
    if (gauge->level >= 5) {
        gauge->level = 5;
        if (fades[0] < 8) {
            fades[0]++;
        } else if (fades[1] < 8) {
            fades[1]++;
        }
    } else {
        gauge->state = 1;
        if (fades[1] != 0) {
            fades[1]--;
        } else if (fades[0] != 0) {
            fades[0]--;
        } else {
            gauge->state = -6;
        }
    }
}
