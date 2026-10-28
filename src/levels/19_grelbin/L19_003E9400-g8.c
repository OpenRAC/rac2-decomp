#include "include_asm.h"
#include "common.h"

extern float D_L19_001B1D28 __attribute__((sda));

extern void func_2EB590();

extern void func_3238E0(void *, void *, int, int, float);

void func_L19_0041C2B8(char *a0)
{
    char *p = a0;
    int obj = *(int *)(p + 0x68);

    func_2EB590(obj + 0x230);
    func_2EB590(obj + 0x234);
    if (*(unsigned short *)(p + 0x96) < 0xFFFF) {
        *(unsigned short *)(p + 0x96) += 1;
    }
    func_3238E0(p, obj + 0x2A0, 1, 1, D_L19_001B1D28);
}

extern int D_L19_001A8F00 __attribute__((sda));
extern u8 D_001A7BDC[] __attribute__((sda));
extern int D_L19_001B2724[4] __attribute__((sda));
extern char *D_L19_001B2B0C[] __attribute__((sda));
extern int D_001A79F0[] __attribute__((sda));
extern u8 D_0019B2E8[];
extern char D_00189EA0[];
extern char D_L19_001BFC40[];

extern void func_4239B8(char *a0);
extern void func_30DFE8(char *a0);
extern void func_318240(char *a0, s32 a1, s32 a2);
extern void func_31A620(char *a0);
extern s32 func_31E128(char *a0, s32 a1);
extern s32 func_2F1940(char *a0, s32 a1);
extern void func_32C2E8(char *a0);
extern void func_2F1A88(char *a0);
extern s32 func_36E868(void);
extern void func_31F110(s32 a0);
extern void func_321BB0(s32 a0);
extern void func_2BBFD8(char *a0, char *a1, s32 a2, s32 a3);
extern void func_30FC48(s32 a0);
extern void func_356928(char *a0, char *a1);
extern void func_309FB8(s32 a0, s32 a1);

void func_L19_00423A98(char *a0)
{
    char *s1 = *(char **)(a0 + 0x68);
    u8 id;

    func_4239B8(a0);
    switch (*(u8 *)(a0 + 0x20)) {
    case 0:
        *(s32 *)(a0 + 0x98) = 0;
        *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) | 0x41) & 0xEFFF;
        if (D_001A7BDC[0] != 0) {
            func_30DFE8(a0);
        } else {
            func_318240(a0, 1, -1);
            func_31A620(a0);
        }
        break;
    case 1:
        if (func_31E128(D_00189EA0, *(s32 *)(s1 + 0x120)) != 0) {
            if (func_2F1940(D_L19_001BFC40, 0x96) != 0) {
                func_2F1940(D_L19_001BFC40, 0x14);
                func_2F1940(D_L19_001BFC40, 0x97);
                func_32C2E8(a0);
                func_2F1A88(D_L19_001BFC40);
                func_318240(a0, 2, -1);
            }
        }
        break;
    case 2:
        D_L19_001B2724[1] = 1;
        if (D_L19_001A8F00 == 2) {
            *(u8 *)(a0 + 0x31) = 0;
            *(u16 *)(a0 + 0x34) |= 1;
        }
        if (func_36E868() == 0) {
            D_L19_001B2724[1] = 0;
            func_31F110(0x14);
            func_321BB0(0x14);
            func_2BBFD8(D_L19_001B2B0C[0] + (*(s32 *)(s1 + 0x120) << 7) + 0x30,
                        D_L19_001B2B0C[0] + (*(s32 *)(s1 + 0x120) << 7) + 0x70, 0, 1);
            *(u16 *)(a0 + 0x34) &= 0xFFFE;
            *(u8 *)(a0 + 0x31) = 1;
            if (*(u8 *)(a0 + 0xB0) != 0xFF) {
                id = *(u8 *)(a0 + 0xB0);
                if ((D_0019B2E8[id + (D_001A79F0[0] << 4)] & 0x80) == 0)
                    func_30FC48(id);
                func_356928(D_00189EA0, D_00189EA0 + 0x10);
                func_309FB8(0, -1);
            } else {
                func_309FB8(0, -1);
            }
            func_30DFE8(a0);
        }
        break;
    }
}
