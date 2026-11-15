#include "include_asm.h"
#include "names.h"

/* func_002BE7E8 in its own unit for the grouped lq/sq profile. */

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    char *target;
    short timer;
    short bone;
    int duration;
    int alpha;
} Follow_002BE7E8;

extern int FastDecTimer(void *);
extern void part_kill(void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern char g_camera_eye_state[];

/* Keeps an effect on its target: removed when its timer runs out or the target
   is gone; fades in over the first fifth of its life and either sits at the
   target or follows one of its bones, pulled 0.4 toward D_001B5340. */
void part_update_target_following(char *effect)
{
    Follow_002BE7E8 *follow;
    float bone[4] __attribute__((aligned(16)));
    float dir[4] __attribute__((aligned(16)));

    if (effect == 0)
        return;
    follow = (Follow_002BE7E8 *)(effect + 0x20);
    if (FastDecTimer(effect + 0x24) != 0 || follow->target == 0 || follow->target[0x20] < 0) {
        part_kill(effect);
        return;
    }
    if (follow->timer < follow->duration / 5)
        *(int *)(effect + 4) = (*(int *)(effect + 4) & 0xFFFFFF)
                               + ((follow->alpha * follow->timer) / (follow->duration / 3) << 24);
    if (follow->bone == -1) {
        *(TI128 *)(effect + 0x10) = *(TI128 *)(follow->target + 0x10);
    } else {
        moby_transform_joint_to_world(follow->target, follow->bone, bone);
        FastVecSub(dir, g_camera_eye_state, bone);
        vec_scale_to_length(dir, dir, 0.4f);
        FastVecAdd(effect + 0x10, bone, dir);
    }
}
