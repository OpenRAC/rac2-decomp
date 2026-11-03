/*
 * Opus 5.5 xhigh worker (v2069), USA v1.01, built in src/game/002C7748.c.
 * Best check.py result: 284/284 bytes, 0/28 places; the first difference is
 * at +0x24. Four words differ:
 *
 *   retail                          this C
 *   mtc1  $at, $f2   (367.0f)       mtc1  $at, $f1
 *   mtc1  $at, $f1   (0.5f)         mtc1  $at, $f2
 *   mul.s $f0, $f0, $f2             mul.s $f0, $f0, $f1
 *   add.s $f0, $f0, $f1             add.s $f0, $f0, $f2
 *
 * The float at D_001B23A4 is bound as an sda incomplete array, so no level
 * address is written as a number. The assembler expands it to retail's
 * "lui $at ; lwc1 $f0, %lo($at)".
 * The float registers follow the order the two constants are created in. The
 * commutative canonicalisation of the addition puts the constant on the right
 * in every spelling, so 367.0f's pseudo is always created first and gets
 * $f1. All of these give the same output: the product in its own variable,
 * the 0.5f in its own variable, either operand order, "0.5f + product",
 * fast-math, debug, and disabling either scheduler.
 * Other variants:
 * - An inline helper that tests the mode gives the exact float registers
 *   but keeps the D_001B23A0 load (292 bytes).
 * - Union construction: 292 bytes.
 * - -mno-split-addresses: 288 bytes.
 * Still open: a spelling in which the 0.5f's pseudo is created first.
 * Body from the retail bytes:
 * - func_0027C540(0); func_0029C1A8();
 * - the count is (int)(D_001B23A4[0] * 367.0f + 0.5f);
 * - func_0027FAA8(0x1B5, count, (long)0x80F0F0F0, func_00288FB8_1(0x2D4F),
 *   -1). Writing the third argument as a long gives retail's
 *   "ori ; dsll 16 ; ori" sequence.
 * - func_0027C660();
 * - the record at D_001A8CFC[0] + 0x38000 + 0x7364 is read twice.
 * The declarations it needs follow. func_0027C540, func_0027C660 and
 * func_00288FB8_1 are already declared in src/game/002C7748.c.
 */
extern void func_0029C1A8(void);
extern float D_001B23A4[] __attribute__((sda));
extern char *D_001A8CFC[] __attribute__((sda));

extern void func_0027FAA8(int v, int p7, long k, int r, int m1);

extern void func_002A0250(void);

extern void func_002A01C8(void);

extern void func_002A01F0(void);

extern void func_002A0220(void);

extern void func_002A0380(void);

extern void func_0034EBE0(int);

extern void func_0034EC70(int);

extern void func_0034ECB0(int);

extern void func_0034EDB0(int, int);

extern void func_002FC3C0(int);

extern void func_0029FEE0(void);

int func_002CD3C0(void)
{
    int v;
    int r;

    func_0027C540(0);
    func_0029C1A8();
    {
        float f = D_001B23A4[0] * 367.0f;
        v = (int)(f + 0.5f);
    }
    r = func_00288FB8_1(0x2D4F);
    func_0027FAA8(0x1B5, v, (long)0x80F0F0F0, r, -1);
    func_0027C660();
    if (D_001A8CFC[0] != 0) {
        if (*(int *)((char *)D_001A8CFC[0] + 0x38000 + 0x7364) != 0) {
            func_002A0250();
            func_002A01C8();
            func_002A01F0();
            v = *(int *)((char *)D_001A8CFC[0] + 0x38000 + 0x7364);
            func_0034EBE0(v);
            func_0034EC70(v);
            func_0034ECB0(v);
            func_0034EDB0(v, v + 0xC00);
            func_002A0220();
            func_002A0380();
            func_002FC3C0(0x10);
            func_0029FEE0();
        }
    }
    return 0;
}
