#include "include_asm.h"
#include "common.h"

/* func_PAL_L14_003E96D8, the PAL copy of func_L14_003E5218: the same C, where both ring heights
 * take the 50 Hz scale. */
void moby_set_child_fade_colors_pal(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    short ring_index = *(short *)(vars + 0x16);
    if ((short)(ring_index % 2) == 1) {
        int height_a = ((short *)vars)[ring_index];
        int height_b = ((short *)vars)[(ring_index + 1) % 8];
        char *child;
        char *child_vars;
        int green;
        child = *(char **)(vars + 0x28);
        if (child) {
            child_vars = *(char **)(child + 0x68);
            *(int *)(child_vars + 0x14) = *(short *)(vars + 0x14) - ((s32)(height_a) * 5 + 2) / 6;
            *(int *)(child_vars + 0x18) = ((s32)(height_a) * 5 + 2) / 6 - ((s32)(height_b) * 5 + 2) / 6;
            green = (*(short *)(vars + 0x42) << 8) | 0x80000000;
            *(int *)(child_vars + 0x30) = *(int *)(child_vars + 0x38) = (*(short *)(vars + 0x44) << 16) | green | *(short *)(vars + 0x40);
            green = (*(short *)(vars + 0x48) << 8) | 0x80000000;
            *(int *)(child_vars + 0x34) = *(int *)(child_vars + 0x3C) = (*(short *)(vars + 0x4A) << 16) | green | *(short *)(vars + 0x46);
            *(float *)(child_vars + 0xC) = 1.0f;
        }
        child = *(char **)(vars + 0x2C);
        if (child) {
            child_vars = *(char **)(child + 0x68);
            *(int *)(child_vars + 0x14) = *(short *)(vars + 0x14) - ((s32)(height_a) * 5 + 2) / 6;
            *(int *)(child_vars + 0x18) = ((s32)(height_a) * 5 + 2) / 6 - ((s32)(height_b) * 5 + 2) / 6;
            green = (*(short *)(vars + 0x42) << 8) | 0x80000000;
            *(int *)(child_vars + 0x30) = *(int *)(child_vars + 0x38) = (*(short *)(vars + 0x44) << 16) | green | *(short *)(vars + 0x40);
            green = (*(short *)(vars + 0x48) << 8) | 0x80000000;
            *(int *)(child_vars + 0x34) = *(int *)(child_vars + 0x3C) = (*(short *)(vars + 0x4A) << 16) | green | *(short *)(vars + 0x46);
            *(float *)(child_vars + 0xC) = 1.0f;
        }
    }
}

extern void gfx_set_clamped_view_distance(float);
extern int flag_is_third_pending_set(char *);
extern void gfx_add_draw_callback_third(void (*f)(char *), char *arg);
extern float math_random_float_range(float, float);
extern void moby_bind_small_data_words(char *);


/* func_PAL_L14_003F53E4, the PAL copy of func_L14_003F0D50: the same C, where both scroll
 * speeds are scaled by 1.2f for 50 Hz. */
void scrolling_l14_texture_update_pal(char *moby) {
    char *moby_copy = moby;
    char *vars = *(char **)(moby + 0x68);

    if (*(unsigned char *)(moby + 0x20) == 0) {
        *(int *)(vars + 0x10) = 1;
        gfx_set_clamped_view_distance(2048.0f);
        *(unsigned char *)(moby + 0x20) = 1;
    }
    *(float *)(vars + 0x0) = *(float *)(vars + 0x0) + *(float *)(vars + 0x4) * 1.2f;
    *(float *)(vars + 0x8) = *(float *)(vars + 0x8) + *(float *)(vars + 0xC) * 1.2f;
    if (*(float *)(vars + 0x0) >= 8.0f) {
        *(float *)(vars + 0x0) = *(float *)(vars + 0x0) - 8.0f;
    }
    if (*(float *)(vars + 0x8) >= 8.0f) {
        *(float *)(vars + 0x8) = *(float *)(vars + 0x8) - 8.0f;
    }
    if (flag_is_third_pending_set(moby_copy) != 0) {
        *(int *)(vars + 0x10) = 0;
    }
    if (*(int *)(vars + 0x10) != 0) {
        gfx_add_draw_callback_third(moby_bind_small_data_words, moby_copy);
    }
    *(float *)(vars + 0x4) = math_random_float_range(0.003f, 0.005f);
    *(float *)(vars + 0xC) = math_random_float_range(0.001f, 0.0025f);
}
