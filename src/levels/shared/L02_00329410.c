#include "names.h"
/* Builds a direction for the object from a vector: with the resident flag clear the vector's
   own length is used; otherwise it is resolved against the object or transformed by the
   optional matrix. The shared rotation helper returns the angle to the caller. */
extern int ref_L02_00329410_00;
extern void ref_L02_00329410_01(char *, float *, int);
extern float func_002F20E8(float *);
extern void func_002F2270(float *, float *, float);
extern float func_002F2078(float *, float *);
extern float func_002F1E78(float);
extern void func_00283098(float *, float *, const void *);
extern float func_00283248(float, float);

/* Works out the turning angle that points an object along a vector. It can use the vector as is, resolve it against the object, or transform it with a matrix first. */
float func_L02_00329410(char *object, float *vec, const void *matrix) {
    float local[4] __attribute__((aligned(16)));
    float objectDir[4] __attribute__((aligned(16)));
    float forward;
    float radial;
    float dot;

    if (ref_L02_00329410_00 == 0) {
        radial = func_002F20E8(vec);
        forward = vec[2];
    } else if (matrix == 0) {
        ref_L02_00329410_01(object + 0x10, objectDir, 1);
        func_002F2270(local, vec, 1.0f);
        dot = func_002F2078(local, objectDir);
        radial = func_002F1E78(1.0f - dot);
        forward = dot;
    } else {
        matrix_mul_vec3(local, vec, matrix);
        radial = func_002F20E8(local);
        forward = local[2];
    }
    return FastMatrixHelperA(forward, radial);
}
