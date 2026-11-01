#include "include_asm.h"

#include "common.h"
typedef struct {
    s16 id;
    u8 pad02[0xE];
    u16 flags;
    s16 base;
    s16 names[8];
    s16 kind;
    s16 index;
} Entry_29DB28;
extern Entry_29DB28 *D_001B1A58[] __attribute__((sda));

/* List the live entries: their ids (or display names), a mask of the kind-2 ones and their values. */
int func_US2_0029E960(int *ids, unsigned int *mask, int *values, int names)
{
    Entry_29DB28 *e = D_001B1A58[0];
    int n = 0;
    int all = 1;
    *ids = 0;
    if (mask) *mask = 0;
    if (values) *values = -1;
    if (e == 0) return 0;
    for (; e->id != 0; e++) {
        if (e->kind != 2 && !(e->flags & 2)) all = 0;
        if (e->flags & 2) continue;
        if (e->kind == 0) continue;
        if ((e->flags & 1) && e->kind == 2) continue;
        ids[n] = e->id;
        if (names) ids[n] = e->kind == 2 ? 0x31B9 : e->names[e->index];
        if (mask && e->kind == 2) *mask |= 1 << n;
        if (values) {
            *values = e->base + e->index;
            values++;
        }
        n++;
    }
    if (mask && all) *mask |= 0x80000000;
    return n;
}

