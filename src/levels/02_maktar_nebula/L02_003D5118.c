#include "include_asm.h"
#include "names.h"

/* func_L02_003D5118 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern void *func_0029FCC0(char *, int, void *);

extern void func_0029FC20(char *, int, void *);

extern void func_00282F20(char *, char *, float);

extern void func_00282CC0(void *, void *, void *);

extern void func_L00_0031BDC0(char *, char *, char *, char *);

extern void func_00282CF0(void *, void *, void *);

extern float func_00282DF0(void *);

extern void func_002A8C28(char *, char *, int, float, float, float, int, int, int);

/* Starts a blade swing hit along a joint towards the hero, stronger the closer the hero is. */
void func_L02_003D5118(char *self, int joint) {
    char *state = *(char **)(self + 0x68);
    float origin[4];
    float tip[4];
    float matrix[16];
    float swing[4];
    float closest[4];
    float toClosest[4];
    float toTip[4];
    float closeness;

    TransformMobyJointToWorld(self, joint, origin);
    TransformMobyJointPoint(self, joint, matrix);
    *(TI128 *)swing = *(TI128 *)matrix;
    vec_scale_to_length((char *)swing, (char *)swing, 5.3f);
    FastVecAdd(tip, origin, swing);
    ProjectPointOnSegment((char *)closest, (char *)origin, (char *)tip, *(char **)(state + 0x30C) + 0x10);
    FastVecSub(toClosest, origin, closest);
    FastVecSub(toTip, origin, tip);
    closeness = FastVecLength(toClosest);
    closeness = closeness / FastVecLength(toTip);
    if (closeness < 0.0f) {
        closeness = 0.0f;
    }
    if (closeness > 1.0f) {
        closeness = 1.0f;
    }
    SweepCollisionFromObject(self, (char *)closest, 0x10001, closeness * 0.2f + 0.3f,
                  (float)*(unsigned char *)(state + 0x34), 1.0f, 0, 1, 0);
}
