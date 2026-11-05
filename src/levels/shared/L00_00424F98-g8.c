#include "common.h"

typedef struct {
    char pad[0x60];
    unsigned short count;
    unsigned short pad62;
    unsigned int best;
    unsigned int flags;
} L00_00424F98_Counter;

/* The vehicle's input block, at +0x1C0 of its motion record. */
typedef struct {
    char pad0[0x10];
    int flags;
    float steer_out;
    char pad18[4];
    float steer;
    char pad20[4];
    float throttle;
} L00_00424F98_Input;

extern float D_00138280[];
extern float D_00138284[];
extern s32 D_001A7BA8 MACRO_ADDR;
extern s32 D_001A7BA4 MACRO_ADDR;
extern s32 D_001A79F0 MACRO_ADDR;
extern unsigned int D_001A7390 MACRO_ADDR;
extern L00_00424F98_Counter D_0018C750;
extern s32 ref_L00_00424F98_00 __attribute__((sda));
extern s32 ref_L00_00424F98_01 __attribute__((sda));
extern float ref_L00_00424F98_02 __attribute__((sda));
extern float ref_L00_00424F98_03 SDATA(ref_L00_00424F98_03);

/* The vehicle's steering and throttle inputs, with the stunt counter: holding the
   stick centred for a second counts one run and records the best time. */
void func_L00_00424F98(char *obj, float *x, float *y)
{
    L00_00424F98_Input *t = (L00_00424F98_Input *)(*(char **)(obj + 0x70) + 0x1C0);
    L00_00424F98_Counter *c;
    unsigned int n;
    float v;

    if (t->flags & 1) {
        *x = 0.0f;
    } else {
        *x = D_00138280[0];
        if (D_001A7BA8 == 0)
            *x = -*x;
    }
    if (*x == 0.0f) {
        ref_L00_00424F98_00 = 0;
        ref_L00_00424F98_01 = 0;
        if (t->steer != 0.0f)
            *x = t->steer;
    } else {
        t->steer_out = ref_L00_00424F98_02;
        c = &D_0018C750;
        n = c->count;
        if ((unsigned short)n < 3U) {
            ref_L00_00424F98_00++;
            if (ref_L00_00424F98_01 == 0 && ref_L00_00424F98_00 > 0x3C) {
                if ((unsigned short)n < 0xFFFF)
                    c->count = n + 1;
                if (D_001A7390 > c->best)
                    c->best = D_001A7390;
                ref_L00_00424F98_01 = 1;
                c->flags = (c->flags | (1u << D_001A79F0)) | 0x80000000u;
            }
        }
    }
    if (t->flags & 2) {
        *y = 0.0f;
    } else {
        v = D_00138284[0];
        *y = -v;
        if (D_001A7BA4 == 0)
            *y = v;
        if (*y != 0.0f)
            return;
    }
    {
        float throttle = t->throttle;
        *y = throttle / ref_L00_00424F98_03;
    }
}
