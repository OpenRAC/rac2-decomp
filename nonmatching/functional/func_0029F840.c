/* functional: high. Draft that compiled to retail bytes alone but has not landed in a linked build; the differences left are placement only. */
/* func_0029F840 - 288 bytes, 28 places (the boot and every level). Tier: Opus 5.5 xhigh, 1 Nov 2026.
   Best check.py result: the C below gives 28 of 28 places in USA v1.01, PAL and v2.00. tools/build.py was not
   run. No match is claimed and the marker stays in src/: the exact bytes need the `if (out != 0)` arm, whose
   `e & 0x100` is always 0 because e is a byte. That is a fake dependency with value-identical arms, whose only
   effect is on scheduling and allocation (AGENTS.md "Rules"; WORKER2.md reports such a form as FAILED).
   Needs a maintainer's ruling, or the original construct. It has the "real test that vanished" shape of
   func_002D3D88, except that its adjustment is an invented always-zero term, not a parameter passed 0.

   Without that arm (the call taking m and the field load directly): 288/288 bytes, 0/28 places, 12 of 72 cdiff
   rows differ, all in the first call's setup.
   Retail:  bne v0,v1 / [move a0,s0]; b / [v0=0]; l.s f12; li.s f20; sll; addu s1; mul.s; move a1,s1; jal
   Clean C: bnel v0,v1 / [l.s f12];   b / [v0=0]; sll; li.s f20; addu s1; move a1,s1; move a0,s0; mul.s; jal

   What retail's order requires, measured with cc1 -dS -dR -fsched-verbose-6:
   - sched2 sees a block boundary right after l.s. l.s and li.s share the one memory unit, so in one block sll
     pairs with l.s; a block starting at li.s gives retail's li.s, sll, addu, mul.s, a1.
   - a0 is set before that boundary through a pseudo p. With p = m in both arms of a test, gcse's cprop rewrites
     a0 = p to a0 = m and a0 stays late, so p's second set must not be a plain copy until after cprop.
   - The test must stay live up to sched2. With a test combine folds (`if (e & 0x100)`, arm p = out; s = 1.0f),
     greg has a0 = s0; l.s; jump, but the label is gone by sched2 and the result is the clean C's 12 rows.
   How the form below gets there, from the dumps: cse2 still has p = m + t; combine reduces it to p = m; greg
   gives a0 = s0 in both places; sched2 keeps the test and the arm, so the boundary holds; jump2 removes the
   arm's redundant move and the test, leaving no word.

   Next: a construct with a real reason to be there that collapses after cse2, probably from a macro or inline
   helper in the original. Measured, not retail: `int adj = 0; ... m + adj * 16` in the arm (the clean C's 12
   rows); `if (e < 0) p = out;` (movn, 304 bytes); `if (e < 0) { p = out; s = 1.0f; }` (304 bytes, the setup in
   retail's order but the test and arm stay); both arms p = m; s = field on `index != 0` (boundary right, a0
   late, s3 and s4 exchanged).
   Needs only the externs below. */
extern void func_00282D60(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283130(void *, unsigned long long);
extern void func_00282D30(void *, void *, float);
int func_0029F840(char *obj, char *m, char *out, int index) {
    int hdr = *(int *)(obj + 0x24);
    int cnt = *(short *)((char *)hdr + 0x2E);
    int tab;
    char *rec;
    int n;
    int i;
    int e;
    char *dst;
    float k;
    char *p;
    float s;

    if (cnt == 0) {
        return 0;
    }
    tab = hdr + cnt * 16;
    index += tab;
    e = ((unsigned char *)index)[1];
    if (e == 0xFF) {
        return 0;
    }
    p = m;
    s = *(float *)(obj + 0x2C);
    if (out != 0) {
        p = m + (e & 0x100);
    }
    k = 0.0009765625f;
    rec = (char *)tab + e * 16;
    func_00282D60(p, rec, s * k);
    rec += 0x10;
    func_00283098(m, m, obj + 0xC0);
    func_00282CC0(m, m, obj + 0x10);
    n = *(short *)(rec + 6);
    if (out != 0 && n > 0) {
        dst = out;
        for (i = n; i != 0;) {
            i--;
            func_00283130(dst, *(unsigned long long *)rec);
            rec += 8;
            func_00282D30(dst, dst, *(float *)(obj + 0x2C) * k);
            *(float *)(dst + 0xC) = 1.0f;
            dst += 0x10;
        }
    }
    return n;
}
