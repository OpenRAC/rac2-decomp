#include "common.h"
extern void func_L07_003F8010(void *);
extern void func_002AB8C0(void *, void *);
extern f32 func_00283CE0(s32);
extern void func_L01_002F14E8(s32, s32, f32);
extern s32 func_00282948(void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AFDD8(void *, void *, void *, s32);
extern f32 func_00283248(f32, f32);
extern f32 func_00283BE0(f32, f32);
extern void func_002B0990(void *, void *, s32, s32, f32);
extern void func_002AEC48(void *, void *, s32, f32, f32);
extern f32 func_00282E20(void *);
extern void func_00282D30(void *, void *, f32);
extern f32 D_L07_001B1100[4] __attribute__((sda));
extern f32 D_L07_001B10F0[4] __attribute__((sda));
extern f32 D_L07_001B1110 __attribute__((sda));
extern f32 D_L07_001B1114 __attribute__((sda));
/* Updates a Siberius gun enemy: turns its body and head joints to face the player within limits. */
void func_L07_003F8D90(u8 *moby)
{
    f32 delta[4], pos[4];
    u8 *vars = *(u8 **)(moby + 0x68);
    f32 angle, pitch, limit;
    if (moby[0x95] != 2) AttachShipPartsToMoby(moby);
    UpdateColorFade(moby, vars + 0x160);
    if (moby[0x95] < 2) StartHudOverlay(6, 0, *(f32 *)(vars + 0x20) / IntToFloat(*(s16 *)(vars + 0x24)));
    (*(u16 *)(moby + 0x96))++;
    FastFloatHelperD(vars + 0x42C);
    matrix_mul_vec3(pos, D_L07_001B1100, moby + 0xC0);
    FastVecAdd(pos, pos, moby + 0x10);
    FastVecSub(delta, vars + 0x140, pos);
    TransformVectorByObjectOrGiven(moby, delta, delta, 0);
    angle = FastMatrixHelperA(delta[0], delta[1]);
    switch (moby[0x43]) { case 2: case 3: angle = fast_subtract_rotations(angle, 3.14159274f); break; }
    SetValueAndStartSmoothChange(moby, vars + 0x360, 2, 0, 2.5f);
    if (angle > 0.785398244f) angle = 0.785398244f;
    else if (angle < -0.785398244f) angle = -0.785398244f;
    *(f32 *)(vars + 0x3C8) = angle * 0.5f;
    UpdateEasedNode(moby, vars + 0x360, 2, 0.03f, 0.3f);
    if ((u32)(moby[0x43] - 2) < 2) {
        pitch = FastMatrixHelperA(vec_length_xy(delta), delta[2]) * D_L07_001B1114;
        limit = D_L07_001B1110 * 0.0174532942f;
        if (pitch > limit) pitch = limit;
        else if (pitch < -limit) pitch = -limit;
        FastVecScale(vars + 0x340, D_L07_001B10F0, pitch);
        *(f32 *)(vars + 0x2C8) = angle * 0.5f;
    }
    UpdateEasedNode(moby, vars + 0x2E0, 3, 0.03f, 0.3f);
    UpdateEasedNode(moby, vars + 0x260, 1, 0.03f, 0.3f);
}
