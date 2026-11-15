#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
extern char *moby_find_record_by_handle_id(int);
extern void cam_switch_active(void *);
extern int cam_compute_direction_angles(void *, void *, void *);
extern char g_camera_eye_state[];
extern float g_hero_position[];

/* Moves the camera to a new place and turning, then starts a blend or hold that lasts the given time. */
void SetCamera5Pose(TI128 *position, TI128 *rotation, int mode, int duration, int flags) {
    TI128 pos, rot, oldpos, oldrot;
    char *camera = moby_find_record_by_handle_id(5);
    char *state, *transition, *statepos, *staterot;
    qcopy(&pos, position);
    qcopy(&rot, rotation);
    qcopy(&oldpos, g_camera_eye_state);
    qcopy(&oldrot, g_camera_eye_state + 0x10);
    cam_switch_active(camera);
    state = *(char **)(camera + 0x70);
    camera[0x7D] = 1;
    transition = state + 0xE0;
    statepos = state + 0x80;
    qcopy(camera + 0x30, &pos);
    qcopy(g_camera_eye_state, &pos);
    qcopy(camera + 0x40, &rot);
    qcopy(statepos, &pos);
    staterot = state + 0x90;
    qcopy(staterot, &rot);
    *(int *)(transition + 0x40) = flags;
    camera[0x88] = mode;
    switch (mode) {
    case 3:
        *(float *)(transition + 0x44) = 1.0f;
        *(int *)(transition + 0x48) = 0;
        qcopy(camera + 0x30, &oldpos);
        qcopy(camera + 0x40, &oldrot);
        qcopy(state + 0x110, g_hero_position);
        cam_compute_direction_angles(state + 0xFC, &oldpos, g_hero_position);
        /* fall through */
    case 2:
        *(int *)(transition + 4) = duration;
        *(int *)(state + 0xE0) = duration;
        break;
    }
}
