/* functional: high. Retail is hand-written assembly that keeps $ra in the $gp slot 0x1B1DA8 (sd/ld) instead of a stack frame, and prefetches the next record; this C keeps a normal frame and drops the prefetch (no state). It still stores its return address in 0x1B1DA8 as retail does: only this function's own epilogue reads that slot, so on the host the store is dead and may be dropped (the gate then differs only in that word). */

/* Walks the 0x40-byte records from D_001B1D90 to the inclusive high-water slot D_001B1D98, skipping those whose
 * flags byte (+1) is negative, and calls D_001F2340[record->handler](record) for each. The cursor and end are kept
 * in D_001B1DB0[0] / [1] and reloaded after every call, so a handler may move them. */

typedef struct EventRecord {
    signed char handler;
    signed char flags;
    char padding[62];
} EventRecord;

extern EventRecord *D_001B1D90 __attribute__((sda));
extern int D_001B1D98 __attribute__((sda));
/* [0] the next record, [1] the end (0x1B1DB4) */
extern EventRecord *D_001B1DB0[2] __attribute__((sda));
extern long D_001B1DA8 __attribute__((sda));
extern void (*D_001F2340[])(EventRecord *);

void func_002B9390(void)
{
    EventRecord *record;
    EventRecord *end;

#ifndef OPENRAC_HOSTGEN
    /* retail parks $ra in this $gp word; only its own epilogue reads it back, so the port leaves it out */
    D_001B1DA8 = (long)(int)__builtin_return_address(0);
#endif
    record = D_001B1D90;
    end = record + D_001B1D98 + 1;
    D_001B1DB0[1] = end;
    while (record != end) {
        if (record->flags < 0) {
            record++;
            continue;
        }
        D_001B1DB0[0] = record + 1;
        D_001F2340[record->handler](record);
        record = D_001B1DB0[0];
        end = D_001B1DB0[1];
    }
}
