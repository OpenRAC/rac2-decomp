/* func_PAL_L00_002AB0C0, the PAL copy of func_L00_002AB1D8: the same C, where 0.05f becomes
   0.072000004f; 0.3f becomes 0.43200004f. */
#include "include_asm.h"

typedef unsigned char u8;

#ifndef RAC2_T_RESIDENTSTATE_FD160FB9C
typedef struct {
    u8 pad000[0x1b8];
    int f1B8;
    u8 pad1bc[0x222 - 0x1bc];
    short s222;
    u8 pad224[0xc2c - 0x224];
    int fC2C;
    u8 padc30[0x149d - 0xc30];
    u8 b149D;
    u8 pad149e[0x2290 - 0x149e];
    u8 *p2290;
    int f2294;
    u8 pad2298[0x22b8 - 0x2298];
    u8 b22B8;
    u8 pad22b9[0x22bb - 0x22b9];
    u8 b22BB;
    u8 pad22bc[0x22bf - 0x22bc];
    u8 b22BF;
    u8 pad22c0[0x24ec - 0x22c0];
    short s24EC;
} ResidentState_Fd160fb9c;
#endif

extern ResidentState_Fd160fb9c D_00189E20_16;

extern float func_00282E48(void *source, void *table);

extern int func_002ABB78(void *object);

extern int func_L00_002ADEA0(int index);

extern void *D_L00_001BF218;

#ifndef RAC2_T_HEROBLOCK_2AB1D8
typedef struct {
    u8 pad000[0x1e4];
    float f1E4;
} HeroBlock_2ab1d8;
#endif

extern HeroBlock_2ab1d8 D_00189EA0;

extern short D_L00_001BF220_2[];

#ifndef RAC2_T_FLOATBLOCK_2AB1D8
typedef struct {
    u8 pad000[0x5e0];
    float f5E0;
    float f5E4;
    u8 pad5e8[0x624 - 0x5e8];
    float f624;
    float f628;
    u8 pad62c[0x690 - 0x62c];
    float f690;
    float f694;
    u8 pad698[0x6d4 - 0x698];
    float f6D4;
    float f6D8;
} FloatBlock_2ab1d8;
#endif

extern FloatBlock_2ab1d8 D_L00_0025BE10_1;

extern int func_L00_002AB108(float *out, float scale, float amount);
void func_PAL_L00_002AB0C0(void)
{
    float ret;
    float f1, f20, f21, f22;
    int v;

    D_00189E20_16.s24EC = 0;

    if (D_00189E20_16.b22BB == 0)
        return;

    if (D_00189E20_16.s222 != 0)
        return;

    if (D_00189E20_16.b22BF != 0)
        return;

    if (func_L00_002AB108(0, D_00189E20_16.b22B8 != 0 ? 0.7f : 0.57f, 1.3f) == 0)
        return;

    if (D_00189E20_16.b22B8 != 0 && D_L00_001BF218 != 0) {
        if (func_002ABB78(D_L00_001BF218) != 0)
            return;
    }

    D_L00_0025BE10_1.f6D4 = 0.072000004f;
    D_L00_0025BE10_1.f6D8 = 0.43200004f;

    ret = func_00282E48(&D_00189EA0, D_L00_001BF220_2);
    f1 = 1.3f - (ret - D_00189EA0.f1E4);
    f22 = f1 * 0.9615385f;
    f20 = f22 * (-70.0f * 0.017453294f);
    if (-30.0f * 0.017453294f < f20)
        f20 = -30.0f * 0.017453294f;
    if (f20 < (-70.0f * 0.017453294f))
        f20 = -70.0f * 0.017453294f;

    f21 = 0.0f;
    v = func_L00_002ADEA0(0);
    if (v == 27 || v == 44) {
        float f0 = 40.0f * 0.017453294f;

        f21 = f22 * f0;
        if (f0 < f21)
            f21 = f0;
    }

    D_L00_0025BE10_1.f694 = f20;
    D_L00_0025BE10_1.f690 = f21;

    if (D_00189E20_16.b22BB == 2) {
        D_L00_0025BE10_1.f624 = D_L00_0025BE10_1.f6D4;
        D_L00_0025BE10_1.f628 = D_L00_0025BE10_1.f6D8;
        D_L00_0025BE10_1.f5E4 = f20;
        D_L00_0025BE10_1.f5E0 = f21;
    }

    D_00189E20_16.s24EC = 1;
}
