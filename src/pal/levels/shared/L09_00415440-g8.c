#include "include_asm.h"

#include "common.h"
extern f32 D_L09_001B1830 __attribute__((sda));
extern f32 D_L09_001B1834 __attribute__((sda));
extern f32 D_L09_001B1838 __attribute__((sda));
extern f32 D_L09_001B183C __attribute__((sda));
extern f32 D_L09_001B1840 __attribute__((sda));
extern void func_002AEE70(char *a0, f32 *a1, f32 *a2, f32 f12, f32 f13, f32 f14);
extern void func_002AEF28(char *a0, f32 *a1, f32 *a2, f32 f12, f32 f13, f32 f14);

/* Drives the two angle pairs of the state, in degrees converted to radians. */
void func_PAL_L09_00415DA0(char *a0)
{
    char *s1 = *(char **)(a0 + 0x68);

    func_002AEE70(a0, (f32 *)(s1 + 0x74), (f32 *)(s1 + 0x70), D_L09_001B1830,
                D_L09_001B1834 * 0.0003490659f, -1.0f);
    func_002AEF28(a0, (f32 *)(s1 + 0x78), (f32 *)(s1 + 0x7C), D_L09_001B1838,
                D_L09_001B183C * 0.0003490659f, D_L09_001B1840 * 0.0003490659f);
}
