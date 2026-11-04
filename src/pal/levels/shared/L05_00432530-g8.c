/* func_PAL_L05_00432530, the PAL copy of func_L05_0042C928: the same C, where 0.00029088825f
   becomes 0.0003490659f; func_L01_00397950 becomes func_PAL_L01_0039AD60. */
#include "include_asm.h"
#include "common.h"

typedef struct ListMoby_0042C928 {
    char pad0[0x28];
    struct ListMoby_0042C928 *next;
    char pad2C[0x7E];
    short oclass;
} ListMoby_0042C928;
extern u8 D_0019B278[] MACRO_ADDR;
extern int D_001A79F0_1;
extern char *D_0018C0B0 NOT_SDA;
extern float D_L05_001B1748 __attribute__((sda));
extern float D_L05_001B174C __attribute__((sda));
extern float D_L05_001B1750 __attribute__((sda));
extern ListMoby_0042C928 *D_L05_001B1780 __attribute__((sda));
extern ListMoby_0042C928 *D_L05_001B2528;
extern char *func_0029EFD0(s32 a0);
extern float func_002A7940(void);
extern void func_PAL_L01_0039AD60(char *a0);
extern void func_002A0488(char *a0, s32 a1, s32 a2, s32 a3);

char *func_PAL_L05_00432530(float *pos, u32 kind, s32 a2, s32 a3)
{
    char *moby;
    char *vars;
    ListMoby_0042C928 *p;
    u8 *collected = D_0019B278;

    if (kind >= 4 || collected[kind + (D_001A79F0_1 << 2)] != 0)
        return 0;
    moby = func_0029EFD0(0x126C);
    if (moby != 0) {
        float x, y, z, r;

        vars = *(char **)(moby + 0x68);
        *(long *)(moby + 0x38) = *(long *)(D_0018C0B0 + 0x38);
        qcopy(moby + 0x10, pos);
        *(s16 *)(moby + 0x32) = 0x40;
        *(u8 *)(moby + 0x30) = 0x40;
        *(u8 *)(moby + 0x31) = 1;
        *(u32 *)vars = kind;
        qcopy(vars + 0x10, moby + 0x10);
        *(float *)(vars + 0x1C) = *(float *)(moby + 0xF8);
        *(float *)(moby + 0xF0) = func_002A7940();
        *(float *)(moby + 0xF4) = func_002A7940();
        *(float *)(moby + 0xF8) = func_002A7940();
        r = func_002A7940();
        x = D_L05_001B1748;
        y = D_L05_001B174C;
        z = D_L05_001B1750;
        *(float *)(moby + 0xFC) = r;
        *(s32 *)(vars + 8) = a3;
        *(s32 *)(vars + 4) = a2;
        x *= 0.0003490659f;
        y *= 0.0003490659f;
        z *= 0.0003490659f;
        *(float *)(vars + 0x60) = z;
        *(float *)(vars + 0x68) = x;
        *(float *)(vars + 0x64) = y;
        *(u8 *)(moby + 0x20) = 1;
        func_PAL_L01_0039AD60(moby);
        func_002A0488(moby, 0x82, 0x82, 0x82);
        if (D_L05_001B1780 == 0) {
            for (p = D_L05_001B2528; p != 0; p = p->next) {
                if (p->oclass == 0xFBF)
                    D_L05_001B1780 = p;
            }
        }
    }
    return moby;
}
