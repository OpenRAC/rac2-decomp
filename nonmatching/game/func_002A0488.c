/* func_002A0488 - 48 bytes, 28 places. The direct-expression form compiles
   to 36 bytes: cc1 reduces the low-word extraction to `lwu` and omits
   retail's `dsll32`/`dsrl32` pair. Lowering optimization to -O1 did not help.

   Best current-master probe: this volatile field represents the measured
   retail `ld` and `sd` of the same word, and reproduces the shifts and ORs.
   It still matches 0/28 because cc1 emits the final store at +0x24, before
   `jr $ra`, and uses a `nop` in the delay slot. Retail has a `nop` at +0x24,
   then `jr $ra` with the store in its delay slot at +0x2C. Adding the existing
   `-fno-schedule-insns` file flag leaves that output unchanged. A 29 October
   2026 replay in the original translation unit confirms these exact positions;
   an isolated `-fno-schedule-insns2` unit stays 48 bytes and 0/28 but exchanges
   the first two instructions (`dsll32` and `ld`); the store still precedes
   `jr $ra`. Stop rather than introduce an artificial operation to control
   the return slot. */
/* 3 November 2026: a non-volatile form now reproduces every retail word
   except the `nop` at +0x24 (blocker 4, "`nop` before `jr $ra`", in
   docs/contributing/matching-blockers.md). The body below, with u64 arguments and the
   duplicate-arm `if` already used by the matched neighbour func_002A0468
   (Lombyte's PackRenderCommandFields), keeps the whole-word `ld` because the
   load and the `(x << 32) >> 32` sit in different blocks when combine runs,
   so cc1 cannot narrow it to `lwu`; jump2 later merges the arms. It gives
   ld, dsll32 x3, dsll32/dsrl32, or x3, jr $ra, sd: 44/48 bytes at all 28
   places, all words equal apart from the missing `nop`. Conditioning on `a`
   instead of `packed` lets jump threading skip the `a << 32` (a branch
   remains), and `& 0xFFFFFFFF` or `(unsigned int)` build a mask or a
   truncate/extend pair. Probe only, not landable: the same body with
   `__asm__ __volatile__("nop")` before the store matches 28/28, which shows
   the nop is the only difference. -g and -Wa,--r5900-swap-branch-slots
   (volatile form: 44 bytes, no nop) do not supply it; no cc1/gas path emits
   a nop there outside short loops. rac1-decomp and Lombyte do not carry this
   body: rac1 goes from pack_render_command_fields (0x0020E340) straight to
   the handwritten blend at 0x0020E360. The neighbours that read the same
   +0x38 word are handwritten-looking (func_002A04B8 uses $at as a working
   register; func_002A04E8 is ASM_FUNC), so this setter may be handwritten
   too, but that needs a maintainer's agreement under AGENTS.md. */
#include "include_asm.h"

typedef unsigned long long u64;

void func_002A0488(u64 *command_words, u64 a, u64 b, u64 c)
{
    u64 packed = command_words[7];
    if (packed) {
        a <<= 32;
        b <<= 40;
        c <<= 48;
    } else {
        a <<= 32;
        b <<= 40;
        c <<= 48;
    }
    packed = (packed << 32) >> 32;
    packed |= a;
    packed |= b;
    packed |= c;
    command_words[7] = packed;
}
