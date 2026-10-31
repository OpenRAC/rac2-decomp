/* func_L20_004450D8, near miss.  Unit: a -G8 file of its own (the limit D_L20_001B2FB8 is
   read through $gp); flags -O2 -G8 -ffunction-sections.  8 differing instructions, all in
   the 11-instruction entry block; the loop (0x445108-end) is retail's instruction for
   instruction.

   Walks the id list of the object's group (byte 0x21) and, for class 0xD0F entries whose
   state has bit 0 set and word 0x420 == 1, sets the state to 2 and clears bit 1 of the
   entry's flags (0x34).

   - goto check before the for (;;): the loop note gives the body label retail's 8-byte
     alignment nop, and loop.c leaves the 0xD0F/1/2 constants in the body.
   - The test reads the index byte first as a direct compare and then as idx, so gcse's PRE
     does not move the test's lbu into the body's exits.
   Left: the entry.  Retail keeps %hi(D_L20_001FBB20) in $v1, forms the table address in
   $a0 and copies the %hi into $t0 in the b's delay slot (gcse's copy at the end of the
   entry block).  Here sched1 hoists the copy next to the lui, so the %lo lands in the
   %hi's register.  Wrapping the goto in do { } while (0) (its loop note pins the copy)
   matches 1 of 1 places, but that is an artificial block barrier (see the open row in
   docs/MATCHING-BLOCKERS.md).  The plain iterator for loop of func_L20_00440198 is far
   off (64 differing lines). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

extern u16 *D_L20_001FBB20[];
extern char *D_L20_001B2F9C;
extern int D_L20_001B2FB8 __attribute__((sda));

void func_L20_004450D8(char *arg0) {
    u16 *rec;
    u8 idx;

    if (*(u8 *)(arg0 + 0x21) == 0xFF) {
        return;
    }
    rec = D_L20_001FBB20[*(u8 *)(arg0 + 0x21)];
    goto check;
    for (;;) {
        {
            u32 idx2 = (*rec & 0x7FFF) << 8;
            char *e = D_L20_001B2F9C + idx2;
            char *o;

            if (e == 0) {
                return;
            }
            if (*(s16 *)(e + 0xAA) == 0xD0F) {
                o = *(char **)(e + 0x68);
                if (o != 0) {
                    if (*(u8 *)(o + 0x302) & 1) {
                        if (*(u32 *)(o + 0x420) != 1) {
                            goto next;
                        }
                        *(u8 *)(o + 0x302) = 2;
                        *(u16 *)(e + 0x34) &= 0xFFFD;
                    }
                }
            }
        next:
            rec++;
        }
    check:
        if (*(u8 *)(arg0 + 0x21) == 0xFF) {
            return;
        }
        idx = *(u8 *)(arg0 + 0x21);
        if (D_L20_001B2FB8 < idx) {
            return;
        }
        if (rec == 0) {
            return;
        }
        if (*(s16 *)(rec - 1) >= 0) {
            continue;
        }
        if (rec == D_L20_001FBB20[idx]) {
            continue;
        }
        return;
    }
}
