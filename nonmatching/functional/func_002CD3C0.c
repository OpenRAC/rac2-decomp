/* functional: high. Same calls and arguments as retail; the float constants are held in different registers. */
/* Near miss: func_002CD3C0 (284 bytes in every program), one word off.
 *
 * The C below compiles to retail's exact 284 bytes and to retail's exact
 * instructions everywhere except one: the `mtc1` that loads the 367.0f
 * constant.  Retail puts it in $f2 and this cc1 puts it in $f1 (and the
 * 0.5f the other way round):
 *
 *   retail                          this C
 *   lui   $at, 0x43B7               lui   $at, 0x43B7
 *   ori   $at, $at, 0x8000          ori   $at, $at, 0x8000
 *   mtc1  $at, $f2                  mtc1  $at, $f1     <- the only difference
 *   lui   $at, 0x1B                 lui   $at, 0x1B
 *   lwc1  $f0, 0x23A4($at)         lwc1  $f0, 0x23A4($at)
 *   lui   $at, 0x3F00               lui   $at, 0x3F00
 *   mtc1  $at, $f1                  mtc1  $at, $f2
 *
 * The float registers follow the order the two constants are created in, and
 * the add's operands are reassociated: this cc1 always expands
 * "product + 0.5f" with the product first, so the 367.0f gets $f1; retail
 * created the 0.5f first ($f1) and the 367.0f second ($f2), then scheduled
 * the 367.0f's materialisation earlier in the code.  Writing the source as
 * "0.5f + 367.0f * x" does not change it here (the reassociation puts the
 * product back first), so this looks like the reassociation's operand order.
 *
 * Measured further (coordinator): the same holds for the product in a
 * variable of its own, for the 0.5f in a variable of its own, for the two
 * operands of the sum written in either order, and for the sum written
 * "0.5f + product" with the product in a variable.  The commutative
 * canonicalisation of the addition puts the constant on the right in every
 * spelling, so the 367.0f's pseudo is always created first and always gets
 * $f1.  What is open is a spelling in which the 0.5f's pseudo is created
 * first.
 *
 * What the retail bytes say about the body:
 *  - func_0027C540(0), then func_0029C1A8();
 *  - the count is (int)(D_001B23A4 * 367.0f + 0.5f);
 *  - func_0027FAA8(0x1B5, count, (long)0x80F0F0F0, func_00288FB8_1(0x2D4F), -1);
 *    - the third argument is written as a long, which is what puts the
 *      three-instruction "ori 0x80F0 ; dsll 16 ; ori 0xF0F0" sequence there
 *      (the same shape as the matched func_002C9B88);
 *  - func_0027C660();
 *  - the record at D_001A8CFC[0] + 0x38000 + 0x7364 is read twice: once for
 *    the test and once for the four calls that take it.
 *
 * The float at 0x001B23A4 is reached through a literal address: with the
 * symbol (extern float D_001B23A4) this cc1 materialises the address in
 * $v0 ("lui $v0,%hi(sym) ; lwc1 $f0,%lo(sym)($v0)") instead of retail's
 * "lui $at,0x1B ; lwc1 $f0,0x23A4($at)", and the instruction order differs
 * as well.  The literal reproduces retail exactly.
 */
extern void func_0029C1A8(void);
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

extern float D_001B23A4;

int func_002CD3C0(void)
{
    int v;
    int r;

    func_0027C540(0);
    func_0029C1A8();
    {
        float f = D_001B23A4 * 367.0f;
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
