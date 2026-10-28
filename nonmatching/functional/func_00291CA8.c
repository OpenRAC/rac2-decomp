/* functional: high. Same relocation loop, copy call and record loop as retail with the retail addresses; only the pointer-bump and register allocation differ from the bytes (fcheck SAME). */
/* func_00291CA8 (312 B, 28 places), M31 26 Oct 2026: 316 of 312 bytes at default -G0 with
   D_001B1DA4 as an sda incomplete array (tied lui/lw reads, $gp stores in the two slots).
   The relocation loop and the call match. Left: the record loop. Retail keeps one pointer
   and bumps it after each of the four loads (no giv combining) while still hoisting the
   table base and base+4 into $s4/$s5; for/do-while combine the givs (s1/s2), a goto loop
   keeps the bumps but loses the hoist (296 B). */
#include "include_asm.h"
#include "common.h"

typedef struct {
    s32 count;
    s32 pad04;
    s32 dataOffset;
    s32 dataSize;
    s32 ptrs[1];
} Reloc291CA8;

typedef struct {
    s32 a;
    s32 b;
} Pair291CA8;

extern s32 D_001B1DA4[] __attribute__((sda));
extern Pair291CA8 D_001F1F40[];
extern s32 D_001F2540[];
extern u8 D_001F2740[];

extern int func_00282A18(int);
extern void func_00282AB0(void *, void *, int);

void func_00291CA8(Reloc291CA8 *hdr, s32 base, s32 *p, s32 n) {
    s32 *src;
    s32 *dst;
    s32 i;
    s32 off;
    s32 size;
    s32 x;
    s32 y;

    src = hdr->ptrs;
    i = hdr->count;
    off = hdr->dataOffset;
    size = hdr->dataSize;
    if (i > 0) {
        dst = D_001F2540;
        do {
            if (*src == 0) {
                *dst = (s32)D_001F2740;
            } else {
                *dst = *src - (off - (s32)D_001F2740);
            }
            dst++;
            i--;
            src++;
        } while (i != 0);
    }
    func_00282AB0(D_001F2740, (u8 *)hdr + off, size);
    for (D_001B1DA4[0] = 0; D_001B1DA4[0] < n; D_001B1DA4[0]++) {
        x = *p;
        p++;
        y = *p;
        p++;
        D_001F1F40[D_001B1DA4[0]].a = ((base + x) << 4) + y;
        x = *p;
        p++;
        y = *p;
        p++;
        D_001F1F40[D_001B1DA4[0]].b = ((base + x) << 4) + func_00282A18(y);
    }
}
