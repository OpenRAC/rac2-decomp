/*
 func_L01_0031B300 (272 bytes, 5 places) - default flags (-O2 -G0), in L01_002A7248.c; right size.
 12 masked lines differ (w5, 2026-10-28): only the saved-register roles of a0 and the global base g (retail a0 -> s2,
 g -> s3; ours g -> s2, a0 -> s3). The qcopy now takes the address inline (`qcopy(&w, g + 0x40); h = g + 0x40;`), which gives
 retail's order `addiu $s0,$sp,0x10` before `addiu $s1,g,0x40`.
 Reopen: a spelling that ranks a0 above g in the allocator (g read via the symbol each time, g before the call,
 f20 load elsewhere, local pos pointer, `return 0` for the shared fail label were all worse).
 30 October 2026: decomp-permuter (asm passes off) reaches 5/5 only by wrapping the 0xAA load as
 `if (a0) v1 = *(short *)(p + 0xAA); else v1 = *(short *)(p + 0xAA);`. Without that identical-arm
 conditional nothing it found matches (splitting `h = g; h += 0x40` alone does not); it is a fake use of
 a0 that ranks a0 above g, so it is not used. The real source must give a0 an extra reference there.
 */
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;

extern char D_L01_001BF900[];

extern int func_002761F8(char *a0, char *a1, int a2, char *a3, char *a4);

extern void func_00282F20(float *a0, float *a1, float f12);

extern void func_00282CF0(void *a0, void *a1, void *a2);

extern float func_00282DB0(float *a0, float *a1);

extern float func_00282C48(float f12);

extern void func_00282CC0(void *a0, void *a1, void *a2);

int func_L01_0031B300(char *a0, int a1, char *a2, char *a3) {
    Vector v, w;
    float f20;
    float f2;
    char *g;
    char *h;
    char *p;
    int v1;

    if (func_002761F8(a2, a3, 0x10, a0, 0) == 0)
        goto fail;
    g = D_L01_001BF900;
    p = *(char **)(g + 0x18);
    if (p != 0) {
        v1 = *(short *)(p + 0xAA);
        if (v1 == 0x881 || v1 == 0)
            return 0;
    }
    f20 = *(float *)(a0 + 0x18);
    qcopy(&w, g + 0x40);
    h = g + 0x40;
    func_00282F20(w.f, w.f, 1.0f);
    func_00282CF0(&v, a3, g + 0x20);
    f2 = func_00282C48(func_00282DB0(v.f, w.f));
    func_00282F20(w.f, (float *)h, f2);
    func_00282CC0(a0 + 0x10, a0 + 0x10, &w);
    *(float *)(a0 + 0x18) = f20;
    return 1;
fail:
    return 0;

}
