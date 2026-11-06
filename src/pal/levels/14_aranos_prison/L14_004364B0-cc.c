/* func_PAL_L14_004364B0, the PAL copy of func_L14_00430B70: the same C, where rename func_L14_004308D0 becomes func_PAL_L14_00436790; wrap func_00282948(s+0x50+i*4) (((int)({e}) * 5 + 2) / 6); wrap (((int)(func_00282948(s+0x50+i*4)) * 5 + 2) / 6) (((int; wrap (int)((float)*(int *)(s+0x10) / ((PrisonVisualState *)s; wrap ((int)((((int)(func_00282948(s+0x50+i*4)) * 5 + 2) / 6); lit 5 becomes 6; lit 6 becomes 5; rewrap (int)((float)*(int *)(s+0x10) / ((PrisonVisualState *; rename func_PAL_L14_00436790 becomes func_L14_004308D0; rename func_L14_00430E08 becomes func_PAL_L14_00436790. */
#include "common.h"
typedef struct { char pad[0x20]; float rate[4]; unsigned int start[4]; unsigned int end[4]; int timer[4]; float angle[4]; } PrisonVisualState;
extern void func_L14_004308D0(void *, int, int, int, float, float, float);
extern float func_L14_00430898(float);
extern void func_PAL_L14_00436790(void *);
extern int func_00282948(void *);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern float func_00283B98(float, float);

void func_PAL_L14_004364B0(char *self)
{
    char *s = *(char **)(self + 0x68);
    int i;
    unsigned int color;
    float t, scale, angle;
    func_L14_004308D0(self + 0x10, *(int *)(s+0xb8), *(int *)(s+0xc0), 1,
        *(float *)(s+0xbc) * *(float *)(s+0x80), *(float *)(s+0x80)*0.5f, 0.0f);
    for (i=0; i<2; i++) {
        if (((((int)(((int)(func_00282948(s+0x50+i*4)) * 6 + 2)) * 5 + 2) / 6) / 5))
            ((PrisonVisualState *)s)->timer[i] = (((int)((int)((float)*(int *)(s+0x10) / ((PrisonVisualState *)s)->rate[i])) * 5 + 2) / 6);
        t = 1.0f - (float)((PrisonVisualState *)s)->timer[i] /
            (float)(((int)((int)((float)*(int *)(s+0x10) / ((PrisonVisualState *)s)->rate[i])) * 5 + 2) / 6);
        if (*(float *)(s+0x14) < t) {
            color = ((PrisonVisualState *)s)->end[i];
            color = (color & 0xffffff) + (((int)((1.0f-t)/(1.0f-*(float *)(s+0x14))*80.0f)+48)<<24);
        } else {
            color = func_00283D38(((PrisonVisualState *)s)->start[i], ((PrisonVisualState *)s)->end[i], t / *(float *)(s+0x14));
            color = (color & 0xffffff) + (((int)(t / *(float *)(s+0x14)*80.0f)+48)<<24);
        }
        scale = *(float *)(s+0x80) * *(float *)(s+0x18);
        angle = func_L14_00430898(t * (((PrisonVisualState *)s)->angle[i] * 6.2831855f));
        func_L14_004308D0(self+0x10, *(int *)(s+0x1c), color, 1, scale, *(float *)(s+0x80)*0.5f, angle + -3.1415927f);
    }
    *(float *)s = func_00283B98(*(float *)s, 0.007f);
    func_L14_004308D0(self+0x10, *(int *)(s+4), *(int *)(s+12), 1,
        *(float *)(s+8)* *(float *)(s+0x80), *(float *)(s+0x80)*0.5f, *(float *)s);
    func_PAL_L14_00436790(self);
}

void func_PAL_L14_00436790(void *arg);
