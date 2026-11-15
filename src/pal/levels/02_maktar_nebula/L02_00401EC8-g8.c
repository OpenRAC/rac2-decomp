/* func_PAL_L02_00401EC8, the PAL copy of func_L02_003FD770: the same C, where the wait is scaled to 50 Hz. */

#include "common.h"

extern char D_L02_001B11D0[8] __attribute__((sda));
extern char D_L02_001B11E0[8] __attribute__((sda));
extern char D_L02_001B11F0[8] __attribute__((sda));
extern char D_L02_001B1200[8] __attribute__((sda));
extern int D_L02_001B1210 __attribute__((sda));

extern void vec_clear_128(void *);
extern void SetCamera5Pose(char *, char *, int, int, int);
extern void SetCamera5Mode(int, int);
extern void object_copy_vector_to_selected(char *);
extern void cam_set_state_rotation(char *);

void func_PAL_L02_00401EC8(char *a0) {
    char buf[16];
    vec_clear_128(buf);
    SetCamera5Pose(D_L02_001B11F0, D_L02_001B1200, 1, 0, 0);
    SetCamera5Mode(2, ((s32)(D_L02_001B1210) * 5 + 2) / 6);
    object_copy_vector_to_selected(D_L02_001B11D0);
    cam_set_state_rotation(D_L02_001B11E0);
}
