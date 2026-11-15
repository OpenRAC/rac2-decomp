#include "names.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
extern char *moby_get_motion_data(u8 *);
extern void moby_init_spawned_sub_object(char *, int);
extern void follower_start_random_push(unsigned char *);

/* Restores the flying object's state and its linked motion record. */
void flying_object_restore_state(u8 *self) {
    char *state = *(char **)(self + 0x68);
    char *motion = (char *)moby_get_motion_data(self);
    *(s32 *)(motion + 0x148) = 10;
    moby_init_spawned_sub_object((char *)self, 1);
    *(float *)(state + 0x180) = 10.0f;
    self[0x20] = 1;
    self[0x30] = 255;
    *(u16 *)(self + 0x32) = 511;
    *(u16 *)(self + 0x34) |= 0x100;
    *(float *)(self + 0x2C) = 0.07999999821186066f;
    *(s32 *)(state + 0x268) = 0;
    *(s32 *)(state + 0x26C) = -1;
    follower_start_random_push(self);
}
