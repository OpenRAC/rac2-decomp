#include "include_asm.h"

#include "common.h"
extern char g_active_camera[], g_camera_mode_state[], g_hero_state[];
extern void vec_scale_to_length(float *, float *, float);
extern void cam_compute_aim_angles(float *, float *, float *, float *, float *, float *);
extern void mat_transform_via_copy(void *, void *);
extern void cam_rebuild_look_at_from_hero(void);
extern void moby_save_vectors(void);
extern void moby_restore_vectors(void);
extern float IntToFloat(int);

/* Applies a new camera matrix to the active camera for its current mode and starts the mode change
   (PAL copy of cam_begin_mode_change). */
void cam_begin_mode_change_pal(char *src_matrix)
{
    unsigned char *cam = (unsigned char *)g_active_camera + 0x290;
    float right[4] __attribute__((aligned(16)));
    float up[4] __attribute__((aligned(16)));
    float forward[4] __attribute__((aligned(16)));
    unsigned char mode;

    if (*(short *)cam == 1) {
        mode = cam[3];
        if (mode == 0) {
            qcopy(cam + 0x50, src_matrix + 0x30);
            mat_transform_via_copy(cam + 0x60, src_matrix);
        } else if (mode == 2) {
            qcopy(cam + 0xC0, src_matrix + 0x30);
            mat_transform_via_copy(cam + 0xD0, src_matrix);
            cam_rebuild_look_at_from_hero();
        } else {
            char *hero = g_hero_state;

            vec_scale_to_length(right, (float *)(*(char **)(hero + 0x2290) + 0xC0), 1.0f);
            vec_scale_to_length(up, (float *)(*(char **)(hero + 0x2290) + 0xD0), 1.0f);
            vec_scale_to_length(forward, (float *)(*(char **)(hero + 0x2290) + 0xE0), 1.0f);
            cam_compute_aim_angles((float *)(cam + 0x70), (float *)(src_matrix + 0x30),
                          (float *)(*(char **)(cam - 0x100) + 0x30), right, up, forward);
            mat_transform_via_copy(cam + 0xB0, src_matrix);
            qcopy(cam + 0xD0, cam + 0xB0);
        }
    } else {
        mode = cam[3];
        if (mode == 2) {
            moby_save_vectors();
            cam_rebuild_look_at_from_hero();
        } else if (mode == 1) {
            moby_save_vectors();
            qcopy(cam + 0xB0, cam + 0xD0);
        } else if (mode == 0) {
            moby_restore_vectors();
        }
    }
    *(short *)g_camera_mode_state = 3;
    cam[2] = cam[3];
    if (cam[2] == 0) {
        unsigned char *blend = cam + 0x10;

        *(float *)(blend + 0x10) = *(float *)(blend + 0x14);
        *(int *)(blend + 0xC) = 0;
        qcopy(cam + 0x40, cam + 0x50);
        *(int *)(cam + 0x10) = 0;
        *(float *)(blend + 0x4) = *(float *)(blend + 0x8);
        qcopy(cam + 0x30, cam + 0x60);
    } else {
        unsigned char *trans = cam + 0x70;
        int steps = ((s32)(++*(int *)(trans + 0x14)) * 5 + 2) / 6;

        *(int *)(trans + 0xC) = steps;
        *(float *)(trans + 0x10) = 1.0f / IntToFloat(steps);
    }
}
