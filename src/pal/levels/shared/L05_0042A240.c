#include "include_asm.h"

#include "common.h"
extern char *CreateMoby(int);
extern char g_origin_vec[];
extern void cam_compute_view_direction(void *, void *, int);
extern void FastVecCross(void *, void *, void *);
extern int math_fast_helper_a(void *, float);
extern float fast_vec_dist(void *, void *);
extern float FastVecDot(void *, void *);
extern float math_fast_angle_helper(float);
extern void part_spawn_large_explosion_pal(void *, void *);
extern void FastVecSub(float *, void *, float *);
extern void vec_scale_to_length(float *, float *, float);

/* Creates a camera-facing burst, sets its lifetime and colors, and shakes
   the camera when a visible burst is nearby. */
char *moby_spawn_large_explosion_pal(void *pos, int shake, int c20, int c24, int c28,
                         int c2c, int c30, int unused, int c34, int mode,
                         int c38, float scale)
{
    float toward[4], up[4], sphere[4], camera_dir[4];
    char *moby = CreateMoby(0x116A);
    char *state;

    if (moby) {
        state = *(char **)(moby + 0x68);
        *(unsigned char *)(moby + 0x30) = 255;
        *(unsigned short *)(moby + 0x32) = 255;
        moby[0x20] = 0;
        qcopy(moby + 0x10, pos);
        *(float *)(moby + 0x1C) = 1.0f;
        FastVecSub(toward, g_origin_vec, (float *)(moby + 0x10));
        vec_scale_to_length(toward, toward, 1.0f);
        cam_compute_view_direction(moby + 0x10, up, 1);
        qcopy(moby + 0xC0, toward);
        FastVecCross(moby + 0xD0, moby + 0xC0, up);
        vec_scale_to_length((float *)(moby + 0xD0), (float *)(moby + 0xD0), 1.0f);
        FastVecCross(moby + 0xE0, moby + 0xD0, moby + 0xC0);
        *(float *)(moby + 0xCC) = *(float *)(moby + 0xDC) = *(float *)(moby + 0xEC) = 0.0f;
        *(short *)state = 50;
        *(short *)(state + 2) = 50;
        *(float *)(state + 8) = scale + scale;
        *(float *)(state + 0xC) = scale * 4.0f;
        *(int *)(state + 0x20) = c20;
        *(int *)(state + 0x24) = c24;
        *(int *)(state + 0x28) = c28;
        *(int *)(state + 0x2C) = c2c;
        *(int *)(state + 0x30) = c30;
        *(int *)(state + 0x34) = c34;
        *(int *)(state + 0x1C) = mode;
        *(int *)(state + 0x38) = c38;
        *(float *)(state + 0x14) = scale;
        *(int *)(state + 0x18) = 0;
        qcopy(sphere, moby + 0x10);
        sphere[3] = scale * 3.0f;
        if (math_fast_helper_a(sphere, 128.0f) == 1) {
            *(short *)(state + 4) = 8;
            *(float *)(state + 0x10) = 0.125f;
            if (fast_vec_dist(pos, g_origin_vec) < 48.0f && shake) {
                char *mgr = g_origin_vec - 0x140;

                *(int *)(mgr + 0x16C) = 0;
                *(int *)(mgr + 0x168) = 33;
                *(float *)(mgr + 0x160) = 0.075f;
            }
            if (*(int *)(state + 0x18)) {
                FastVecSub(camera_dir, moby + 0x10, (float *)g_origin_vec);
                vec_scale_to_length(camera_dir, camera_dir, 1.0f);
                if (1.5707964f - math_fast_angle_helper(FastVecDot(camera_dir, g_origin_vec + 0x230)) < 0.45378566f)
                    *(int *)(state + 0x18) = 1;
                else
                    *(int *)(state + 0x18) = 0;
            }
        } else {
            *(short *)(state + 4) = 0;
            *(int *)(state + 0x18) = 0;
        }
        part_spawn_large_explosion_pal(moby, up);
    }
    return moby;
}

