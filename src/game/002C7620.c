#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 word; float values[4]; } Vec4;

extern int FastDecTimer(void *);
extern void part_kill(void *);
extern void FastVecAdd(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern float IntToFloat(int);
extern int FloatToInt(float);

/* Updates a streak particle that stretches along its movement and fades out. */
void part_update_stretched_streak(char *self) {
    Vec4 prev_pos, offset;
    char *pos;
    char *motion = self + 0x30;
    float t;
    int color;

    if (FastDecTimer(self + 0xA) != 0) {
        part_kill(self);
        return;
    }
    pos = self + 0x10;
    prev_pos.word = *(TI128 *)pos;
    FastVecAdd(pos, pos, motion);
    *(float *)(motion + 8) = *(float *)(motion + 8) - *(float *)(motion + 0xC);
    t = FastVecLength(motion);
    vec_scale_to_length(&offset, motion, t * 0.4f);
    FastVecSub(self + 0x20, pos, &offset);
    *(float *)(self + 0x2C) = 1.0f;
    if (*(short *)(self + 0xA) < *(unsigned char *)(self + 8)) {
        t = IntToFloat(*(short *)(self + 0xA)) / IntToFloat(*(unsigned char *)(self + 8));
        color = (FloatToInt(t * 127.0f) << 24) | 0x00FFFFFF;
        *(int *)(self + 0xC) = color;
        *(int *)(self + 4) = color;
    }
}
