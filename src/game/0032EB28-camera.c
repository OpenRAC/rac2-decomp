#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
extern char *func_00270280(int);
extern void func_00270598(void *);
extern void func_00272550(void *, void *, void *);
extern char D_001B5340[];
extern float D_00189EA0[];

/* Moves the camera to a new place and turning, then starts a blend or hold that lasts the given time. */
void func_00335438(TI128 *position, TI128 *rotation, int mode, int duration, int flags) {
    TI128 pos, rot, oldpos, oldrot;
    char *camera = FindRecordByHandleId(5);
    char *state, *transition, *statepos, *staterot;
    qcopy(&pos, position);
    qcopy(&rot, rotation);
    qcopy(&oldpos, gCameraState_001B5340);
    qcopy(&oldrot, gCameraState_001B5340 + 0x10);
    SwitchActiveCamera(camera);
    state = *(char **)(camera + 0x70);
    camera[0x7D] = 1;
    transition = state + 0xE0;
    statepos = state + 0x80;
    qcopy(camera + 0x30, &pos);
    qcopy(gCameraState_001B5340, &pos);
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
        qcopy(state + 0x110, gHeroPosition);
        ComputeDirectionAngles(state + 0xFC, &oldpos, gHeroPosition);
        /* fall through */
    case 2:
        *(int *)(transition + 4) = duration;
        *(int *)(state + 0xE0) = duration;
        break;
    }
}
