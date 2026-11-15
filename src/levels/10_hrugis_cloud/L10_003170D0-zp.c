#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
extern u8 *D_001B251C[] __attribute__((sda));
extern void func_L10_003F6110(u8 *);
extern void func_L10_003F61C8(u8 *);
extern void func_L00_003CD158(void);
extern int func_L00_00367720();
extern u8 *func_002ED688(u8 *);
extern void func_L05_00379E60(u8 *, void *, int, int);
extern void func_L05_0037B538(u8 *, int, int, int);
extern f32 func_002A7940(void);
extern f32 func_00283198(f32);
extern f32 func_00283180(f32);
extern f32 func_00309B38(f32, f32);
extern void func_0029FC20(u8 *, int, void *);
extern void func_00282F20(void *, void *, f32);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, f32);
extern void func_00283958(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_L00_002E6EF8(void *, void *);

/* Update of the beam moby. It starts up, then each frame it follows a joint of its target
   moby, slowly turns around its own axis and draws the beam. */
void func_L10_003F5EF8(u8 *moby) {
    f32 upVector[4] __attribute__((aligned(16)));
    f32 jointMatrix[4][4] __attribute__((aligned(16)));
    f32 newPosition[4] __attribute__((aligned(16)));
    f32 spinQuat[4] __attribute__((aligned(16)));
    f32 spinMatrix[12] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *forward;
    f32 *right;
    f32 angle;
    u8 *target;

    *(TI128 *)upVector = 0;
    upVector[2] = 1.0f;
    switch (moby[0x20]) {
    case 0:
        moby[0x30] = 0xFF;
        if (GetStoredPointerValue() == 0) {
            return;
        }
        InitHrugisBeamMoby(moby);
        if (*(int *)(vars + 0x268) != 0) {
            AppendLevelObject(moby, EmptyFunction_L00, 0, 0);
        }
        *(f32 *)(vars + 0x27C) = RandomAngle();
        break;
    case 1:
        forward = moby + 0xC0;
        right = (f32 *)(moby + 0xD0);
        *(int *)(GetMobyMotionData(moby) + 0x14C) = 0;
        angle = func_00309B38(*(f32 *)(vars + 0x27C), 0.011635531f);
        target = D_001B251C[0] + (*(int *)(vars + 0x260) << 8);
        *(f32 *)(vars + 0x27C) = angle;
        TransformMobyJointPoint(target, *(int *)(vars + 0x26C), jointMatrix);
        vec_scale_to_length(newPosition, jointMatrix[1], 50.0f);
        FastVecAdd(newPosition, jointMatrix[3], newPosition);
        vec_scale_to_length(forward, jointMatrix[1], -1.0f);
        FastVecCross(right, forward, upVector);
        vec_scale_to_length(right, right, 1.0f);
        FastVecCross(moby + 0xE0, right, forward);
        FastVecScale(spinQuat, forward, FastSinOrCosB(*(f32 *)(vars + 0x27C) * 0.5f));
        spinQuat[3] = FastSinOrCosA(*(f32 *)(vars + 0x27C) * 0.5f);
        quaternion_to_rotation_basis(spinQuat, spinMatrix);
        multiply_matrix3x3(forward, spinMatrix, forward);
        qcopy(moby + 0x10, newPosition);
        ProcessObjectCollisionHit(moby, 0, 0, 0);
        break;
    }
    AddDrawCallbackToList3(DrawHrugisBeamEffect, moby);
}
