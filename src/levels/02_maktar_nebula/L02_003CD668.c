#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern void func_002A7750(u8 *, u8, int), func_002A7398(s8 *, int, int);
extern void func_0029FC20(char *, int, char *), func_00283678(void *, void *);
extern int func_L02_002EF388(void *, void *, void *, void *, int);
/* Resets the actor pose, restores its child and registers both together. */
void func_L02_003CD668(char *self, void *position) {
    Quad transform[4];
    char *state = *(char **)(self + 0x68);
    SetMobyState((u8 *)self, 0x16, 4);
    StartAnimationImmediate((s8 *)self, 0, 0);
    TransformMobyJointPoint(self, 0, (char *)transform);
    copy_matrix3x4(*(char **)(state + 0x370) + 0xC0, transform);
    *(Quad *)(*(char **)(state + 0x370) + 0x10) = transform[3];
    *(u16 *)(self + 0x34) = (*(u16 *)(self + 0x34) & 0xFFBE) | 0x1000;
    *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x24) + 0x10);
    *(u16 *)(*(char **)(state + 0x370) + 0x34) &= 0xFFBE;
    *(u16 *)(*(char **)(state + 0x370) + 0x34) |= 0x1000;
    *(int *)(*(char **)(state + 0x370) + 0x98) = *(int *)(*(char **)(*(char **)(state + 0x370) + 0x24) + 0x10);
    self[0x7F] = 0;
    FuseObjectWithLinkedObjects(self, position, self + 0xF0, state + 0x370, 1);
}
