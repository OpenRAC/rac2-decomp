#include "include_asm.h"

#include "common.h"

extern void func_0032F620(int, int, int);

/* func_L13_0041B670 is in L13_0041B670-g16.c (-G16). */

/* Plays the resident message for the sub-object's state; states 2..4 and the
   out-of-range case repeat the default message in their own block. */

/* func_L13_0041BAE0 is in L13_0041BAE0-ring.c (-G32). */

/* func_L13_0041FBE0 is in L13_0041FBE0-g64.c (-G64). */




/* func_L13_00438D88 is in L13_00438D88.c (-g). */

typedef struct { float x, y, z, w; } __attribute__((aligned(16))) PathPoint;
typedef struct { int count; int reserved[3]; PathPoint point[0]; } CameraPath;
extern char *g_cam_settings_table[] __attribute__((sda));
extern char *g_camera_path_source;
extern CameraPath *g_guard_path_table[];
extern float g_hero_position[4];
extern float fast_vec_dist(void *, void *);
extern int find_nearest_path_point(void *, void *, void *, int *, float *, int, float, float, float);
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void cam_path_init(char *);

/* Starts the path camera: copies the current camera view, measures the path segments and checks which way the player faces along the path. */
void cam_path_start(char *camera) {
    float projected[4] __attribute__((aligned(16)));
    float tangent[4] __attribute__((aligned(16)));
    float difference[4] __attribute__((aligned(16)));
    int segment;
    float fraction;
    char *source;
    char *settings = *(char **)(g_cam_settings_table[0] + *(short *)(camera + 0x84) * 32 + 0x1C);
    source = g_camera_path_source;
    qcopy(camera + 0x30, source + 0x30);
    qcopy(camera, source);
    qcopy(camera + 0x10, source + 0x10);
    qcopy(camera + 0x20, source + 0x20);
    qcopy(camera + 0x40, camera);
    if (*(int *)(settings + 0x20) >= 0) {
        CameraPath *path = g_guard_path_table[*(int *)(settings + 0x20)];
        int i;
        for (i = 0; i < path->count; i++) {
            path->point[i].w = fast_vec_dist(&path->point[i], &path->point[(i + 1) % path->count]);
        }
    }
    *(short *)(settings + 0x36) = 0;
    if (*(int *)(settings + 0x30) == 3) {
        CameraPath *path = g_guard_path_table[*(int *)(settings + 0x20)];
        segment = 0;
        fraction = 0.0f;
        if (find_nearest_path_point(path, g_hero_position, projected, &segment, &fraction, 0, 20.0f, 1.0f, 0.0f)) {
            int count = path->count;
            int next = segment + 1;
            if (next >= count) next = count - 1;
            FastVecSub(tangent, &path->point[next], &path->point[segment]);
            if (FastVecLength(tangent) != 0.0f && next != segment) {
                vec_scale_to_length(tangent, tangent, 1.0f);
                FastVecSub(difference, camera + 0x30, g_hero_position);
                if (FastVecDot(difference, tangent) > 0.0f)
                    *(short *)(settings + 0x36) = 1;
            }
        }
    }
    cam_path_init(camera);
}
