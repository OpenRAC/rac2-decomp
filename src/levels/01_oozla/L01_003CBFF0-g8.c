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

/* Sets up the swamp monster arm when it appears, then starts its idle or attack animation. */
void func_L01_003CBFF0(u8 *moby)
{
    OozlaSpawnState *vars = *(OozlaSpawnState **)(moby + 0x68);

    vars->field48 = FloatToInt(5.0f);
    vars->field4a = FloatToInt(32.0f);
    vars->field29 = 1;
    *(float *)(moby + 0x2C) = *(float *)(*(u8 **)(moby + 0x24) + 0x24) * 2.5f;
    qcopy(vars->field80, moby + 0x10);
    if (!D_L01_001B2088[0] && moby[0x21] != 255)
        *vars->fieldd8 = 0;
    vars->field30 = 2.0f;
    vars->field2a = 8;
    vars->field28 = 3;
    vars->field2e = 3;
    vars->fieldbc = 0;
    if (vars->fieldb8 != -1)
        ComputePathSegmentLengths_L01(D_L01_001FE180[vars->fieldb8]);
    vars->fieldf0 = vars->fielde8;
    if (vars->fielddd)
        *(u16 *)(moby + 0x34) |= 0x8000;
    if (vars->fieldb4 != -1) {
        vars->fieldf0 = vars->fielde0;
        if ((gMobyTable_L01 + (vars->fieldb4 << 8)) &&
            (gMobyTable_L01 + (vars->fieldb4 << 8))[0x20] != 254 &&
            (gMobyTable_L01 + (vars->fieldb4 << 8))[0x20] != 253) {
            *(u16 *)(moby + 0x32) = 0x3FF;
            moby[0x30] = 255;
            if (vars->fieldd0 > 0.0f)
                *(float *)(moby + 0x18) = vars->fieldd0;
            if (vars->fieldc8)
                StartAnimationImmediate(moby, 8, 0);
            else
                StartAnimationImmediate(moby, 5, 0);
            SetMobyState(moby, 0, 1);
        } else {
            vars->fieldb4 = -1;
        }
    }
    if (vars->fieldb4 == -1) {
        if (vars->fieldd4 > 0.0f)
            *(float *)(moby + 0x18) = vars->fieldd4;
        vars->fieldbc = 120;
        StartAnimationImmediate(moby, 0, 0);
        *(float *)(moby + 0x48) = 0.0f;
        *(u16 *)(moby + 0x34) &= 0xEFFF;
        SetMobyState(moby, 0, 4);
    }
}
