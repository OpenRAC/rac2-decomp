#include "include_asm.h"

extern char *D_001A8CFC[] __attribute__((sda));
extern int D_001A7A00[] __attribute__((sda));
extern unsigned char D_001A7BB0[] __attribute__((sda));
extern int D_001A79F0 __attribute__((sda));
extern unsigned char D_001395E9;
extern unsigned char D_001395B8[];
extern int D_001AA438 __asm__("D_001AA438__gp") __attribute__((section(".sdata")));
extern unsigned char D_001ABA30 __asm__("D_001ABA30__gp") __attribute__((section(".sdata")));
extern unsigned char D_001ABA31[] __attribute__((sda));
extern unsigned char D_001ABA32[] __attribute__((sda));
extern unsigned char D_001ABA33[] __attribute__((sda));
extern unsigned char D_001ABA34[] __attribute__((sda));
extern unsigned char D_001ABA35[] __attribute__((sda));
extern unsigned char D_001ABA36[] __attribute__((sda));
extern unsigned char D_001ABA37[] __attribute__((sda));

/* func_US2_002D2538, the v2.00 copy of func_002D1590: the same C, where the last test also needs D_001A79F0 > 0. */
int func_US2_002D2538(void)
{
    if (D_001A8CFC[0] != 0 && ((unsigned char *)D_001A7A00)[0xA] != 0) {
        if (D_001A7BB0[0x3A] != 0 && D_001395E9 != 0)
            D_001ABA30 = 1;
        if (D_001A7BB0[0x3C] != 0 && (D_001395B8[0x4D] != 0 || D_001395B8[0x52] != 0))
            D_001ABA31[0] = 1;
        if (D_001A7BB0[0x43] != 0 && (D_001395B8[0x57] != 0 || D_001395B8[0x5C] != 0))
            D_001ABA32[0] = 1;
        if (D_001A7BB0[0x43] != 0 && D_001395B8[0x3D] != 0)
            D_001ABA33[0] = 1;
        if (D_001A7BB0[0x52] != 0)
            D_001ABA34[0] = 1;
        if (D_001A7BB0[0x4E] != 0)
            D_001ABA35[0] = 1;
        if (D_001A7BB0[0x4F] != 0)
            D_001ABA36[0] = 1;
        if (D_001AA438 != 0 && D_001A79F0 > 0)
            D_001ABA37[0] = 1;
    }
    return 0;
}
