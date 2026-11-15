#include "include_asm.h"
#include "names.h"

/* Family 8c659bbcffcd2ad3 -- 324 bytes, 27 level placements. */

#ifndef RAC2_T_BLOCK48_F8C659BBC
#define RAC2_T_BLOCK48_F8C659BBC
typedef struct { char pad[48]; } Block48_F8c659bbc;
#endif

#ifndef RAC2_T_BLOCK16_F8C659BBC
#define RAC2_T_BLOCK16_F8C659BBC
typedef struct { char pad[16]; } Block16_F8c659bbc;
#endif

extern char D_L00_001B1B10[] __attribute__((sda));

extern char D_L00_001B8DC0[];

extern char D_L00_001B8FF0[];

extern char D_L00_001A8E30 __attribute__((sda));

extern void func_00282CF0(char *a, char *b, char *c);

extern void func_00282F20(char *a, char *b, float f);

extern void func_002833F0(char *a, char *b);

extern void func_00283738(char *a, char *b, char *c);

extern void func_00282DD8(char *a, char *b, char *c);

extern float func_00282DF0(char *a);

extern void func_002ACE78(char *a, char *b, float f);

extern void func_002AAC80(char *a, float f1, float f2, float f3, float f4);

extern void func_00283958(char *a, char *b);

/* Turns the camera to follow the player: builds a rotation from the current view and eases it, then folds it into the camera matrix. */
void func_00287BD8(char *easeState, int useFixedAngle)
{
    Block48_F8c659bbc finalRotation;
    Block48_F8c659bbc combined;
    Block48_F8c659bbc lookMatrix;
    Block16_F8c659bbc axis;
    Block16_F8c659bbc direction;
    float halfAngle;

    FastVecSub((char *)&direction, gCameraPosition_L00, D_L00_001B1B10);
    vec_scale_to_length((char *)&direction, (char *)&direction, 1.0f);
    euler_rotation_basis((char *)&lookMatrix, (char *)&D_L00_001A8E30);
    multiply_matrix3x3((char *)&combined, gCameraPosition_L00 + 560, (char *)&lookMatrix);
    FastVecCross((char *)&axis, (char *)&combined, (char *)&direction);
    halfAngle = FastVecLength((char *)&axis) * 0.5f;
    if (useFixedAngle != 0) {
        SetDirectionWithComplement((char *)&axis, (char *)&axis, -halfAngle);
    } else {
        ApproachTargetWithBraking(easeState, halfAngle, 5.8177649043500423431396e-04f,
                5.8177649043500423431396e-04f,
                5.2359886467456817626953e-02f);
        SetDirectionWithComplement((char *)&axis, (char *)&axis, -*(float *)easeState);
    }
    quaternion_to_rotation_basis((char *)&axis, (char *)&finalRotation);
    multiply_matrix3x3(D_L00_001B8FF0, (char *)&finalRotation, D_L00_001B8FF0);
}

extern float D_L00_001A8DD0 __attribute__((sda));
/* Rolls the camera by an amount taken from the stick roll value. */
void func_00287D20(float *roll) { char rotation[0x40]; float angle = *roll * 0.0002908882452175021f * D_L00_001A8DD0; SetDirectionWithComplement(rotation, D_L00_001B8FF0, angle); quaternion_to_rotation_basis(rotation, rotation + 0x10); multiply_matrix3x3(D_L00_001B8FF0, rotation + 0x10, D_L00_001B8FF0); }

extern void func_00282CC0(char *a, char *b, char *c);

extern int D_L00_001A8DC8 __attribute__((sda));

/* Moves the camera direction by the given offset and re-normalizes it. */
void func_00287D98(char *offset)
{
    FastVecSub(gCameraPosition_L00, gCameraPosition_L00, D_L00_001B1B10);
    FastVecAdd(gCameraPosition_L00, gCameraPosition_L00, offset);
    vec_scale_to_length(gCameraPosition_L00, gCameraPosition_L00, (float)D_L00_001A8DC8);
    FastVecAdd(gCameraPosition_L00, gCameraPosition_L00, D_L00_001B1B10);
}
