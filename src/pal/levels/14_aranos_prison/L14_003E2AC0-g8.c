#include "common.h"

/* func_PAL_L14_003E2AC0, the PAL copy of func_L14_003DE9B0 by way of USA v2.00's
 * func_US2_L14_003DFE88: case 0 also records the current angle at s + 0x1C and scales the
 * turn speed by 1.2 for 50 Hz, and case 2 fades the colour by the angle left to turn. */

/* Widen the packed high channels before combining the low channel, retaining
 * the original color-expression grouping with the pinned compiler. */

extern char *g_moby_l14_pool __attribute__((sda));
extern char g_hero_position[];
/* One unsplit `la`: it cannot fill the guard branch's delay slot, so the slot comes from the target. */
extern char g_identity_l14_matrix[] MACRO_ADDR;
extern void moby_set_state(void *, int, int);
extern int flag_set_first_pending(void *);
extern float fast_vec_dist(void *, void *);
extern int IsPointInCuboid(void *, int);
extern float math_fast_sin_or_cos_b(float);
extern void moby_set_flag_bit(void *, int);
extern void moby_rotate_about_point(void *, void *, float, float, float);
extern void euler_rotation_basis(void *, void *);

/* Spinning glow piece: waits for the hero, then turns half a revolution while its colour fades, and pulses its glow all the time. */
void swinging_glow_update_pal(char *self) {
    float v[4] __attribute__((aligned(16)));
    char *vars = *(char **)(self + 0x68);
    int glow, fade;

    switch ((unsigned char)self[0x20]) {
    case 0:
        if (*(int *)vars >= 0) {
            *(char **)(vars + 0x10) = g_moby_l14_pool + (*(int *)vars << 8);
            *(int *)(self + 0x78) = 0x80404040;
            *(unsigned short *)(self + 0x34) |= 0x10;
            *(int *)(vars + 0x14) = 0;
        } else {
            *(int *)(vars + 0x10) = 0;
        }
        *(float *)(vars + 4) *= 1.2f;
        if (*(int *)(vars + 8)) {
            *(float *)(vars + 0x1C) = *(float *)(self + 0xF4);
        } else {
            *(float *)(vars + 0x1C) = *(float *)(self + 0xF8);
        }
        moby_set_state(self, 1, -1);
        break;
    case 1:
        glow = *(int *)(vars + 0x18);
        *(int *)(self + 0x78) = (long long)(int)(0x80000000 | (glow << 16) | (glow << 8)) | glow;
        if (*(int *)(vars + 0xC) == -1) {
            if (fast_vec_dist(g_hero_position, self + 0x10) < 10.0f) {
                moby_set_state(self, 2, -1);
            }
        } else if (IsPointInCuboid(g_hero_position, *(int *)(vars + 0xC))) {
            moby_set_state(self, 2, -1);
        }
        break;
    case 2:
        if (*(int *)(vars + 8)) {
            fade = (int)((float)*(int *)(vars + 0x18) * (*(float *)(self + 0xF4) + 3.1415927f) * 0.31830987f);
        } else {
            fade = (int)((float)*(int *)(vars + 0x18) * (3.1415927f - *(float *)(self + 0xF8)) * 0.31830987f);
        }
        *(int *)(self + 0x78) = (long long)(int)(0x80000000 | (fade << 16) | (fade << 8)) | *(int *)(vars + 0x18);
        if ((*(float *)(self + 0xF8) >= 3.1415927f && !*(int *)(vars + 8)) ||
            (*(float *)(self + 0xF4) <= -3.1415927f && *(int *)(vars + 8))) {
            moby_set_state(self, 3, -1);
            break;
        }
        if (*(int *)(vars + 8)) {
            *(float *)(self + 0xF4) -= *(float *)(vars + 4);
        } else {
            *(float *)(self + 0xF8) += *(float *)(vars + 4);
        }
        if (*(char **)(vars + 0x10)) {
            qcopy(v, g_identity_l14_matrix);
            v[2] -= 0.5f;
            moby_rotate_about_point(*(char **)(vars + 0x10), v, *(float *)(vars + 4), 0.0f, 0.0f);
            euler_rotation_basis(*(char **)(vars + 0x10) + 0xC0, *(char **)(vars + 0x10) + 0xF0);
        }
        break;
    case 3:
        if (flag_set_first_pending(self)) {
            *(float *)(self + 0xF8) = 3.1415927f;
            if (*(char **)(vars + 0x10)) {
                moby_set_flag_bit(*(char **)(vars + 0x10), 1);
            }
        }
        *(int *)(self + 0x78) = *(int *)(vars + 0x18) | 0x80000000;
        break;
    }
    ++*(int *)(vars + 0x14);
    *(int *)(vars + 0x18) = (int)(math_fast_sin_or_cos_b((float)(*(int *)(vars + 0x14) % 150) * 0.041887905f) * 48.0f) + 80;
}
