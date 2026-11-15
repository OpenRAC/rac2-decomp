#include "common.h"

/* D_L05_001B34E0 is read both ways: its first float through $gp (the _gp view, also the address passed to
   euler_rotation_basis), the other fields absolutely. */
typedef struct { float x, y, z; int flags; } Rotation;
typedef struct { float x, y, z, w; } Vector;
typedef struct { Vector rows[3]; } Matrix;
extern int D_L05_001B0FA4 __attribute__((sda));
extern char D_L05_001C7840[];
extern Rotation D_L05_001B34E0;
extern Rotation D_L05_001B34E0_gp SDATA(D_L05_001B34E0);
extern Vector D_L05_001B34F0;
extern float D_L05_001B3500;
extern float func_00283B98(float, float);
extern void func_00282C88(void *);
extern void func_002833F0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D90(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);

void func_L05_00418288(char *object)
{
    Vector value;
    Matrix rotation;
    char *entry = D_L05_001C7840 + D_L05_001B0FA4 * 32;
    char *position = object + 0x10;
    char *output = entry + 0x10;
    D_L05_001B34E0.flags = 0;
    D_L05_001B34E0_gp.x = FastAddRotations(D_L05_001B34E0_gp.x, 0.1f);
    D_L05_001B34E0.y = FastAddRotations(D_L05_001B34E0.y, 0.09f);
    D_L05_001B34E0.z = FastAddRotations(D_L05_001B34E0.z, 0.11f);
    func_00282C88(&value);
    value.x = 0.4f;
    euler_rotation_basis(&rotation, &D_L05_001B34E0_gp);
    matrix_mul_vec3(&value, &value, &rotation);
    FastVecAdd(&value, &value, position);
    qcopy(output, &value);
    *(float *)(entry + 0x1C) = 3.0f;
    if (D_L05_001B3500 > 0.0f) {
        divide_vector_xyz(&D_L05_001B34F0, &D_L05_001B34F0, D_L05_001B3500);
        FastVecSub(&D_L05_001B34F0, &D_L05_001B34F0, position);
        vec_scale_to_length(&D_L05_001B34F0, &D_L05_001B34F0, 5.0f);
        FastVecAdd(&D_L05_001B34F0, &D_L05_001B34F0, position);
        qcopy(output, &D_L05_001B34F0);
        *(float *)(entry + 0x1C) = 10.0f;
    } else {
        *(float *)(entry + 0x1C) = 0.0f;
    }
    func_00282C88(&D_L05_001B34F0);
    D_L05_001B3500 = 0.0f;
}