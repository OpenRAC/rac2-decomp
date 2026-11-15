#include "common.h"
extern char *CreateMoby(int);
extern void cam_compute_view_direction(void *, void *, int);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_angle(void), IntToFloat(int);
extern int CollLine(void *, void *, int, void *, int);
extern int math_fast_helper_a(void *, float);
extern void part_emit_blast_and_shake(void *, void *);
extern char g_camera_eye_state[];
extern float D_001B081C __attribute__((sda));
extern short D_001B0750 __attribute__((sda)), D_001B0778 __attribute__((sda));
extern short D_001B0754 __attribute__((sda)), D_001B077C __attribute__((sda));
extern short D_001B0828 __attribute__((sda)), D_001B082C __attribute__((sda));
extern int D_001B0834 __attribute__((sda)), D_001B0838 __attribute__((sda));
/* Spawns a small blast effect at a position, giving it random spin and timing values. It also adds a ground mark when the spot is on a surface. */
char *part_spawn_blast_effect_moby(int unused, float *position, float *direction, float height)
{
    float basis[4], offset[4], sphere[4];
    char *self = CreateMoby(0xD4E /* moby class 3406 */);
    char *state;
    float value;
    unsigned short first, second;
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
            if (D_001B081C * 1.5f <= *(float *)(self + 0x18) - height) height = 0.0f;
        }
        *(float *)(state + 0x18) = height;
        *(float *)(state + 0) = math_random_angle();
        *(float *)(state + 4) = math_random_angle();
        *(float *)(state + 8) = math_random_angle();
        *(float *)(state + 12) = math_random_angle();
        *(float *)(state + 16) = math_random_angle();
        value = math_random_angle();
        first = D_001B0750;
        second = D_001B0778;
        *(short *)(state + 0x1C) = first;
        *(short *)(state + 0x1E) = second;
        *(float *)(state + 20) = value;
        *(float *)(state + 0x20) = 1.0f / IntToFloat(*(short *)(state + 0x1C));
        value = 1.0f / IntToFloat(*(short *)(state + 0x1E));
        first = D_001B0754;
        *(short *)(state + 0x28) = *(short *)(state + 0x1C) - first;
        *(float *)(state + 0x24) = value;
        value = 1.0f / IntToFloat(*(short *)(state + 0x28));
        first = D_001B077C;
        *(short *)(state + 0x2A) = *(short *)(state + 0x1E) - first;
        *(float *)(state + 0x2C) = value;
        *(float *)(state + 0x30) = 1.0f / IntToFloat(*(short *)(state + 0x2A));
        if (CollLine(self + 0x10, g_camera_eye_state, 18, 0, 0)) {
            *(short *)(state + 0x36) = 0;
        } else {
            *(short *)(state + 0x36) = D_001B0828;
            *(float *)(state + 0x38) = 1.0f / IntToFloat(*(short *)(state + 0x36));
            qcopy(sphere, self + 0x10);
            sphere[3] = 1.0f;
            if (math_fast_helper_a(sphere, 128.0f) == 1) {
                *(short *)(state + 0x34) = D_001B082C;
                *(float *)(state + 0x3C) = 1.0f / IntToFloat(*(short *)(state + 0x34));
                *(int *)(state + 0x40) = D_001B0834;
                *(float *)(state + 0x44) = 1.0f / IntToFloat(*(int *)(state + 0x40));
                extra = D_001B0838;
                *(int *)(state + 0x40) += extra;
            } else {
                *(short *)(state + 0x34) = 0;
                *(int *)(state + 0x40) = 0;
            }
        }
        part_emit_blast_and_shake(self, basis);
    }
    return self;
}
