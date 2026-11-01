/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* func_002E3360 (264 bytes, boot 0x2E3360, 27 places)
 *
 * Draft, not matched.  The candidate compiles to 168 bytes against the retail's 264.
 *
 * The body: it walks a halfword index list, and for every index it takes the
 * 32-byte record at `base + (index << 5)`, reads the 16-bit word at +0x1E of that
 * record, and looks for the nibble that holds the selector: the low nibble
 * against `sel`, the next against `sel << 4`, the next against `sel << 8` and
 * the top one against `sel << 12`.  The nibble that matches is cleared (the top
 * nibble of the word is set to F), the word is written back, and a record whose
 * word has become 0xFFFF is flagged with a byte 1 at +0x1B.
 *
 * What matches in the candidate: the `lw $a3,0x30A8($gp)` (the table of records,
 * so the unit has to be built with -G8), the four tests in the retail's order,
 * the store of the word and the flag, and the end of the walk.
 *
 * What differs:
 *  - The retail keeps the test at the top of the loop and jumps back to it with
 *    an absolute `j` (five of them: one per case and one for the default), while
 *    the candidate rotates the loop and merges the four cases' identical tails
 *    into one block.  The retail's shape is what a loop whose body ends in a
 *    jump gets: the loop is not rotated, so the back edge stays a `jump_insn`
 *    (`j`), and the four tails are not cross-jumped because each of them ends in
 *    its own `j`.
 *  - The retail has `sll $t2,$a2,0` for the first mask: this compiler folds
 *    `x << 0` away, and `x * 1` as well (the candidate compares against $a2
 *    directly).  Either the retail's compiler did not fold it - the retail was
 *    built with the March 1999 gcc trunk, this tree uses the November 1999
 *    public EE gcc - or the source spelled the first mask differently.
 *  - The candidate's loop is 96 bytes shorter: the four cases are merged and the
 *    `sll $t2,$a2,0` and the extra `ori` are missing.
 *
 * Tried: the four cases as an if/else chain and as four `if` statements with
 * `continue`; the back edge as a `goto` to a label at the head of the loop; the
 * masks as `sel << n` and as `sel * 2^n`; the record address as `base + (idx << 5)`
 * and as a pointer variable.  None of them keeps the test at the top of the loop
 * or stops the tail merging.
 *
 * What would unblock it: a source shape whose loop body ends in a jump (so the
 * loop is not rotated) and whose four case tails are not identical (so they are
 * not cross-jumped), and a compiler that keeps `x << 0`.
 */
typedef unsigned short u16;
typedef unsigned char u8;

/* The table of 32-byte records: its address differs from program to program, so it
   has no level in its name, and it is small data, so the unit is built with -G8. */
extern int ref_L00_001B2098_00 __attribute__((sda));

void func_002E3360(u16 *p, u16 *end, int sel)
{
    int *base = ref_L00_001B2098_00;
    int mask = 0xFFFF;
    int m0 = sel << 0;
    int m1 = sel << 4;
    int m2 = sel << 8;
    int m3 = sel << 12;
    u8 one = 1;

    while (p != end) {
        u16 idx = *p;
        u8 *rec;
        u16 v;

        p += 2;
        rec = (u8 *)base + (idx << 5);
        v = *(u16 *)(rec + 0x1E);
        if ((v & 0xF) == m0) {
            v = (v >> 4) | 0xF000;
            *(u16 *)(rec + 0x1E) = v;
            if (v == mask)
                *(u8 *)(rec + 0x1B) = one;
        } else if ((v & 0xF0) == m1) {
            v = (u16)(((v >> 4) & 0xFF0) | ((v & 0xF) | 0xF000));
            *(u16 *)(rec + 0x1E) = v;
            if (v == mask)
                *(u8 *)(rec + 0x1B) = one;
        } else if ((v & 0xF00) == m2) {
            v = (u16)(((v >> 4) & 0xF00) | ((v & 0xFF) | 0xF000));
            *(u16 *)(rec + 0x1E) = v;
            if (v == mask)
                *(u8 *)(rec + 0x1B) = one;
        } else if ((v & 0xF000) == m3) {
            v |= 0xF000;
            *(u16 *)(rec + 0x1E) = v;
            if (v == mask)
                *(u8 *)(rec + 0x1B) = one;
        }
    }
}
