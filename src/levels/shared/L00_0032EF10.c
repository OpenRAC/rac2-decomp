#include "common.h"

typedef struct {
    char reserved000[0x18E];
    s16 head;
    s32 count;
    char reserved194[0x1E0 - 0x194];
    s32 ring[30];
} History;

extern History g_pad_state;

/* walks the 30-entry history ring back from its head (at most arg1 entries) and returns the
   first entry's mask bits, storing how far back it was */
s32 PadPressedWithin(u32 mask, s32 arg1, s32 *out)
{
    s32 n = g_pad_state.count;
    s32 i;

    if (n >= arg1)
        n = arg1;
    for (i = 1; i < n + 1; i++) {
        s32 *p = &g_pad_state.ring[(g_pad_state.head - i + 30) % 30];

        if ((*p & mask) != 0) {
            if (out != 0)
                *out = i - 1;
            return *p & mask;
        }
    }
    return 0;
}
