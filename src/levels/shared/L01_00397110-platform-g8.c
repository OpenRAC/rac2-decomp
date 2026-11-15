#include "common.h"

extern void moby_set_state(char *, int, int);
extern void matrix_mul_vec3(void *, void *, void *);
extern char g_hero_position[];
extern char *D_001B255C __attribute__((sda));
extern int IsPointInCuboid(void *, int);
extern int PlayMobySound(int, int, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_move_angle_toward_target(float, float, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void euler_rotation_basis(void *, void *);
extern float FastAddRotations(float, float);
extern void mat_combine_and_store(void *, void *, void *, void *);

#define BF(p, o) (*(float *)((p) + (o)))
#define BI(p, o) (*(int *)((p) + (o)))
#define BU(p, o) (*(unsigned char *)((p) + (o)))

/* Moves and rotates a moby between two poses while a cuboid trigger is occupied. */
void UpdateCuboidTriggeredMoby(char *moby)
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
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (IsPointInCuboid(g_hero_position, BI(vars, 0xA0))) {
            if (!BI(vars, 0xB8)) PlayMobySound(0, 0, moby);
            moby_set_state(moby, 2, -1);
        }
        if (BI(vars, 0xB0) != -1) {
            char *other = D_001B255C + (BI(vars, 0xB0) << 8);
            if (other && BU(other, 0x20) != 254 && BU(other, 0x20) != 253 &&
                IsPointInCuboid(other + 0x10, BI(vars, 0xA0))) {
                if (!BI(vars, 0xB8)) PlayMobySound(0, 0, moby);
                moby_set_state(moby, 2, -1);
            }
        }

        break;
    case 2: {
        float t;

        BF(vars, 0xAC) += 1.0f / BF(vars, 0xA4);
        if (BF(vars, 0xAC) > 1.0f) BF(vars, 0xAC) = 1.0f;
        else if (BF(vars, 0xAC) < 0.0f) BF(vars, 0xAC) = 0.0f;
        t = 1.0f - math_fast_sin_or_cos_a(BF(vars, 0xAC) * 3.1415927410125732f);
        t *= 0.5f;
        FastVecScale(offset, vars + 0x80, t);
        euler_rotation_basis(rotationMatrix, vars + 0x70);
        matrix_mul_vec3(offset, offset, rotationMatrix);
        FastVecAdd(moby + 0x10, vars + 0x60, offset);
        BF(moby, 0xF8) = math_move_angle_toward_target(BF(vars, 0x78), FastAddRotations(BF(vars, 0x78), BF(vars, 0x98)), t);
        BF(moby, 0xF4) = math_move_angle_toward_target(BF(vars, 0x74), FastAddRotations(BF(vars, 0x74), BF(vars, 0x94)), t);
        BF(moby, 0xF0) = math_move_angle_toward_target(BF(vars, 0x70), FastAddRotations(BF(vars, 0x70), BF(vars, 0x90)), t);
        if (BF(vars, 0xAC) >= 1.0f) moby_set_state(moby, 3, -1);

        break;
    }
    case 3:
        if (!BI(vars, 0xA8) && !IsPointInCuboid(g_hero_position, BI(vars, 0xA0))) {
            if (BI(vars, 0xB0) != -1) {
                char *other = D_001B255C + (BI(vars, 0xB0) << 8);
                if (!other || BU(other, 0x20) == 254 || BU(other, 0x20) == 253 ||
                    IsPointInCuboid(other + 0x10, BI(vars, 0xA0)))
                    goto clear;
            }
            if (!BI(vars, 0xB8)) PlayMobySound(0, 0, moby);
            moby_set_state(moby, 4, -1);
        }
        break;
    case 4: {
        float t;

        BF(vars, 0xAC) -= 1.0f / BF(vars, 0xA4);
        if (BF(vars, 0xAC) > 1.0f) BF(vars, 0xAC) = 1.0f;
        else if (BF(vars, 0xAC) < 0.0f) BF(vars, 0xAC) = 0.0f;
        t = 1.0f - math_fast_sin_or_cos_a(BF(vars, 0xAC) * 3.1415927410125732f);
        t *= 0.5f;
        FastVecScale(offset, vars + 0x80, t);
        euler_rotation_basis(rotationMatrix, vars + 0x70);
        matrix_mul_vec3(offset, offset, rotationMatrix);
        FastVecAdd(moby + 0x10, vars + 0x60, offset);
        BF(moby, 0xF8) = math_move_angle_toward_target(BF(vars, 0x78), FastAddRotations(BF(vars, 0x78), BF(vars, 0x98)), t);
        BF(moby, 0xF4) = math_move_angle_toward_target(BF(vars, 0x74), FastAddRotations(BF(vars, 0x74), BF(vars, 0x94)), t);
        BF(moby, 0xF0) = math_move_angle_toward_target(BF(vars, 0x70), FastAddRotations(BF(vars, 0x70), BF(vars, 0x90)), t);
        if (BF(vars, 0xAC) >= 1.0f) moby_set_state(moby, 1, -1);

        if (IsPointInCuboid(g_hero_position, BI(vars, 0xA0))) {
            if (!BI(vars, 0xB8)) PlayMobySound(0, 0, moby);
            moby_set_state(moby, 2, -1);
        }
        if (BI(vars, 0xB0) != -1) {
            char *other = D_001B255C + (BI(vars, 0xB0) << 8);
            if (other && BU(other, 0x20) != 254 && BU(other, 0x20) != 253 &&
                IsPointInCuboid(other + 0x10, BI(vars, 0xA0))) {
                if (!BI(vars, 0xB8)) PlayMobySound(0, 0, moby);
                moby_set_state(moby, 2, -1);
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
        mat_combine_and_store(vars + 0x20, offset, oldRotation, moby + 0xF0);
    }
}
