#include "common.h"
extern int func_002E5CF8(int, int, char *);
/* Observed eight GPR arguments, two FP arguments and four stack words. */
extern void *func_0032C700(float, float, void *, int, int, int, int, int, int, int, int, int, int, void *);
extern void func_002FE8D8(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern void func_002AF000(float *, float, float, float);
extern void func_00283098(void *, void *, void *);
extern char *func_L00_00409558(void *, void *, int, int);
extern void func_002FEE50(int);
extern void *D_L00_001ADB2C MACRO_ADDR;
extern int D_L00_001B0C24 __attribute__((sda));

/* Build a surface-aligned frame, then launch the configured number of fragments. */

void func_L00_003FF530(char *object) {
    float basis[3][4];
    float perpendicular[4];
    float direction[4];
    char *state = *(char **)(object + 0x68);
    char *position = object + 0x10;
    char *fragment;
    float strength = 0.7f;
    float heading;
    float elevation;
    float speed;
    int i;
    int j;

    PlayMobySound(0, 0, object);
    for (j = 1; j >= 0; j--) {
        SpawnExplosion(strength, 20.0f, object + 0x10, 1, 14, 10, 15, 10, 20, 1,
                       0, 1, 0, D_L00_001ADB2C);
        strength += 0.3f;
    }
    GetObjectFacingDirection(position, basis[2]);
    perpendicular[0] = basis[2][2];
    perpendicular[1] = basis[2][2];
    perpendicular[2] = -(basis[2][0] + basis[2][1]);
    vec_scale_to_length(basis[0], perpendicular, 1.0f);
    FastVecCross(basis[1], basis[0], basis[2]);
    basis[0][3] = basis[1][3] = basis[2][3] = 0.0f;
    for (i = 0; i < D_L00_001B0C24; i++) {
        heading = RandomAngle();
        if (*(int *)(state + 0x2C) != 0) {
            elevation = RandomFloatRange(0.698131799697876f, 1.3089970350265503f);
            speed = RandomFloatRange(4.0f, 12.0f) * 0.016666668f;
        } else {
            elevation = RandomFloatRange(0.8726646900177002f, 1.5707964897155762f);
            speed = RandomFloatRange(4.0f, 9.0f) * 0.016666668f;
        }
        BuildSphericalOffset(direction, speed, heading, elevation);
        direction[3] = 0.0f;
        matrix_mul_vec3(direction, direction, basis);
        fragment = CreateTumblingDebris(position, direction, i, *(int *)(state + 0x2C));
        if (fragment != 0) *(int *)(fragment + 0xB8) = *(int *)(object + 0xB8);
    }
    ClearEntryFlag(*(int *)(state + 0x30));
}
