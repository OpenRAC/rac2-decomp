#include "include_asm.h"

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

void func_PAL_002907D0(Gauge *g)
{
    unsigned char *c = g->counter;
    int max = *g->limit;
    int cur = g->current;

    g->clamped = max;
    if (cur < max)
        g->clamped = cur;
    else if (max < 0)
        g->clamped = 0;
    if (g->level >= 4) {
        g->level = 4;
        if (c[0] < 8) {
            c[0]++;
        } else if (c[1] < 8) {
            c[1]++;
        }
    } else {
        g->state = 1;
        if (c[1] != 0) {
            c[1]--;
        } else if (c[0] != 0) {
            c[0]--;
        } else {
            g->state = -6;
        }
    }
}

