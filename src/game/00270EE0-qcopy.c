#include "common.h"
extern char g_active_camera[], g_camera_mode_state[], g_hero_state[];
extern void vec_scale_to_length(float *, float *, float);
extern void cam_compute_aim_angles(float *, float *, float *, float *, float *, float *);
extern void mat_transform_via_copy(void *, void *);
extern void cam_rebuild_look_at_from_hero(void);
extern void moby_save_vectors(void);
extern void moby_restore_vectors(void);
extern float IntToFloat(int);
/* Starts a camera mode change: stores the new camera data, picks the transition setup and resets its timers. */
void cam_begin_mode_change(char *from)
{
    unsigned char *cam = (unsigned char *)g_active_camera + 0x290;
    float row_a[4] __attribute__((aligned(16)));
    float row_b[4] __attribute__((aligned(16)));
    float row_c[4] __attribute__((aligned(16)));
    unsigned char sub_mode;

    if (*(short *)cam == 1) {
        sub_mode = cam[3];
        if (sub_mode == 0) {
            qcopy(cam + 0x50, from + 0x30);
            mat_transform_via_copy(cam + 0x60, from);
        } else if (sub_mode == 2) {
            qcopy(cam + 0xC0, from + 0x30);
            mat_transform_via_copy(cam + 0xD0, from);
            cam_rebuild_look_at_from_hero();
        } else {
            char *hero = g_hero_state;

            vec_scale_to_length(row_a, (float *)(*(char **)(hero + 0x2290) + 0xC0), 1.0f);
            vec_scale_to_length(row_b, (float *)(*(char **)(hero + 0x2290) + 0xD0), 1.0f);
            vec_scale_to_length(row_c, (float *)(*(char **)(hero + 0x2290) + 0xE0), 1.0f);
            cam_compute_aim_angles((float *)(cam + 0x70), (float *)(from + 0x30),
                          (float *)(*(char **)(cam - 0x100) + 0x30), row_a, row_b, row_c);
            mat_transform_via_copy(cam + 0xB0, from);
            qcopy(cam + 0xD0, cam + 0xB0);
        }
    } else {
        sub_mode = cam[3];
        if (sub_mode == 2) {
            moby_save_vectors();
            cam_rebuild_look_at_from_hero();
        } else if (sub_mode == 1) {
            moby_save_vectors();
            qcopy(cam + 0xB0, cam + 0xD0);
        } else if (sub_mode == 0) {
            moby_restore_vectors();
        }
    }
    *(short *)g_camera_mode_state = 3;
    cam[2] = cam[3];
    if (cam[2] == 0) {
        unsigned char *fade = cam + 0x10;

        *(float *)(fade + 0x10) = *(float *)(fade + 0x14);
        *(int *)(fade + 0xC) = 0;
        qcopy(cam + 0x40, cam + 0x50);
        *(int *)(cam + 0x10) = 0;
        *(float *)(fade + 0x4) = *(float *)(fade + 0x8);
        qcopy(cam + 0x30, cam + 0x60);
    } else {
        unsigned char *blend = cam + 0x70;
        int count = ++*(int *)(blend + 0x14);

        *(int *)(blend + 0xC) = count;
        *(float *)(blend + 0x10) = 1.0f / IntToFloat(count);
    }
}
