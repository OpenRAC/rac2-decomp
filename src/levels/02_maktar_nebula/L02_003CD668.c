#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern void moby_set_state(u8 *, u8, int), anim_start_immediate(s8 *, int, int);
extern void moby_transform_joint_point(char *, int, char *), copy_matrix3x4(void *, void *);
extern int moby_fuse_linked_objects(void *, void *, void *, void *, int);
/* Resets the actor pose, restores its child and registers both together. */
void actor_reset_pose_register_child(char *self, void *position) {
    Quad transform[4];
    char *state = *(char **)(self + 0x68);
    moby_set_state((u8 *)self, 0x16, 4);
    anim_start_immediate((s8 *)self, 0, 0);
    moby_transform_joint_point(self, 0, (char *)transform);
    copy_matrix3x4(*(char **)(state + 0x370) + 0xC0, transform);
    *(Quad *)(*(char **)(state + 0x370) + 0x10) = transform[3];
    *(u16 *)(self + 0x34) = (*(u16 *)(self + 0x34) & 0xFFBE) | 0x1000;
    *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x24) + 0x10);
    *(u16 *)(*(char **)(state + 0x370) + 0x34) &= 0xFFBE;
    *(u16 *)(*(char **)(state + 0x370) + 0x34) |= 0x1000;
    *(int *)(*(char **)(state + 0x370) + 0x98) = *(int *)(*(char **)(*(char **)(state + 0x370) + 0x24) + 0x10);
    self[0x7F] = 0;
    moby_fuse_linked_objects(self, position, self + 0xF0, state + 0x370, 1);
}
