#include "names.h"
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(float *, float *, float *);
extern float func_00282DF0(float *);
extern void func_00282F20(float *, float *, float);
extern void func_00282D30(void *, void *, float);
extern int func_002E5CF8(int, int, void *);
extern float func_002A7798(float);
extern void func_002A8240(void *, void *, int, float, float, float);
extern void func_002A7CA0(void *, float, float, float, float, void *);
extern char D_L06_00188660[];

/* Steps the follower's weight toward its goal and blends the state vectors; returns 1 on arrival. */
int func_L06_00420548(char *moby, float accel, float maxSpeed, float targetYaw, float blend)
{
    char *handleRecord;
    float distance;
    float speed;
    char *vars = *(char **)(moby + 0x68);
    int done = 0;
    float maxStep = maxSpeed * 0.016666668f;
    float brakeRatio;
    char *velocity;
    float toGoal[4];
    float accelStep = accel * 0.00027777778f;

    FastVecSub(toGoal, (float *)(vars + 0x220), (float *)(moby + 0x10));
    distance = FastVecLength(toGoal);
    speed = FastVecLength((float *)(vars + 0x230));
    handleRecord = D_L06_00188660 + *(int *)(vars + 0x254) * 0x70;
    brakeRatio = speed / accelStep;
    if (*(char **)(handleRecord + 0x88) != moby || *(unsigned char *)(handleRecord + 0x74) == 0)
        *(int *)(vars + 0x254) = PlayMobySound(0, 4, moby);
    if (distance < speed * brakeRatio) {
        speed -= accelStep;
        done = 1;
    } else {
        speed += accelStep * EaseOutQuad((maxStep - speed) / maxStep);
    }
    vec_scale_to_length(toGoal, toGoal, speed);
    velocity = vars + 0x230;
    FastVecScale(velocity, velocity, blend);
    FastVecScale(toGoal, toGoal, 1.0f - blend);
    FastVecAdd(velocity, velocity, toGoal);
    MoveAndCollideObject(moby, velocity, 0, 0.0f, 1.5f, 0.0f);
    MobySpringTurn(moby, targetYaw, 0.0005817765f, 0.0017453294713050127f, 0.03490659222006798f, vars + 0x25C);
    return done;
}
