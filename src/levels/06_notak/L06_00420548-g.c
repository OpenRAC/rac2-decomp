#include "names.h"
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(float *, float *, float *);
extern float FastVecLength(float *);
extern void vec_scale_to_length(float *, float *, float);
extern void FastVecScale(void *, void *, float);
extern int PlayMobySound(int, int, void *);
extern float math_ease_out_quad(float);
extern void moby_move_and_collide(void *, void *, int, float, float, float);
extern void MobySpringTurn(void *, float, float, float, float, void *);
extern char D_L06_00188660[];

/* Steps the follower's weight toward its goal and blends the state vectors; returns 1 on arrival. */
int actor_move_toward_goal(char *moby, float accel, float maxSpeed, float targetYaw, float blend)
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
        speed += accelStep * math_ease_out_quad((maxStep - speed) / maxStep);
    }
    vec_scale_to_length(toGoal, toGoal, speed);
    velocity = vars + 0x230;
    FastVecScale(velocity, velocity, blend);
    FastVecScale(toGoal, toGoal, 1.0f - blend);
    FastVecAdd(velocity, velocity, toGoal);
    moby_move_and_collide(moby, velocity, 0, 0.0f, 1.5f, 0.0f);
    MobySpringTurn(moby, targetYaw, 0.0005817765f, 0.0017453294713050127f, 0.03490659222006798f, vars + 0x25C);
    return done;
}
