#include "common.h"

/* func_L07_0040E198's state machine. A unit of its own: $gp data, a jump table and float
 * constants, with the copy and gcse options it needs (config/cflags.txt). */

typedef int TI128 __attribute__((mode(TI)));
typedef union {
    TI128 q;
    float f[4];
} Vector;

typedef struct {
    u8 pad[0x6C];
    s16 f6C;
    u8 pad6E[4];
    s16 f72;
} GameStatus;

typedef struct {
    u8 pad[0x140];
    float pos[4];
    u8 pad150[0x16C - 0x150];
    int f16C;
    u8 pad170[0x180 - 0x170];
    float f180;
    int f184;
    int f188;
} CameraObject;

typedef struct {
    u8 pad00[0x90];
    int f90;
    u8 pad94[0xD0 - 0x94];
    int fD0;
    u8 padD4[0x100 - 0xD4];
    void *f100;
    u8 pad104[0x110 - 0x104];
    float f110;
    float f114;
    float f118;
    float f11C;
    u8 pad120[0x1AC - 0x120];
    int f1AC;
    u8 pad1B0[0x16B0 - 0x1B0];
    float f16B0;
    float f16B4;
    float f16B8;
    int f16BC;
    u8 pad16C0[8];
    float f16C8;
    int f16CC;
} ShipState;

typedef struct {
    u8 pad00[0x10];
    float pos[4];
    u8 state;
    u8 pad21[15];
    u8 f30;
    u8 f31;
    u16 f32;
    u16 flags;
    u8 pad36[0x68 - 0x36];
    ShipState *vars;
    u8 pad6C[0xAA - 0x6C];
    s16 classId;
    u8 padAC[4];
    u8 fB0;
    u8 padB1[0xC0 - 0xB1];
    float mtx[12];
    float rot[4];
} ShipObject;

extern void func_L07_0040F8F8(void *);
extern void func_L07_0040FC50(void *);
extern void func_L07_0040E980(void *);
extern void func_L07_00410700(void *, int);
extern void func_L07_0040EC08(void *);
extern void func_L07_0040FC88(void *);
extern void func_L07_0040F0D0(void *);
extern void func_L07_00410930(void *);
extern void func_L07_004106B8(void *);
extern void func_L07_00423B28(void *);
extern void func_L07_00423B80(void *);
extern void func_002A7750(void *, int, int);
extern int func_002E5CF8(int, int, void *);
extern int func_002B3868(void *);
extern float func_002AAA00(void *, void *, float, float, float, float, int);
extern void func_L02_002DCEA0(int, float);
extern void func_L00_00303530(int, int);
extern void func_L00_002B9D60(void *, void *, int, int);
extern void func_002B6D28(void);
extern float func_002AA548(void *, void *, float, float, float, float);
extern float func_002AA140(float, float, float);
extern void func_00283098(void *, void *, void *);
extern float func_00282C48(float);
extern void func_002833F0(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_002AA2E8(void *, float, float);
extern float func_00283248(float, float);
extern float func_00282E80(void *, void *);
extern float func_00283B98(float, float);
extern void func_002AD6F0(void *, void *, void *, void *);

extern int D_L07_001B1740 __attribute__((sda));
extern int D_L07_001C9780 NOT_SDA;
extern int D_L07_001B19F8;
extern u8 D_0018C0E2 NOT_SDA;
extern u8 D_001A7BD0;
extern int D_001A79F0;
extern u8 D_0019B2E8[][16];
extern void *D_0018A15C[3] NOT_SDA;
extern float D_L07_001B1D20;
extern GameStatus D_001A63A8;
extern int D_L07_001B9330 NOT_SDA;
extern CameraObject D_L07_001B90C0;
extern float D_L07_001B9200[4];
extern float D_L07_001B1744 __attribute__((sda));
extern float D_L07_001B1748 __attribute__((sda));
extern float D_L07_001B174C __attribute__((sda));
extern float D_L07_001B1750 __attribute__((sda));
extern float D_L07_001B1758 __attribute__((sda));
extern float D_L07_001B175C __attribute__((sda));
extern float D_L07_001B1760[2] __attribute__((sda));
/* Other code in this level reads a halfword at 0x1B2024; the int follows it. */
extern struct {
    s16 f0;
    s16 f2;
    int f4;
} D_L07_001B2024;

/* Main update for the Siberius ship objects (moby classes 4569 to 4573): starts them, runs the ride along the path, and plays the final crash sequence. */
void func_L07_0040E198(ShipObject *ship)
{
    Vector savedPos, savedRot, v, w, x, y;
    ShipState *vars = ship->vars;
    float bounceSpeed, spin, offsetX, fadeState;
    int i;

    if (!vars)
        return;

    switch (ship->state) {
    case 0:
        ship->flags |= 1;
        ship->f31 = 0;
        ComputePathCentersAndRadii(ship);
        vars->f1AC = -1;
        if (vars->f90 == -1) {
            if (ship->classId == 0x11D9 /* moby class 4569 */)
                SetMobyState(ship, 3, -1);
            else
                SetMobyState(ship, 4, -1);
        } else {
            ship->f30 = 255;
            ClearFlagBlock(ship);
            StartShipChain(ship);
            SetMobyState(ship, 2, -1);
        }
        break;
    case 2:
        if (D_L07_001B1740) {
            D_L07_001B1740 = 0;
            StartShipSecondPhase(vars->f100, vars->fD0);
        }
        if (D_L07_001C9780) {
            SetMobyState(ship, 1, -1);
            vars->f16CC = PlayMobySound(2, 4, ship);
            vars->f16C8 = 6.0f;
        }
        break;
    case 1:
        D_0018C0E2 = 1;
        D_L07_001B19F8 = 1;
        MoveShipRidersAlongPath(ship);
        RunShipSequenceEvents(ship);
        break;
    case 3:
        if (SetFirstPendingFlag(ship))
            PlayMobySound(1, 0, ship);
        UpdateShipAttachedParts(ship);
        if (D_001A7BD0 || (D_0019B2E8[gCurrentMapIndex][ship->fB0] & 0x80)) {
            UpdateShipAttachedParts(ship);
            ship->flags |= 2;
            break;
        }
        if (D_0018A15C[0] == ship) {
            if (vars->f110 >= 0.5f)
                PlayMobySound(1, 0, ship);
            ApproachTargetWithDirectionMode(&vars->f110, &vars->f118, -1.0f, 0.0017453294713050127f,
                          0.0017453294713050127f, 0.10471977f, 0);
            if (vars->f110 <= -1.0f) {
                StartTimedCountdown(1, 10.0f);
                if (D_L07_001B1D20 >= 1.0f) {
                    savedPos.q = 0;
                    savedRot.q = 0;
                    savedPos.f[0] = 191.5800018310547f;
                    savedPos.f[1] = 501.15f;
                    savedPos.f[2] = 457.69000244140625f;
                    savedRot.f[2] = 3.1415927f;
                    LoadSceneChunk(1, 0);
                    ResetHeroPositionAndDirection(&savedPos, &savedRot, 0, 1);
                }
            }
        } else {
            ApproachTargetWithDirectionMode(&vars->f110, &vars->f118, 0.5f, 0.0017453294713050127f,
                          0.0017453294713050127f, 0.10471977f, 0);
        }
        break;
    case 5:
        if (vars->f16B8 >= 1.0f && D_L07_001B1D20 >= 1.0f) {
            if (gMusicState.f72 != 3 || gMusicState.f6C >= 6000)
                break;
            D_L07_001B9330 = 0;
            ResumeMusicStream();
        }
        savedPos.q = *(TI128 *)ship->pos;
        savedRot.q = *(TI128 *)ship->rot;
        if (vars->f16B8 > 0.0f) {
            StepValueTowardTarget(ship->pos, &vars->f11C, 400.0f, 0.0f, D_L07_001B1748 * 0.00027777778f,
                          D_L07_001B1744 * 0.016666668f);
            vars->f16B8 = (ship->pos[0] - 400.0f) * 0.014285714f;
            ship->rot[2] = LerpFloat_002AA140(D_L07_001B1750, 0.0f, vars->f16B8);
            ship->rot[0] = LerpFloat_002AA140(0.7853975296020508f, 0.0f, vars->f16B8);
            ship->pos[2] = 213.0f - vars->f16B8 * 3.0f;
        } else if ((fadeState = D_L07_001B1D20) == 0.0f) {
            matrix_mul_vec3(&v, D_L07_001B1760, ship->mtx);
            vars->f16B4 += ship->rot[0] * 7.272206130437553e-05f + 7.272206130437553e-05f;
            ship->rot[0] += vars->f16B4;
            if (ship->rot[0] > 1.5707964f) {
                ship->rot[0] = 1.5707964f;
                bounceSpeed = FloatAbs(vars->f16B4);
                if (bounceSpeed < 0.0005817764904350042f)
                    StartTimedCountdown(1, 15.0f);
                else
                    vars->f16B4 *= -0.333f;
                if (!vars->f16BC) {
                    D_L07_001B90C0.f16C = 0;
                    D_L07_001B90C0.f188 = 90;
                    D_L07_001B90C0.f180 = 0.02f;
                    vars->f16BC = 1;
                }
            }
            euler_rotation_basis(ship->mtx, ship->rot);
            matrix_mul_vec3(&w, D_L07_001B1760, ship->mtx);
            FastVecSub(&v, &w, &v);
            FastVecSub(ship->pos, ship->pos, &v);
        } else if (fadeState >= 1.0f) {
            EnterBossSecondPhase(ship);
            break;
        }

        D_L07_001B2024.f4 = 1;
        ApproachValue(&vars->f16B0, 1.0f, D_L07_001B174C * 0.00027777778f);
        offsetX = vars->f11C + vars->f16B0;
        if (offsetX > 0.0f)
            offsetX = 0.0f;
        v.q = *(TI128 *)D_L07_001B9200;
        v.f[0] += offsetX;
        v.f[2] += D_L07_001B175C * 0.016666668f;
        func_L07_00423B28(&v);

        qzero_nc(&w);
        x.q = *(TI128 *)ship->pos;
        x.f[2] += 6.0f;
        w.f[2] = FastMatrixHelperA(ship->pos[0] - D_L07_001B90C0.pos[0], ship->pos[1] - D_L07_001B90C0.pos[1]);
        w.f[1] = FastMatrixHelperA(vec_distance_xy(&x, D_L07_001B90C0.pos), D_L07_001B90C0.pos[2] - x.f[2]);
        w.f[0] = D_L07_001B1758 * 0.017453294f;
        func_L07_00423B80(&w);

        UpdateMobyMatrix(ship);

        spin = vars->f16B8 * 0.04363323748111725f + 0.008726648f;
        for (i = 0; i < 8; i++)
            *(float *)((u8 *)vars + 0x15B4 + i * 0x20) = FastAddRotations(*(float *)((u8 *)vars + 0x15B4 + i * 0x20), spin);

        FastVecSub(&y, ship->pos, &savedPos);
        CombineTransformsAndStore((u8 *)vars + 0x20, &y, &savedRot, ship->rot);
        break;
    }
}
