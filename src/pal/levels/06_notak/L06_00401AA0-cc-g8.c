/* func_PAL_L06_00401AA0, the PAL copy of func_L06_003FDEB8: the same C, where expr 0.016666668f becomes 0.020000001f; wrap state (((int)({e}) * 5 + 2) / 6); rewrap func_002A7820(D_L06_001AFC58, D_L06_001AFC5C). */
/* Path group setup, motion and spacing update. This unit needs -g for division padding. */
#include "common.h"
extern float func_002A7878(float, float);
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
void func_PAL_L06_00401AA0(int group)
{
    unsigned short *entry = D_L06_001FB3A0[group];
    char *path, *state, *last;
    float reciprocal, pathLength;
    int count, reverse, closed;
    if (!entry)
        return;
    state = D_L06_001B281C[*entry & 0x7FFF].state;
    path = D_L06_001FE500[*(int *)state];
    count = 0;
    reciprocal = func_00282E48(path + 0x10, path + 0x20);
    reciprocal = 1.0f / reciprocal;
    pathLength = (float)*(int *)path;
    closed = 1;
    if (!(func_00282E48(path + 0x10, path + (*(int *)path << 4)) < 5.0f))
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
        *(float *)(state + 0x14) = (reciprocal * (0.020000001f)) *
                                  func_002A7878(*(float *)(state + 8), *(float *)(state + 0xC));
        *(float *)(state + 0x18) = (reciprocal * 0.00040000002f) *
                                  (*(float *)(state + 0xC) - *(float *)(state + 8));
        position = func_00283CE0(reverse);
        reverse--;
        position = position / func_00283CE0(count);
        position *= pathLength;
        *(char **)(state + 0x34) = last;
        *(float *)(state + 0x60) = reciprocal;
        *(char **)(state + 0x30) = path;
        *(int *)(state + 0x40) = closed;
        *(float *)(state + 0x38) = *(float *)(state + 0x14);
        *(float *)(state + 0x5C) = *(float *)(state + 0x14);
        *(float *)(state + 0x1C) = reciprocal * 3.5f;
        *(float *)(state + 0x10) = position;
        func_00282C88(state + 0x20);
        *(float *)(state + 0x20) = func_002A78D8(0.0f, *(float *)(state + 4));
        *(float *)(state + 0x28) = func_002A78D8(0.0f, *(float *)(state + 4));
        *(int *)(state + 0x48) = (((int)(func_002A7820(D_L06_001AFC58, D_L06_001AFC5C)) * 5 + 2) / 6);
        *(float *)(state + 0x4C) = func_002A7940();
        *(float *)(state + 0x50) = func_002A78D8(D_L06_001AFC60, D_L06_001AFC64) * 0.0003490659f;
        *(unsigned char *)(moby + 0x20) = 1;
        *(unsigned short *)(moby + 0x32) = 0xFF;
        *(int *)(state + 0x54) = -1;
        last = moby;
    } while ((short)*entry++ >= 0);
}

/* Advance a moving object's path and keep its spacing from the next object. */
