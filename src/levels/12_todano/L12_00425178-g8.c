#include "common.h"

typedef int L12_25178Quad __attribute__((mode(TI)));

extern s32 *D_L12_001FEAC0[];
extern f32 D_L12_001B20CC __attribute__((sda));

extern int math_random_int_below(int);
extern float vec_distance_xy(void *, void *);
extern int subtract_integer_with_clamp(int);
extern s32 CollLine(void *from, void *to, s32 mode, void *self, s32 flags);

/* Picks a random point of the object's list other than the current one (+0x2B0), up to 30
   tries. With LIMIT set, a point farther than the global range from the current target
   (+0x2B4) is taken only if it is no more steps away than the current one. The point may
   be at most 2.0 above the object and has to be in sight. Returns its index, or the
   current one when no try succeeds. */
s32 path_pick_random_visible_point(u8 *object, s32 limit)
{
    f32 from[4] __attribute__((aligned(16)));
    f32 target[4] __attribute__((aligned(16)));
    f32 to[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(object + 0x68);
    s32 *list = D_L12_001FEAC0[*(s32 *)(state + 0x298)];
    f32 dist;
    s32 steps;
    s32 current;
    s32 pick;
    s32 i;

    qcopy(from, object + 0x10);
    from[2] += 0.5f;
    qcopy(target, (L12_25178Quad *)list + *(s32 *)(state + 0x2B4) + 1);
    for (i = 0; i < 30; i++) {
        pick = math_random_int_below(list[0]);
        if (pick == *(s32 *)(state + 0x2B0))
            continue;
        qcopy(to, (L12_25178Quad *)list + pick + 1);
        to[2] += 0.5f;
        if (limit != 0) {
            dist = vec_distance_xy(to, target);
            steps = subtract_integer_with_clamp(pick - *(s32 *)(state + 0x2B4));
            current = subtract_integer_with_clamp(*(s32 *)(state + 0x2B0) - *(s32 *)(state + 0x2B4));
            if (D_L12_001B20CC < dist && current < steps)
                continue;
        }
        if (from[2] + 2.0f < to[2])
            continue;
        if (CollLine(from, to, 2, object, 0) == 0)
            return pick;
    }
    return *(s32 *)(state + 0x2B0);
}
