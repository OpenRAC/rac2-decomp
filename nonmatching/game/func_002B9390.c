/* 6 November 2026, round 6: marked ASM_FUNC in src/ (original assembly, pending maintainer review); see the src comment for the evidence. */
#include "include_asm.h"

/* func_002B9390: measured plain-C near miss, not linked.
 *
 * Compiled in src/game/002B7E28-g8.c with -O2 -G8 -ffunction-sections.
 * Current-master USA v1.01 recheck: 140 bytes and 0/28. The 0x40-byte record
 * walk, negative-flag skip, indexed handler call and prefetch are represented,
 * but the candidate starts with a stack-frame save while retail stores $ra at
 * $gp+0x2DB8. Retail also uses a GP-resident end pointer, branch-likely
 * control flow, and different loop/call register setup. Historical checks
 * reported 0/28 in PAL and USA v2.00; those ROMs are not present in this
 * checkout, so they were not rerun here.
 * Other measured forms were 164, 152 and 140 bytes (the byte-pointer form),
 * 156 bytes with a volatile handler read, and 152 bytes when storing
 * `__builtin_return_address(0)` to the GP slot.
 * The next useful experiment needs a plain-C source shape that makes this
 * compiler use the retail GP return-address slot. These trials do not establish
 * that the function is handwritten assembly.
 */

typedef struct EventRecord {
    signed char handler;
    signed char flags;
    char padding[62];
} EventRecord;

extern EventRecord *D_L00_001B1D90 __attribute__((sda));
extern int D_L00_001B1D98 __attribute__((sda));
extern EventRecord *D_L00_001B1DB0 __attribute__((sda));
extern EventRecord *D_L00_001B1DB4 __attribute__((sda));
extern void (*D_L00_001F2340[])(EventRecord *);

void func_002B9390(void)
{
    EventRecord *record;
    EventRecord *end;

    record = D_L00_001B1D90;
    end = record + D_L00_001B1D98 + 1;
    D_L00_001B1DB4 = end;
loop:
    if (record == end)
        return;
    if (record->flags < 0) {
        record++;
        goto loop;
    }
    D_L00_001B1DB0 = record + 1;
    __builtin_prefetch(record, 0, 0);
    D_L00_001F2340[record->handler](record);
    record = D_L00_001B1DB0;
    end = D_L00_001B1DB4;
    goto loop;
}
