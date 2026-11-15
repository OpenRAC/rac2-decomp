#include "include_asm.h"
#include "names.h"

/* func_002B5E48 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give
   retail's grouped `lq`/`sq` with register addresses and keep the instructions around the
   copy on their own side of it. */

typedef int TI128_002B5E48 __attribute__((mode(TI)));
typedef union { TI128_002B5E48 q; float f[4]; } Vec4Q_002B5E48;

extern int func_002C9218(int a0, void *a1, void *a2, float f);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(char *, char *, float);

/* Pushes the object out of another solid object it has moved into and returns 1 if it had to move it. */
int func_002B5E48(char *self, char *ctl)
{
    Vec4Q_002B5E48 hitPoint;
    char *position;
    int id;

    id = *(int *)(ctl + 0x3C);
    if (id == -1) return 0;
    if (*(unsigned int *)(ctl + 0x9C) & 1) return 0;
    position = self + 0x10;
    hitPoint.q = *(TI128_002B5E48 *)position;
    if (PushPointAwayFromPath(id, &hitPoint, position, *(float *)ctl) != 0) {
        FastVecSub(ctl + 0x60, &hitPoint, position);
        vec_scale_to_length(ctl + 0x60, ctl + 0x60, *(float *)ctl);
        *(unsigned int *)(ctl + 0x94) |= 0x10;
        return 1;
    }
    return 0;
}
