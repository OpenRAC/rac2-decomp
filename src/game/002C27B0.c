#include "names.h"
/* func_002C27B0: own unit, the two 16-byte copies are qcopy() so the count at state + 4
 * is read after the first copy, as retail does. */
#include "common.h"
extern void part_kill(void *);
extern float math_random_float_range(float, float);
extern float fast_vec_dist(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void moby_transform_joint_to_world(int, int, void *);
extern void FastVecAdd(char *, char *, char *);

typedef int V4 __attribute__((mode(TI)));

/* Updates a particle that follows another object. It disappears when that object is gone or dying. */
void part_update_following_moby(char *self)
{
    V4 prevPos;
    char *state = self + 0x30;
    char *target = *(char **)(self + 0x30);
    float randomFactor;
    float newSize;
    float savedExtra;
    int count;

    if (target == 0)
        goto kill;
    if (*(short *)(target + 0xAA) == *(int *)(state + 8)) {
        if (*(unsigned char *)(target + 0x20) == 0xFE)
            goto kill;
        if (*(unsigned char *)(target + 0x20) != 0xFD)
            goto cont;
    }
kill:
    part_kill(self);
    return;
cont:
    randomFactor = math_random_float_range(0.5f, 1.0f);
    savedExtra = *(float *)(self + 0x2C);
    newSize = *(float *)(state + 0xC) * randomFactor;
    qcopy(&prevPos, self + 0x10);
    count = *(int *)(state + 4);
    if (count > 0) {
        moby_transform_joint_to_world(*(int *)(self + 0x30), count, self + 0x10);
    } else {
        qcopy(self + 0x10, (char *)*(int *)(self + 0x30) + 0x10);
    }
    if (1.5f < fast_vec_dist(self + 0x10, self + 0x20)) {
        FastVecSub(&prevPos, &prevPos, self + 0x10);
        vec_scale_to_length(&prevPos, &prevPos, 1.5f);
        FastVecAdd(self + 0x20, self + 0x10, &prevPos);
    }
    *(float *)(self + 0x1C) = newSize;
    *(float *)(self + 0x2C) = savedExtra;
}
