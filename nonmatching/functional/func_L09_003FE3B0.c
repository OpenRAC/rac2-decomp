/* functional: high. Near-miss draft within a few instructions of retail: differences are register allocation, scheduling and instruction shape. */
/* func_L09_003FE3B0 (288 bytes, 1 place) -- NEAR MISS, not integrated.
   state: 296 bytes, 8 over retail's 288; the frame, the prologue, the epilogue, the
   track walk and the float compare are retail's; what is left is the twenty-entry
   screen-table scan in the loop body.
   check.py (09_dobbo), with the source below:
     09_dobbo: 296 bytes, expected 288
   The eight extra bytes are two instructions: retail's peeled first iteration of the
   screen scan ends in the same "found" block as the loop's own exit, this cc1 copies it
   (so the peel's `found = 1` and its jump are two extra instructions), and it computes
   `q + 1` twice (retail once, in the beq's delay slot).

   What is measured and right:
   - the frame is 0x50 and the saved set $s0-$s6 + $ra is retail's, once the entity base
     is read through `D_L09_001B285C_1[0]` (the array form): a plain
     `extern char *D_L09_001B285C` gives `lui $s7; lw $v1,0($s7)` (the %hi hoisted into a
     saved register) against retail's `lui $a1,0x1B; lw $a1,0x285C($a1)`, and the extra
     $s7 makes the frame 0x60 and 316 bytes.
   - `D_L09_001B9A00` is an object, not a pointer: retail computes its address
     (`addiu $a0,$s6,-0x6600`) where a pointer declaration would load the word at it.
   - the table is `int D_L09_00257110[20]`, indexed: retail loads screen[0] with
     `lw $a0,0x7110($s4)` and the rest with `sll $v0,$a2,2; addu $v0,$v0,$s3`.
   - the track walk is `while ((short)*q++ >= 0)`, the same spelling as the matched
     func_L09_003F87D8 in src/levels/shared/L09_002B7238.c: the load of the halfword is
     the loop's condition and the pointer advances in the branch delay slot.
   - the call is `func_00282E80(D_L09_001B9A00, r + 0x10)`, and the compare is
     `if (bestf < f)`, which is retail's `c.lt.s $f20,$f0` + `bc1f`.
   Tried and not enough: the scan as `for (i = 0; i < 20; i++)` with `found` set inside
     (this cc1 peels two iterations and copies the exit block); the same loop with
     `found = (i < 20)` after it (the exit block is shared, but the flag then costs a
     `slti`/`bnel` instead of retail's constant 1, and the table access becomes a pointer
     walk); a do-while over the scan; `continue` instead of `break`; the scan and the
     found flag at function scope or block scope (same bytes).
   Next idea: a source whose peeled first iteration ends in the loop's own exit block and
   still stores the constant 1 there. The 284-byte variant
   (`found = (i < 20)` after the scan) is the closest measured shape for the exit block. */

extern unsigned char *D_L09_001B285C_1[3] __attribute__((sda));
extern short *D_L09_001FB560[];
extern int D_L09_00257110[];
extern char D_L09_001B9A00[];

extern float func_00282E80(void *, void *);

/* Walks the record's track while its signed halfwords stay non-negative and returns the
   entry whose measured value is largest, skipping the entries whose field 0xB2 is in the
   twenty-value screen table. */
void *func_L09_003FE3B0(int index, int *table)
{
    unsigned short *q = (unsigned short *)D_L09_001FB560[index];
    char *r;
    void *best = 0;
    float bestf = 0.0f;
    int found;
    int i;

    if (q == 0)
        return 0;
    do {
        found = 0;
        i = 0;
        r = (char *)D_L09_001B285C_1[0] + ((q[0] & 0x7FFF) << 8);
        for (i = 0; i < 20; i++) {
            if (*(short *)(r + 0xB2) == D_L09_00257110[i]) {
                found = 1;
                break;
            }
        }
        if (found == 0) {
            float f = func_00282E80(D_L09_001B9A00, r + 0x10);
            if (bestf < f) {
                bestf = f;
                best = r;
            }
        }
    } while ((short)*q++ >= 0);
    return best;
}
