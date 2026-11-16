#include "include_asm.h"
#include "names.h"

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

/* Updates the fade counters of a HUD gauge: they grow while the level is full and shrink back otherwise (PAL: full at 4). */
void gauge_update_fade_counters_pal(Gauge *gauge)
{
    unsigned char *fades = gauge->counter;
    int limit_value = *gauge->limit;
    int current_value = gauge->current;

    gauge->clamped = limit_value;
    if (current_value < limit_value)
        gauge->clamped = current_value;
    else if (limit_value < 0)
        gauge->clamped = 0;
    if (gauge->level >= 4) {
        gauge->level = 4;
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

