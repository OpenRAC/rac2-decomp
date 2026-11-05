#include "common.h"


struct Slot { int w; int rest[4]; };
struct Table1 { char pad[19264]; struct Slot slots[48]; };
struct Table2 { char pad[52]; int slots[4]; };
extern struct Table1 D_0014B540;
extern struct Table2 D_00152CD0;
extern int func_00294630(int);
extern void func_00294398(int, int);

typedef struct { char pad[20]; int value; char rest[200]; } CacheRecord;
extern CacheRecord D_00239BA0[];
extern unsigned char D_00139568[];
typedef struct { char pad[0x22C8]; int cur; char pad2[0x22E4 - 0x22CC]; int primary; } CacheHero;
extern CacheHero D_00189E20;
extern short D_001A63AC;
extern int D_001A7398 __attribute__((sda));
extern int D_001A7A04 __attribute__((sda));

void func_00294420(int value)
{
    int a, b, i, sa, sb;

    if (func_00294630(value))
        return;
    if (D_001A63AC)
        return;
    i = 0;
    {
        CacheHero *hero = &D_00189E20;
        int p = hero->primary;
        int q = D_001A7398;
        CacheRecord *rec = &D_00239BA0[D_00139568[p]];
        CacheRecord *rec2 = &D_00239BA0[D_00139568[q]];

        a = rec->value;
        b = rec2->value;
    }
    if (b == a) {
        CacheRecord *rec = &D_00239BA0[D_00139568[D_001A7A04]];

        b = rec->value;
    }
    sb = -1;
    if (a == value)
        a = -1;
    if (b == value)
        b = -1;
    sa = -1;
    for (; i < 3; i++) {
        struct Table2 *cache = &D_00152CD0;
        /* A cache slot may be -1. Its word belongs to the preceding part of
           the complete table owner, not to slots[-1]. */
        int v = *(int *)((char *)&D_0014B540 + (0x4B40 + cache->slots[i] * 20));

        if (a == v)
            sa = i;
        if (b == v)
            sb = i;
    }
    for (i = 0; i == sa || i == sb; i++)
        ;
    {
        CacheHero *hero = &D_00189E20;
        int cur = hero->cur;

        if (cur) {
            struct Table2 *cache = &D_00152CD0;
            int k = cache->slots[i];

            if (k != -1) {
                struct Table1 *toc = &D_0014B540;
                CacheRecord *rec = &D_00239BA0[D_00139568[cur]];

                if (rec->value == toc->slots[k].w)
                    hero->cur = 0;
            }
        }
    }
    func_00294398(value, i);
}
