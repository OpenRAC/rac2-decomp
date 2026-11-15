#include "include_asm.h"

typedef int s32;
typedef unsigned char u8;

typedef struct {
    s32 pad;
    s32 first;
    s32 second;
    s32 extra;
} Entry;

/* caches the table slot the moby's vars selects, then clears the flag at the head of its
   sub-moby */
void func_L04_003A1578(u8 *moby, Entry *entries, s32 *table)
{
    u8 *vars = *(u8 **)(moby + 0x68);

    if (vars[0x14] == 0)
        *(s32 **)(moby + 0x98) = &table[entries[*(s32 *)(vars + 0x1C)].first];
    else
        *(s32 **)(moby + 0x98) = &table[entries[*(s32 *)(vars + 0x1C)].second];
    *(s32 *)(*(u8 **)(moby + 0x24) + 0x10) = 0;
}
