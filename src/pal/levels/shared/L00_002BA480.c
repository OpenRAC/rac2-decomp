#include "include_asm.h"

#include "common.h"
typedef struct {
    u8 pad0[0x184];
    float f184;
    u8 pad188[0x1B8 - 0x188];
    int i1B8;
    u8 pad1bc[0x278 - 0x1BC];
    float f278;
    u8 pad27c[0x280 - 0x27C];
    float f280;
    u8 b284;
    u8 pad285[0xC04 - 0x285];
    float fC04;
    float fC08;
    u8 padc0c[0x1220 - 0xC0C];
    char *p1220;
    u8 pad1224[0x123A - 0x1224];
    u8 b123A;
    u8 pad123b[0x1500 - 0x123B];
    int i1500;
    u8 pad1504[0x1A30 - 0x1504];
    u8 area1A30[0x2290 - 0x1A30];
    char *p2290;
    int i2294;
} ResidentState_A508;
extern ResidentState_A508 D_00189E20_A508;
extern struct {
    u8 pad0[0x150];
    float x, y, z;
} D_L00_001B8C80_A508;
extern float func_00283B98(float a, float b);
extern int func_L00_002B3248(void *obj);
extern void func_00282C88(void *m);
extern void func_L00_002D3798(void *dst, void *src, float f);
extern void func_002AF000(void *m, float a, float b, float c);
extern void func_002833F0(void *dst, void *v);
extern void func_00283738(void *dst, void *a, void *b);
extern void func_00283658(void *dst, void *src);
extern void func_002AB6D8(void *src, void *dst);
extern void func_L00_00322A98(void *obj, void *area);
extern void func_L00_00322AC0(void *area, int a, int b, float f);
extern void func_PAL_002A7E68(void *obj, int a, int b, int c);

/* Once per hero state, set up the object at resident +0x1220 (the special case uses a stored angle
   and the level vector at +0x150 of the block func_L00_002BA410 queries, otherwise the unit scale
   and the parent transform) and pass the composed transform to the object at +0xF0.
   Does nothing once the byte at +0x123A is set. */
void func_PAL_L00_002BA480(void)
{
    float scratch[4];
    u8 transform[48], level_transform[48], composed[64];
    char *object, *record, *matrix;
    int special;

    if (D_00189E20_A508.b123A)
        return;

    special = 0;
    if (D_00189E20_A508.i1500)
        special = 1;
    if (D_00189E20_A508.i2294 == 1 || D_00189E20_A508.i2294 == 29) {
        special = 0;
        if (D_00189E20_A508.i1B8 > 17)
            special = 1;
    }

    if (special && !func_L00_002BA410()) {
        D_00189E20_A508.fC04 = D_L00_001B8C80_A508.z;
        D_00189E20_A508.fC08 = func_00283B98(-D_L00_001B8C80_A508.y, 0.12217305600643158f);
    }

    object = D_00189E20_A508.p1220;
    if (!func_L00_002B3248(object))
        return;
    D_00189E20_A508.b123A = 1;
    if (special)
        func_L00_002B9B88(17, 0);

    *(u8 *)(object + 0x20) = 10;
    record = *(char **)(object + 0x68);
    if (D_00189E20_A508.f278 < 1.2f && D_00189E20_A508.f280 > 0.6632251739501953f
        && !D_00189E20_A508.b284)
        *(short *)(record + 0x76) = 1;

    matrix = record + 0x40;
    func_00282C88(matrix);
    if (!special)
        func_L00_002D3798(matrix, matrix, 1.0f);
    else
        func_002AF000(matrix, 1.0f, D_00189E20_A508.fC04, D_00189E20_A508.fC08);

    func_00282C88(scratch);
    func_002833F0(transform, scratch);
    if (special) {
        scratch[0] = D_L00_001B8C80_A508.x;
        scratch[1] = D_L00_001B8C80_A508.y;
        scratch[2] = D_L00_001B8C80_A508.z;
        func_002833F0(level_transform, scratch);
        func_00283738(transform, level_transform, transform);
    } else {
        func_00283738(transform, D_00189E20_A508.p2290 + 0xC0, transform);
    }
    func_00283658(composed, transform);
    func_002AB6D8(composed, object + 0xF0);

    *(int *)(record + 0x64) = 0;
    *(float *)(record + 0x60) = 0.46000004f;
    if (D_00189E20_A508.f184 < 0.40000004f) {
        func_L00_00322A98(object, D_00189E20_A508.area1A30);
        func_L00_00322AC0(D_00189E20_A508.area1A30, 48, 3, 0.0f);
        func_L00_00322AC0(D_00189E20_A508.area1A30, 23, 5, 0.0f);
    }
    func_PAL_002A7E68(object, 6, 0, 4);
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_002BA750);


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_002C3250);


