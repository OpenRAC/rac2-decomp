/* 2 November 2026, current pinned game compiler, default G0 profile.
 * Canonical incomplete-SDA-array scale access preserves the measured
 * lui-at/lwc1 macro load. Explicit void renderer returns agree with current
 * source definitions; the text getter returns its real 32-bit pointer, then
 * the caller explicitly passes its address bits to the existing interface.
 * Both symbol and truthful-return trials: 284/284 bytes, 0/28 USA v1.01
 * places, first difference +0x24. The 367.0f and 0.5f constants still exchange
 * f1/f2, including their multiply/add uses. Prior product-local, half-local
 * and commuted-add spellings tied. Reopen with an independent constant-
 * lifetime witness; no other-release or linked validation is claimed.
 * The formatter's return was subsequently corrected to int from its current
 * definition in 0027F980.c. The final retained declaration was checked on
 * 4 November 2026: 284/284 bytes, 0/28 USA placements, first +0x24.
 * US2 and PAL have no catalogue identity of this name; those are absences,
 * not successful placement checks.
 */
extern void func_0027C540(int);
extern void func_0027C660(void);
extern void *func_00288FB8_1(int);
extern float D_001B23A4[] __attribute__((sda));
extern void func_0029C1A8(void);
extern char *D_001A8CFC[] __attribute__((sda));

extern int func_0027FAA8(int v, int p7, unsigned long long k, char *r, int m1);

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
    r = (int)func_00288FB8_1(0x2D4F);
    func_0027FAA8(0x1B5, v, (long)0x80F0F0F0, (char *)r, -1);
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
