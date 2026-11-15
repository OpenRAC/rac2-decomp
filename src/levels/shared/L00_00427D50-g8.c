#include "common.h"

/* func_L00_00427D50 reads its tuning floats through $gp, so it needs the small-data
   profile (-G8, from this file's name); the gate word is read with an absolute
   address, hence its incomplete-array declaration. */

extern float func_00283B98(float, float);
extern float func_002703B0(char *, float, float, float, float, float);
extern float func_002702C8(char *, float, float, float, float, float);
extern void func_00282D30(char *, char *, float);
extern void func_00282CC0(char *, char *, char *);
extern void func_L00_002DA0B8(char *, char *, char *);
extern void func_00283410(char *, char *);
extern void func_00283678(char *, char *);
extern void func_002AB668(char *, char *, float);
extern void func_002ACDE8(char *, char *, char *);
extern int D_L00_001A8FF0[] MACRO_ADDR;
extern float D_L00_001B1624 __attribute__((sda));
extern float D_L00_001B1628 __attribute__((sda));
extern float D_L00_001B162C __attribute__((sda));

/* Steps the object's five parameters at +0x50..+0x60 towards the state's targets through
   two per-parameter helpers (the first target adjusted by the focus block's +0x18), then
   steps the focus block's three floats unless the state's flag at +0x9C asks for a
   straight 16-byte copy. When the gate word is set and the focus has an attached owner
   (+0x44), the object's position at +0x30 is built from the owner's position and two
   scaled rows of its basis, the owner's basis rows (+0xC0..+0xE0) are copied into the
   object and its first and third rows are turned about the second by the tuning angle
   (degrees); otherwise the position comes from a helper and the orientation from three
   angles through a matrix. */
/* Moves the camera a little each frame towards its goal values, then works out its position and facing. */
void func_L00_00427D50(char *object)
{
    char scaled0[16] __attribute__((aligned(16)));
    char scaled1[16] __attribute__((aligned(16)));
    char rotation[16] __attribute__((aligned(16)));
    char matrix[64] __attribute__((aligned(16)));
    char *state = *(char **)(object + 0x70);
    char *focus = state + 0xB0;

    *(float *)(object + 0x50) = StepSpringDamperStored(state, *(float *)(object + 0x50),
        FastAddRotations(*(float *)(focus + 0x18), *(float *)(state + 0x14)),
        *(float *)(state + 0x28), *(float *)(state + 0x3C), *(float *)(state + 0x50));
    *(float *)(object + 0x54) = StepSpringDamperStored(state + 4, *(float *)(object + 0x54),
        *(float *)(state + 0x18), *(float *)(state + 0x2C), *(float *)(state + 0x40),
        *(float *)(state + 0x54));
    *(float *)(object + 0x58) = StepSpringDamperClamped(state + 8, *(float *)(object + 0x58),
        *(float *)(state + 0x1C), *(float *)(state + 0x30), *(float *)(state + 0x44),
        *(float *)(state + 0x58));
    *(float *)(object + 0x5C) = StepSpringDamperStored(state + 12, *(float *)(object + 0x5C),
        *(float *)(state + 0x20), *(float *)(state + 0x34), *(float *)(state + 0x48),
        *(float *)(state + 0x5C));
    *(float *)(object + 0x60) = StepSpringDamperStored(state + 16, *(float *)(object + 0x60),
        *(float *)(state + 0x24), *(float *)(state + 0x38), *(float *)(state + 0x4C),
        *(float *)(state + 0x60));
    if (*(int *)(state + 0x9C) == 0) {
        *(float *)(state + 0xB0) = StepSpringDamperClamped(state + 0x90, *(float *)(state + 0xB0),
            *(float *)(state + 0x80), *(float *)(state + 0xA0), *(float *)(state + 0xA4),
            *(float *)(state + 0xA8));
        *(float *)(focus + 4) = StepSpringDamperClamped(state + 0x94, *(float *)(focus + 4),
            *(float *)(state + 0x84), *(float *)(state + 0xA0), *(float *)(state + 0xA4),
            *(float *)(state + 0xA8));
        *(float *)(focus + 8) = StepSpringDamperClamped(state + 0x98, *(float *)(focus + 8),
            *(float *)(state + 0x88), *(float *)(state + 0xA0), *(float *)(state + 0xA4),
            *(float *)(state + 0xA8));
    } else {
        qcopy_nc(focus, state + 0x80);
    }
    if (D_L00_001A8FF0[0] && *(char **)(focus + 0x44)) {
        char *owner;

        FastVecScale(scaled0, *(char **)(focus + 0x44) + 0xE0, D_L00_001B1624);
        FastVecAdd(object + 0x30, *(char **)(focus + 0x44) + 0x10, scaled0);
        FastVecScale(scaled1, *(char **)(focus + 0x44) + 0xC0, D_L00_001B1628);
        FastVecAdd(object + 0x30, object + 0x30, scaled1);
        owner = *(char **)(focus + 0x44);
        qcopy(object, owner + 0xC0);
        qcopy(object + 0x10, owner + 0xD0);
        qcopy(object + 0x20, owner + 0xE0);
        BuildAxisAngleQuaternion(rotation, object + 0x10, D_L00_001B162C * 0.01745329424738884f);
        RotateVectorByQuaternion(object, object, rotation);
        RotateVectorByQuaternion(object + 0x20, object + 0x20, rotation);
    } else {
        SphericalToVector(object + 0x30, object + 0x50, focus);
        *(float *)(object + 0x40) = *(float *)(state + 0xAC);
        *(float *)(object + 0x44) = FastAddRotations(*(float *)(object + 0x54),
                                                  *(float *)(object + 0x5C));
        *(float *)(object + 0x48) = FastAddRotations(3.1415927f, *(float *)(object + 0x50));
        *(float *)(object + 0x48) = FastAddRotations(*(float *)(object + 0x48),
                                                  *(float *)(object + 0x60));
        euler_to_matrix(matrix, object + 0x40);
        copy_matrix3x4(object, matrix);
    }
}
