/* Complete C near miss; not linked and no matching credit.
 * 2026-10-30: game -O2 -G8 -ffunction-sections -g.
 * us: 0/3; us2: 0/3; pal: absent.
 * 424/424 bytes. New contract/address/debug hypothesis: canonical allocator/random/setup/color
 * helper names, real resident owner pointer and real list-head pointer replace the old aliases
 * and fake one-element pointer-array view. Initial mask/return CFG and GP float scheduling
 * differ; first mismatch+0x4C. Debug labels do not close it.
 * Reopen: New early-exit/float snapshot evidence; do not replay old masked-line claims.
 */
#include "common.h"

extern u8 D_0019B278[];
extern int D_001A79F0 NOT_SDA;
extern char *D_0018C0B0 NOT_SDA;
extern float D_L05_001B1748 __attribute__((sda));
extern float D_L05_001B174C __attribute__((sda));
extern float D_L05_001B1750 __attribute__((sda));
extern char *D_L05_001B1780 __attribute__((sda));
extern char *D_L05_001B2528 NOT_SDA;
extern char *func_0029EFD0(s32 a0);
extern float func_002A7940(void);
extern void func_L01_00397950(char *a0);
extern void func_002A0488(char *a0, s32 a1, s32 a2, s32 a3);

char *func_L05_0042C928(float *pos, u32 kind, s32 a2, s32 a3)
{
    char *s2;
    char *s0;
    char *p;
    char *r;
    float ax;
    float ay;
    float az;

    if (kind < 4) {
        if (D_0019B278[(D_001A79F0 << 2) + kind] != 0)
            return 0;
    }
    s2 = func_0029EFD0(0x126C);
    if (s2 == 0)
        return 0;
    s0 = *(char **)(s2 + 0x68);
    *(long *)(s2 + 0x38) = *(long *)(D_0018C0B0 + 0x38);
    qcopy(s2 + 0x10, pos);
    *(u8 *)(s2 + 0x30) = 0x40;
    *(s16 *)(s2 + 0x32) = 0x40;
    *(u8 *)(s2 + 0x31) = 1;
    *(u32 *)s0 = kind;
    qcopy(s0 + 0x10, s2 + 0x10);
    *(float *)(s0 + 0x1C) = *(float *)(s2 + 0xF8);
    *(float *)(s2 + 0xF0) = func_002A7940();
    *(float *)(s2 + 0xF4) = func_002A7940();
    *(float *)(s2 + 0xF8) = func_002A7940();
    *(float *)(s2 + 0xFC) = func_002A7940();
    ax = D_L05_001B1748;
    ay = D_L05_001B174C;
    az = D_L05_001B1750;
    *(float *)(s0 + 0x60) = az * 0.00029088825f;
    *(s32 *)(s0 + 8) = a3;
    *(float *)(s0 + 0x68) = ax * 0.00029088825f;
    *(s32 *)(s0 + 4) = a2;
    *(float *)(s0 + 0x64) = ay * 0.00029088825f;
    *(u8 *)(s2 + 0x20) = 1;
    func_L01_00397950(s2);
    func_002A0488(s2, 0x82, 0x82, 0x82);
    if (D_L05_001B1780 == 0) {
        r = 0;
        for (p = D_L05_001B2528; p != 0; p = *(char **)(p + 0x28)) {
            if (*(s16 *)(p + 0xAA) == 0xFBF)
                r = p;
        }
        D_L05_001B1780 = r;
    }
    return s2;
}
