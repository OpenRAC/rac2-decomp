#include "include_asm.h"
#include "names.h"



extern int IsPointInCuboid(void *, int);
extern int ForceClaimNotice(int, int, int);
extern void moby_set_state(void *, int, int);
extern int flag_set_first_pending(void *);
extern char *museum_tweak_menu_spawn(void *);
extern void MuseumTweakMenuAddItem(void *, void *, void *, int, int, int);
extern char g_hero_position[];
extern long g_pad_pressed_flags;
extern char g_str_tweak_toggle_label[];
extern char g_str_tweak_value_label_a[];
extern char g_str_tweak_value_label_b[];
extern char g_str_tweak_value_label_c[];
extern char g_str_tweak_value_label_d[];
extern char g_str_tweak_value_label_e[];
extern char g_str_tweak_color_label_a[];
extern char g_str_tweak_color_label_b[];
extern char g_str_tweak_color_label_c[];
extern char g_str_tweak_flag_label_a[];
extern char g_str_tweak_flag_label_b[];
extern char g_str_tweak_flag_label_c[];
char *func_PAL_L30_0041A748(void *, float, int, int, int, int, int, int, int, int, int, int);

/* func_L30_00413528 is defined in L30_00413528.c. */

/* func_L30_004135A0 is defined in L30_004135A0-g8.c. */


void func_PAL_L30_0041A400(char *obj) {
    char *st = *(char **)(obj + 0x68);
    char *menu;
    long buttons;
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        *(int *)(obj + 0x1C) = 0;
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        if (*(int *)(st + 0x3C) != -1 && IsPointInCuboid(g_hero_position, *(int *)(st + 0x3C))) {
            ForceClaimNotice(1, 0x1338, 1);
            buttons = g_pad_pressed_flags;
            buttons &= 3;
            if (buttons == 3) moby_set_state(obj, 2, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(obj)) {
            *(char **)(st + 0x2C) = museum_tweak_menu_spawn(obj);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 4, g_str_tweak_toggle_label, 1, 0, 1);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 12, g_str_tweak_value_label_a, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 16, g_str_tweak_value_label_b, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 20, g_str_tweak_value_label_c, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 24, g_str_tweak_value_label_d, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 28, g_str_tweak_value_label_e, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 32, g_str_tweak_color_label_a, 0, 0, 255);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 36, g_str_tweak_color_label_b, 0, 0, 255);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 40, g_str_tweak_color_label_c, 0, 0, 255);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 48, g_str_tweak_flag_label_a, 0, 0, 1);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 52, g_str_tweak_flag_label_b, 0, 0, 1);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 8, g_str_tweak_flag_label_c, 0, 0, 1);

        }
        ForceClaimNotice(1, 0, 1);
        menu = *(char **)(st + 0x2C);
        if (!menu || *(short *)(menu + 0xAA) != 0x118A || *(unsigned char *)(menu + 0x20) == 0xFE || *(unsigned char *)(menu + 0x20) == 0xFD) {
            moby_set_state(obj, 1, -1);
        }
        break;
    }
    if (*(float *)(obj + 0x1C) >= 45.0f) {
        int color;
        *(int *)(obj + 0x1C) = 0;
        color = (*(int *)(st + 40) << 16) | (*(int *)(st + 36) << 8) | *(int *)(st + 32);
        *(char **)st = func_PAL_L30_0041A748(obj + 0x10, *(float *)(st + 4), *(int *)(st + 8), *(int *)(st + 12), *(int *)(st + 16), *(int *)(st + 20), *(int *)(st + 24), *(int *)(st + 28), *(int *)(st + 48), *(int *)(st + 52), *(int *)(st + 56), color);
    }
    *(float *)(obj + 0x1C) += 1.0f;
}


#include "common.h"
extern char *CreateMoby(int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void cam_compute_view_direction(void *, void *, int);
extern void FastVecCross(void *, void *, void *);
extern int math_fast_helper_a(void *, float);
extern float fast_vec_dist(void *, void *);
extern float FastVecDot(void *, void *);
extern float math_fast_angle_helper(float);
extern void func_PAL_L30_0041AC18(void *, void *);
extern struct Player153 {
    char pad[0x140];
    float position[4];
    char pad2[0x10];
    float shakeStrength;
    int pad3;
    int shakeDuration, shakeTimer;
    char pad4[0x200];
    float forward[4];
} D_L30_001B9C80;
typedef struct {
    short life, initialLife, duration;
    short pad;
    float inner, outer, strength, scale;
    int sound, flash, a2, a3, a4, a5, a6, a8, color;
} State153;

char *func_PAL_L30_0041A748(void *pos, float scale, int shake, int a2, int a3, int a4, int a5, int a6, int sound, int a8, int a9, int color) {
    float direction[4] __attribute__((aligned(16)));
    float normal[4] __attribute__((aligned(16)));
    float sphere[4] __attribute__((aligned(16)));
    float towardPlayer[4] __attribute__((aligned(16)));
    char *obj = CreateMoby(0x11E5);
    State153 *st;
    if (obj) {
        st = *(State153 **)(obj + 0x68);
        *(unsigned char *)(obj + 0x30) = 255;
        *(unsigned short *)(obj + 0x32) = 255;
        *(unsigned char *)(obj + 0x20) = 0;
        qcopy(obj + 0x10, pos);
        *(float *)(obj + 0x1C) = 1.0f;
        FastVecSub(direction, g_camera_l30_state.position, obj + 0x10);
        vec_scale_to_length(direction, direction, 1.0f);
        cam_compute_view_direction(obj + 0x10, normal, 1);
        qcopy(obj + 0xC0, direction);
        FastVecCross(obj + 0xD0, obj + 0xC0, normal);
        vec_scale_to_length(obj + 0xD0, obj + 0xD0, 1.0f);
        FastVecCross(obj + 0xE0, obj + 0xD0, obj + 0xC0);
        *(float *)(obj + 0xCC) = *(float *)(obj + 0xDC) = *(float *)(obj + 0xEC) = 0.0f;
        st->initialLife = st->life = 50;
        st->inner = scale + scale;
        st->outer = scale * 4.0f;
        st->a2 = a2;
        st->a3 = a3;
        st->a4 = a4;
        st->a5 = a5;
        st->a6 = a6;
        st->a8 = a8;
        st->flash = a9;
        st->sound = sound;
        st->color = color;
        st->scale = scale;
        qcopy(sphere, obj + 0x10);
        sphere[3] = scale * 3.0f;
        if (math_fast_helper_a(sphere, 128.0f) == 1) {
            st->duration = 8;
            st->strength = 0.125f;
            if (fast_vec_dist(pos, g_camera_l30_state.position) < 48.0f && shake) {
                g_camera_l30_state.shakeTimer = 0;
                g_camera_l30_state.shakeDuration = 33;
                g_camera_l30_state.shakeStrength = 0.075f;
            }
            if (st->sound) {
                FastVecSub(towardPlayer, obj + 0x10, g_camera_l30_state.position);
                vec_scale_to_length(towardPlayer, towardPlayer, 1.0f);
                if (1.5707963705062866f - math_fast_angle_helper(FastVecDot(towardPlayer, g_camera_l30_state.forward)) < 0.45378565788269043f)
                    st->sound = 1;
                else
                    st->sound = 0;
            }
        } else {
            st->duration = 0;
            st->sound = 0;
        }
        func_PAL_L30_0041AC18(obj, normal);
    }
    return obj;
}
