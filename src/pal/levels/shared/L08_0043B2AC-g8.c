#include "names.h"
/* func_PAL_L08_0043B2AC, the PAL copy of func_L08_004356B8: the same C, where both
   `vars+0x18` steps become `D_L08_001B1F90 * 1.2f` and 0.00029088825f becomes 0.0003490659f. */
#include "common.h"
extern float g_attached_effect_scale __attribute__((sda)), g_follower_scale_max __attribute__((sda)), g_follower_near_distance __attribute__((sda)), g_follower_target_range __attribute__((sda)), g_follower_initial_value __attribute__((sda));
extern float g_follower_base_height __attribute__((sda)), g_follower_delta_x __attribute__((sda)), g_follower_delta_y __attribute__((sda)), g_follower_delta_z __attribute__((sda));
extern float g_follower_scale_step __attribute__((sda)), g_follower_float_param_a __attribute__((sda)), g_follower_angle_degrees __attribute__((sda));
extern u8 g_follower_moby_flag __attribute__((sda));
extern float g_hud_l08_bar_threshold[] __attribute__((sda));
extern float g_hero_l08_matrix[];
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

/* Interpolates an object between two points and turns it toward its target. */
void func_PAL_L08_0043B2AC(u8 *self)
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
        (g_attached_effect_scale + (g_follower_scale_max-g_attached_effect_scale)* *(float *)(vars+0x18));
    self[0x23] = g_follower_moby_flag;
    target = *(u8 **)(vars+0x10);
    if (!target || target[0x20]==0xFE || target[0x20]==0xFD) {
        moby_mark_spawned(self);
        return;
    }
    distance = vec_distance_xy(target+0x10, vars);
    limit = g_follower_target_range;
    *(float *)(vars+0xC) = g_follower_initial_value;
    result = math_fast_helper_a(vars,limit);
    qcopy(base, vars);
    base[2] += g_follower_base_height;
    delta[0] = g_follower_delta_x;
    delta[1] = g_follower_delta_y;
    delta[2] = g_follower_delta_z;
    matrix_mul_vec3(delta,delta,g_hero_l08_matrix);
    FastVecAdd(endpoint,delta,g_hero_l08_matrix-140);
    if (distance < g_follower_near_distance) UpdateNearestTarget(self,vars);
    if (distance < g_follower_target_range && (result > 0 || distance < g_hud_l08_bar_threshold[0]))
        *(float *)(vars+0x18) += g_follower_scale_step * 1.2f;
    else *(float *)(vars+0x18) -= g_follower_scale_step * 1.2f;
    if (*(float *)(vars+0x18)>1.0f) *(float *)(vars+0x18)=1.0f;
    else if (*(float *)(vars+0x18)<0.0f) *(float *)(vars+0x18)=0.0f;
    FastVecSub(delta,base,endpoint);
    FastVecScale(delta,delta,*(float *)(vars+0x18));
    FastVecAdd(self+0x10,endpoint,delta);
    *(float *)(self+0xF8) = mat_fast_helper_a(*(float *)vars-*(float *)(self+0x10),*(float *)(vars+4)-*(float *)(self+0x14));
    distance = vec_distance_xy(self+0x10,vars);
    distance = mat_fast_helper_a(distance,*(float *)(vars+8)-*(float *)(self+0x18));
    scale = g_follower_angle_degrees*0.0003490659f;
    *(float *)(self+0xF4) = -distance;
    *(float *)(self+0xF0) = FastAddRotations(*(float *)(self+0xF0),scale);
}
