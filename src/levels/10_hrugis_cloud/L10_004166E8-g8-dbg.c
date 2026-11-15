#include "common.h"
/* func_L10_004166E8 needs -fstrict-aliasing and -g (config/cflags.txt). With strict aliasing retail
   can load the table base D_001B251C ahead of the reload at 0x2B0: a pointer load cannot alias the
   int store before it. Accesses through RAC1's Vec4 union have alias set 0, so they keep their order
   against everything: the zeroed vector, the moby's position and rotation rows, and the field at
   0x180. -g supplies the two nops before div.s. */

/* As RAC1's include/vector.h. */
typedef u32 VecQuad __attribute__((mode(TI), aligned(16)));
typedef union {
    VecQuad q;
    f32 f[4];
    s32 i[4];
} Vec4;

extern s32 func_L05_0037B538(u8 *,s32,s32,s32);
extern void func_L05_0037B948(u8 *,s32,f32);
extern s32 func_L00_00367720(void);
extern void func_L10_00417040(u8 *);
extern void func_L10_00417440(u8 *);
extern void func_L10_004174C8(u8 *);
extern void func_L05_00379E60(u8 *,void *,s32,void *);
extern u8 *func_L10_00417CE0(u8 *,s32);
extern s32 func_L10_0037CC20(void);
extern f32 func_00283CE0(s32);
extern u8 *func_002ED688(u8 *);
extern void func_L10_004175C8(u8 *);
extern f32 func_00283B98(f32,f32);
extern f32 func_00283198(f32);
extern f32 func_00283180(f32);
extern f32 func_00282E48(void *,void *);
extern s32 func_00283DB8(void *,f32);
extern void func_L10_004176C0(u8 *);
extern s32 func_00282948(void *);
extern f32 func_002A7878(f32,f32);
extern void func_L10_004177E8(u8 *,s32,f32);
extern void func_L10_00417A38(u8 *,s32,f32);
extern void func_L10_00425930(void *,s32,f32,s32,s32,s32,s32,s32,s32,s32,s32,s32);
extern void func_0029F9F0(u8 *,void *);
extern void func_0029F338(u8 *);
extern void func_L10_004170F8(u8 *);
extern void func_L00_0031AA28(void *,void *,void *,void *,void *,f32);
extern void func_00282CF0(void *,void *,void *);
extern f32 func_00282DF0(void *);
extern void func_00282F20(void *,void *,f32);
extern void func_00282DD8(void *,void *,void *);
extern void func_0029FCC0(u8 *,s32,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_L10_0039D5E0(void *,void *,s32,s32,u32,u32,f32,s32,s32,f32,f32,f32);
extern void func_L05_0037AE40(u8 *);
extern u8 *D_001B251C MACRO_ADDR;
extern f32 D_L10_001B0F40 __attribute__((sda));
extern s32 D_L10_001B0F44 __attribute__((sda));
extern s32 D_L10_001B0F48 __attribute__((sda));
extern f32 D_L10_001B34D8 MACRO_ADDR;
/* Update of the Hrugis boss moby. It floats and bobs, carries two objects and throws out
   smoke. When it is hit it drops them and sends a child flying along a curve at the player,
   then waits for it to land. */
void func_L10_004166E8(u8 *moby) {
    Vec4 up;
    Vec4 probe;
    Vec4 oldpos;
    Vec4 delta;
    Vec4 a, b;
    Vec4 c, d;
    Vec4 e, f;
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *info, *child;
    s32 hit, i;
    f32 distance, t;
    u8 *childpos, *bank;

    up.q = 0;
    up.f[2] = 1.0f;
    hit = ProcessObjectCollisionHit(moby, 1, 1, 1);
    CheckPlayerInViewAndRange(moby, 1, 32.0f);
    switch (moby[0x20]) {
    case 0:
        moby[0x30] = 0xFF;
        *(f32 *)(vars + 0x2E0) = 1.0f;
        if (!GetStoredPointerValue())
            return;
        InitHrugisBossMoby(moby);
        if (*(s32 *)(vars + 0x2B4))
            AppendLevelObject(moby, InitGroupMobyStates, 0, ReleaseGroupEffects);
        D_L10_001B0F44 = 0;
        D_L10_001B0F48 = 0;
        D_L10_001B34D8 = 1.0f / (D_L10_001B0F40 * 60.0f);
        break;
    case 1:
        if (!*(u8 **)(vars + 0x2C0))
            *(u8 **)(vars + 0x2C0) = SpawnAttachedObject(moby, 1);
        if (!*(u8 **)(vars + 0x2C4))
            *(u8 **)(vars + 0x2C4) = SpawnAttachedObject(moby, 0);
        D_L10_001B0F40 = IntToFloat(GetBossDifficulty()) * 2.5f + 30.0f;
        if (D_L10_001B0F40 > 60.0f)
            D_L10_001B0F40 = 60.0f;
        info = GetMobyMotionData(moby);
        if (*(s32 *)(vars + 0x2B0) != -1) {
            *(s32 *)(info + 0x11C) = 1;
            bank = D_001B251C;
            *(u8 **)(info + 0x120) = bank + (*(s32 *)(vars + 0x2B0) << 8);
        }
        UpdateBossSwaySpeed(moby);
        *(f32 *)(moby + 0xF8) = FastAddRotations(*(f32 *)(moby + 0xF8), *(f32 *)(vars + 0x2CC));
        *(f32 *)(vars + 0x2BC) = FastAddRotations(*(f32 *)(vars + 0x2BC), *(f32 *)(vars + 0x2D0));
        ((Vec4 *)(moby + 0x10))->f[2] = FastSinOrCosB(*(f32 *)(vars + 0x2BC)) * 4.0f + *(f32 *)(vars + 0x2B8);
        distance = fast_vec_dist(*(u8 **)(info + 0x120) + 0x10, moby + 0x10);
        qcopy(&probe, moby + 0x10);
        probe.f[3] = *(f32 *)(moby + 0xC) * 0.000976559997071f;
        if (FastMathHelperA(&probe, 64.0f) != -1 && distance >= 24.0f)
            PlayBossCarriedObjectFlash(moby);
        FastFloatHelperD(vars + 0x2E4);
        if (*(f32 *)(vars + 0x180) < 25.0f)
            SpawnSmokePuff(moby, 0, RandomFloatRange(2.0f, 3.0f));
        if (*(f32 *)(vars + 0x180) < 15.0f)
            SpawnSmokeParticle_L10(moby, 0, RandomFloatRange(1.8f, 2.8f));
        if (!hit)
            break;
        func_L10_00425930(*(u8 **)(vars + 0x2C0) + 0x10, 0, 1.0f, 50, 30, 30, 30, 40, 1, 1, 1, 0);
        func_L10_00425930(*(u8 **)(vars + 0x2C4) + 0x10, 0, 1.0f, 50, 30, 30, 30, 40, 1, 1, 0, 0);
        DetachManipulator(*(u8 **)(vars + 0x2C0), vars + 0x2F0);
        DetachManipulator(*(u8 **)(vars + 0x2C0), vars + 0x330);
        DetachManipulator(*(u8 **)(vars + 0x2C4), vars + 0x370);
        DetachManipulator(*(u8 **)(vars + 0x2C4), vars + 0x3B0);
        vars[0x2F1] = 0;
        vars[0x331] = 0;
        vars[0x371] = 0;
        vars[0x3B1] = 0;
        child = *(u8 **)(*(u8 **)(*(u8 **)(vars + 0x2C0) + 0x68) + 0x18);
        if (child)
            MarkMobySpawned(child);
        child = *(u8 **)(*(u8 **)(*(u8 **)(vars + 0x2C4) + 0x68) + 0x18);
        if (child)
            MarkMobySpawned(child);
        MarkMobySpawned(*(u8 **)(vars + 0x2C0));
        MarkMobySpawned(*(u8 **)(vars + 0x2C4));
        *(u8 **)(vars + 0x2C0) = 0;
        *(u8 **)(vars + 0x2C4) = 0;
        *(s32 *)(vars + 0x2E0) = 0;
        moby[0x20] = 2;
        LaunchChildOnCurvePath(moby);
        break;
    case 2:
        UpdateBossSwaySpeed(moby);
        *(f32 *)(moby + 0xF8) = FastAddRotations(*(f32 *)(moby + 0xF8), *(f32 *)(vars + 0x2CC));
        *(f32 *)(vars + 0x2BC) = FastAddRotations(*(f32 *)(vars + 0x2BC), *(f32 *)(vars + 0x2D0));
        ((Vec4 *)(moby + 0x10))->f[2] = FastSinOrCosB(*(f32 *)(vars + 0x2BC)) * 4.0f + *(f32 *)(vars + 0x2B8);
        if (*(u8 **)(vars + 0x2C8)) {
            info = GetMobyMotionData(*(u8 **)(vars + 0x2C8));
            if (!*(s32 *)(info + 0x110)) {
                *(s32 *)(vars + 0x2DC) = 600;
                *(u8 **)(vars + 0x2C8) = 0;
                break;
            }
            *(f32 *)(vars + 0x2D4) += *(f32 *)(vars + 0x2D8);
            if (*(f32 *)(vars + 0x2D4) > 3.1415927f) {
                t = D_L10_001B34D8;
                *(f32 *)(vars + 0x2D4) = 3.1415927f;
                *(f32 *)(vars + 0x2E0) += t;
            }
            childpos = *(u8 **)(vars + 0x2C8) + 0x10;
            qcopy(&oldpos, childpos);
            t = (FastSinOrCosA(*(f32 *)(vars + 0x2D4) - 3.1415927f) + 1.0f) * 0.5f;
            InterpolateCubicVector_L00(childpos, vars + 0x260, vars + 0x270, vars + 0x280, vars + 0x290, t);
            FastVecSub(&delta, *(u8 **)(vars + 0x2C8) + 0x10, &oldpos);
            if (FastVecLength(&delta) >= 0.0001f) {
                vec_scale_to_length(*(u8 **)(vars + 0x2C8) + 0xC0, &delta, 1.0f);
                ((Vec4 *)(*(u8 **)(vars + 0x2C8) + 0xC0))->i[3] = 0;
                FastVecCross(*(u8 **)(vars + 0x2C8) + 0xD0, *(u8 **)(vars + 0x2C8) + 0xC0, &up);
                ((Vec4 *)(*(u8 **)(vars + 0x2C8) + 0xD0))->i[3] = 0;
                vec_scale_to_length(*(u8 **)(vars + 0x2C8) + 0xD0, *(u8 **)(vars + 0x2C8) + 0xD0, 1.0f);
                FastVecCross(*(u8 **)(vars + 0x2C8) + 0xE0, *(u8 **)(vars + 0x2C8) + 0xD0, *(u8 **)(vars + 0x2C8) + 0xC0);
                ((Vec4 *)(*(u8 **)(vars + 0x2C8) + 0xE0))->i[3] = 0;
            } else {
                TransformMobyJointToWorld(*(u8 **)(vars + 0x2C8), 0, &a);
                TransformMobyJointToWorld(*(u8 **)(vars + 0x2C8), 1, &b);
                TransformMobyJointToWorld(*(u8 **)(vars + 0x2C8), 2, &c);
                TransformMobyJointToWorld(*(u8 **)(vars + 0x2C8), 3, &d);
                FastVecSub(&e, &c, &a);
                FastVecSub(&f, &d, &b);
                vec_scale_to_length(&e, &e, 4.0f);
                vec_scale_to_length(&f, &f, 4.0f);
                FastVecAdd(&e, &c, &e);
                FastVecAdd(&f, &d, &f);
                CreateEnergyStrip(&c, &e, 2, 0, 0x7F7F7F, 0xFF1010, 0.5f, 70, 70, 0.2f, 0.402000010014f, 1.1222499609f);
                CreateEnergyStrip(&d, &f, 2, 0, 0x7F7F7F, 0xFF1010, 0.5f, 70, 70, 0.2f, 0.402000010014f, 1.1222499609f);
            }
            for (i = 0; i < 16; i++) {
                InterpolateCubicVector_L00(&a, vars + 0x260, vars + 0x270, vars + 0x280, vars + 0x290, IntToFloat(i) * 0.0625f);
                InterpolateCubicVector_L00(&b, vars + 0x260, vars + 0x270, vars + 0x280, vars + 0x290, IntToFloat(i + 1) * 0.0625f);
            }
            if (*(f32 *)(vars + 0x2E0) >= 1.0f) {
                *(s32 *)(vars + 0x2DC) = 0;
                moby[0x20] = 1;
                ResetObjectActionState(*(u8 **)(vars + 0x2C8));
                *(f32 *)(vars + 0x2E0) = 1.0f;
                *(u8 **)(vars + 0x2C8) = 0;
                info = GetMobyMotionData(moby);
                ((Vec4 *)(vars + 0x180))->f[0] = (f32)*(s32 *)(info + 0x148);
                D_L10_001B0F48 = 1;
            }
        } else if (FastFloatHelperD(vars + 0x2DC)) {
            LaunchChildOnCurvePath(moby);
        }
        if (*(f32 *)(vars + 0x2E0) <= 0.5f)
            SpawnSmokeParticle_L10(moby, 0, RandomFloatRange(1.9f, 2.25f) - *(f32 *)(vars + 0x2E0));
        if (*(f32 *)(vars + 0x2E0) <= 0.75f)
            SpawnSmokePuff(moby, 0, RandomFloatRange(2.0f, 3.0f) - *(f32 *)(vars + 0x2E0));
        break;
    }
    UpdateBossSwaySpeed(moby);
}
