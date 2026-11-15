#include "include_asm.h"

#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));

typedef struct {
    char pad0[0x80];
    float position[4];      /* 0x80 */
    float rotation[4];      /* 0x90 */
    char padA0[0x13C];
    short mode;        /* 0x1DC */
    char pad1DE[0x1652];
    int field1830;     /* 0x1830 */
} Hero6A28;

typedef struct {
    char pad[0x3D4];
    float f;           /* 0x3D4 */
    char pad2[0x10];
    char b0;           /* 0x3E8 */
    char b1;           /* 0x3E9 */
} AimState6A28;

extern void func_0029F338(char *);
extern void func_002A7750(char *, int, int);
extern float func_00282E80(char *, char *);
extern void func_00283698(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern int func_002B38B8(char *);
extern int func_L03_0032AB20(int);
extern void func_002B0C28(int, int, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282C88(void *);
extern float func_00283B98(float, float);
extern void func_L00_002B9D60(void *, void *, int, int);
extern void func_L03_003C6E50(char *, void *, void *);
extern void func_00335438(void *, void *, int, int, int);
extern void func_L03_003C7A40(char *);
extern void func_L03_003C7A88(char *);
extern void func_003355A8(int);
extern void func_0029B810(int);
extern void func_00335370(void *);
extern void func_003353C8(void *);
extern int func_L03_0041F090(void *);
extern void func_L00_003294F0(void *, int);
extern void func_0029B7C0(void *, void *, int);
extern void func_L03_003C7018(void);

extern Hero6A28 D_00189E20;
extern char D_00189EA0[];
/* Entity pool base (256-byte entries): absolute and $gp-relative views. */
extern char *D_L03_001B2A1C MACRO_ADDR;
extern char *D_L03_001B2A1C_GP SDATA(D_L03_001B2A1C);
extern char *D_0018B650 NOT_SDA;
extern int D_00138324 NOT_SDA;
extern AimState6A28 D_L03_001B9840;
extern char D_L03_003C7010[];

/* Updates a camera console. When the player stands in front of it and presses the button, the view switches to a remote camera, and it switches back on the next press. */
void func_L03_003C6A28(char *obj)
{
    char mat[0x40] __attribute__((aligned(16)));
    float localPos[4] __attribute__((aligned(16)));
    float rotation[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float cameraPos[4] __attribute__((aligned(16)));
    float cameraRot[4] __attribute__((aligned(16)));
    char *vars = *(char **)(obj + 0x68);

    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        if (*(int *)vars == -1) {
            MarkMobySpawned(obj);
            break;
        }
        *(int *)(vars + 0x30) = -1;
        *(int *)(obj + 0x98) = 0;
        *(unsigned short *)(obj + 0x34) |= 1;
        obj[0x31] = 0;
        SetMobyState(obj, 1, -1);
        break;

    case 1:
    case 2:
        if (vec_distance_xy(obj + 0x10, gHeroPosition) < 6.0f && *(int *)(gHeroPosition + 0x2C0)) {
            matrix_from_basis_rows(mat, obj + 0xC0);
            FastVecSub(localPos, gHeroPosition, obj + 0x10);
            matrix_mul_vec3(localPos, localPos, mat);
            if (*(u8 *)(obj + 0x20) == 1 && IsThirdPendingFlagSet(obj))
                SetMobyState(obj, 2, -1);
            if (localPos[0] < 4.0f && localPos[0] > 0.0f && localPos[1] < 2.5f && localPos[1] > -2.5f) {
                if (*(u8 *)(obj + 0x20) == 1) {
                    TryClaimNotice(8, 0x27BE, 1);
                    break;
                }
                TryClaimNotice(8, 0x27A8, 1);
                if (IsHeroAllowedForMode(8) && (D_00138324 & 0x10)) {
                    SetMobyState(obj, 3, -1);
                    *(Quad *)position = 0;
                    position[0] = 2.0f;
                    matrix_mul_vec3(position, position, obj + 0xC0);
                    FastVecAdd(position, position, obj + 0x10);
                    ClearVector128(rotation);
                    rotation[2] = FastAddRotations(*(float *)(obj + 0xF8), 3.14159f);
                    ResetHeroPositionAndDirection(position, rotation, 0x31, 1);
                    D_0018B650 = D_L03_001B2A1C + (*(int *)vars << 8);
                    SelectRemoteCameraView(obj, cameraPos, cameraRot);
                    SetCamera5Pose(cameraPos, cameraRot, 1, 0, 0);
                    StartConsoleRemoteView(D_L03_001B2A1C + (*(int *)vars << 8));
                }
            }
        }
        break;

    case 3:
        gHeroState.mode = 5;
        if (D_00138324 & 0x10) {
            SetCameraModeState(0);
            ResetHeroPositionAndDirection(gHeroState.position, gHeroState.rotation, 0, 1);
            gHeroState.field1830 = 0;
            EndConsoleRemoteView(D_L03_001B2A1C + (*(int *)vars << 8));
            D_L03_001B9840.f = 64.42f;
            D_L03_001B9840.b1 = 1;
            D_L03_001B9840.b0 = 0;
            SetMobyState(obj, 2, -1);
            ClearLevelObjectTableEntry(0);
        } else {
            SelectRemoteCameraView(obj, mat, mat + 0x10);
            CopyVectorToSelectedObject(mat);
            SetCameraStateRotation(mat + 0x10);
            if (*(int *)(vars + 0x1C) != -1
                && PrepareEntityForShot(D_L03_001B2A1C_GP + (*(int *)(vars + 0x1C) << 8))) {
                if (*(int *)(vars + 0x20) != -1)
                    SetObjectFlagBit(D_L03_001B2A1C_GP + (*(int *)(vars + 0x20) << 8), 1);
            }
            SetLevelObjectTableEntry(D_L03_003C7010, DrawTwoLineMenuPanel, 0);
        }
        break;
    }
}
