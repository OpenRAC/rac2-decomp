#include "include_asm.h"

#include "common.h"
typedef struct {
    u8 pad0[0x28], field28, field29, field2a, pad2b[3], field2e, pad2f;
    float field30;
    u8 pad34[0x14], field48, pad49, field4a, pad4b[0x35];
    u8 field80[16], pad90[0x24];
    int fieldb4, fieldb8, fieldbc;
    u8 padc0[8];
    int fieldc8;
    u8 padcc[4];
    float fieldd0, fieldd4;
    int *fieldd8;
    u8 fielddc, fielddd, padde[2];
    int fielde0;
    u8 pade4[4];
    int fielde8;
    u8 padec[4];
    int fieldf0;
} OozlaSpawnState;
extern s32 func_00283CF0(f32);
extern void func_L01_003377C8(u32);
extern void func_002A7398(u8 *, s32, s32);
extern void func_002A7750(u8 *, s32, s32);
extern int D_L01_001B2088[] __attribute__((sda));
extern u32 D_L01_001FE180[];
extern u8 *D_L01_001B255C MACRO_ADDR;

void func_PAL_L01_003D00C8(u8 *a0)
{
    OozlaSpawnState *p = *(OozlaSpawnState **)(a0 + 0x68);

    p->field48 = func_00283CF0(5.0f);
    p->field4a = func_00283CF0(32.0f);
    p->field29 = 1;
    *(float *)(a0 + 0x2C) = *(float *)(*(u8 **)(a0 + 0x24) + 0x24) * 2.5f;
    qcopy(p->field80, a0 + 0x10);
    if (!D_L01_001B2088[0] && a0[0x21] != 255)
        *p->fieldd8 = 0;
    p->field30 = 2.0f;
    p->field2a = 8;
    p->field28 = 3;
    p->field2e = 3;
    p->fieldbc = 0;
    if (p->fieldb8 != -1)
        func_L01_003377C8(D_L01_001FE180[p->fieldb8]);
    p->fieldf0 = p->fielde8;
    if (p->fielddd)
        *(u16 *)(a0 + 0x34) |= 0x8000;
    if (p->fieldb4 != -1) {
        p->fieldf0 = p->fielde0;
        if ((D_L01_001B255C + (p->fieldb4 << 8)) &&
            (D_L01_001B255C + (p->fieldb4 << 8))[0x20] != 254 &&
            (D_L01_001B255C + (p->fieldb4 << 8))[0x20] != 253) {
            *(u16 *)(a0 + 0x32) = 0x3FF;
            a0[0x30] = 255;
            if (p->fieldd0 > 0.0f)
                *(float *)(a0 + 0x18) = p->fieldd0;
            if (p->fieldc8)
                func_002A7398(a0, 8, 0);
            else
                func_002A7398(a0, 5, 0);
            func_002A7750(a0, 0, 1);
        } else {
            p->fieldb4 = -1;
        }
    }
    if (p->fieldb4 == -1) {
        if (p->fieldd4 > 0.0f)
            *(float *)(a0 + 0x18) = p->fieldd4;
        p->fieldbc = 100;
        func_002A7398(a0, 0, 0);
        *(float *)(a0 + 0x48) = 0.0f;
        *(u16 *)(a0 + 0x34) &= 0xEFFF;
        func_002A7750(a0, 0, 4);
    }
}
