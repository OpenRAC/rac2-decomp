/* func_PAL_002D0500, the PAL copy of func_002CF5B0: the same C, where rename func_002923C0 becomes func_PAL_00292CD0. */
/* func_PAL_002D0500 in its own unit: retail reaches D_001AB9EC through $gp, so the file is compiled
   at -G32 (config/cflags.txt), like 002D01D0-g32.c. Menu input handler over the 12-entry table
   D_001ABCD0 (entries with cost 100 are skipped). One pointer variable holds the table base for the
   cost test and later the D_001A7A40 slot; that reuse makes the base live in two blocks, so global
   allocation puts it in $a0 as retail does. */
#include "common.h"

typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;
typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;
typedef struct { unsigned char f0; unsigned char f1; unsigned char item; unsigned char cost; } ShopEntry;

extern SelectionCallback D_001F2840;
extern CallbackMenuState D_00138180;
extern int D_001AB9EC __attribute__((sda));
extern ShopEntry D_001ABCD0[] MACRO_ADDR;
extern unsigned char D_001A7A60[] MACRO_ADDR;
extern unsigned char D_001A7A40[] MACRO_ADDR;
typedef struct { char pad0[0x20]; short level; char pad22[0x1E]; } Settings_002F9198;
extern Settings_002F9198 D_001A79F8 MACRO_ADDR;
extern int func_002B0E90(void);
extern int func_002E5E58(int, unsigned int, void *);
extern void func_PAL_00292CD0(void *);

static __inline__ ShopEntry *shop_entry(int index)
{
    return &D_001ABCD0[index];
}

static __inline__ int shop_cost(int index)
{
    return shop_entry(index)->cost;
}

static __inline__ int shop_item(int index)
{
    return shop_entry(index)->item;
}

int func_PAL_002D0500(void)
{
    int result = 0;
    int status;
    unsigned char *slot;
    int limit = func_002B0E90();
    int flags = D_00138180.flags;

    if (flags & 0x10) {
        int value, rc;
        D_001AB9EC = 0;
        value = *(int *)(D_001F2840.source + 0xE0);
        if (value != 0)
            D_001F2840.value = value;
        else if (D_001F2840.fallback == 0) {
            rc = -1;
            goto finish;
        }
        rc = 0;
finish:
        return rc;
    }
    if (flags & 0x900) {
        D_001AB9EC = 0;
        result = 1;
    } else {
        if (flags & 0x1000) {
            func_002E5E58(3, 0, 0);
            do {
                ShopEntry *table;
                if (--D_001AB9EC < 0)
                    D_001AB9EC = 11;
                table = D_001ABCD0;
                if (table[D_001AB9EC].cost != 100)
                    break;
            } while (1);
        } else if (flags & 0x4000) {
            int cur;
            ShopEntry *table;
            func_002E5E58(3, 0, 0);
            cur = D_001AB9EC;
            table = D_001ABCD0;
            do {
                if (++cur >= 12)
                    cur = 0;
            } while (table[cur].cost == 100);
            D_001AB9EC = cur;
        }
        if (D_00138180.flags & 0x40) {
            slot = (unsigned char *)D_001ABCD0;
            status = ((ShopEntry *)slot)[D_001AB9EC].cost;
            if ((status != 0x5A && status <= limit)
                || (shop_cost(D_001AB9EC) == 0x5A && D_001A7A60[0] != 0)) {
                func_002E5E58(4, 0, 0);
                slot = &D_001A7A40[shop_entry(D_001AB9EC)->item];
                if (*slot)
                    *slot = 0;
                else
                    *slot = 1;
                {
                    flags = shop_item(D_001AB9EC);
                    if (flags == 9 || flags == 10 || (unsigned char)flags == 2 || (unsigned char)flags == 11)
                        func_PAL_00292CD0((void *)(s32)D_001A79F8.level);
                }
            } else
                func_002E5E58(5, 0, 0);
        }
    }
    return result;
}
