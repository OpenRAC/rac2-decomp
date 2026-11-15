#include "common.h"
extern float D_L08_001B1F94 __attribute__((sda)), D_L08_001B1F98 __attribute__((sda)), D_L08_001B1F78 __attribute__((sda)), D_L08_001B1F7C __attribute__((sda)), D_L08_001B1FA4 __attribute__((sda));
extern float D_L08_001B1F8C __attribute__((sda)), D_L08_001B1F80 __attribute__((sda)), D_L08_001B1F84 __attribute__((sda)), D_L08_001B1F88 __attribute__((sda));
extern float D_L08_001B1F90 __attribute__((sda)), D_L08_001B1F74 __attribute__((sda)), D_L08_001B1FA0 __attribute__((sda));
extern u8 D_L08_001B1F9C __attribute__((sda));
extern float D_L08_001B031C[] __attribute__((sda));
extern float D_L08_001B9D30[];
extern void func_0029F338(void *);
extern float func_00282E80(void *, void *);
extern int func_00283DB8(void *, float);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_L08_003D3928(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);

/* Interpolates an object between two points and turns it toward its target. */
void func_L08_004356B8(u8 *self)
{
    float base[4] __attribute__((aligned(16)));
    float endpoint[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(self+0x68);
    u8 *target;
    float distance;
    float limit, scale;
    int result;
    *(float *)(self+0x2C) = *(float *)(*(u8 **)(self+0x24)+0x24) *
        (D_L08_001B1F94 + (D_L08_001B1F98-D_L08_001B1F94)* *(float *)(vars+0x18));
    self[0x23] = D_L08_001B1F9C;
    target = *(u8 **)(vars+0x10);
    if (!target || target[0x20]==0xFE || target[0x20]==0xFD) {
        func_0029F338(self);
        return;
    }
    distance = vec_distance_xy(target+0x10, vars);
    limit = D_L08_001B1F7C;
    *(float *)(vars+0xC) = D_L08_001B1FA4;
    result = func_00283DB8(vars,limit);
    qcopy(base, vars);
    base[2] += D_L08_001B1F8C;
    delta[0] = D_L08_001B1F80;
    delta[1] = D_L08_001B1F84;
    delta[2] = D_L08_001B1F88;
    matrix_mul_vec3(delta,delta,D_L08_001B9D30);
    FastVecAdd(endpoint,delta,D_L08_001B9D30-140);
    if (distance < D_L08_001B1F78) UpdateNearestTarget(self,vars);
    if (distance < D_L08_001B1F7C && (result > 0 || distance < D_L08_001B031C[0]))
        *(float *)(vars+0x18) += D_L08_001B1F90;
    else *(float *)(vars+0x18) -= D_L08_001B1F90;
    if (*(float *)(vars+0x18)>1.0f) *(float *)(vars+0x18)=1.0f;
    else if (*(float *)(vars+0x18)<0.0f) *(float *)(vars+0x18)=0.0f;
    FastVecSub(delta,base,endpoint);
    FastVecScale(delta,delta,*(float *)(vars+0x18));
    FastVecAdd(self+0x10,endpoint,delta);
    *(float *)(self+0xF8) = func_00283248(*(float *)vars-*(float *)(self+0x10),*(float *)(vars+4)-*(float *)(self+0x14));
    distance = vec_distance_xy(self+0x10,vars);
    distance = func_00283248(distance,*(float *)(vars+8)-*(float *)(self+0x18));
    scale = D_L08_001B1FA0*0.00029088825f;
    *(float *)(self+0xF4) = -distance;
    *(float *)(self+0xF0) = FastAddRotations(*(float *)(self+0xF0),scale);
}
