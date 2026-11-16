#include "include_asm.h"
#include "names.h"


extern int text_measure_width_small(unsigned char *text, int length); /* text width */

/* func_PAL_00339B88, the PAL copy of func_00337E30: the same C, plus a store of the second argument at +0x1C4. */
void func_PAL_00339B88(char *p, int a1, int a2, float f12, float f13)
{
    char *q = p + 168;

    *(int *)(p + 452) = a1;
    *(float *)(*(int *)p) = f12;
    *(float *)(*(int *)p + 4) = f13;
    p[423] = 0;
    *(int *)(p + 440) = a2;
    *(int *)(p + 472) = (int)q;
    *(int *)(p + 468) = text_measure_width_small((unsigned char *)q, -1);
    *(int *)(p + 432) = 1;
    *(float *)(*(int *)(p + 4)) = 1.0f;
}

extern char *strncpy(void *, int, int);
extern void func_PAL_00339BF8(void *, int, int, float, float);

/* clamps a caller-supplied terminator value (-1 meaning unset) to 360, then runs two callees on two sub-objects of one handle, the second with a float pair */
void func_PAL_00339DC8(int object, int value, int count)
{
    int limit = (count == -1) ? 300 : count;
    int inner = object + 8156;

    strncpy((void *)(object + 8324), value, 255);
    func_PAL_00339BF8((void *)inner, 2, limit, 255.0f, 80.0f);
}





/* clamps a caller-supplied terminator value (-1 meaning unset) to 180, then runs two callees on two sub-objects of one handle, the second with a float pair */
void msg_box_init_short_pal(int object, int value, int count)
{
    int limit = (count == -1) ? 150 : count;
    int inner = object + 7564;

    strncpy((void *)(object + 7732), value, 254);
    func_PAL_00339BF8((void *)inner, 2, limit, 255.0f, 123.0f);
}

