/* 4 November 2026: meaningful coordinate grouping and a complete position
 * view reduce this to a 360-byte near miss, 0/28 USA placements, first +0x60.
 * The 300.0 literal and mutable screen-scale load still issue in the opposite
 * order. Explicit multiplication steps and an incomplete sda array view tie.
 * No const claim is made for the scale that the display-mode setter writes.
 * US2/PAL also differ at +0x24 because their object fields moved by 16 bytes;
 * a future promotion must establish their separate catalogue identities.
 * Profile: -O2 -G0 -ffunction-sections. No linked match is claimed.
 */
#include "common.h"

typedef struct { float x, y, width, height; } TitlePosition;
extern void func_00336710(void *, void *, void *);
extern void func_00335F88(void *, float, float, float, float);
extern int func_00335E20(void *);
extern void func_003369A8(void *, void *, void *);
extern int *func_00336DA8(int, int);
extern int func_00336E40(void *);
extern char D_001ADC88[];
extern float D_001B23A4[] __attribute__((sda));

void func_0033A520(unsigned char *obj, void *arg)
{
    float v;
    TitlePosition *p;
    char *text;

    *(int *)(obj + 0x1F8) = 0;
    *(void **)(obj + 0x200) = arg;
    if (arg != 0) {
        int *alloc = func_00336DA8(16, func_00336E40(arg));
        *(int **)(obj + 0x1FC) = alloc;
        alloc[1] = 0;
        alloc[2] = 0;
        alloc[3] = 0;
        alloc[0] = 0;
    }
    do {
        v = 300.0f;
        v *= D_001B23A4[0];
        v = (float)(int)(v + 0.5f);
        p = *(TitlePosition **)(obj + 0x1FC);
        p->x = 70.0f;
    } while (0);
    text = D_001ADC88;
    p = *(TitlePosition **)(obj + 0x1FC);
    p->y = v;
    func_00336710(obj + 0x134, text, *(void **)(obj + 0x200));
    func_00335F88(obj + 0x134, 24.0f, 24.0f, 0.0f, 0.0f);
    *(int *)func_00335E20(obj + 0x134) = 0x60F0F0B0;
    v = 65.0f;
    *(float *)(obj + 0x204) = v;
    func_003369A8(obj + 0x170, text, *(void **)(obj + 0x200));
    *(int *)func_00335E20(obj + 0x170) = 0x80F0F0F0;
    func_00335F88(obj + 0x170, 0.7f, 0.7f, 0.0f, 0.0f);
}

/* 5 November 2026 (w-c2): 360/360 bytes, 0/28, first +0x60 (same as above). Retail issues lui 0x4396/mtc1
 * (300.0) before the lui/lwc1 of D_001B23A4, with the product in $f0 and 70.0 in $f1. Tried: `D * 300.0f`,
 * `300.0f * D`, scalar extern instead of array, locals c/sc, direct expression with no group
 * (356/360 bytes): the global load is always first or the registers rotate. Same ordering blocker. */
