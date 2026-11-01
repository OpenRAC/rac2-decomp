#include "include_asm.h"

#include "common.h"
extern unsigned char D_L30_001B1810 __attribute__((sda));
extern unsigned char D_L30_001B1811 __attribute__((sda));
extern unsigned char D_L30_001B1812 __attribute__((sda));
extern unsigned char D_L30_001B1813 __attribute__((sda));
extern unsigned char D_L30_001B1814 __attribute__((sda));
extern unsigned char D_L30_001B1815 __attribute__((sda));
extern unsigned char D_L30_001B1816 __attribute__((sda));
extern unsigned char D_L30_001B1817 __attribute__((sda));
extern unsigned char D_L30_001B1818 __attribute__((sda));
extern unsigned char D_L30_001B1819 __attribute__((sda));
extern unsigned char D_L30_001B181A __attribute__((sda));
extern unsigned char D_L30_001B181B __attribute__((sda));
extern unsigned char D_L30_001B181C __attribute__((sda));
extern int D_L30_001B1760 __attribute__((sda));
extern int D_L30_001B1764 __attribute__((sda));
extern int D_L30_001B1768 __attribute__((sda));
extern int D_L30_001B176C __attribute__((sda));
extern int D_L30_001B1780 __attribute__((sda));
extern int D_L30_001B1784 __attribute__((sda));
extern float D_L30_001B1788 __attribute__((sda));
extern float D_L30_001B178C __attribute__((sda));
extern float D_L30_001B1790 __attribute__((sda));
extern float D_L30_001B1794 __attribute__((sda));
extern float D_L30_001B1798 __attribute__((sda));
extern float D_L30_001B16F4 __attribute__((sda));
extern unsigned char D_L30_001B1808[4] __attribute__((sda));
extern int D_L30_001B2848 __attribute__((sda));
typedef struct {
    char pad[0x183C];
    float current;
    float maximum;
} GaugeState;
extern GaugeState D_00189E20;
extern int D_001A7344;
extern unsigned D_L30_0025CEB0[];
extern void func_L08_00389B68(int, int, unsigned long, int, unsigned long);
extern unsigned long func_US2_0027CED8(int);
extern int func_00283CF0(float);
extern float func_00282DF0(void *), func_00282C48(float), func_00283B98(float, float);
extern void func_0027E018(int, int, int, int, int, int, int, int, unsigned long, unsigned long);
extern void func_0027E4A8(float, float, float, float, float,
                              int, int, unsigned long, int, int, int, int, float, float);
extern int func_00288FB8(int);
extern void func_0027FB40(int, int, unsigned long, int, int);
static __inline__ unsigned long PackGaugeFlag(unsigned long flags,
                                              unsigned char value, int shift)
{
    return flags | ((unsigned long)value << shift);
}

/* Draws the museum status gauge and updates its swizzled palette. */
void func_US2_L30_0040B478(char *obj) {
    char *s = *(char **)(obj + 0x68);
    unsigned long tex;
    float scale = 0.017453294f, delta, absdelta, angle;
    int n, lo, hi, i, j;

    unsigned long flags, mode;
    flags = D_L30_001B1815;
    flags = PackGaugeFlag(flags, D_L30_001B1816, 1);
    flags = PackGaugeFlag(flags, D_L30_001B1817, 4);
    flags = PackGaugeFlag(flags, D_L30_001B1818, 12);
    flags = PackGaugeFlag(flags, D_L30_001B1819, 14);
    flags = PackGaugeFlag(flags, D_L30_001B181A, 15);
    mode = D_L30_001B1810;
    mode = PackGaugeFlag(mode, D_L30_001B1811, 2);
    flags = PackGaugeFlag(flags, D_L30_001B181B, 16);
    mode = PackGaugeFlag(mode, D_L30_001B1812, 4);
    mode = PackGaugeFlag(mode, D_L30_001B1813, 6);
    func_L08_00389B68(2, 0x47, flags | ((unsigned long)D_L30_001B181C << 17),
            0x42, mode | ((unsigned long)D_L30_001B1814 << 32));
    tex = func_US2_0027CED8(D_L30_001B1764 + *(int *)(s + 0x64));
    func_0027E018(func_00283CF0(D_L30_001B1798), D_001A7344 - 80,
           64, 64, 0, 0, 64, 64, D_L30_001B1760, tex);
    tex = func_US2_0027CED8(D_L30_001B1768 + *(int *)(s + 0x64));
    func_0027E018(func_00283CF0(D_L30_001B1798) + 64, D_001A7344 - 80,
           64, 64, 0, 0, 64, 64, D_L30_001B1760, tex);
    tex = func_US2_0027CED8(D_L30_001B176C + *(int *)(s + 0x64));
    angle = D_L30_001B1788 * (func_00282DF0(s) * scale);
    angle /= D_L30_001B16F4 * 0.016666668f;
    angle = func_00283B98(angle, D_L30_001B178C * scale);
    func_0027E4A8(D_L30_001B1798 + 32.0f, (float)(D_001A7344 - 48),
           32.0f, 32.0f, angle, 32, 32, tex, 0xFFFFF3, 0x60808080, 0, 0, 0.5f, 0.35f);
    absdelta = D_L30_001B1790 * (func_00282C48(*(float *)(s + 0x5C)) * scale);
    angle = func_00283B98(D_L30_001B1794 * scale, absdelta);
    func_0027E4A8(D_L30_001B1798 + 64.0f + 32.0f, (float)(D_001A7344 - 48),
           32.0f, 32.0f, angle, 32, 32, tex, 0xFFFFF3, 0x60808080, 0, 0, 0.5f, 0.35f);
    delta = D_00189E20.current - *(float *)(s + 0x94);
    delta *= 0.2f;
    absdelta = func_00282C48(delta);
    if (absdelta > 1.0f) {
        delta /= absdelta;
    }
    *(float *)(s + 0x94) += delta;
    n = func_00283CF0(*(float *)(s + 0x94) * 251.0f / D_00189E20.maximum) + 2;
    if (n > 253) {
        n = 253;
    }
    if (n < 2) {
        n = 2;
    }
    lo = *(int *)(s + 0x98) <= n ? *(int *)(s + 0x98) : n;
    hi = *(int *)(s + 0x98) < n ? n : *(int *)(s + 0x98);
    for (i = lo; i <= hi; i++) {
        j = (i & 0xE7) | ((i & 16) >> 1) | ((i & 8) << 1);
        if (i < n) {
            (*(unsigned **)&D_L30_001B1808)[j] = D_L30_0025CEB0[j];
        } else {
            (*(unsigned **)&D_L30_001B1808)[j] = 0x80000000;
        }
    }
    tex = func_US2_0027CED8(*(int *)(s + 0x64) + D_L30_001B1780);
    func_0027E018(368, D_001A7344 - 144, 128, 128, 0, 0, 128, 128, 0x70808080, tex);
    tex = func_US2_0027CED8(*(int *)(s + 0x64) + D_L30_001B1784);
    func_0027E018(368, D_001A7344 - 144, 128, 128, 0, 0, 128, 128, 0x70808080, tex);
    *(int *)(s + 0x98) = n;
    if (D_00189E20.current < D_00189E20.maximum * 0.1f && ((D_L30_001B2848 / 90) & 1)) {
        func_0027FB40(256, 370, 0x80000080, func_00288FB8(0x31D5), 100);
    }
    func_L08_00389B68(2, 0x47, 0x5340B, 0x42, 0x8000000044UL);
}
