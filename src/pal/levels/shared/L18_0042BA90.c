#include "include_asm.h"

#include "common.h"
typedef unsigned char BatchA_A18_u8;
typedef int BatchA_A18_s32;
extern BatchA_A18_u8 D_0018C0D4;
extern BatchA_A18_s32 ref_L18_002E4090_00(BatchA_A18_s32 a0, BatchA_A18_s32 a1);
extern BatchA_A18_s32 func_002A8AF0(BatchA_A18_s32 a0, BatchA_A18_s32 a1, BatchA_A18_s32 a2);
extern BatchA_A18_s32 D_001FE480[];
extern BatchA_A18_s32 D_001FE480[];
extern BatchA_A18_s32 func_L18_003F8E40(BatchA_A18_u8 *s);
extern BatchA_A18_s32 func_002A77E0(BatchA_A18_s32 a0);
extern BatchA_A18_s32 func_L18_003F75E8(BatchA_A18_s32 a0, BatchA_A18_u8 *a1);
extern void func_00335388(BatchA_A18_u8 *a0, BatchA_A18_s32 a1, BatchA_A18_s32 a2,
                          BatchA_A18_s32 a3);
extern void func_002EC9C8(BatchA_A18_u8 *a0, BatchA_A18_s32 a1);
extern BatchA_A18_s32 func_L09_0033E690(BatchA_A18_u8 *a0, BatchA_A18_s32 a1, float f12);
extern BatchA_A18_s32 func_L09_00329178(BatchA_A18_u8 *a0, BatchA_A18_s32 a1,
                                        BatchA_A18_s32 a2, BatchA_A18_s32 a3);
extern BatchA_A18_s32 func_L09_0033E658(void *a0);

void func_PAL_L18_0042BA90(BatchA_A18_u8 *a0, BatchA_A18_s32 a1, BatchA_A18_s32 a2, float f12) {
    if (a0[0xBC] == 0) {
        if (a0[0x43] != a1) {
            func_00335388(a0, a1, a2, (BatchA_A18_s32)f12);
        }
    } else {
        func_002EC9C8((BatchA_A18_u8 *)a1, a2);
    }
}

extern void *func_002B60B0(BatchA_A18_u8 *, float, float, float, float);
extern void func_00282948(void *a0);
extern void func_00282948(void *a0);

/* the object's scale angles are re-submitted in degrees, then the matrix is rebuilt */
void func_PAL_L18_0042BAE0(BatchA_A18_u8 *a0) {
    BatchA_A18_u8 *p = *(BatchA_A18_u8 **)(a0 + 0x68);
    if (a0[0x21] != 0xFF) {
        if (*(BatchA_A18_u8 *)(p + 0x39F) != 0) {
            func_002B60B0(a0, 0.00040000002f * *(float *)(p + 0x3C4),
                          0.020000001f * *(float *)(p + 0x3C0),
                          6.981318e-06f * *(float *)(p + 0x3D4),
                          0.0003490659f * *(float *)(p + 0x3D0));
            func_00282948(*(void **)(p + 0x388));
        }
    }
    *(BatchA_A18_u8 *)(p + 0x39F) = 0;
}

