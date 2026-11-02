/* functional: high. Near-miss draft within a few instructions of retail: differences are register allocation, scheduling and instruction shape. */
/* Opus 5.5 xhigh, task v1750; USA v1.01 game -O2 -G0 -ffunction-sections, 28 places.
 * Best: 412/412 bytes, 0 of 28 places, first mismatch +0x54. Exactly 5 instructions differ, all one
 * swap: the child pointer (o + 0x17C) is $s2 and the q3 address $s1; retail has them the other way
 * round. Everything else, including the schedule, already equals retail.
 * Cause, from the dumps: local-alloc orders values by floor_log2(refs) * refs / (2 * delta), delta
 * being the distance from def to last use in the order sched1 leaves (this reproduces the order of
 * the $s and $t registers here). q3 has 2 refs, delta 19 (526); child has 3 refs, delta 32 (468); retail needs child
 * first. That takes child's delta <= 28, q3's >= 22, or a fourth child reference. Child's address
 * ranks early in sched1 because it has 3 dependents against 2 for the other address adds.
 * Same allocation in the dumps: inlined call helper, returning or not. Same bytes (tie): `register` or
 * `char *const` child, table local just before the call, incomplete-array D_001A8CFC, and -g, -fno-gcse, -fno-expensive-optimizations, -ffast-math,
 * -fno-sched-interblock, -fno-sched-spec, -fno-rerun-loop-opt, -fmove-all-movables,
 * -fno-cse-follow-jumps, -fno-thread-jumps, -fno-strength-reduce, -frac2-hazard-labels,
 * -frac2-keep-block-order, -frac2-gcse-unsplit-edges, -frac2-no-null-pointer-checks.
 * `if (f)` around the first call (forbidden shape, measured only): leaves a (use (const_int 0)) no-op,
 * but sched1 moves it before the call, both ranges grow by one, same bytes.
 * Worse: child initialised at its declaration (7 differ), table local before the descriptor (34),
 * -fstrict-aliasing (22), -fno-schedule-insns (87; child does get $s1 there, the rest does not fit).
 * Next: a source shape that adds a reference to child, or lowers its address's rank in sched1.
 */
typedef struct { unsigned int lo; unsigned int hi; } Word2_340498;
extern const Word2_340498 D_001AE078;
extern const Word2_340498 D_001AE080;
extern const Word2_340498 D_001AE088;
extern const Word2_340498 D_001AE090;
extern char D_00259F58[];
extern char *D_001A8CFC __attribute__((sda));
extern void func_00336390(void *, void *, int);
extern void func_00337210(int *);

static __inline__ void initDescriptor_340498(int *f) { f[20] = 0; f[21] = 1; }

void func_00340498(char *o)
{
    Word2_340498 q0 = D_001AE078;
    Word2_340498 q1 = D_001AE080;
    Word2_340498 q2 = D_001AE078;
    Word2_340498 q3 = D_001AE088;
    Word2_340498 q4 = D_001AE090;
    int f[23];
    char *child;

    initDescriptor_340498(f);
    f[19] = *(int *)(o + 0x820);
    f[21] = *(int *)(o + 0x81C) == 0;
    f[3] = *(int *)(o + 0x814);
    f[4] = *(int *)(o + 0x818);
    f[16] = (int)(o + 0xA18);
    f[9] = (int)&q4;
    f[1] = 4;
    f[2] = 6;
    f[0] = (int)D_00259F58;
    f[17] = (int)(o + 0x870);
    f[13] = (int)(o + 0x260);
    f[14] = 0;
    child = o + 0x17C;
    func_00336390(child, D_001A8CFC + 0x8710, 0x23);
    {
        char *first = o + 0x214;
        char *second = o + 0x98;
        char *third = o + 0x7D0;
        f[10] = (int)child;
        f[15] = (int)third;
        f[8] = (int)&q3;
        f[7] = (int)&q2;
        f[6] = (int)&q1;
        f[12] = (int)first;
        f[11] = (int)second;
    }
    f[18] = *(int *)(o + 0x80C);
    f[5] = (int)&q0;
    f[22] = 0;
    func_00337210(f);
}
