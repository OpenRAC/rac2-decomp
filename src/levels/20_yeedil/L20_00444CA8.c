#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union {
    TI128 q;
    float f[4];
} Vec4;

extern char *D_L20_001B2F9C __attribute__((sda));
extern void func_002A7750(char *, int, int);
extern float func_00283BE0(float, float);
extern void func_00282CC0(char *, char *, char *);
extern unsigned char D_0019B2E8[];
extern float func_002AA548(char *, char *, float, float, float, float);
extern int D_001A79F0 __attribute__((sda));
extern void func_L09_003EAF60(char *);
extern void func_00282F20(void *, void *, float);
extern int func_002B38B8(char *);
extern int func_002B3868(char *);
extern int func_002E5CF8(int, int, char *);
extern void func_L20_004450D8(char *);
extern void *jtbl_002B5940[];

/* Runs the swinging arm (moby class 4584). It goes through its raise, drop and settle steps and keeps its linked object attached to it. */
void func_L20_00444CA8(char *obj) {
    /* Keep all eight destinations represented by the level's dispatch table. */
    static void *volatile states[] = {
        &&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7
    };
    Vec4 v, w;
    unsigned int sel;
    char *state = *(char **)(obj + 0x68);
    char *target = D_L20_001B2F9C + (*(int *)state << 8);

    sel = *(unsigned char *)(obj + 0x20);
    if (sel >= 8) goto c7;
    goto *jtbl_002B5940[sel];
    c0:
        if (*(int *)(state + 8)>=0) *(char **)(state + 0x10)=(char *)(D_L20_001B2F9C+(*(int *)(state + 8)<<8));
        else *(char **)(state + 0x10)=0;
        SetMobyState(obj, 1, -1); goto c7;
    c1:
        if (IsThirdPendingFlagSet(target)) {
            PlayMobySound(0, 0, obj);
            SetMobyState(obj, 2, -1);
        }
        if (D_0019B2E8[(unsigned char)obj[0xB0]+gCurrentMapIndex*16]&0x80) {
            *(float *)(obj + 0xF0)=fast_subtract_rotations(*(float *)(obj + 0xF0), 1.57079649f);
            SetMobyState(obj, 6, -1);
        }
        goto c7;
    c2:
        StepValueTowardTarget(obj + 0xF0, state + 4, -1.57079649f, 0.000533295097f, 174.532944f, 290.888275f);
        if (*(float *)(obj + 0xF0)<=-0.785398245f) {
            char *other=*(char **)(state + 0x10);
            if (other && *(short *)(other + 0xAA)==0xCBC /* Megacorp Hover Tank */ && (unsigned char)other[0x20]!=0xFE && (unsigned char)other[0x20]!=0xFD)
                DestroyMobyWithExplosion(other);
        }
        if (*(float *)(obj + 0xF0)<=-1.57079649f) { *(int *)(state + 4)=0; SetMobyState(obj, 3, -1); PlayMobySound(1, 0, obj); }
        goto c7;
    c3:
        StepValueTowardTarget(obj + 0xF0, state + 4, -1.30899704f, 0.0174532942f, 0.000436332368f, 0.87266475f);
        if (*(float *)(obj + 0xF0)>=-1.30899704f) { *(int *)(state + 4)=0; SetMobyState(obj, 4, -1); }
        goto c7;
    c4:
        StepValueTowardTarget(obj + 0xF0, state + 4, -1.57079649f, 0.000436332368f, 0.17453295f, 2.90888262f);
        if (*(float *)(obj + 0xF0)<=-1.57079649f) { *(int *)(state + 4)=0; SetMobyState(obj, 5, -1); PlayMobySound(1, 0, obj); }
        goto c7;
    c5:
        StepValueTowardTarget(obj + 0xF0, state + 4, -1.48353004f, 0.0174532942f, 0.000436332368f, 0.87266475f);
        if (*(float *)(obj + 0xF0)>=-1.48353004f) { *(int *)(state + 4)=0; SetMobyState(obj, 6, -1); }
        goto c7;
    c6:
        if (SetFirstPendingFlag(obj)) WakeGroupTroopers(obj);
        StepValueTowardTarget(obj + 0xF0, state + 4, -1.57079649f, 0.000436332368f, 0.17453295f, 2.90888262f);
        if (*(float *)(obj + 0xF0)<=-1.57079649f) { *(int *)(state + 4)=0; SetMobyState(obj, 7, -1); PlayMobySound(1, 0, obj); }
        goto c7;
    c7:
    {
        char *pos = target + 0x10;

        qcopy(pos, obj + 0x10);
        vec_scale_to_length(&v, obj + 0xE0, 5.7f);
        FastVecAdd(pos, pos, (char *)&v);
        vec_scale_to_length(&w, obj + 0xD0, 0.35f);
        FastVecAdd(pos, pos, (char *)&w);
    }
}
