/* func_L10_00417CE0 - 592 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   func_L10_00417CE0 (592 B), in L10_003170D0.c (base file, no gp). Fully
   decoded (draft.c): spawn moby 0xF86, init fields, 4 vectors scaled by
   1/m[0x2C]*1024, three-point setup, second moby 0x134F. Constants: 18855.0f
   (0x46934E00), 0.8f, 1024.0f, 16.0f.
   Draft is 612 B vs 592, ~144 masked lines: mine uses 8 saved registers
   ($s0..$s7 + frame 0x60), retail 7 ($s0..$s6, frame 0x50): retail reuses
   $s0/$s1/$s2 for vB/vA/m+0x10 after a0, a0's state and a1 are dead. Storing
   the 0x3C field before the func_00283360 call (so 18855.0f is not kept
   across the call in $f20) was needed and is right. The body must be wrapped
   in `if (m != 0) {...} return m;` (retail jumps to a common `daddu
   $v0,$s3,$zero`). */

extern u8 *func_0029EFD0(int);
extern void func_00283360(void *);
extern void func_0029FCC0(u8 *, int, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, f32);
extern void func_0029F978(u8 *, int, void *);
extern void func_002A0F48(u8 *);
extern void func_00282C88(void *);

u8 *func_L10_00417CE0(u8 *a0, int a1) {
    u8 *s1 = *(u8 **)(a0 + 0x68);
    u8 *m = func_0029EFD0(0xF86);
    u8 *s4;
    u8 *s5;
    u8 *s6;
    u8 *vA;
    u8 *vB;
    u8 *n;

    if (m != 0) {
    s4 = *(u8 **)(m + 0x68);
    m[0x30] = 0xFF;
    *(u16 *)(m + 0x32) = 0x1FF;
    *(u16 *)(m + 0x34) |= 0x100;
    *(u8 **)(s4 + 0x10) = a0;
    *(int *)(s4 + 0x14) = a1;
    *(f32 *)(m + 0x2C) = *(f32 *)(*(u8 **)(m + 0x24) + 0x24) * 0.8f;
    *(f32 *)(*(u8 **)(*(u8 **)(m + 0x24) + 0x48) + 0xC) = 18855.0f;
    *(f32 *)(*(u8 **)(m + 0x24) + 0x3C) = 18855.0f;
    func_00283360(m + 0xC0);
    if (a1 != 0) {
        s6 = s1 + 0x330;
        s5 = s1 + 0x2F0;
    } else {
        s6 = s1 + 0x3B0;
        s5 = s1 + 0x370;
    }
    vA = s5 + 0x30;
    func_0029FCC0(m, 0, vA);
    vB = s6 + 0x30;
    func_0029FCC0(m, 1, vB);
    func_00282CF0(vA, vA, m + 0x10);
    func_00282CF0(vB, vB, m + 0x10);
    func_00282CF0(vB, vB, vA);
    func_00282D30(vA, vA, 1.0f / *(f32 *)(m + 0x2C) * 1024.0f);
    func_00282D30(vB, vB, 1.0f / *(f32 *)(m + 0x2C) * 1024.0f);
    func_0029F978(m, 0, s5);
    func_0029F978(m, 1, s6);
    *(f32 *)(s5 + 0x3C) = 1.0f;
    s5[3] = 1;
    *(f32 *)(s5 + 0xC) = 1.0f;
    *(f32 *)(s6 + 0x3C) = 1.0f;
    *(f32 *)(s6 + 0xC) = 1.0f;
    func_L10_00417F30(m);
    s6[3] = 1;
    func_002A0F48(m);
    func_00282C88(s4);
    *(f32 *)s4 = 1.0f;
    n = func_0029EFD0(0x134F);
    *(u8 **)(s4 + 0x18) = n;
    if (n != 0) {
        *(f32 *)(*(u8 **)(*(u8 **)(n + 0x24) + 0x48) + 0xC) = 18855.0f;
        *(f32 *)(*(u8 **)(n + 0x24) + 0x3C) = 18855.0f;
        (*(u8 **)(s4 + 0x18))[0x30] = 0xFF;
        *(u16 *)(*(u8 **)(s4 + 0x18) + 0x32) = 0x1FF;
        *(u16 *)(*(u8 **)(s4 + 0x18) + 0x34) |= 0x100;
        *(f32 *)(*(u8 **)(s4 + 0x18) + 0x2C) = 16.0f;
    }
    }
    return m;
}
