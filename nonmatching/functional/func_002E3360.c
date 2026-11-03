/* functional: high. Retail is hand-written assembly with the same tests in the same order; it also reads the halfword at `end` once when the walk ends (a dead load), which this C does not. The near miss stepped the list by 4 bytes and named the table base by a ref_ name; both fixed (2-byte step, D_001B2098). */

/* For each 16-bit record index in [p, end), takes the 32-byte record at D_001B2098 + (index << 5) and clears
 * the first nibble of its halfword at +0x1E that equals `sel` (nibble 0, 1, 2 or 3, tested in that order):
 * the nibbles above it move down one place and the top nibble becomes 0xF (for nibble 3 the word just gets
 * 0xF000 or'ed in). A record whose word becomes 0xFFFF gets a byte 1 at +0x1B. */

extern unsigned char *D_001B2098 __attribute__((sda));

void func_002E3360(unsigned short *p, unsigned short *end, int sel)
{
    unsigned char *base = D_001B2098;
    int m0 = sel;
    int m1 = sel << 4;
    int m2 = sel << 8;
    int m3 = sel << 12;

    while (p != end) {
        unsigned char *rec = base + ((unsigned int)*p << 5);
        unsigned int v = *(unsigned short *)(rec + 0x1E);

        p++;
        if ((v & 0xF) == m0) {
            v = (v >> 4) | 0xF000;
        } else if ((v & 0xF0) == m1) {
            v = ((v >> 4) & 0xFF0) | ((v & 0xF) | 0xF000);
        } else if ((v & 0xF00) == m2) {
            v = ((v >> 4) & 0xF00) | ((v & 0xFF) | 0xF000);
        } else if ((v & 0xF000) == m3) {
            v |= 0xF000;
        } else {
            continue;
        }
        *(unsigned short *)(rec + 0x1E) = v;
        if (v == 0xFFFF)
            rec[0x1B] = 1;
    }
}
