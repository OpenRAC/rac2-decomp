/* functional: high. Near-miss draft within a few instructions of retail: differences are register allocation, scheduling and instruction shape. */
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
#include "include_asm.h"

struct A0488 { unsigned char pad[0x38]; volatile unsigned long long word; };

void func_002A0488(struct A0488 *p, unsigned int a, unsigned int b, unsigned int c)
{
    unsigned long long value = (p->word << 32) >> 32;
    value |= (unsigned long long)a << 32;
    value |= (unsigned long long)b << 40;
    value |= (unsigned long long)c << 48;
    p->word = value;
}
