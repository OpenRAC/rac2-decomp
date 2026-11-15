#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float IntToFloat(int);

extern void hud_start_overlay(int, int, float);

extern void yeedil_boss_update_camera(char *);

extern void yeedil_boss_spawn_minions_edge(char *);

extern void moby_update_eased_node(void *, void *, int, float, float);

extern int math_fast_float_d(void *);

extern void *yeedil_boss_spawn_minion_at_point(char *);

extern void matrix_mul_vec3(void *, const void *, const void *);

extern void euler_rotation_basis(char *, char *);

extern void FastVecSub(void *, void *, void *);

extern void moby_update_ground_check(void *);

extern void value_set_and_smooth(void *, float *, float, int, int);


extern float D_L20_001B20B0[] SDATA(D_L20_001B20B0);


extern float D_L20_001B2164 __attribute__((sda));

/* Does the upkeep shared by every state of the big enemy. It updates the health display, camera and spawning, applies its tilt, ages it and moves it. */
void yeedil_boss_frame_upkeep(char *moby) {
    char *self = moby;
    char *vars = *(char **)(moby + 0x68);
    char *linked_moby;
    char *dst;
    char *src;
    TI128 before, after, delta;
    float tilt;
    unsigned short frames;

    if (*(unsigned char *)(moby + 0x95) != 6) {
        hud_start_overlay(0xA, 0,
                         *(float *)(vars + 0x20)
                         / IntToFloat(*(short *)(vars + 0x24)));
        yeedil_boss_update_camera(moby);
        yeedil_boss_spawn_minions_edge(moby);
    }
    moby_update_eased_node(moby, vars + 0x250, 0, 0.015f, 0.3f);
    if (*(int *)(vars + 0x1810) > 0) {
        if (math_fast_float_d(vars + 0x1810) != 0) {
            yeedil_boss_spawn_minion_at_point(moby);
            *(int *)(vars + 0x1810) = -1;
        }
    }
    linked_moby = *(char **)(vars + 0x1850);
    if (linked_moby != 0) {
        if (*(short *)(linked_moby + 0xAA) != 0x1316) {
            *(int *)(vars + 0x1850) = 0;
        } else {
            if (*(unsigned char *)(linked_moby + 0x20) != 0xFE) {
                if (*(unsigned char *)(linked_moby + 0x20) != 0xFD) {
                    goto copy;
                }
            }
            *(int *)(vars + 0x1850) = 0;
        }
    }
copy:
    dst = vars + 0x17E0;
    src = moby + 0x10;
    qcopy(dst, src);
    tilt = *(float *)(vars + 0x1800);
    if (tilt == 0.0f && *(float *)(vars + 0x1804) == 0.0f) {
        goto done;
    }
    *(float *)(moby + 0xF0) = tilt;
    *(float *)(moby + 0xF4) = *(float *)(vars + 0x1804);
    matrix_mul_vec3(&before, D_L20_001B20B0, moby + 0xC0);
    euler_rotation_basis(moby + 0xC0, moby + 0xF0);
    matrix_mul_vec3(&after, D_L20_001B20B0, moby + 0xC0);
    FastVecSub(&delta, &after, &before);
    FastVecSub(src, src, &delta);
done:
    moby_update_ground_check(moby);
    frames = *(unsigned short *)(moby + 0x96);
    moby[0xBD] = 2;
    if (frames <= 0xFFFE) {
        *(unsigned short *)(moby + 0x96) = frames + 1;
    }
    value_set_and_smooth(moby, (float *)(vars + 0x250), D_L20_001B2164, 0, 1);
}
