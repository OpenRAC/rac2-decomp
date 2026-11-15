#include "include_asm.h"
#include "names.h"

/* func_L02_003D5118 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern void moby_transform_joint_to_world(char *, int, void *);

extern void moby_transform_joint_point(char *, int, void *);

extern void vec_scale_to_length(char *, char *, float);

extern void FastVecAdd(void *, void *, void *);

extern float coll_project_point_on_segment(char *, char *, char *, char *);

extern void FastVecSub(void *, void *, void *);

extern float FastVecLength(void *);

extern int coll_sweep_from_object(char *, char *, int, float, float, float, int, int, int);

/* Starts a blade swing hit along a joint towards the hero, stronger the closer the hero is. */
void chainblade_start_swing_hit(char *self, int joint) {
    char *state = *(char **)(self + 0x68);
    float origin[4];
    float tip[4];
    float matrix[16];
    float swing[4];
    float closest[4];
    float toClosest[4];
    float toTip[4];
    float closeness;

    moby_transform_joint_to_world(self, joint, origin);
    moby_transform_joint_point(self, joint, matrix);
    *(TI128 *)swing = *(TI128 *)matrix;
    vec_scale_to_length((char *)swing, (char *)swing, 5.3f);
    FastVecAdd(tip, origin, swing);
    coll_project_point_on_segment((char *)closest, (char *)origin, (char *)tip, *(char **)(state + 0x30C) + 0x10);
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
    coll_sweep_from_object(self, (char *)closest, 0x10001, closeness * 0.2f + 0.3f,
                  (float)*(unsigned char *)(state + 0x34), 1.0f, 0, 1, 0);
}
