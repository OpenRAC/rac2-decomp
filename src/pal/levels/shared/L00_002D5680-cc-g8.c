/* func_PAL_L00_002D5680, the PAL copy of func_L00_002D5158: the same C, where rename func_L00_002D64B8 becomes func_PAL_L00_002D6A08; rename func_L00_002D6588 becomes func_PAL_L00_002D6AD8; rename func_L00_002D5940 becomes func_PAL_L00_002D5E90; scale D_L00_001A7CE8. */
#include "common.h"

typedef int HeroVector __attribute__((mode(TI)));
typedef struct {
    char matrix[0x100];
    char pad100[0x5C];
    float heading;
    char pad160[0x30];
    HeroVector motion;
    float motionHeight;
    float motionTarget;
    char pad1A8[0x10];
    int timer;
    char pad1BC[0x10C];
    float groundNormalZ;
    char pad2CC[0xF54];
    char *targetObject;
    char pad1224[0x230];
    short mode;
    char pad1456[0x6];
    float targetHeight;
    char pad1460[0x80];
    float direction[4];
    float pitchRate;
    float yawRate;
    union { float value; int bits; } blend;
    int blendTime;
    int active;
    char pad1504[0x8];
    int activeTime;
    char pad1510[0xD80];
    int probeFlags;
    int state;
} AimHero;
extern AimHero g_hero_state;
typedef struct { char pad[0x100]; float pitch, yaw; } AimInput;
typedef struct { char pad[0x18]; char *object; char unused[4]; float position[4]; } AimProbe;
extern AimInput g_pad_state;
extern AimProbe g_collision_result;
typedef struct { char pad[0x158]; float height; char pad15C[0x214]; HeroVector motion; } AimCamera;
extern AimCamera g_scalar_transition_state;
extern char g_cam_follow_matrix[];
extern int g_invert_aim_option, g_hero_locked_flag;
extern int g_hero_aim_min_timer __attribute__((sda));
extern float g_look_sensitivity_a __attribute__((sda)), g_look_sensitivity_b __attribute__((sda));
extern float g_look_rate_scale_a __attribute__((sda)), g_look_rate_scale_b __attribute__((sda));
extern float g_aim_rate_scale_a __attribute__((sda)), g_aim_rate_scale_b __attribute__((sda));
extern float g_aim_correction_scale __attribute__((sda)), g_aim_damping_scale __attribute__((sda));
extern int hero_is_action_allowed(void);
extern int hero_get_camera_params_pal(float *, float *, float *);
extern void hero_update_camera_block_pal(void), UpdateHeroHeldObject_pal(void);
extern float FastVecLength(void *), vec_length_xy(void *), mat_fast_helper_a(float,float);
extern void vec_scale_to_length(void *,void *,float), matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *), FastVecSub(void *,void *,void *);
extern int CollLine(void *,void *,int,int,int);
extern float fast_vec_dist(void *,void *), math_fabs(float), FastVecDot(void *,void *);
extern void cam_set_view_space_height(void *,void *,float);
extern float fast_subtract_rotations(float,float),FastAddRotations(float,float);
/* EE argument banks are independent: target is $f12, output is $a0,
 * followed by the three $f13-$f15 rates/limit arguments. */
extern void math_approach_target_with_braking(float target, float *output, float rate, float acceleration, float limit);
extern f32 ApproachValue(float *,float,float);
extern void vec_build_spherical_offset(void *,float,float,float), mat_build_rotation_from_angles(void *,void *);
extern void hero_steer_heading(int,float,float,float);
#define HF(o) (*(float *)(hero + (o)))
#define HI(o) (*(int *)(hero + (o)))
/* Update the hero aim direction, collision-sensitive turn rates, and aim transitions. */
void UpdateHeroAimAndTransitions_pal(void)
{
    char *hero;
    char *aim;
    float direction[4], local[4];
    float target, probe_rate, probe_limit, rate, limit, yaw, pitch, yaw_scale, pitch_scale, distance;
    float value, pitch_bound;
    int hit;
    char *object;
    if (hero_is_action_allowed()) {
        aim = (char *)&g_hero_state + 0x14E0;
        if (FastVecLength(aim) == 0.0f)
            vec_scale_to_length(aim, aim - 0x14E0, 1.0f);
        hero = aim - 0x14E0;
        if (HF(0x2C8) > -0.99f)
            matrix_mul_vec3(aim, aim, aim - 0x14A0);
        yaw = mat_fast_helper_a(HF(0x14E0), HF(0x14E4));
        pitch = mat_fast_helper_a(vec_length_xy(aim), HF(0x14E8));
        if (hero_get_camera_params_pal(&target, &probe_rate, &probe_limit)) {
            math_approach_target_with_braking(-pitch, (float *)(aim + 0x10), probe_rate, probe_rate, probe_limit);
            value = fast_subtract_rotations(target, yaw);
            math_approach_target_with_braking(value, (float *)(aim + 0x14), probe_rate, probe_rate, probe_limit);
        } else {
            distance = 0.0f;
            vec_scale_to_length(direction, g_cam_follow_matrix, 30.0f);
            hit = 0;
            FastVecAdd(direction, direction, g_cam_follow_matrix - 0x230);
            if (CollLine(g_cam_follow_matrix - 0x230, direction, 1, HI(0x2290), 0)) {
                char *probe_object = g_collision_result.object;
                if (probe_object && *(short *)(*(char **)(probe_object + 0x24) + 0x46) == 5) {
                    distance = fast_vec_dist(g_cam_follow_matrix - 0x230, g_collision_result.position);
                    hit = 1;
                }
            }
            yaw_scale = math_fabs(g_pad_state.yaw) < 1.0f ? 0.3f : 1.0f;
            pitch_scale = math_fabs(g_pad_state.pitch) < 1.0f ? 0.3f : 1.0f;
            if (hit) {
                if (yaw_scale > 0.6f) yaw_scale = 0.6f;
                if (pitch_scale > 0.6f) pitch_scale = 0.6f;
            }
            limit = -g_pad_state.pitch * 0.0003490659f * g_look_sensitivity_a * pitch_scale;
            rate = g_pad_state.yaw * 0.0003490659f * g_look_sensitivity_b * yaw_scale;
            if (g_invert_aim_option) rate = -rate;
            if (hit) {
                float cap = g_look_sensitivity_b * 0.0003490659f;
                cam_set_view_space_height(local, (char *)&g_hero_state + 0x120, 0.0f);
                if (math_fabs(g_pad_state.pitch) < 1.0f) {
                    float correction = FastVecDot(local, g_cam_follow_matrix + 0x10);
                    correction = -(correction / distance) * g_aim_correction_scale;
                    if (correction > cap) correction = cap;
                    else if (correction < -cap) correction = -cap;
                    if (g_pad_state.pitch == 0.0f) limit = correction;
                    else { limit -= correction; limit *= g_aim_damping_scale; limit += correction; }
                }
                if (math_fabs(g_pad_state.yaw) < 1.0f) {
                    float correction = FastVecDot(local, g_cam_follow_matrix + 0x20);
                    correction = (correction / distance) * g_aim_correction_scale;
                    if (correction > cap) correction = cap;
                    else if (correction < -cap) correction = -cap;
                    if (g_pad_state.yaw == 0.0f) rate = correction;
                    else { rate -= correction; rate *= g_aim_damping_scale; rate += correction; }
                }
            }
            value = math_fabs(g_hero_state.pitchRate);
            if (math_fabs(rate) < value || g_hero_state.pitchRate * rate < 0.0f)
                ApproachValue(&g_hero_state.pitchRate, rate, g_aim_rate_scale_b * 6.981318e-06f);
            else
                ApproachValue(&g_hero_state.pitchRate, rate, g_look_rate_scale_b * (yaw_scale * 6.981318e-06f));
            value = math_fabs(g_hero_state.yawRate);
            if (math_fabs(limit) < value || g_hero_state.yawRate * limit < 0.0f)
                ApproachValue(&g_hero_state.yawRate, limit, g_aim_rate_scale_a * 6.981318e-06f);
            else
                ApproachValue(&g_hero_state.yawRate, limit, g_look_rate_scale_a * (pitch_scale * 6.981318e-06f));
        }
        yaw = FastAddRotations(yaw, g_hero_state.yawRate);
        pitch = FastAddRotations(pitch, g_hero_state.pitchRate);
        if (!g_hero_locked_flag) yaw = FastAddRotations(yaw, g_hero_state.heading);
        pitch_bound = 1.483529999f;
        if (pitch > pitch_bound) { pitch = pitch_bound; g_hero_state.pitchRate = 0; }
        else if (pitch < -pitch_bound) { g_hero_state.pitchRate = 0; pitch = -pitch_bound; }
        aim = (char *)&g_hero_state + 0x14E0;
        vec_build_spherical_offset(aim, 1.0f, yaw, pitch);
        hero = aim - 0x14E0;
        if (g_hero_state.groundNormalZ > -0.99f) matrix_mul_vec3(aim, aim, hero);
        hero_update_camera_block_pal();
        if (!hero_get_camera_params_pal(0, 0, 0)) {
            AimCamera *camera = &g_scalar_transition_state;
            *(short *)(hero + 0x1454) = 2;
            *(float *)(hero + 0x1A0) = camera->height;
            camera = (AimCamera *)((char *)camera + 0x370);
            qcopy(aim - 0x1350, camera);
            *(float *)(hero + 0x1A4) = *(float *)(hero + 0x145C);
            hero_steer_heading(0, 0.053280003f, 0.36f, 0.24434614f);
        }
    }
    if (hero_is_action_allowed() || ((g_hero_state.state == 1 || g_hero_state.state == 0x1D) && g_hero_state.timer >= (((int)(g_hero_aim_min_timer) * 5 + 2) / 6))) {
        if (!g_hero_state.active) {
            object = g_hero_state.targetObject;
            if (object && *(short *)(object + 0xAA) != 0x47) {
                FastVecSub((char *)&g_hero_state + 0x14A0, object + 0x10, (char *)&g_hero_state + 0x80);
                matrix_mul_vec3((char *)&g_hero_state + 0x14A0, (char *)&g_hero_state + 0x14A0, (char *)&g_hero_state + 0x40);
                mat_build_rotation_from_angles((char *)&g_hero_state + 0x14B0, object + 0xF0);
            }
            g_hero_state.active = 1;
            g_hero_state.blend.bits = 0;
            g_hero_state.blendTime = 0;
            g_hero_state.activeTime = 0;
        }
    } else if (g_hero_state.state != 1 && g_hero_state.state != 0x1D) {
        char *old_object;
        if (!g_hero_state.active) return;
        UpdateHeroHeldObject_pal();
        old_object = g_hero_state.targetObject;
        if (old_object && *(short *)(old_object + 0xAA) != 0x47) {
            FastVecSub((char *)&g_hero_state + 0x14A0, old_object + 0x10, (char *)&g_hero_state + 0x80);
            matrix_mul_vec3((char *)&g_hero_state + 0x14A0, (char *)&g_hero_state + 0x14A0, (char *)&g_hero_state + 0x40);
            g_hero_state.blendTime = 0;
            g_hero_state.blend.value = 1.0f;
        }
        g_hero_state.active = 0;
    }
    if (g_hero_state.active) UpdateHeroHeldObject_pal();
}
