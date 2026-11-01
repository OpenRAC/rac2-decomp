#include "include_asm.h"

#include "common.h"
extern int D_L19_001A8F00 __attribute__((sda));
extern u8 D_001A7BDC[] __attribute__((sda));
extern int D_L19_001B2724[4] __attribute__((sda));
extern char *D_L19_001B2B0C[] __attribute__((sda));
extern int D_001A79F0[] __attribute__((sda));
extern u8 D_0019B2E8[];
extern char D_00189EA0[];
extern char D_L19_001BFC40[];
extern void func_L04_00423178(char *a0);
extern void func_0029F338(char *a0);
extern void func_002A7750(char *a0, s32 a1, s32 a2);
extern void func_L01_003128C0(char *a0);
extern s32 func_002ACBC8(char *a0, s32 a1);
extern s32 func_00288AA0(char *a0, s32 a1);
extern void func_L01_003246D0(char *a0);
extern void func_00288BE8(char *a0);
extern s32 func_002F5D10(void);
extern void func_002AD7B8(s32 a0);
extern void func_US2_002AFF10(s32 a0);
extern void func_L00_002B9D60(char *a0, char *a1, s32 a2, s32 a3);
extern void func_002A0430(s32 a0);
extern void func_002DF3F8(char *a0, char *a1);
extern void func_0029B3E0(s32 a0, s32 a1);

void func_US2_L19_00424DC8(char *a0)
{
    char *s1 = *(char **)(a0 + 0x68);
    u8 id;

    func_L04_00423178(a0);
    switch (*(u8 *)(a0 + 0x20)) {
    case 0:
        *(s32 *)(a0 + 0x98) = 0;
        *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) | 0x41) & 0xEFFF;
        if (D_001A7BDC[0] != 0) {
            func_0029F338(a0);
        } else {
            func_002A7750(a0, 1, -1);
            func_L01_003128C0(a0);
        }
        break;
    case 1:
        if (func_002ACBC8(D_00189EA0, *(s32 *)(s1 + 0x120)) != 0) {
            if (func_00288AA0(D_L19_001BFC40, 0x96) != 0) {
                func_00288AA0(D_L19_001BFC40, 0x14);
                func_00288AA0(D_L19_001BFC40, 0x97);
                func_L01_003246D0(a0);
                func_00288BE8(D_L19_001BFC40);
                func_002A7750(a0, 2, -1);
            }
        }
        break;
    case 2:
        D_L19_001B2724[1] = 1;
        if (D_L19_001A8F00 == 2) {
            *(u8 *)(a0 + 0x31) = 0;
            *(u16 *)(a0 + 0x34) |= 1;
        }
        if (func_002F5D10() == 0) {
            D_L19_001B2724[1] = 0;
            func_002AD7B8(0x14);
            func_US2_002AFF10(0x14);
            func_L00_002B9D60(D_L19_001B2B0C[0] + (*(s32 *)(s1 + 0x120) << 7) + 0x30,
                        D_L19_001B2B0C[0] + (*(s32 *)(s1 + 0x120) << 7) + 0x70, 0, 1);
            *(u16 *)(a0 + 0x34) &= 0xFFFE;
            *(u8 *)(a0 + 0x31) = 1;
            if (*(u8 *)(a0 + 0xB0) != 0xFF) {
                id = *(u8 *)(a0 + 0xB0);
                if ((D_0019B2E8[id + (D_001A79F0[0] << 4)] & 0x80) == 0)
                    func_002A0430(id);
                func_002DF3F8(D_00189EA0, D_00189EA0 + 0x10);
                func_0029B3E0(0, -1);
            } else {
                func_0029B3E0(0, -1);
            }
            func_0029F338(a0);
        }
        break;
    }
}
