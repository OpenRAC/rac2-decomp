#include "common.h"

/* func_US2_L14_003DFE88, the USA v2.00 copy of func_L14_003DE9B0: case 0 also records the
 * current angle at vars + 0x1C, and case 2 fades the colour by the angle left to turn instead
 * of a hit timer. */

/* Widen the packed high channels before combining the low channel, retaining
 * the original color-expression grouping with the pinned compiler. */

extern char *g_moby_l14_pool __attribute__((sda));
extern char g_hero_position[];
/* One unsplit `la`: it cannot fill the guard branch'vars delay slot, so the slot comes from the target. */
extern char g_identity_l14_matrix[] MACRO_ADDR;
extern void moby_set_state(void *, int, int);
extern int flag_set_first_pending(void *);
extern float fast_vec_dist(void *, void *);
extern int IsPointInCuboid(void *, int);
extern float math_fast_sin_or_cos_b(float);
extern void moby_set_flag_bit(void *, int);
extern void moby_rotate_about_point(void *, void *, float, float, float);
extern void euler_rotation_basis(void *, void *);

/* Swinging glow update (USA v2.00): turns the glowing bar about its pivot when the hero is near,
   pulsing its colour. */
void swinging_glow_update_us2(char *moby) {
    float pivot[4] __attribute__((aligned(16)));
    char *vars = *(char **)(moby + 0x68);
    int brightness, fade;

    switch ((unsigned char)moby[0x20]) {
    case 0:
        if (*(int *)vars >= 0) {
            *(char **)(vars + 0x10) = g_moby_l14_pool + (*(int *)vars << 8);
            *(int *)(moby + 0x78) = 0x80404040;
            *(unsigned short *)(moby + 0x34) |= 0x10;
            *(int *)(vars + 0x14) = 0;
        } else {
            *(int *)(vars + 0x10) = 0;
        }
        if (*(int *)(vars + 8)) {
            *(float *)(vars + 0x1C) = *(float *)(moby + 0xF4);
        } else {
            *(float *)(vars + 0x1C) = *(float *)(moby + 0xF8);
        }
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        brightness = *(int *)(vars + 0x18);
        *(int *)(moby + 0x78) = (long long)(int)(0x80000000 | (brightness << 16) | (brightness << 8)) | brightness;
        if (*(int *)(vars + 0xC) == -1) {
            if (fast_vec_dist(g_hero_position, moby + 0x10) < 10.0f) {
                moby_set_state(moby, 2, -1);
            }
        } else if (IsPointInCuboid(g_hero_position, *(int *)(vars + 0xC))) {
            moby_set_state(moby, 2, -1);
        }
        break;
    case 2:
        if (*(int *)(vars + 8)) {
            fade = (int)((float)*(int *)(vars + 0x18) * (*(float *)(moby + 0xF4) + 3.1415927f) * 0.31830987f);
        } else {
            fade = (int)((float)*(int *)(vars + 0x18) * (3.1415927f - *(float *)(moby + 0xF8)) * 0.31830987f);
        }
        *(int *)(moby + 0x78) = (long long)(int)(0x80000000 | (fade << 16) | (fade << 8)) | *(int *)(vars + 0x18);
        if ((*(float *)(moby + 0xF8) >= 3.1415927f && !*(int *)(vars + 8)) ||
            (*(float *)(moby + 0xF4) <= -3.1415927f && *(int *)(vars + 8))) {
            moby_set_state(moby, 3, -1);
            break;
        }
        if (*(int *)(vars + 8)) {
            *(float *)(moby + 0xF4) -= *(float *)(vars + 4);
        } else {
            *(float *)(moby + 0xF8) += *(float *)(vars + 4);
        }
        if (*(char **)(vars + 0x10)) {
            qcopy(pivot, g_identity_l14_matrix);
            pivot[2] -= 0.5f;
            moby_rotate_about_point(*(char **)(vars + 0x10), pivot, *(float *)(vars + 4), 0.0f, 0.0f);
            euler_rotation_basis(*(char **)(vars + 0x10) + 0xC0, *(char **)(vars + 0x10) + 0xF0);
        }
        break;
    case 3:
        if (flag_set_first_pending(moby)) {
            *(float *)(moby + 0xF8) = 3.1415927f;
            if (*(char **)(vars + 0x10)) {
                moby_set_flag_bit(*(char **)(vars + 0x10), 1);
            }
        }
        *(int *)(moby + 0x78) = *(int *)(vars + 0x18) | 0x80000000;
        break;
    }
    ++*(int *)(vars + 0x14);
    *(int *)(vars + 0x18) = (int)(math_fast_sin_or_cos_b((float)(*(int *)(vars + 0x14) % 150) * 0.041887905f) * 48.0f) + 80;
}
