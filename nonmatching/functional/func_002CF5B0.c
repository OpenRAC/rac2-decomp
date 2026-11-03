/* functional: high. From the near-miss draft (nonmatching/game/func_002CF5B0.c, 12 words of register choice), with its inline accessors folded into plain reads. Same reads, writes and calls in the same order as retail; retail's second test of cost against 0x5A uses the byte already loaded, as this C does. D_001A7A10[4] is retail's lh of 0x1A7A18 (the halfword at D_001A7A10 + 8), the form the repository's other C uses for it. */

#include "common.h"

typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;
typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;
typedef struct { unsigned char f0; unsigned char f1; unsigned char item; unsigned char cost; } ShopEntry;

extern SelectionCallback D_001F2840;
extern CallbackMenuState D_00138180;
extern int D_001AB9EC __attribute__((sda));
extern ShopEntry D_001ABCD0[];
extern unsigned char D_001A7A60[];
extern unsigned char D_001A7A40[];
extern short D_001A7A10[4] NOT_SDA;
extern int func_002B0E90(void);
extern int func_002E5E58(int, unsigned int, void *);
extern void func_002923C0(int);

/* Armour (shop list) menu input handler. Selection 0..11 is D_001AB9EC over the 12-entry table D_001ABCD0, skipping
   entries whose cost byte is 100. Flag 0x10: confirm the callback (copy the source's +0xE0 word, or -1 if none and no
   fallback). 0x900: close (returns 1). 0x1000/0x4000: move up/down with sound 3. 0x40: toggle the selected entry's
   item flag in D_001A7A40 if its cost is within func_002B0E90() (cost 0x5A needs D_001A7A60[0]), sound 4, and refresh
   the level state for items 2, 9, 10 and 11; otherwise sound 5. */
int func_002CF5B0(void)
{
    int result = 0;
    int limit = func_002B0E90();
    int flags = D_00138180.flags;

    if (flags & 0x10) {
        int value;

        D_001AB9EC = 0;
        value = *(int *)(D_001F2840.source + 0xE0);
        if (value != 0) {
            D_001F2840.value = value;
            return 0;
        }
        if (D_001F2840.fallback == 0) {
            return -1;
        }
        return 0;
    }

    if (flags & 0x900) {
        D_001AB9EC = 0;
        result = 1;
    } else {
        if (flags & 0x1000) {
            func_002E5E58(3, 0, 0);
            do {
                if (--D_001AB9EC < 0) {
                    D_001AB9EC = 11;
                }
            } while (D_001ABCD0[D_001AB9EC].cost == 100);
        } else if (flags & 0x4000) {
            int cur;

            func_002E5E58(3, 0, 0);
            cur = D_001AB9EC;
            do {
                if (++cur >= 12) {
                    cur = 0;
                }
            } while (D_001ABCD0[cur].cost == 100);
            D_001AB9EC = cur;
        }

        if (D_00138180.flags & 0x40) {
            int cost = D_001ABCD0[D_001AB9EC].cost;

            if ((cost != 0x5A && cost <= limit) || (cost == 0x5A && D_001A7A60[0] != 0)) {
                unsigned char *slot;
                int item;

                func_002E5E58(4, 0, 0);
                slot = &D_001A7A40[D_001ABCD0[D_001AB9EC].item];
                if (*slot) {
                    *slot = 0;
                } else {
                    *slot = 1;
                }
                item = D_001ABCD0[D_001AB9EC].item;
                if (item == 9 || item == 10 || item == 2 || item == 11) {
                    func_002923C0(D_001A7A10[4]);
                }
            } else {
                func_002E5E58(5, 0, 0);
            }
        }
    }
    return result;
}
