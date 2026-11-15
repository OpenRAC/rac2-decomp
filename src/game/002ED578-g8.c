#include "include_asm.h"
#include "common.h"
extern int func_002ED688(unsigned char *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern float D_L00_001AC588 __attribute__((sda));

typedef float Vec000[4] __attribute__((aligned(16)));
typedef struct {
    char pad0[0x30];
    float rot[4];   /* 0x30: Euler angles; x is eased and clamped here, y and z follow velocity */
    float smoothRot[4]; /* 0x40 */
    char pad50[0x40];
    float velocity[4]; /* 0x90 */
    char padA0[0xA0];
    float axisScale;   /* 0x140 */
} Obj002EE000;

extern int func_002EE6A8(unsigned char *);
extern float func_00282E20(void *);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern float func_00283C80(float, float);
extern void func_002A91F0(void *, void *);
extern void func_00283810(void *, void *, void *, float);
extern void func_00283958(void *, void *);
extern float D_001AC244 __attribute__((sda));
extern char *D_001B5390 NOT_SDA;

/* Tilts an object to lean into its turns, based on how it is moving. */
void func_002EE000(unsigned char *owner)
{
    Obj002EE000 *obj = (Obj002EE000 *)GetMobyMotionData(owner);
    Vec000 old;
    Vec000 temp;
    float sign;
    float speed;
    float turnAmount;

    if (!obj)
        return;
    if (GetFollowerState(owner) != 8 && GetFollowerState(owner) != 9) {
        qcopy(old, obj->rot);
        speed = vec_length_xy(obj->velocity);
        sign = 1.0f;
        obj->rot[1] = -FastMatrixHelperA(speed, obj->velocity[2]);
        obj->rot[2] = FastMatrixHelperA(obj->velocity[0], obj->velocity[1]);
        if (fast_subtract_rotations(obj->rot[2], old[2]) < 0.0f)
            sign = -1.0f;
        turnAmount = FastDiffRots(old[2], obj->rot[2]);
        if (GetFollowerState(owner) != 2 && GetFollowerState(owner) != 12) {
            obj->rot[0] *= 0.98f;
            obj->rot[0] += (turnAmount * -sign) * (D_001AC244 * 1.4137166738510132f) * 8.0f;
            if (obj->rot[0] > 1.4137166738510132f)
                obj->rot[0] = 1.4137166738510132f;
            else if (obj->rot[0] < -1.4137166738510132f)
                obj->rot[0] = -1.4137166738510132f;
            BuildRotationFromAngles(temp, obj->rot);
            quaternion_to_rotation_basis(temp, owner + 0xC0);
        } else {
            BuildRotationFromAngles(temp, obj->rot);
            FastVectorNormalize3(obj->smoothRot, obj->smoothRot, temp, 0.0125f);
            quaternion_to_rotation_basis(obj->smoothRot, owner + 0xC0);
        }
    } else {
        char *p = D_001B5390;

        vec_scale_to_length(owner + 0xC0, p + 0x10, obj->axisScale);
        vec_scale_to_length(owner + 0xE0, p, -1.0f);
        vec_scale_to_length(owner + 0xD0, p + 0x20, -1.0f);
    }
}

/* Measures how fast the object is moving and caps it at the top speed. */
void func_002EE610(unsigned char *owner)
{
    char *data = (char *)GetMobyMotionData(owner);
    if (data) {
        char *vector = data + 0x90;
        float length = FastVecLength(vector);
        float limit = D_L00_001AC588;
        *(float *)(data + 0x124) = length;
        if (limit < length) {
            vec_scale_to_length(vector, vector, limit);
            *(float *)(data + 0x124) = D_L00_001AC588;
        }
    }
}
