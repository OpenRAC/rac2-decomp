/* Opus 5.5, v2133: still 112/108 bytes, 0/27 places (cc1 -fsched-verbose-5 traced).
 * Cause: sched1 issues the `a3 = block` copy (weight 0) next to the first block
 * store, ahead of the a1/a2 argument moves (weight +1), so block lives past the
 * copy and cannot tie to $a3. Reading the word into a local first adds an ALU
 * copy that delays it: with `extern u64 D_001A72C8[]` (split load) as well, block
 * lands in $a3 exactly as in retail, but the word load then issues before the
 * `D_001A72C0 = value` store, so it cannot share $a0 (lw t0 + move a0). Retail
 * needs that load ordered after the store; no alias-free C found for it.
 */
/* GPT-6.1 Sol low, v0351: 112/108 bytes, 0/27 places, -O2 -G8.
 * Corrected actual addresses: lui 0x1d/addiu -0x6e40 = 0x1c91c0;
 * lui 0x1c/lw -0xe4c = 0x1bf1b4. Earlier prose had spurious FF digits.
 * Constant ordering and early word-local trials remained 112 bytes; the
 * early local moved block into a3 but added a word-to-a0 copy.
 * Retain original body with corrected symbols; declarations included. */
#include "include_asm.h"

typedef unsigned long long u64;
typedef unsigned int u32;
typedef unsigned char u8;

extern u8 D_L00_001A9510[4] __attribute__((sda));

extern u64 D_001A72C8;
extern u32 D_001A72C0;
extern u32 D_L00_001BF1B4;
extern u64 D_L00_001C91C0[3];

extern void func_002933D0(u32, u32, void *, void *);

/* latches the incoming word, seeds the three-word block from the resident latch
   and hands both to the shared routine */
void func_L00_002FE268(u32 value)
{
    u64 previous = D_001A72C8;
    u64 *block = D_L00_001C91C0;

    D_001A72C0 = value;
    block[0] = previous;
    block[2] = 0x40000400004000ULL;
    block[1] = 0xFFA0000000E0ULL;
    func_002933D0(D_L00_001BF1B4, 0, D_L00_001A9510, block);
}
