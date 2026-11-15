#include "common.h"

extern int func_00283CF0(float);
extern void func_002A7750(char *, int, int);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(char *);
extern int func_002E5CF8(int, int, char *);
extern int func_002B0ED8(char *, void *, int);
extern void func_L07_003E5AC8(char *);
extern void func_L07_003E5D80(char *);
extern void func_L07_003E6148(char *);
/* Returns int (src/game/002B3BA8.c); the call's result register shapes the allocation after it. */
extern int func_002B3BA8(char *, int, void *, int, float, float);

/* Two tuning values: the first scaled by 1/3600, the second by 1/60. */
extern float D_L07_001B0AA0 __attribute__((sda));
extern float D_L07_001B0AA4 __attribute__((sda));
extern char D_L07_001B9200[];
/* The sound slots, 0x70 bytes each. */
extern char D_00188660[];

/* In state 0, set up the object's state block (offsets in ascending order, with +0x98 first and
   +0x30 last, as retail's store schedule requires). Then: within 24 units of D_L07_001B9200 while
   +0x31 is set, call func_002A93B0; restart the sound when its slot no longer belongs to the
   object; run func_L07_003E5AC8 and func_L07_003E5D80 on a func_002B0ED8 count of two or more or
   when +0x2E is 2; and follow the platform at +0x260 unless the state byte is 8. */
void func_L07_003E56B8(char *arg)
{
    char *o = *(char **)(arg + 0x68);
    char *slot;
    float f, g;

    if (*(unsigned char *)(arg + 0x20) == 0) {
        *(unsigned char *)(o + 0x48) = FloatToInt(15.0f);
        *(unsigned char *)(o + 0x4A) = FloatToInt(2.4f);
        *(unsigned char *)(o + 0x60) = 7;
        *(unsigned char *)(o + 0x2E) = 1;
        *(unsigned char *)(o + 0xC7) = 1;
        f = D_L07_001B0AA0;
        g = D_L07_001B0AA4;
        f *= 0.00027777778f;
        g *= 0.016666667f;
        *(int *)(o + 0x98) = 3;
        *(float *)(o + 0x80) = 0.5f;
        *(int *)(o + 0x84) = 0;
        *(float *)(o + 0x8C) = 0.15f;
        *(float *)(o + 0xA8) = 1.0f;
        *(float *)(o + 0xAC) = 1.0f;
        *(float *)(o + 0x120) = 0.45f;
        *(int *)(o + 0x124) = 0;
        *(float *)(o + 0x140) = f;
        *(float *)(o + 0x144) = f;
        *(float *)(o + 0x148) = g;
        *(int *)(o + 0x158) |= 0x15;
        *(int *)(o + 0x30) = 0;
        qcopy(o + 0x220, arg + 0x10);
        if (*(short *)(o + 0x218))
            func_002A7750(arg, 1, 0);
        else {
            *(int *)(arg + 0x98) = 0;
            *(unsigned short *)(arg + 0x34) = (*(unsigned short *)(arg + 0x34) | 0x41) & 0xEFFF;
            func_002A7750(arg, 8, 4);
        }
    }
    if (*(unsigned char *)(arg + 0x31) && fast_vec_dist(arg + 0x10, D_L07_001B9200) < 24.0f) {
        func_002A93B0(arg);
        *(unsigned char *)(arg + 0x6F) = 22;
    }
    if (*(unsigned char *)(arg + 0x95) != 4) {
        slot = D_00188660 + *(int *)(o + 0x264) * 0x70;
        if (*(char **)(slot + 0x88) != arg || !*(unsigned char *)(slot + 0x74))
            *(int *)(o + 0x264) = PlayMobySound(1, 4, arg);
    }
    if (func_002B0ED8(arg, o + 0x50, 0) >= 2 || *(unsigned char *)(o + 0x2E) == 2) {
        func_L07_003E5AC8(arg);
        func_L07_003E5D80(arg);
    }
    func_002B3BA8(arg, *(int *)(o + 0x214), 0, 0, 0.0f, 0.0f);
    if (*(int *)(o + 0x260) && *(unsigned char *)(arg + 0x20) != 8)
        func_L07_003E6148(arg);
}
