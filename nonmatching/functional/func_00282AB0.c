/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* func_00282AB0 -- the game's own memcpy, 160 bytes in retail.

   It picks the stride from the alignment of the destination, the source and
   the end address: sixteen bytes when all three are sixteen-byte aligned,
   four bytes when they are four-byte aligned, one byte otherwise.

   Current-master USA v1.01 replay in a standalone -O2 -G0 unit:
   156 bytes against retail's 160, 0/28 places.

   What differs, after this wave's measurements:

   - the block layout is now retail's: the byte loop first, then the four-byte
     loop, then the sixteen-byte loop, with the two alignment tests jumping
     forward over them.  The source has to test the sixteen-byte alignment
     first and the four-byte alignment inside it; the other nesting lays the
     blocks out in the wrong order.
   - the copied byte is loaded with `lb` when it goes through a signed char
     temporary (`s8 v = *src; *dst = v;`); `*dst = *src` makes this cc1
     widen the load to `lbu`, retail keeps `lb`.
   - the sixteen-byte copy is retail's `lq`/`sq` pair (a `mode(TI)` copy).
   - the residue: retail computes the end address with the trapping `add`
     (`add $a2,$a0,$a2`) and the strides with the trapping `addi`, this cc1
     uses `addu`/`addiu` everywhere.  Measured with the compiler itself
     (tools/probe3.c): for a signed int, an unsigned int, a `signed char *`,
     an `unsigned char *` and a `volatile` pointer this cc1 never emits the
     trapping `add`/`addi` - `addu`/`addiu` is its only 32-bit addition.
     The SDK compiler profile (build/compiler/sdk, "sdk -O2 -G0
     -ffunction-sections -fno-builtin") emits the same words.
   - retail's alignment word lives in `$v1` and the test result in `$v0`,
     this cc1 the other way round, and retail's two alignment branches are
     plain `beqz` where this cc1 emits the branch-likely `beql` with the
     target's first instruction in the delay slot.

   The trapping `add`/`addi` is the wall: no C spelling of this body reaches
   retail's bytes with this compiler.  It is also the mark the repository
   already uses for handwritten code: func_00283150, in this same file, is
   marked ASM_FUNC and its body is `add $v0,$v0,$a2` / `add $v0,$v0,$a3` with
   the same trapping additions.
*/
typedef unsigned int u32;
typedef int s32;
typedef signed char s8;
typedef int TI128 __attribute__((mode(TI)));

void func_00282AB0(s8 *dst, s8 *src, s32 len) {
    s8 *end = dst + len;
    u32 align;

    if (len == 0) {
        return;
    }
    align = (u32)dst | (u32)src | (u32)end;
    if (align & 0xF) {
        if (align & 3) {
            do {
                s8 v = *src;
                *dst = v;
                dst++;
                src++;
            } while (dst != end);
        } else {
            do {
                *(s32 *)dst = *(s32 *)src;
                dst += 4;
                src += 4;
            } while (dst != end);
        }
    } else {
        do {
            *(TI128 *)dst = *(TI128 *)src;
            dst += 16;
            src += 16;
        } while (dst != end);
    }
}
