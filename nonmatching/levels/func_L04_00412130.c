/* func_L04_00412130 - 468 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   New file src/levels/shared/L04_0040F8F0-g8.c (needs `-g8` for $gp; no
   cflags line). Structure and all instructions right (bubble sort of 21 ids).
   Needs volatile int* for the two timer-register stores (0x10000010 = 0x81,
   0x10000000 = 0), as func_L02_00332900 does; without it the stores fold to
   lui/at and reorder.
   Only difference: saved-register numbering. retail s3=list ptr, s4=owner,
   s5=loop counter; mine s3=counter, s4=list ptr, s5=owner (about 40 masked
   lines, all renames).
   Tried: index vs pointer walk for list, for-header order. */

#include "common.h"

extern char *D_L04_001B24DC __attribute__((sda));
extern char *D_L04_001B24DC_abs[] MACRO_ADDR;
extern float func_L04_00410788(char *obj, char *owner, int *a2, int *a3, int t0, int t1);

void func_L04_00412130(char *a0)
{
    char *list[21];
    char *s4;
    int *ids;
    char **lp = list;
    int count = 0;
    int i;
    int j;
    volatile int *tmr_mode = (volatile int *)0x10000010;
    volatile int *tmr_count = (volatile int *)0x10000000;

    *tmr_mode = 0x81;
    *tmr_count = 0;
    s4 = *(char **)(a0 + 0x68);
    ids = (int *)(s4 + 0x1E4);
    for (i = 20; i >= 0; i--, ids++) {
        char *obj;
        char *s0;
        if (*ids == -1)
            continue;
        obj = D_L04_001B24DC + (*ids << 8);
        s0 = *(char **)(obj + 0x68);
        *(float *)(s0 + 0x11C) = func_L04_00410788(obj, s4, (int *)(s0 + 0x120), (int *)(s0 + 0x124),
                                                   *(int *)(s0 + 0x160), *(int *)(s0 + 0x244));
        if (*(u8 *)(D_L04_001B24DC_abs[0] + (*ids << 8) + 0x20) == 2)
        {
            *lp++ = obj;
            count++;
        }
    }
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - 1 - i; j++) {
            char *cur = list[j];
            char *nxt = list[j + 1];
            if (*(float *)(*(char **)(cur + 0x68) + 0x11C) < *(float *)(*(char **)(nxt + 0x68) + 0x11C)) {
                if (!(*(int *)(*(char **)(nxt + 0x68) + 0x160) < *(int *)(*(char **)(cur + 0x68) + 0x160))) {
                    list[j] = nxt;
                    list[j + 1] = cur;
                }
            }
        }
    }
    for (i = 0; i < count; i++) {
        char *p = *(char **)(list[i] + 0x68);
        *(u8 *)(p + 0xA3) = count;
        *(u8 *)(p + 0xA2) = i + 1;
    }
}
