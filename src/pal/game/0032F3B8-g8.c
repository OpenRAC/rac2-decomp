#include "common.h"

/* func_PAL_0032F3B8, the PAL copy of func_0032DA58: the same C, where the small-data timers
   are ints scaled for 50 Hz, and each float goes straight to its field ahead of the next scale. */
extern char *CreateMoby(int);
extern void cam_compute_view_direction(void *, void *, int);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_angle(void), IntToFloat(int);
extern int CollLine(void *, void *, int, void *, int);
extern int math_fast_helper_a(void *, float);
extern void func_PAL_0032F7C8(void *, void *);
extern char g_camera_eye_state[];
extern float g_blast_moby_height_limit __attribute__((sda));
extern int g_blast_moby_first_id_a __attribute__((sda)), g_blast_moby_second_id __attribute__((sda));
extern int g_blast_moby_first_id_b __attribute__((sda)), g_blast_moby_first_id_c __attribute__((sda));
extern int g_blast_moby_state_short_a __attribute__((sda)), g_blast_moby_state_short_b __attribute__((sda));
extern int g_blast_moby_state_word __attribute__((sda)), g_blast_moby_extra_word __attribute__((sda));
char *func_PAL_0032F3B8(int unused, float *position, float *direction, float height)
{
    float basis[4], offset[4], sphere[4];
    char *self = CreateMoby(0xD4E);
    char *state;
    int extra;
    if (self) {
        *(unsigned char *)(self + 0x30) = 255;
        *(short *)(self + 0x32) = 255;
        state = *(char **)(self + 0x68);
        *(char *)(self + 0x20) = 0;
        qcopy(self + 0x10, position);
        *(float *)(self + 0x1C) = 1.0f;
        cam_compute_view_direction(self + 0x10, basis, 1);
        qcopy(self + 0xC0, direction);
        FastVecCross(self + 0xD0, self + 0xC0, basis);
        vec_scale_to_length(self + 0xD0, self + 0xD0, 1.0f);
        FastVecCross(self + 0xE0, self + 0xD0, self + 0xC0);
        *(float *)(self + 0xCC) = *(float *)(self + 0xDC) = *(float *)(self + 0xEC) = 0.0f;
        FastVecScale(offset, self + 0xC0, 0.5f);
        FastVecAdd(self + 0x10, self + 0x10, offset);
        if (height != 0.0f) {
            if (g_blast_moby_height_limit * 1.5f <= *(float *)(self + 0x18) - height) height = 0.0f;
        }
        *(float *)(state + 0x18) = height;
        *(float *)(state + 0) = math_random_angle();
        *(float *)(state + 4) = math_random_angle();
        *(float *)(state + 8) = math_random_angle();
        *(float *)(state + 12) = math_random_angle();
        *(float *)(state + 16) = math_random_angle();
        *(float *)(state + 20) = math_random_angle();
        *(short *)(state + 0x1C) = ((s32)(g_blast_moby_first_id_a) * 5 + 2) / 6;
        *(short *)(state + 0x1E) = ((s32)(g_blast_moby_second_id) * 5 + 2) / 6;
        *(float *)(state + 0x20) = 1.0f / IntToFloat(*(short *)(state + 0x1C));
        *(float *)(state + 0x24) = 1.0f / IntToFloat(*(short *)(state + 0x1E));
        *(short *)(state + 0x28) = *(short *)(state + 0x1C) - ((s32)(g_blast_moby_first_id_b) * 5 + 2) / 6;
        *(float *)(state + 0x2C) = 1.0f / IntToFloat(*(short *)(state + 0x28));
        *(short *)(state + 0x2A) = *(short *)(state + 0x1E) - ((s32)(g_blast_moby_first_id_c) * 5 + 2) / 6;
        *(float *)(state + 0x30) = 1.0f / IntToFloat(*(short *)(state + 0x2A));
        if (CollLine(self + 0x10, g_camera_eye_state, 18, 0, 0)) {
            *(short *)(state + 0x36) = 0;
        } else {
            *(short *)(state + 0x36) = (((int)(g_blast_moby_state_short_a) * 5 + 2) / 6);
            *(float *)(state + 0x38) = 1.0f / IntToFloat(*(short *)(state + 0x36));
            qcopy(sphere, self + 0x10);
            sphere[3] = 1.0f;
            if (math_fast_helper_a(sphere, 128.0f) == 1) {
                *(short *)(state + 0x34) = (((int)(g_blast_moby_state_short_b) * 5 + 2) / 6);
                *(float *)(state + 0x3C) = 1.0f / IntToFloat(*(short *)(state + 0x34));
                *(int *)(state + 0x40) = (((int)(g_blast_moby_state_word) * 5 + 2) / 6);
                *(float *)(state + 0x44) = 1.0f / IntToFloat(*(int *)(state + 0x40));
                extra = (((int)(g_blast_moby_extra_word) * 5 + 2) / 6);
                *(int *)(state + 0x40) += extra;
            } else {
                *(short *)(state + 0x34) = 0;
                *(int *)(state + 0x40) = 0;
            }
        }
        func_PAL_0032F7C8(self, basis);
    }
    return self;
}
