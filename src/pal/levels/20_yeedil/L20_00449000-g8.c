#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float IntToFloat(int);
extern void hud_start_overlay(int, int, float);
extern void yeedil_boss_update_camera_pal(char *);
extern void yeedil_boss_spawn_minions_edge_pal(char *);
extern void moby_update_eased_node(void *, void *, int, float, float);
extern int math_fast_float_d(void *);
extern void *yeedil_boss_spawn_minion_at_point_pal(char *);
extern void matrix_mul_vec3(void *, const void *, const void *);
extern void euler_rotation_basis(char *, char *);
extern void FastVecSub(void *, void *, void *);
extern void moby_update_ground_check(void *);
extern void value_set_and_smooth_pal(void *, float *, float, int, int);
extern float g_local_to_world_vec[] SDATA(D_L20_001B20B0);
extern float g_yeedil_smoothed_value __attribute__((sda));

/* Does the upkeep shared by every state of the big enemy. It updates the health display, camera and spawning, applies its tilt, ages it and moves it. (PAL) */
void yeedil_boss_frame_upkeep_pal(char *moby) {
    char *self = moby;
    char *vars = *(char **)(moby + 0x68);
    char *linked_moby;
    char *saved_pos;
    char *moby_pos;
    TI128 basis_before, basis_after, basis_delta;
    float tilt;
    unsigned short frame_count;

    if (*(unsigned char *)(moby + 0x95) != 6) {
        hud_start_overlay(0xA, 0,
                         *(float *)(vars + 0x20)
                         / IntToFloat(*(short *)(vars + 0x24)));
        yeedil_boss_update_camera_pal(moby);
        yeedil_boss_spawn_minions_edge_pal(moby);
    }
    moby_update_eased_node(moby, vars + 0x250, 0, 0.0216f, 0.43200004f);
    if (*(int *)(vars + 0x1810) > 0) {
        if (math_fast_float_d(vars + 0x1810) != 0) {
            yeedil_boss_spawn_minion_at_point_pal(moby);
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
    saved_pos = vars + 0x17E0;
    moby_pos = moby + 0x10;
    qcopy(saved_pos, moby_pos);
    tilt = *(float *)(vars + 0x1800);
    if (tilt == 0.0f && *(float *)(vars + 0x1804) == 0.0f) {
        goto done;
    }
    *(float *)(moby + 0xF0) = tilt;
    *(float *)(moby + 0xF4) = *(float *)(vars + 0x1804);
    matrix_mul_vec3(&basis_before, g_local_to_world_vec, moby + 0xC0);
    euler_rotation_basis(moby + 0xC0, moby + 0xF0);
    matrix_mul_vec3(&basis_after, g_local_to_world_vec, moby + 0xC0);
    FastVecSub(&basis_delta, &basis_after, &basis_before);
    FastVecSub(moby_pos, moby_pos, &basis_delta);
done:
    moby_update_ground_check(moby);
    frame_count = *(unsigned short *)(moby + 0x96);
    moby[0xBD] = 2;
    if (frame_count <= 0xFFFE) {
        *(unsigned short *)(moby + 0x96) = frame_count + 1;
    }
    value_set_and_smooth_pal(moby, (float *)(vars + 0x250), g_yeedil_smoothed_value, 0, 1);
}
