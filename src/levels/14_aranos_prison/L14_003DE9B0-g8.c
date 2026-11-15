#include "common.h"

/* Widen the packed high channels before combining the low channel, retaining
 * the original color-expression grouping with the pinned compiler. */

extern char *g_moby_l14_pool __attribute__((sda));
extern char g_hero_position[];
/* One unsplit `la`: it cannot fill the guard branch's delay slot, so the slot comes from the target. */
extern char D_L14_001A8F20[] MACRO_ADDR;
extern void moby_set_state(void *, int, int);
extern int flag_set_first_pending(void *);
extern float fast_vec_dist(void *, void *);
extern int IsPointInCuboid(void *, int);
extern float math_fast_sin_or_cos_b(float);
extern void moby_set_flag_bit(void *, int);
extern void moby_rotate_about_point(void *, void *, float, float, float);
extern void euler_rotation_basis(void *, void *);

/* Updates a moby of class 2791: a glowing light that pulses, swings around to a half turn and then settles, carrying a linked object with it. */
void swinging_glow_update(char *self) {
    float linkPos[4] __attribute__((aligned(16)));
    char *vars = *(char **)(self + 0x68);
    int glow, baseGlow, scaledGlow;

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
        if (flag_set_first_pending(self)) {
            *(int *)(vars + 0x1C) = 100;
        }
        if (*(int *)(vars + 0x1C)) {
            --*(int *)(vars + 0x1C);
        }
        baseGlow = *(int *)(vars + 0x18);
        scaledGlow = (int)((float)baseGlow * (float)*(int *)(vars + 0x1C) * 0.01f);
        *(int *)(self + 0x78) = (long long)(int)(0x80000000 | (scaledGlow << 16) | (scaledGlow << 8)) | baseGlow;
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
            qcopy(linkPos, D_L14_001A8F20);
            linkPos[2] -= 0.5f;
            moby_rotate_about_point(*(char **)(vars + 0x10), linkPos, *(float *)(vars + 4), 0.0f, 0.0f);
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
