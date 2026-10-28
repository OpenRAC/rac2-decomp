/* func_002DE618 - 212 bytes, 27 places (src/game/002DDEC8.c): clears bit 2 of
   the chunk table entry (D_001B1F50, five {key, flags} pairs) whose key is
   `key`; if bit 4 was set it is cleared too, and a pending flag at
   D_001F2840+0xDB is serviced through func_002B7AD0.  Returns 0.

   Best: 188 of 212 bytes (below).  Retail keeps four values in $s0-$s3: the
   owner address, the base 0x1B1F54 (built inside the loop, after the key
   matches), a byte offset that steps by 8 (the loop counter, kept because the
   final clear is `base + offset`) and the mask -3.  The key and flags walks
   are $a1/$a2 and the loop ends on the key pointer (`slt a1, a3` against
   0x1B1F78).  Every attempt merges the final clear into the flags walk, so
   the offset and base disappear and the frame is 0x20, not 0x30.

   Tried (all 176-192 bytes, same merge): pointer walks with a counter;
   array index i*2 everywhere; ((Chunk *)table)[i] for all accesses or only
   for the clear; a local `int *flags = &D_001B1F54[i*2]`; a byte-offset
   counter (below); the flags value cached in a local.  D_001B1F50 must be
   declared without sda here (block-scope extern), though func_002DE3A0 in
   the same file reaches it through $gp.

   Next: a different table type (one struct array with a third field, or the
   clear through another symbol), or the clear outside the loop after a
   break. */

#include "include_asm.h"

typedef unsigned int u32;
typedef struct {
    u32 key;
    u32 flags;
} Chunk;
typedef struct { unsigned char pad[0xDB]; unsigned char pending; } Owner;
extern int D_001F2840[];
extern void func_002B7AD0(void);

int func_002DE618(u32 key)
{
    extern int D_001B1F50[10];
    extern int D_001B1F54[10];
    int *keys = D_001B1F50;
    int *flags = D_001B1F54;
    int off;
    for (off = 0; off < 0x28; off += 8) {
        if (*keys == key && (*flags & 2)) {
            if (*flags & 4) { *flags ^= 4; if (((Owner *)D_001F2840)->pending) { func_002B7AD0(); ((Owner *)D_001F2840)->pending = 0; } }
            *(int *)((char *)D_001B1F54 + off) &= ~2;
            return 0;
        }
        keys += 2;
        flags += 2;
    }
    return 0;
}
