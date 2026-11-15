#include "names.h"
/* func_003309A0: -G8 unit. The two globals are read both absolutely and through $gp, so
 * each has an sda name (_1) for the $gp form. The aim vector d is a float[4] copied with
 * qcopy(), which gives retail's frame (a, b, c, d, e, then the 0x30-byte matrix); one float
 * carries the cosine and then the turn, so it lives in $f20 as retail has it. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_001B2854;
extern float D_001B2854_1 __attribute__((sda));
extern s32 D_001B2850;
extern s32 D_001B2850_1 __attribute__((sda));
extern char D_001B5570[];

extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, char *);
extern float FastVecDot(void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, char *);
extern void FastVecCross(void *, void *, void *);
extern float math_fast_angle_helper(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern void quaternion_to_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);

/* Steers the object's heading toward the vector stored in its record: builds the aim vector, measures the angle to the current heading and turns the heading by a tenth of the remainder. */
void moby_steer_heading_to_aim(char *obj)
{
    float aim[4] __attribute__((aligned(16)));
    float projection[4] __attribute__((aligned(16)));
    float target[4] __attribute__((aligned(16)));
    float turnAxis[4] __attribute__((aligned(16)));
    float turnQuat[4] __attribute__((aligned(16)));
    float turnMatrix[12] __attribute__((aligned(16)));
    char *vars = *(char **)(obj + 0x68);
    char *heading, *facing;
    float angleCos;

    aim[0] = *(float *)(vars + 0x50);
    aim[1] = *(float *)(vars + 0x54);
    D_001B2854 = D_001B2854 * 0.7f;
    aim[2] = 0.0f;
    aim[3] = 0.0f;
    D_001B2850_1 = 0;
    if (FastVecLength(aim) != 0.0f) {
        heading = obj + 0xE0;
        facing = obj + 0xC0;
        vec_scale_to_length(aim, aim, 1.0f);
        matrix_mul_vec3(aim, aim, D_001B5570);
        angleCos = FastVecDot(aim, heading);
        FastVecScale(projection, heading, angleCos);
        FastVecSub(aim, aim, projection);
        vec_scale_to_length(aim, aim, 1.0f);
        vec_scale_to_length(target, aim, 10.0f);
        FastVecAdd(target, target, obj + 0x10);
        FastVecCross(turnAxis, facing, aim);
        if (FastVecLength(turnAxis) == 0.0f)
            qcopy(turnAxis, facing);
        angleCos = FastVecDot(facing, aim);
        D_001B2854_1 = 1.0f - angleCos;
        if (angleCos > 0.75f)
            D_001B2850 = 1;
        angleCos = 1.5707964f - math_fast_angle_helper(angleCos);
        angleCos = angleCos * 0.1f;
        FastVecScale(turnQuat, turnAxis, math_fast_sin_or_cos_b(angleCos));
        turnQuat[3] = math_fast_sin_or_cos_a(angleCos);
        quaternion_to_rotation_basis(turnQuat, turnMatrix);
        multiply_matrix3x3(facing, turnMatrix, facing);
    }
}
