/* func_00288308: the two per-class flag tables are sda arrays, which -G0 addresses with
 * the la macro (lui/addiu together) as retail does; func_00287FF8 returns a value (it
 * ends with daddu $v0,$s2), which keeps the final store's high half out of $v0. */
/* func_00288308 (near miss, boot 0x00288308, 220 bytes, 28 places).
 *
 * The activate arm of the class-record updaters in game/002880E0.c.  Retail:
 *   - if the byte at 0x1A7AF8[a0] is already set, return (void function);
 *   - set 0x1A7B30[a0] and 0x1A7AF8[a0] to 1, in that order;
 *   - when the record's halfword at +0x88 is non-zero and the count word at
 *     0x139688[a0] is zero, copy the halfword at +0x92 into the count (note the
 *     direction: the non-zero halfword gates the store, it is not tested as a
 *     cleared flag);
 *   - call func_002883E8 and then func_00288208 with the same id;
 *   - for id 0x10 only: when func_00288D58() is non-zero call
 *     func_00287FF8(0x10, 2) and then clear 0x1398A8, which is inside that
 *     inner if.
 *
 * Measured: -O2 -G0 -ffunction-sections, 220 bytes, exact size, 0 of 28
 * places.  Instruction at +0x8 is the first difference: retail keeps the
 * `lui`/`addiu` pair of D_001A7AF8 together before the two `sd` prologue
 * stores, this cc1 puts `sd $s0` between them, and the same hoisting
 * difference moves the two address additions (`$s0 + D_00139568` and
 * `$s0 + 0x1A7B30`) four instructions earlier in retail.  Every instruction
 * and operand otherwise agrees (including the shared `$v0 = 1` for both
 * byte stores).  `-fno-schedule-insns` reproduced the same difference.
 * Reopen only with evidence for the original statement order, e.g. a sibling
 * whose prologue has the same hoist.
 */

typedef int s32;

typedef unsigned char u8;

typedef struct {
    int word00;
    unsigned char byte04;
    unsigned char pad05[7];
    int word0C;
    unsigned char pad10[0x70];
    int word80;
    unsigned char pad84[4];
    unsigned short half88;
    unsigned char pad8A[8];
    unsigned short half92;
    unsigned char pad94[0x4C];
} ClassRecord;

extern ClassRecord D_00239BA0[];

extern unsigned char D_00139568[];

extern unsigned char D_001A7AF8[] __attribute__((sda));

extern unsigned char D_001A7B30[] __attribute__((sda));

extern int D_00139688[];

extern int D_001398A8;

extern int func_00287FF8(int, int);

extern int func_00288D58(void);

extern void func_002883E8(int);

extern void func_00288208(int);

/* Marks slot a0 as set (once only), copies a default value from its class record and runs the follow-up updates for that slot. */
void func_00288308(int a0)
{
    ClassRecord *record;

    if (D_001A7AF8[a0] != 0)
        return;
    D_001A7AF8[a0] = 1;
    D_001A7B30[a0] = 1;
    record = &D_00239BA0[D_00139568[a0]];
    if (record->half88 != 0 && D_00139688[a0] == 0)
        D_00139688[a0] = record->half92;
    func_002883E8(a0);
    func_00288208(a0);
    if (a0 == 0x10) {
        if (func_00288D58() != 0) {
            func_00287FF8(0x10, 2);
            D_001398A8 = 0;
        }
    }
}
