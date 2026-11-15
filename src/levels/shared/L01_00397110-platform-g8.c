#include "common.h"

extern void func_002A7750(char *, int, int);
extern void func_00283098(void *, void *, void *);
extern char D_00189EA0[];
extern char *D_001B255C __attribute__((sda));
extern int func_002ACBC8(void *, int);
extern int func_002E5CF8(int, int, void *);
extern float func_00283180(float);
extern float func_002AA150(float, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002833F0(void *, void *);
extern float func_00283B98(float, float);
extern void func_002AD6F0(void *, void *, void *, void *);

#define BF(p, o) (*(float *)((p) + (o)))
#define BI(p, o) (*(int *)((p) + (o)))
#define BU(p, o) (*(unsigned char *)((p) + (o)))

/* Moves and rotates a moby between two poses while a cuboid trigger is occupied. */
void func_L01_003C91C8(char *moby)
{
    float oldPosition[4], oldRotation[4], offset[4], rotationMatrix[12];
    char *vars = *(char **)(moby + 0x68);

    qcopy_nc(oldPosition, moby + 0x10);
    qcopy_nc(oldRotation, moby + 0xF0);
    ++*(unsigned short *)(moby + 0x96);
    switch (BU(moby, 0x20)) {
    case 0:
        if ((unsigned short)(*(unsigned short *)(moby + 0xAA) - 0xA6A) < 2 ||
            *(short *)(moby + 0xAA) == 0xAA0 /* moby class 2720 */ || *(short *)(moby + 0xAA) == 0xAA1 /* moby class 2721 */)
            *(unsigned short *)(moby + 0x34) |= 0x800;
        qcopy_nc(vars + 0x60, moby + 0x10);
        qcopy_nc(vars + 0x70, moby + 0xF0);
        BF(vars, 0xAC) = 0;
        SetMobyState(moby, 1, -1);
        break;
    case 1:
        if (IsPointInCuboid(gHeroPosition, BI(vars, 0xA0))) {
            if (!BI(vars, 0xB8)) PlayMobySound(0, 0, moby);
            SetMobyState(moby, 2, -1);
        }
        if (BI(vars, 0xB0) != -1) {
            char *other = D_001B255C + (BI(vars, 0xB0) << 8);
            if (other && BU(other, 0x20) != 254 && BU(other, 0x20) != 253 &&
                IsPointInCuboid(other + 0x10, BI(vars, 0xA0))) {
                if (!BI(vars, 0xB8)) PlayMobySound(0, 0, moby);
                SetMobyState(moby, 2, -1);
            }
        }

        break;
    case 2: {
        float t;

        BF(vars, 0xAC) += 1.0f / BF(vars, 0xA4);
        if (BF(vars, 0xAC) > 1.0f) BF(vars, 0xAC) = 1.0f;
        else if (BF(vars, 0xAC) < 0.0f) BF(vars, 0xAC) = 0.0f;
        t = 1.0f - FastSinOrCosA(BF(vars, 0xAC) * 3.1415927410125732f);
        t *= 0.5f;
        FastVecScale(offset, vars + 0x80, t);
        euler_rotation_basis(rotationMatrix, vars + 0x70);
        matrix_mul_vec3(offset, offset, rotationMatrix);
        FastVecAdd(moby + 0x10, vars + 0x60, offset);
        BF(moby, 0xF8) = MoveAngleTowardTarget(BF(vars, 0x78), FastAddRotations(BF(vars, 0x78), BF(vars, 0x98)), t);
        BF(moby, 0xF4) = MoveAngleTowardTarget(BF(vars, 0x74), FastAddRotations(BF(vars, 0x74), BF(vars, 0x94)), t);
        BF(moby, 0xF0) = MoveAngleTowardTarget(BF(vars, 0x70), FastAddRotations(BF(vars, 0x70), BF(vars, 0x90)), t);
        if (BF(vars, 0xAC) >= 1.0f) SetMobyState(moby, 3, -1);

        break;
    }
    case 3:
        if (!BI(vars, 0xA8) && !IsPointInCuboid(gHeroPosition, BI(vars, 0xA0))) {
            if (BI(vars, 0xB0) != -1) {
                char *other = D_001B255C + (BI(vars, 0xB0) << 8);
                if (!other || BU(other, 0x20) == 254 || BU(other, 0x20) == 253 ||
                    IsPointInCuboid(other + 0x10, BI(vars, 0xA0)))
                    goto clear;
            }
            if (!BI(vars, 0xB8)) PlayMobySound(0, 0, moby);
            SetMobyState(moby, 4, -1);
        }
        break;
    case 4: {
        float t;

        BF(vars, 0xAC) -= 1.0f / BF(vars, 0xA4);
        if (BF(vars, 0xAC) > 1.0f) BF(vars, 0xAC) = 1.0f;
        else if (BF(vars, 0xAC) < 0.0f) BF(vars, 0xAC) = 0.0f;
        t = 1.0f - FastSinOrCosA(BF(vars, 0xAC) * 3.1415927410125732f);
        t *= 0.5f;
        FastVecScale(offset, vars + 0x80, t);
        euler_rotation_basis(rotationMatrix, vars + 0x70);
        matrix_mul_vec3(offset, offset, rotationMatrix);
        FastVecAdd(moby + 0x10, vars + 0x60, offset);
        BF(moby, 0xF8) = MoveAngleTowardTarget(BF(vars, 0x78), FastAddRotations(BF(vars, 0x78), BF(vars, 0x98)), t);
        BF(moby, 0xF4) = MoveAngleTowardTarget(BF(vars, 0x74), FastAddRotations(BF(vars, 0x74), BF(vars, 0x94)), t);
        BF(moby, 0xF0) = MoveAngleTowardTarget(BF(vars, 0x70), FastAddRotations(BF(vars, 0x70), BF(vars, 0x90)), t);
        if (BF(vars, 0xAC) >= 1.0f) SetMobyState(moby, 1, -1);

        if (IsPointInCuboid(gHeroPosition, BI(vars, 0xA0))) {
            if (!BI(vars, 0xB8)) PlayMobySound(0, 0, moby);
            SetMobyState(moby, 2, -1);
        }
        if (BI(vars, 0xB0) != -1) {
            char *other = D_001B255C + (BI(vars, 0xB0) << 8);
            if (other && BU(other, 0x20) != 254 && BU(other, 0x20) != 253 &&
                IsPointInCuboid(other + 0x10, BI(vars, 0xA0))) {
                if (!BI(vars, 0xB8)) PlayMobySound(0, 0, moby);
                SetMobyState(moby, 2, -1);
            }
        }

        break;
    }
    default:
        break;
    }
clear:
    BU(moby, 0xBC) = 0;
    if (BI(vars, 0xB0) != -1) {
        char *other = D_001B255C + (BI(vars, 0xB0) << 8);
        if (!other || BU(other, 0x20) == 254 || BU(other, 0x20) == 253) BI(vars, 0xB0) = -1;
    }
    if (BU(moby, 0x20) < 5) {
        FastVecSub(offset, moby + 0x10, oldPosition);
        CombineTransformsAndStore(vars + 0x20, offset, oldRotation, moby + 0xF0);
    }
}
