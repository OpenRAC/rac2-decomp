/* func_00285398 - 432 bytes.  Worker attempt, 27 October 2026 (draft below).

   Draft: 424 B vs 432. Packet stores/constants all right. Diff:
   - retail: s1=width, s0=count, s2=height (mine swaps s0/s1).
   - retail loop is NOT strength-reduced the way mine is: keeps i (slt t6,s0),
   pointer a1 += 8 after each of the two sd, lo/hi givs a2/a0 += 0x200,
   preceded by a loop-align nop. Mine reverses the counter and merges the two
   pointer increments (+0x10, offsets -8/0).
   - retail computes the loop invariants (negu width*8, (0x8000-h*8)<<16 ...)
   after the blez guard; mine too in the last version.
   Tried: index form e[i*2], pointer walk e++, explicit lo/hi locals before
   loop, expressions inside loop. */

/* replaces the func_00285398 marker in src/game/00284FC0.c */
extern void func_002FC560(int, long long);
extern char *D_001B22A8;

void func_00285398(int width, int height)
{
    int count = width / 32;
    int i;
    char *p;
    unsigned long long *q;
    unsigned long long *e;

    func_002FC560(0x42, 0x800000004AULL);
    *(int *)(D_001B22A8 + 0) = (count + 5) | 0x10000000;
    *(int *)(D_001B22A8 + 4) = 0;
    *(int *)(D_001B22A8 + 8) = 0;
    *(int *)(D_001B22A8 + 12) = (count + 5) | 0x50000000;
    p = D_001B22A8;
    D_001B22A8 = p + 16;
    q = (unsigned long long *)(p + 16);
    q[0] = 0x1000000000000001ULL;
    q[9] = 0x44;
    q[1] = 0xE;
    q[2] = 0x32003;
    q[3] = 0x47;
    q[4] = 0x2400000000000001ULL;
    q[5] = 0x10;
    q[6] = 0x146;
    q[7] = 0x80008080ULL;
    q[8] = count | 0x8000 | 0x2400000000000000ULL;
    e = (unsigned long long *)(p + 0x60);
    for (i = 0; i < count; i++) {
        *e++ = (0x8000 - width * 8 + i * 0x200) | ((long long)(0x8000 - height * 8) << 16);
        *e++ = (0x8200 - width * 8 + i * 0x200) | ((long long)(height * 8 + 0x7FF0) << 16);
    }
    D_001B22A8 = D_001B22A8 + 0x50 + count * 16;
}
