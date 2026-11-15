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

/* Updates a gauge: clamps its current value to its limit and advances its level and counters. */
void func_0028FF50(Gauge *g)
{
    unsigned char *c = g->counter;
    int max = *g->limit;
    int cur = g->current;

    g->clamped = max;
    if (cur < max)
        g->clamped = cur;
    else if (max < 0)
        g->clamped = 0;
    if (g->level >= 5) {
        g->level = 5;
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
