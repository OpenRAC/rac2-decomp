/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
#include "include_asm.h"

/* Reads bytes 4, 5 and 6 of the 64-bit command-block word at +0x38. The getter and its
   callers treat the object and output pointers as ordinary memory. Current-master
   candidate, rechecked from the marker: the boot and all 27 USA v1.01 placements report
   44 bytes, expected 48 (0/28); this is not a match. Retail keeps the loaded word in $a0,
   shifts/masks into $v1/$a0/$v0 and puts the third store in the jr delay slot. This cc1
   was replayed in its original unit on 28 October 2026: it loads the word over the input
   pointer in $a0, uses $at/$v0/$v1 for the three results, writes all three before `jr`,
   and returns with a nop. All 28 places remain 0/28. The result is an allocation/schedule
   tie; no source change was retained.

   29 October 2026 equivalent byte-field probe: reading object bytes +0x3C,
   +0x3D and +0x3E directly compiles to 28/48 bytes, 0/28. It gives the same
   values for ordinary memory, but emits three `lbu` instructions and no wide
   load or shift/mask sequence; it is not a closer match.

   A 29 October declaration-order probe using the ordinary-memory wide-load
   candidate, with locals declared `third`, `second`, `first` but stores kept
   in first/second/third order, compiles to 44 bytes, 0/28. It places the third
   store in the `jr` delay slot like retail, but removes retail's preceding
   nop, loads into `$v0` instead of `$a0`, and extracts the bytes in a different
   register/order sequence.

   A 29 October isolated `-O2 -G8 -ffunction-sections -fno-schedule-insns`
   unit using that declaration order remains 44/48 bytes and 0/28. Scheduling
   changes the extraction registers, but the load still targets `$v0`, the
   preceding nop is absent, and the final store remains before `jr`; this
   profile does not recover retail's 48-byte sequence. An isolated
   `-fno-schedule-insns2` unit also remains 44/48 bytes and 0/28; disabling the
   later scheduling pass does not recover the missing four bytes. */
struct A04B8 { unsigned char pad[0x38]; unsigned long long word; };

void func_002A04B8(struct A04B8 *p, int *a, int *b, int *c)
{
    unsigned long long value = p->word;
    int first = (int)(unsigned char)(value >> 32);
    int second = (int)(unsigned char)(value >> 40);
    int third = (int)(unsigned char)(value >> 48);
    *a = first;
    *b = second;
    *c = third;
}
