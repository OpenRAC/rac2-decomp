#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; s32 w[4]; } V4_F428000;

extern float g_cam_target_offset[];
typedef struct { u8 pad[0x80]; V4_F428000 pos; u8 pad90[0x1220 - 0x90]; char *partner; } HeroView_F428000;
typedef struct { u8 pad[0x140]; V4_F428000 pos; u8 pad150[8]; float yaw; } CamView_F428000;
extern HeroView_F428000 g_hero_state;
extern CamView_F428000 g_scalar_transition_state;

extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_copy5_blend_first(void *, void *, float);
extern void cam_set_target_and_weight(char *, void *, float, void *);
extern float FastAddRotations(float, float);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float vec_distance_xy(void *, void *);
extern void vec_transform_or_copy(void *, void *);

/* func_US2_L00_00429510, the USA v2.00 copy of func_L00_00428000: the same C, where the smaller of
   the hero's and the partner's distances to the camera becomes the hero's distance alone. */
/* Camera follow step for a target object: aims at a point offset from the target and
   adjusts the orbit by the hero's distance; returns 0 on the easing path, else 1. */
int cam_follow_update_target_us2(char *camera_moby, char *target)
{
    V4_F428000 offset, pos;
    char *camera = *(char **)(camera_moby + 0x70);
    float *orbit = (float *)(camera + 0x64);
    char *follow_info;
    float angle;
    float distance;

    *(char **)(camera + 0xF4) = target;
    if (target != 0) {
        offset.q = 0;
        offset.f[0] = g_cam_target_offset[0];
        offset.f[2] = 0.12f;
        follow_info = *(char **)(target + 0x68);
        matrix_mul_vec3(&offset, &offset, target + 0xC0);
        FastVecAdd(&pos, target + 0x10, &offset);
        if (*(int *)(follow_info + 0x10) == -1) {
            vec_copy5_blend_first(orbit, camera_moby + 0x50, 0.0f);
            orbit[2] = 6.0f;
            orbit[1] = orbit[3];
            orbit[3] = 0.0f;
            cam_set_target_and_weight(camera_moby, orbit, 0.0f, &pos);
        }
        if (*(int *)(follow_info + 0x10) <= 0) {
            *(float *)(camera + 0xAC) = FastAddRotations(*(float *)(camera + 0xAC), *(float *)(follow_info + 0x18));
            *(float *)(follow_info + 0x18) *= 0.97f;
            angle = FastDiffRots(mat_fast_helper_a(g_scalar_transition_state.pos.f[0] - g_hero_state.pos.f[0],
                                                g_scalar_transition_state.pos.f[1] - g_hero_state.pos.f[1]),
                                  g_scalar_transition_state.yaw);
            distance = vec_distance_xy(&g_hero_state.pos, &g_scalar_transition_state.pos);
            if (distance < 0.77f) {
                if (angle < 1.5707965f) {
                    *(float *)(camera + 0x1C) -= 0.7f - distance;
                    *(int *)(follow_info + 4) = 0;
                } else {
                    *(float *)(camera + 0x1C) += 0.7f - distance;
                }
            } else {
                *(float *)(camera + 0x1C) += *(float *)(follow_info + 4);
                *(float *)(follow_info + 4) *= 0.97f;
            }
            qcopy(camera + 0x80, &pos);
            vec_transform_or_copy(camera + 0x80, camera + 0x80);
            return 0;
        }
        *(float *)(camera + 0xAC) = *(float *)(target + 0xF0) * 0.5f;
        *(float *)(camera + 0x20) += (*(float *)(target + 0xF4) - *(float *)(camera + 0x20)) * 0.05f;
        qcopy(camera + 0x80, &pos);
        qcopy(camera + 0xC0, target + 0xF0);
    }
    return 1;
}
