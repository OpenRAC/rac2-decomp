/* Path group setup, motion and spacing update. This unit needs -g for division padding. */
#include "common.h"
extern void func_002C9828(char *, int, float *, float *, int, float);
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern float func_002A7878(float, float);
extern float D_L06_001AFCA0 __attribute__((sda));

extern unsigned short *D_L06_001FB3A0[];
typedef struct { char prefix[0x68]; char *state; char tail[0x94]; } PathMoby;
extern PathMoby *D_L06_001B281C;
extern char *D_L06_001FE500[];
/* Tuning ranges, read only here. The upper bounds are read-only declarations: retail schedules
   their loads ahead of the stores before them and keeps them absolute; the lower bounds go to
   the call slots, where the assembler addresses them through $gp. */
extern int D_L06_001AFC58;
extern const int D_L06_001AFC5C;
extern float D_L06_001AFC60;
extern const float D_L06_001AFC64;
extern float func_00282E48(void *, void *);
extern float func_002A78D8(float, float);
extern float func_00283CE0(int);
extern void func_00282C88(void *);
extern int func_002A7820(int, int);
extern float func_002A7940(void);

/* Space the group's objects around a path and initialize their movement. */
void func_L06_003FDEB8(int group)
{
    unsigned short *entry = D_L06_001FB3A0[group];
    char *path, *state, *last;
    float reciprocal, pathLength;
    int count, reverse, closed;
    if (!entry)
        return;
    state = D_L06_001B281C[*entry & 0x7FFF].state;
    path = gPathList[*(int *)state];
    count = 0;
    reciprocal = fast_vec_dist(path + 0x10, path + 0x20);
    reciprocal = 1.0f / reciprocal;
    pathLength = (float)*(int *)path;
    closed = 1;
    if (!(fast_vec_dist(path + 0x10, path + (*(int *)path << 4)) < 5.0f))
        closed = 0;
    do {
        last = (char *)&D_L06_001B281C[*entry & 0x7FFF];
        count++;
    } while ((short)*entry++ >= 0);
    entry = D_L06_001FB3A0[group];
    reverse = count - 1;
    do {
        char *moby = (char *)&D_L06_001B281C[*entry & 0x7FFF];
        float position;
        state = *(char **)(moby + 0x68);
        *(float *)(state + 0x14) = (reciprocal * (1.0f / 60.0f)) *
                                  RandomFloatRange(*(float *)(state + 8), *(float *)(state + 0xC));
        *(float *)(state + 0x18) = (reciprocal * 0.0002777777845f) *
                                  (*(float *)(state + 0xC) - *(float *)(state + 8));
        position = IntToFloat(reverse);
        reverse--;
        position = position / IntToFloat(count);
        position *= pathLength;
        *(char **)(state + 0x34) = last;
        *(float *)(state + 0x60) = reciprocal;
        *(char **)(state + 0x30) = path;
        *(int *)(state + 0x40) = closed;
        *(float *)(state + 0x38) = *(float *)(state + 0x14);
        *(float *)(state + 0x5C) = *(float *)(state + 0x14);
        *(float *)(state + 0x1C) = reciprocal * 3.5f;
        *(float *)(state + 0x10) = position;
        ClearVector128(state + 0x20);
        *(float *)(state + 0x20) = RandomSignedFloatRange(0.0f, *(float *)(state + 4));
        *(float *)(state + 0x28) = RandomSignedFloatRange(0.0f, *(float *)(state + 4));
        *(int *)(state + 0x48) = RandomIntRange(D_L06_001AFC58, D_L06_001AFC5C);
        *(float *)(state + 0x4C) = RandomAngle();
        *(float *)(state + 0x50) = RandomSignedFloatRange(D_L06_001AFC60, D_L06_001AFC64) * 0.0002908882452f;
        *(unsigned char *)(moby + 0x20) = 1;
        *(unsigned short *)(moby + 0x32) = 0xFF;
        *(int *)(state + 0x54) = -1;
        last = moby;
    } while ((short)*entry++ >= 0);
}

/* Advance a moving object's path and keep its spacing from the next object. */
void func_L06_003FE178(char *moby)
{
    char *state = *(char **)(moby + 0x68);
    char *next;
    float phase, pathPosition;
    int length;
    SamplePathPosition(*(char **)(state + 0x30), *(int *)(state + 0x40),
                 (float *)(moby + 0x10), (float *)(moby + 0xF0), 0, *(float *)(state + 0x10));
    phase = FastAddRotations(*(float *)(state + 0x4C), *(float *)(state + 0x50));
    *(float *)(state + 0x4C) = phase;
    *(float *)(moby + 0x18) += D_L06_001AFCA0 * FastSinOrCosB(phase);
    length = **(int **)(state + 0x30);
    pathPosition = *(float *)(state + 0x10) + *(float *)(state + 0x14);
    *(float *)(state + 0x10) = pathPosition;
    if ((float)length <= pathPosition)
        *(float *)(state + 0x10) = pathPosition - (float)length;
    if (*(float *)(state + 0x14) > *(float *)(state + 0x38))
        *(float *)(state + 0x14) -= *(float *)(state + 0x18);
    else
        *(float *)(state + 0x14) += *(float *)(state + 0x18);
    next = *(char **)(state + 0x34);
    if (next && next != moby) {
        char *other = *(char **)(next + 0x68);
        float nextSpeed;
        float gap = *(float *)(other + 0x10) - *(float *)(state + 0x10);
        float ownSpeed;
        if (gap < 0.0f)
            gap += (float)**(int **)(state + 0x30);
        nextSpeed = *(float *)(other + 0x38);
        ownSpeed = *(float *)(state + 0x38);
        if (nextSpeed < ownSpeed) {
            float difference = ownSpeed - nextSpeed;
            float deceleration = *(float *)(state + 0x18);
            float nextMargin = *(float *)(other + 0x1C);
            float ownMargin = *(float *)(state + 0x1C);
            deceleration += deceleration;
            /* The shared source line preserves the measured debug-label padding. */
            difference *= difference; if (gap < difference / deceleration + nextMargin + ownMargin) {
                *(float *)(other + 0x38) = ownSpeed;
                *(float *)(state + 0x38) = nextSpeed;
            }
        }
        if (*(unsigned char *)(*(char **)(state + 0x34) + 0x20) == 2 &&
            gap < *(float *)(state + 0x1C) * 3.0f) {
            *(float *)(state + 0x5C) = *(float *)(state + 0x38);
            *(int *)(state + 0x38) = 0;
        }
        if (*(unsigned char *)(*(char **)(state + 0x34) + 0x20) == 3) {
            *(float *)(state + 0x38) = *(float *)(state + 0x5C);
            *(char **)(state + 0x34) = *(char **)(other + 0x34);
        }
        if (*(float *)(state + 0x38) != 0.0f)
            return;
        if (*(float *)(other + 0x38) == 0.0f)
            return;
        *(float *)(state + 0x38) = *(float *)(other + 0x38);
    } else {
        float random = RandomFloatRange(*(float *)(state + 8), *(float *)(state + 0xC));
        *(float *)(state + 0x38) = (*(float *)(state + 0x60) * (1.0f / 60.0f)) * random;
    }
}
