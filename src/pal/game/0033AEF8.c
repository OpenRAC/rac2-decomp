#include "include_asm.h"

extern void func_003361A8(void *p);
extern void func_00336968(void *p);

/* func_00338F58 is matched in 00338F58.c. */

/* Initialises eight sub-objects at byte offsets 8, 84, 160, 236 (step 76) and 312, 384, 456, 528 (step 72) of the argument with two different helpers and returns the argument. */
void *func_PAL_0033AEF8(char *a0)
{
    func_003361A8(a0 + 8);
    func_003361A8(a0 + 84);
    func_003361A8(a0 + 160);
    func_003361A8(a0 + 236);
    func_00336968(a0 + 312);
    func_00336968(a0 + 400);
    func_00336968(a0 + 488);
    func_00336968(a0 + 576);
    return a0;
}


typedef struct { float x, y; } Float2_0033B218;

typedef struct {
    char pad[0x1C8];
    unsigned short count;
    unsigned short unused;
    unsigned int maximum;
    unsigned int levels;
} Statistics_0033B218;

extern void func_00335E38(void *, float, float, float, float);
extern int func_002DF1F8(void *, int);

extern Float2_0033B218 ref_L00_0042EC50_00;
extern Float2_0033B218 ref_L00_0042EC50_01;
extern Float2_0033B218 ref_L00_0042EC50_02;

extern int D_001B1688 __attribute__((sda));
extern int D_001C51D0;
extern unsigned int D_001A7390 __attribute__((sda));
extern int D_001A79F0 __attribute__((sda));
extern Statistics_0033B218 D_0018C750;

/* func_PAL_0033B218, the PAL copy of func_00339320: the same C, where the widgets from +0x180 sit 0x10 and 0x20 further on,
   the object at +0x258 is at +0x298, and the highest level time is scaled to 50 Hz before it is compared and kept. */
int func_PAL_0033B218(char *a0)
{
    Float2_0033B218 z0 = {0.0f, 0.0f};
    Float2_0033B218 z1 = {0.0f, 0.0f};
    Float2_0033B218 z2 = {0.0f, 0.0f};
    Float2_0033B218 z3 = {0.0f, 0.0f};
    Float2_0033B218 g0 = ref_L00_0042EC50_00;
    Float2_0033B218 g1 = ref_L00_0042EC50_01;
    Float2_0033B218 g2 = ref_L00_0042EC50_02;

    func_00335E38(a0 + 8, z0.x + (*(float **)(a0 + 4))[0], z0.y + (*(float **)(a0 + 4))[1], 0.0f, 0.0f);
    func_00335E38(a0 + 0x54, z3.x + (*(float **)(a0 + 4))[0], z3.y + (*(float **)(a0 + 4))[1], 0.0f, 0.0f);
    func_00335E38(a0 + 0xA0, z1.x + (*(float **)(a0 + 4))[0], z1.y + (*(float **)(a0 + 4))[1], 0.0f, 0.0f);
    func_00335E38(a0 + 0xEC, z2.x + (*(float **)(a0 + 4))[0], z2.y + (*(float **)(a0 + 4))[1], 0.0f, 0.0f);
    func_00335E38(a0 + 0x138, g0.x + (*(float **)(a0 + 4))[0], g0.y + (*(float **)(a0 + 4))[1], 0.0f, 0.0f);
    func_00335E38(a0 + 0x190, g1.x + (*(float **)(a0 + 4))[0], g1.y + (*(float **)(a0 + 4))[1], 0.0f, 0.0f);
    func_00335E38(a0 + 0x1E8, g2.x + (*(float **)(a0 + 4))[0], g2.y + (*(float **)(a0 + 4))[1], 0.0f, 0.0f);
    func_002DF1F8(a0 + 0x298, D_001C51D0);
    if (D_001B1688 >= 11) {
        if (D_0018C750.count < 0xffff) D_0018C750.count++;
    }
    if (((int)D_001A7390 * 5 + 2) / 6 > D_0018C750.maximum) D_0018C750.maximum = ((int)D_001A7390 * 5 + 2) / 6;
    D_0018C750.levels = (D_0018C750.levels | (1u << D_001A79F0)) | 0x80000000u;
    return 0;
}

extern void func_00336320(char *a);
extern void func_PAL_00338770(char *a);

/* early-returns when a 32-bit field is zero, otherwise calls one helper four times and another three times with fixed byte offsets off the argument pointer. */
void func_PAL_0033B4B8(char *a0)
{
    if (*(int *)(a0 + 728) == 0)
        return;
    func_00336320(a0 + 8);
    func_00336320(a0 + 84);
    func_00336320(a0 + 160);
    func_00336320(a0 + 236);
    func_PAL_00338770(a0 + 312);
    func_PAL_00338770(a0 + 400);
    func_PAL_00338770(a0 + 488);
}



typedef int s32;
typedef unsigned char u8;

void func_PAL_0033B688(u8 *a0) {s32 v=1;*(s32 *)(a0+0x330)=v;}

extern void func_0033AE18(unsigned char *owner, int value);

void func_PAL_0033B698(unsigned char *owner, int value)
{
    func_0033AE18(owner + 8, value);
}

/* Measured target: byte-identical across all 27 levels. */
void func_PAL_0033B6B8(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x328) = a1; }

extern int func_00288FB8_3(int);
extern void func_0033B050(char *, int, int, int);
extern void func_0033B0A8(char *, float);

/* Calls a one-argument helper three times with three fixed small integers, passes the three results and a pointer plus 8 to a four-argument helper, calls a two-argument helper with the same address and 0.0f, then clears the word at offset 764. */
void func_PAL_0033B6C0(char *p)
{
    int first = func_00288FB8_3(2991);
    int second = func_00288FB8_3(2989);

    func_0033B050(p + 8, first, second, func_00288FB8_3(2912));
    func_0033B0A8(p + 8, 0.0f);
    *(int *)(p + 812) = 0;
}



extern void func_L00_0042BAD0_1(char *object);
extern void func_L00_0042C290_1(char *object);

/* calls two one-argument functions on a sequence of sub-objects of the argument (four at 8..236 stride 76, nine at 312..888 stride 72) and returns the argument */
char *func_PAL_0033B960(char *object)
{
    func_L00_0042BAD0_1(object + 8);
    func_L00_0042BAD0_1(object + 84);
    func_L00_0042BAD0_1(object + 160);
    func_L00_0042BAD0_1(object + 236);
    func_L00_0042C290_1(object + 312);
    func_L00_0042C290_1(object + 400);
    func_L00_0042C290_1(object + 488);
    func_L00_0042C290_1(object + 576);
    func_L00_0042C290_1(object + 664);
    func_L00_0042C290_1(object + 752);
    func_L00_0042C290_1(object + 840);
    func_L00_0042C290_1(object + 928);
    func_L00_0042C290_1(object + 1016);
    return object;
}

typedef struct {
    float x, y;
} Point2_0033BE50;

extern void *func_00115484(void *, int, int);
extern void func_00335F88(void *, float, float, float, float);
extern int func_00288FB8(int);
extern void func_00336A38(void *, int);
extern Point2_0033BE50 D_001ADCE0, D_001ADCE8, D_001ADCF0, D_001ADCF8;
extern Point2_0033BE50 D_001ADD00 __attribute__((sda));
extern Point2_0033BE50 D_001ADD00_gp __asm__("D_001ADD00__gp") __attribute__((section(".sdata")));
extern char D_001C4FA0[];
extern int D_00258D70[];
extern char D_001ADC88[];

/* func_PAL_0033BE50, the PAL copy of func_00339F28: the same C, where the six list widgets from
   +0x190 sit 0x58 apart instead of 0x48, and the scale pair is read directly at each call instead
   of through a stack copy. Retail reads its x through $gp and its y absolute, so x uses the
   measured GP view of the same address. */
int func_PAL_0033BE50(char *obj, int unused)
{
    Point2_0033BE50 z0, z1, z2, z3;
    Point2_0033BE50 title, list, prev, next;
    char *base;
    int index;

    func_00115484(&z0, 0, 8);
    func_00115484(&z1, 0, 8);
    func_00115484(&z2, 0, 8);
    func_00115484(&z3, 0, 8);
    title = D_001ADCE0;
    list = D_001ADCE8;
    prev = D_001ADCF0;
    next = D_001ADCF8;
    func_00335F88(obj + 0x190, D_001ADD00_gp.x, D_001ADD00.y, 0.0f, 0.0f);
    func_00335F88(obj + 0x1E8, D_001ADD00_gp.x, D_001ADD00.y, 0.0f, 0.0f);
    func_00335F88(obj + 0x240, D_001ADD00_gp.x, D_001ADD00.y, 0.0f, 0.0f);
    func_00335F88(obj + 0x298, D_001ADD00_gp.x, D_001ADD00.y, 0.0f, 0.0f);
    func_00335F88(obj + 0x2F0, D_001ADD00_gp.x, D_001ADD00.y, 0.0f, 0.0f);
    func_00335F88(obj + 0x348, D_001ADD00_gp.x, D_001ADD00.y, 0.0f, 0.0f);
    func_00335E38(obj + 0x8, z0.x + (*(float **)(obj + 4))[0],
                  z0.y + (*(float **)(obj + 4))[1], 0.0f, 0.0f);
    func_00335E38(obj + 0x54, z3.x + (*(float **)(obj + 4))[0],
                  z3.y + (*(float **)(obj + 4))[1], 0.0f, 0.0f);
    func_00335E38(obj + 0xA0, z1.x + (*(float **)(obj + 4))[0],
                  z1.y + (*(float **)(obj + 4))[1], 0.0f, 0.0f);
    func_00335E38(obj + 0xEC, z2.x + (*(float **)(obj + 4))[0],
                  z2.y + (*(float **)(obj + 4))[1], 0.0f, 0.0f);
    func_00335E38(obj + 0x138, title.x + (*(float **)(obj + 4))[0],
                  title.y + (*(float **)(obj + 4))[1], 0.0f, 0.0f);
    func_00335E38(obj + 0x190, list.x + (*(float **)(obj + 4))[0],
                  list.y + (*(float **)(obj + 4))[1], 0.0f, 0.0f);
    func_00335E38(obj + 0x1E8, list.x + (*(float **)(obj + 4))[0],
                  list.y + (*(float **)(obj + 4))[1] + 18.0f, 0.0f, 0.0f);
    func_00335E38(obj + 0x240, list.x + (*(float **)(obj + 4))[0],
                  list.y + (*(float **)(obj + 4))[1] + 36.0f, 0.0f, 0.0f);
    func_00335E38(obj + 0x298, list.x + (*(float **)(obj + 4))[0],
                  list.y + (*(float **)(obj + 4))[1] + 54.0f, 0.0f, 0.0f);
    func_00335E38(obj + 0x2F0, list.x + (*(float **)(obj + 4))[0],
                  list.y + (*(float **)(obj + 4))[1] + 72.0f, 0.0f, 0.0f);
    func_00335E38(obj + 0x348, list.x + 8.0f + (*(float **)(obj + 4))[0],
                  list.y + (*(float **)(obj + 4))[1] + 90.0f, 0.0f, 0.0f);
    func_00335E38(obj + 0x3A0, prev.x + (*(float **)(obj + 4))[0],
                  prev.y + (*(float **)(obj + 4))[1], 0.0f, 0.0f);
    func_00335E38(obj + 0x3F8, next.x + (*(float **)(obj + 4))[0],
                  next.y + (*(float **)(obj + 4))[1], 0.0f, 0.0f);
    base = D_001C4FA0;
    func_002DF1F8(obj + 0x450, *(int *)(base + 0x230));
    index = D_00258D70[*(int *)(base + 0x230) * 2 + 1];
    if (index >= 0)
        func_00336A38(obj + 0x3F8, func_00288FB8(index));
    else
        func_00336A38(obj + 0x3F8, (int)D_001ADC88);
    return 0;
}

extern void F8ad956d6_FUN_00336320(char *target);
extern void F8ad956d6_FUN_002FC560(int marker, int code);
extern void F8ad956d6_FUN_00295F60(int first, int second);
extern void F8ad956d6_FUN_002DAF68(char *target);
extern void F8ad956d6_FUN_00336A78(char *target);

void func_PAL_0033C308(char *object)
{
    char *s0 = object;

    if (*(int *)(s0 + 1168) == 0)
        return;
    F8ad956d6_FUN_00336320(s0 + 8);
    F8ad956d6_FUN_00336320(s0 + 84);
    F8ad956d6_FUN_002FC560(66, 68);
    F8ad956d6_FUN_002FC560(71, 11);
    F8ad956d6_FUN_00295F60(0, 1);
    F8ad956d6_FUN_002DAF68(0);
    F8ad956d6_FUN_00336320(s0 + 160);
    F8ad956d6_FUN_00336320(s0 + 236);
    F8ad956d6_FUN_00336A78(s0 + 312);
    F8ad956d6_FUN_00336A78(s0 + 400);
    F8ad956d6_FUN_00336A78(s0 + 488);
    F8ad956d6_FUN_00336A78(s0 + 576);
    F8ad956d6_FUN_00336A78(s0 + 664);
    F8ad956d6_FUN_00336A78(s0 + 752);
    F8ad956d6_FUN_00336A78(s0 + 840);
    F8ad956d6_FUN_00336A78(s0 + 928);
    F8ad956d6_FUN_00336A78(s0 + 1016);
}

