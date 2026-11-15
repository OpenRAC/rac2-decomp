#include "common.h"

typedef struct { float f[4]; } __attribute__((aligned(16))) V;
typedef struct { float a, va, b, vb, ang, z, vz; } S_9f38;
typedef struct { u8 p0[0x15C]; float f15C; u8 p1[0x348-0x160]; short s348; u8 p2[0x2290-0x34A]; u8 *p2290; u8 p3[0x22A0-0x2294]; int i22A0; u8 p4[0x22B5-0x22A4]; u8 b22B5; } HeroInput;
typedef struct { u8 p0[0x100]; float f100,f104,f108,f10C; u8 p1[0x1A0-0x110]; int i1A0; } Controller;
extern HeroInput D_00189E20;
extern Controller D_00138180;
typedef struct { u8 pad[0x290]; short phase; } CamGlobal;
extern CamGlobal D_L00_001B8C80_1;
extern char *D_L00_001B1844;
extern int D_001A7BA0[] __attribute__((sda));
extern int D_001A8FF0 __attribute__((sda));
extern float D_L00_001B15C8 __attribute__((sda));
extern float D_L00_001B15CC __attribute__((sda));
extern float D_L00_001B15D0 __attribute__((sda));
extern float D_L00_001B15D4 __attribute__((sda));
extern float D_L00_001B15D8 __attribute__((sda));
void func_L00_00426480(void *);
void func_00282F20(void *,void *,float);
void func_00282DD8(void *,void *,void *);
void func_00282CC0(void *,void *,void *);
float func_00283CE0(int);
float func_00282C48(float);
float func_002702C8(float,float,float,float,float,float *);
void func_002ACEC0(void *,void *,void *,float);
float func_00283B98(float,float);
float func_00283BE0(float,float);
int func_00277258(void *,int,void *,float);

/* Adapted from RAC1 update_hero_aligned_camera_from_input, camera_modes_and_scripts.c. */
/* Turns the aligned camera left, right, up and down from the control stick and keeps it from tilting too far. */
void func_L00_004266E8(u8 *camera) {
    V up;
    V side;
    V d;
    S_9f38 *state;
    float stick, turn, speed;
    char *params = *(char **)(D_L00_001B1844 + *(short *)(camera + 0x84) * 0x20 + 0x1C);
    state = *(S_9f38 **)(camera + 0x70);
    BuildCameraAimFromHero(camera);
    vec_scale_to_length(&up, gHeroState.p2290 + 0xE0, 1.0f);
    if (D_L00_001B8C80_1.phase == 0 && gHeroState.b22B5 == 0) gHeroState.b22B5 = 1;
    stick = -gPadState.f108;
    if (stick == 0.0f) stick = -gPadState.f100;
    if (stick == 0.0f) stick = IntToFloat((gPadState.i1A0 >> 15) & 1);
    if (stick == 0.0f) stick = -IntToFloat((gPadState.i1A0 >> 13) & 1);
    if (*(short *)(params + 0x26)) stick = 0.0f;
    turn = FloatAbs(state->a);
    speed = D_L00_001B15C8 + (D_L00_001B15CC - D_L00_001B15C8) * turn;
    state->a = turn = StepSpringDamperClamped(state->a, stick, D_L00_001B15D0, D_L00_001B15D4, D_L00_001B15D8, &state->va);
    if (turn != 0.0f) ApplyAxisRotationToQuaternion(camera, camera, &up, speed * turn);
    if (gHeroState.f15C != 0.0f && gHeroState.s348 == 0 && D_001A8FF0 == 0)
        ApplyAxisRotationToQuaternion(camera, camera, &up, gHeroState.f15C);
    stick = -gPadState.f10C;
    if (stick == 0.0f) stick = -gPadState.f104;
    if (stick == 0.0f) stick = IntToFloat((gPadState.i1A0 >> 12) & 1);
    if (stick == 0.0f) stick = -IntToFloat((gPadState.i1A0 >> 14) & 1);
    if (D_L00_001B8C80_1.phase != 0 && gHeroState.i22A0 == 2) stick = 0.0f;
    if (*(short *)(params + 0x26)) stick = 0.0f;
    if (D_001A7BA0[1] == 0) stick = -stick;
    turn = FloatAbs(state->b);
    speed = D_L00_001B15C8 + (D_L00_001B15CC - D_L00_001B15C8) * turn;
    state->b = StepSpringDamperClamped(state->b, stick, D_L00_001B15D0, D_L00_001B15D4, D_L00_001B15D8, &state->vb);
    if (state->b != 0.0f) {
        float step, tilt, zero;
        FastVecCross(&side, camera, &up);
        step = speed * state->b;
        tilt = FloatAbs(FastAddRotations(state->ang, step));
        if (1.1170108318328857f < tilt && FloatAbs(state->ang) < tilt)
            step += -step * (fast_subtract_rotations(tilt, 1.1170108318328857f) * 2.86478853225708f);
        if (tilt >= 1.1152654886245728f && state->ang > 0.0f)
            state->z = StepSpringDamperClamped(state->z, 0.5f, 0.005f, 0.2f, 0.0f, &state->vz);
        else
            state->z = StepSpringDamperClamped(state->z, 0.0f, 0.005f, 0.2f, 0.0f, &state->vz);
        zero = 0.0f;
        d.f[0] = *(float *)(camera + 0);
        d.f[1] = *(float *)(camera + 4);
        d.f[3] = zero;
        d.f[2] = zero;
        vec_scale_to_length(&d, &d, state->z);
        FastVecAdd(camera + 0x30, camera + 0x30, &d);
        if (TestPointAgainstCollision(camera + 0x30, 0x12, gHeroState.p2290, 0.3f))
            state->z = StepSpringDamperClamped(state->z, zero, 0.005f, 0.2f, zero, &state->vz);
        tilt = FastAddRotations(state->ang, step);
        if (FloatAbs(tilt) > 1.4660767316818237f)
            { float limit = 1.4660767316818237f; if (!(zero < tilt)) limit = -1.4660767316818237f; step = fast_subtract_rotations(limit, state->ang); }
        ApplyAxisRotationToQuaternion(camera, camera, &side, step);
        state->ang = FastAddRotations(state->ang, step);
    }
    vec_scale_to_length(camera, camera, 1.0f);
    FastVecCross(camera + 0x10, camera, &up);
    vec_scale_to_length(camera + 0x10, camera + 0x10, 1.0f);
    FastVecCross(camera + 0x20, camera + 0x10, camera);
    *(short *)(params + 0x26) = 0;
}
