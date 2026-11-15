#include "common.h"
extern float D_L08_001B1F94 __attribute__((sda)), D_L08_001B1F98 __attribute__((sda)), D_L08_001B1F78 __attribute__((sda)), D_L08_001B1F7C __attribute__((sda)), D_L08_001B1FA4 __attribute__((sda));
extern float D_L08_001B1F8C __attribute__((sda)), D_L08_001B1F80 __attribute__((sda)), D_L08_001B1F84 __attribute__((sda)), D_L08_001B1F88 __attribute__((sda));
extern float D_L08_001B1F90 __attribute__((sda)), D_L08_001B1F74 __attribute__((sda)), D_L08_001B1FA0 __attribute__((sda));
extern u8 D_L08_001B1F9C __attribute__((sda));
extern float D_L08_001B031C[] __attribute__((sda));
extern float D_L08_001B9D30[];
extern void moby_mark_spawned(void *);
extern float vec_distance_xy(void *, void *);
extern int math_fast_helper_a(void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void UpdateNearestTarget(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);

/* Per-frame update of moby class 2456: it slides between two points toward a target and turns to face it. It deletes itself when the target is gone. */
/* Interpolates an object between two points and turns it toward its target. */
void target_l08_follower_update(u8 *moby)
{
    float base[4] __attribute__((aligned(16)));
    float endpoint[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(moby+0x68);
    u8 *target;
    float distance;
    float limit, scale;
    int result;
    *(float *)(moby+0x2C) = *(float *)(*(u8 **)(moby+0x24)+0x24) *
        (D_L08_001B1F94 + (D_L08_001B1F98-D_L08_001B1F94)* *(float *)(vars+0x18));
    moby[0x23] = D_L08_001B1F9C;
    target = *(u8 **)(vars+0x10);
    if (!target || target[0x20]==0xFE || target[0x20]==0xFD) {
        moby_mark_spawned(moby);
        return;
    }
    distance = vec_distance_xy(target+0x10, vars);
    limit = D_L08_001B1F7C;
    *(float *)(vars+0xC) = D_L08_001B1FA4;
    result = math_fast_helper_a(vars,limit);
    qcopy(base, vars);
    base[2] += D_L08_001B1F8C;
    delta[0] = D_L08_001B1F80;
    delta[1] = D_L08_001B1F84;
    delta[2] = D_L08_001B1F88;
    matrix_mul_vec3(delta,delta,D_L08_001B9D30);
    FastVecAdd(endpoint,delta,D_L08_001B9D30-140);
    if (distance < D_L08_001B1F78) UpdateNearestTarget(moby,vars);
    if (distance < D_L08_001B1F7C && (result > 0 || distance < D_L08_001B031C[0]))
        *(float *)(vars+0x18) += D_L08_001B1F90;
    else *(float *)(vars+0x18) -= D_L08_001B1F90;
    if (*(float *)(vars+0x18)>1.0f) *(float *)(vars+0x18)=1.0f;
    else if (*(float *)(vars+0x18)<0.0f) *(float *)(vars+0x18)=0.0f;
    FastVecSub(delta,base,endpoint);
    FastVecScale(delta,delta,*(float *)(vars+0x18));
    FastVecAdd(moby+0x10,endpoint,delta);
    *(float *)(moby+0xF8) = mat_fast_helper_a(*(float *)vars-*(float *)(moby+0x10),*(float *)(vars+4)-*(float *)(moby+0x14));
    distance = vec_distance_xy(moby+0x10,vars);
    distance = mat_fast_helper_a(distance,*(float *)(vars+8)-*(float *)(moby+0x18));
    scale = D_L08_001B1FA0*0.00029088825f;
    *(float *)(moby+0xF4) = -distance;
    *(float *)(moby+0xF0) = FastAddRotations(*(float *)(moby+0xF0),scale);
}
