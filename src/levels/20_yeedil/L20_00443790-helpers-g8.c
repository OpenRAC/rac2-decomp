#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L20_001B2168 __attribute__((sda));
extern float D_L20_001B216C __attribute__((sda));
extern float D_L20_001B2170 __attribute__((sda));

extern void *func_0029EFD0(int);
extern void func_002B37E8(char *, char *);
extern void func_002833F0(char *, char *);
extern void func_00282CF0(char *, char *, char *);
extern void func_00282F20(char *, char *, float);
extern void func_00282DD8(char *, char *, char *);
extern float func_00283198(float);
extern void func_002ACE78(float *, float *, float);
extern float func_L00_0031CDD0(char *, char *, float *, float, float);
extern int func_00283CF0(float);
extern void func_L20_00443908(char *);

/* Creates an object of the given class at the owner and throws it in an arc toward the target. Returns the new object. */
char *func_L20_00443790(char *owner, int classId, char *aimTarget) {
    char *obj = (char *)CreateMoby(classId);
    char *state;
    char *velocity;
    float speed;
    float acceleration;
    float flightTime;
    unsigned short flags;

    if (obj != 0) {
        InitChildObjectFromParent(obj, owner);
        qcopy(obj + 0xF0, owner + 0xF0);
        euler_rotation_basis(obj + 0xC0, obj + 0xF0);
        flags = *(unsigned short *)(obj + 0x34);
        flags |= 0x100;
        flags &= 0xEFDF;
        state = *(char **)(obj + 0x68);
        speed = D_L20_001B2168 * 0.0166666675f;
        acceleration = D_L20_001B216C * 0.000277777785f;
        velocity = state + 0x10;
        *(unsigned short *)(obj + 0x34) = flags;
        flightTime = 0.0f;
        FastVecSub(state, aimTarget, obj + 0x10);
        *(float *)(state + 8) = 0.0f;
        vec_scale_to_length(state, state, speed);
        FastVecCross(velocity, state, obj + 0xE0);
        SetDirectionWithComplement((float *)velocity, (float *)velocity, FastSinOrCosB(D_L20_001B2170 * 0.000290888245f));
        *(float *)(state + 8) = ComputeShotLaunchSpeed(obj + 0x10, aimTarget, &flightTime, speed, -acceleration);
        *(float *)(state + 0x20) = acceleration;
        *(int *)(state + 0x24) = FloatToInt(flightTime);
        *(void (**)(char *))(obj + 0x64) = UpdateTumblingDebrisMoby;
    }
    return obj;
}
