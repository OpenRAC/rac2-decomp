/* func_PAL_L01_00432438, the PAL copy of func_L01_0042C8D8: the same C, where 0.016666668f becomes
   0.020000001f; func_L01_002BEB90 becomes func_PAL_L01_002BEC60. */
#include "common.h"
typedef float RouteVector[4] __attribute__((aligned(16)));
typedef struct { short idx[8]; float angle[8]; float roll; } PathKeys;
typedef struct { char pad0[0x20]; int path; int look; int target; float offset[3]; char pad38; unsigned char finished; char pad3a[2]; float speed; char pad40[0x18]; int lock; } CameraPath;
typedef struct { int segment; float distance; float length; float scale; float travelled; short started; short stop; } PathMotion;
extern unsigned char *g_camera_path_configs;
extern unsigned char *g_path_l01_table[];
extern unsigned char *g_moby_l01_table;
extern unsigned char g_water_view_matrix[];
extern unsigned char g_hero_state_block[];
extern int g_camera_lock_flag;
extern int D_L01_001B1FA8_gp SDATA(D_L01_001B1FA8);
extern int Spline_AdvanceByDistance(void *, void *, void *, void *, int, float);
extern int FastDecTimer(void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern float fast_vec_dist(void *, void *);
extern void cam_set_value_target(int, int, float, float, float, float);
extern void cam_set_transition_frames(float);
extern float math_cosine_blend(float, float, float);
extern s32 func_PAL_L01_002BEC60(int, int);

void func_PAL_L01_00432438(unsigned char *camera)
{
    RouteVector old, up, direction, target;
    unsigned char *v = *(unsigned char **)(camera + 0x70);
    CameraPath *c = *(CameraPath **)(g_camera_path_configs + *(short *)(camera + 0x84) * 32 + 0x1c);
    PathMotion *motion = (PathMotion *)(v + 0x40);
    unsigned char *path;
    PathKeys *keys = (PathKeys *)(v + 0x58);
    int done, i, j, k, target_index, local_segment;
    float along, total, local_distance;
    if (!motion->started) {
        unsigned char *start = g_path_l01_table[c->path];
        unsigned char *look = g_path_l01_table[c->look];
        if (c->lock) g_camera_lock_flag = 1;
        motion->started = 1;
        qcopy(camera + 0x30, start + 0x10);
        target_index = c->target;
        if (target_index >= 0) {
            float *src = c->offset;
            unsigned char *entity = g_moby_l01_table + target_index * 256;
            up[0] = src[0]; up[1] = src[1]; up[2] = src[2];
            *(int *)&up[3] = 0;
            matrix_mul_vec3(up, up, g_water_view_matrix);
            FastVecAdd(direction, entity + 0x10, up);
            FastVecSub(old, direction, camera + 0x30);
        } else FastVecSub(old, look + 0x10, camera + 0x30);
        FastVecScale(up, g_hero_state_block, -1.0f);
        vec_scale_to_length(camera, old, 1.0f);
        FastVecCross(camera + 0x10, camera, up);
        vec_scale_to_length(camera + 0x10, camera + 0x10, 1.0f);
        FastVecCross(camera + 0x20, camera + 0x10, camera);
        return;
    }
    path = g_path_l01_table[c->path];
    qcopy(old, camera + 0x30);
    done = Spline_AdvanceByDistance(path, camera + 0x30, &motion->segment, v + 0x44, 0, c->speed * 0.020000001f);
    if (motion->stop && FastDecTimer(v + 0x56)) done = 1;
    if (c->finished) done = 1;
    if (done) {
        c->finished = 1;
        cam_set_value_target(0, 3, keys->roll, 0.005f, 0.2f, 0.0f);
        cam_set_transition_frames(4.0f);
        *(short *)(camera + 0x7e) = 4;
        if (c->lock) D_L01_001B1FA8_gp = 0;
        func_PAL_L01_002BEC60(0, 1);
        return;
    }
    for (i = 0; i < 7 && keys->idx[i] >= 0 && keys->idx[i + 1] >= 0; ++i) {
        if (motion->segment >= keys->idx[i] && motion->segment < keys->idx[i + 1]) {
            along = 0;
            for (j = keys->idx[i]; j < motion->segment; ++j) along += *(float *)(path + j * 16 + 0x1c);
            total = along;
            along += motion->distance;
            for (k = motion->segment; k < keys->idx[i + 1]; ++k) total += *(float *)(path + k * 16 + 0x1c);
            cam_set_value_target(0, 3, math_cosine_blend(keys->angle[i],
                keys->angle[i + 1], along / total) * 0.017453294f, 0.005f, 0.2f, 0);
        }
    }
    motion->travelled += fast_vec_dist(old, camera + 0x30);
    target_index = c->target;
    if (target_index >= 0) {
        float *src = c->offset;
        unsigned char *entity = g_moby_l01_table + target_index * 256;
        direction[0] = src[0]; direction[1] = src[1]; direction[2] = src[2];
        *(int *)&direction[3] = 0;
        matrix_mul_vec3(direction, direction, g_water_view_matrix);
        FastVecAdd(target, entity + 0x10, direction);
        FastVecSub(up, target, camera + 0x30);
    } else {
        float progress = motion->travelled / motion->length * motion->scale;
        local_segment = 0; local_distance = 0;
        Spline_AdvanceByDistance(g_path_l01_table[c->look], direction, &local_segment, &local_distance, 0, progress);
        FastVecSub(up, direction, camera + 0x30);
    }
    FastVecScale(direction, g_hero_state_block, -1.0f);
    vec_scale_to_length(camera, up, 1.0f);
    FastVecCross(camera + 0x10, camera, direction);
    vec_scale_to_length(camera + 0x10, camera + 0x10, 1.0f);
    FastVecCross(camera + 0x20, camera + 0x10, camera);
}
