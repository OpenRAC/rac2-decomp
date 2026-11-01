/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* Opus 5.5 xhigh, task v1750; USA v1.01 game -O2 -G0 -ffunction-sections, 28 places.
 * Best: 448/448 bytes, 0 of 28 places, first mismatch +0x1C. 20 instructions differ, all from four
 * allocation or order facts:
 * - child (o + 0x17C) is $s2 and the q3 address $s1, retail the reverse: same cause as
 *   func_00340498 (see its draft); here q3's delta must grow by one, or child's shrink by two.
 * - o + 0xA18 takes $v1, so D_00259CE0 moves to $a3 and the 0x820 load to $a2, which also moves the
 *   sltiu in sched2. By the model, retail needs that address's delta >= 8 (it is 7), or D_00259CE0's
 *   <= 28 (it is 29).
 * - constant 1 is $t5 and o + 0x870 $t6, retail the reverse. The local `pos` already gives retail's
 *   $t2/$t3/$t4 for 3, 2 and &q4 (without it those are $t3/$t4/$t2); pos's delta is 21 and must be
 *   <= 20, which the model says takes the 0x8710 constant before pos in first-pass order.
 * - `sw $s0,0x9C` and `daddu $a0,$s6` are swapped in one cycle: retail needs the a0 copy before that
 *   store in sched1's order. func_00340498's extra address add gives it that order; this has none.
 * The pos-less draft has 21 differences, and so do these on it: incomplete-array D_001A8CFC, `if (f)`
 * around the call (forbidden shape, measured only), -fstrict-aliasing, -fno-sched-interblock,
 * -fno-sched-spec, -fno-rerun-loop-opt, -fmove-all-movables, -fno-cse-follow-jumps, -fno-thread-jumps,
 * -fno-strength-reduce, -frac2-hazard-labels, -frac2-no-null-pointer-checks. Worse: -fno-schedule-insns (92).
 * Next: as func_00340498; a fix for child's rank in sched1 should also lengthen o + 0xA18's range.
 */
typedef struct { unsigned int lo; unsigned int hi; } Word2_340638;
extern const Word2_340638 D_001AE090;
extern const Word2_340638 D_001AE098;
extern const Word2_340638 D_001AE0A0;
extern const Word2_340638 D_001AE0A8;
extern const Word2_340638 D_001AE0B0;
extern char D_00259CE0[];
extern char *D_001A8CFC __attribute__((sda));
extern void func_00336390(void *, void *, int);
extern void func_00337210(int *);

static __inline__ void initDescriptor_340498(int *f) { f[20] = 0; f[21] = 1; }

void func_00340638(char *o)
{
    Word2_340638 q0 = D_001AE098;
    Word2_340638 q1 = D_001AE0A0;
    Word2_340638 q2 = D_001AE098;
    Word2_340638 q3 = D_001AE0A8;
    Word2_340638 q4 = D_001AE090;
    Word2_340638 q5 = D_001AE0B0;
    int f[23];
    char *child;
    char *pos;

    initDescriptor_340498(f);
    f[21] = *(int *)(o + 0x81C) == 1;
    f[16] = (int)(o + 0xA18);
    f[19] = *(int *)(o + 0x820);
    f[3] = *(int *)(o + 0x814);
    f[4] = *(int *)(o + 0x818);
    f[9] = (int)&q4;
    pos = o + 0x870;
    f[14] = 1;
    f[0] = (int)D_00259CE0;
    f[1] = 3;
    f[2] = 2;
    f[17] = (int)pos;
    f[13] = 0;
    child = o + 0x17C;
    func_00336390(child, D_001A8CFC + 0x8710, 0x5D);
    {
        char *first = o + 0x214;
        char *third = o + 0x7D0;
        f[10] = (int)child;
        f[15] = (int)third;
        f[8] = (int)&q3;
        f[7] = (int)&q2;
        f[6] = (int)&q1;
        f[20] = (int)&q5;
        f[12] = (int)first;
    }
    f[18] = *(int *)(o + 0x80C);
    f[11] = 0;
    f[5] = (int)&q0;
    f[22] = 0;
    func_00337210(f);
}
