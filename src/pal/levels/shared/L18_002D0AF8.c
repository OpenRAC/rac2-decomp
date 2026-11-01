#include "include_asm.h"

#include "common.h"
extern s32 D_L18_001AFBB0 MACRO_ADDR;
extern u8 D_00189E20[];
typedef struct {
    u8 reserved000[0x80];
    float position[4];
    u8 reserved090[0x1D00];
    float positionHistory[32][4];
    u8 reserved1F90[0x3AC];
    float headingHistory[32];
    s32 headingIndex, headingCount, positionIndex, positionCount;
} HeroHistory;
typedef struct {
    u8 reserved000[0x108];
    float horizontal, vertical;
    u8 reserved110[0x90];
    s32 held;
    u8 reserved1A4[12];
    s32 pressed;
} InputRecordPrefix;
extern InputRecordPrefix D_00138180;
extern void func_L00_002B2BD0(void);
extern s32 func_00282978(void *);
extern s32 func_PAL_L00_002D3928(void);
extern float func_L00_002B3900(void);
extern float func_00282E20(void *);
extern void func_PAL_L18_002D7598(void);
extern void func_00283410(void *, void *);
extern void func_00283388(void *);
extern void func_00283698(void *, void *);
extern void func_PAL_L18_002D0738(void);
extern void func_PAL_L00_002C2F88(void);
extern void func_PAL_L18_002DF168(void);
extern s32 func_002761F8(void *, void *, s32, void *, void *);
extern s32 func_00278E78(void);

/* func_L18_002C4000 is defined in L18_002C4000-hero.c. */

/* func_L18_002C41F0 is defined in L18_002C4000-g8.c (this unit has $gp access for it). */

/* func_L18_002CFD68 is defined in L18_002CFD68-qcopy.c. */

/* func_L18_002CFF48 is defined in L18_002CFD68-qcopy.c. */

void func_PAL_L18_002D0AF8(void)
{
    u8 *base;
    u8 *snapshot;
    u8 *positions;
    s32 index;
    s32 active = D_L18_001AFBB0;
    if (active) {
        func_L00_002B2BD0();
        return;
    }
    snapshot = D_00189E20 + 0x2030;
    qcopy(snapshot, snapshot - 0x1FB0);
    if (D_00138180.held & 3) {
        u8 *hero = snapshot - 0x2030;
        if (*(s16 *)(hero + 0x1454) < 1) *(s16 *)(hero + 0x1454) = 1;
    } else func_00282978(snapshot - 0xBDC);
    base = D_00189E20;
    if (*(s32 *)(base + 0x2294) == 16) *(s16 *)(base + 0x1454) = 0;
    base[0x22C3] = func_PAL_L00_002D3928();
    *(float *)(base + 0x1FB0) = D_00138180.horizontal;
    *(float *)(base + 0x1FB4) = D_00138180.vertical;
    *(s32 *)(base + 0x270) = 0;
    *(float *)(base + 0x24BC) = func_L00_002B3900();
    if (func_00282E20(base + 0x1FB0) < 0.25f) {
        /* horizontal and vertical start as the left and down bits. */
        s32 right = (D_00138180.pressed >> 13) & 1;
        s32 horizontal = (D_00138180.pressed >> 15) & 1;
        s32 up = (D_00138180.pressed >> 14) & 1;
        s32 vertical = (D_00138180.pressed >> 12) & 1;
        horizontal = right - horizontal;
        vertical = up - vertical;
        *(float *)(base + 0x1FB0) = (float)horizontal;
        *(float *)(base + 0x1FB4) = (float)vertical;
    }
    *(float *)(base + 0x24B8) = func_L00_002B3900();
    func_PAL_L18_002D7598();
    ((HeroHistory *)base)->headingHistory[((HeroHistory *)base)->headingIndex] = *(float *)(base + 0x98);
    *(s32 *)(base + 0x23BC) = (*(s32 *)(base + 0x23BC) + 1) % 32;
    if (++*(s32 *)(base + 0x23C0) > 32) *(s32 *)(base + 0x23C0) = 32;
    index = *(s32 *)(base + 0x23C4);
    positions = base + 0x1D90;
    qcopy_nc(positions + index * 16, (base + 0x80));
    *(s32 *)(base + 0x23C4) = (index + 1) % 32;
    if (++*(s32 *)(base + 0x23C8) > 32) *(s32 *)(base + 0x23C8) = 32;
    func_00283410(base, base + 0x90);
    func_00283388(base + 0x40);
    func_00283698(base + 0x40, base);
    func_PAL_L18_002D0738();
    func_PAL_L00_002C2F88();
    func_PAL_L18_002DF168();
}


extern s32 func_L00_002D3400(void);
typedef struct { u8 prefix[0x18]; s32 object; s32 count; u8 gap[0x20]; float normal[4]; } MotionCollision;
extern MotionCollision D_L18_001BFC00;
extern float func_L00_002D3A58(void *);
extern void func_L00_002D36E0(float *, float, float, float, s32);
extern void func_00282F20(void *, void *, float);
extern void func_L00_002D3B58(float *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_L00_002D3EA8(void *);
extern float func_00282DB0(void *, void *);
extern void func_00282F20(void *a0, void *a1, float f12);
extern void func_00282CC0(void *a0, void *a1, void *a2);
extern void func_00282F20(void *a0, void *a1, float f12);
extern void func_00282CC0(void *a0, void *a1, void *a2);

void func_PAL_L18_002D1890(s32 force)
{
    float start[4], end[4], lowerStart[4], lowerEnd[4];
    float height, reach, angle, dot;
    s32 material;
    if (func_L00_002D3A58(D_00189E20 + 0xF0) < 0.002f) return;
    /* Each block forms its own hero pointer; retail keeps only the %hi part across calls. */
    {
        u8 *hero = D_00189E20;
        height = 0.37f;
        reach = 0.5f;
        if ((u32)(*(s32 *)(hero + 0x229C) - 17) < 2) {
            height = 0.0f;
            reach = 0.7f;
        } else if (hero[0x22B4] == 4) height = 0.35f;
    }
    func_L00_002D36E0(start, 0.0f, 0.0f, height, 1);
    func_L00_002D36E0(lowerStart, 0.0f, 0.0f, height * 0.3f, 1);
    if (force || func_00282E20(D_00189E20 + 0xF0) < 0.01f) {
        func_00282F20(end, D_00189E20, reach);
        func_00282F20(lowerEnd, D_00189E20, reach * 1.4f);
    } else {
        func_L00_002D3B58(end, D_00189E20 + 0xF0, 0.0f);
        func_00282F20(end, end, reach);
        func_00282D30(lowerEnd, end, 1.4f);
    }
    func_00282CC0(end, end, start);
    material = -1;
    func_00282CC0(lowerEnd, lowerEnd, lowerStart);
    {
        u8 *hero = D_00189E20;
        if (func_002761F8(lowerStart, lowerEnd, 2, *(u8 **)(hero + 0x2290), 0) && D_L18_001BFC00.count > 0) material = func_00278E78();
    }
    angle = 0.0f;
    {
        u8 *hero = D_00189E20;
        if (func_002761F8(start, end, 2, *(u8 **)(hero + 0x2290), 0) && D_L18_001BFC00.count > 0) angle = func_L00_002D3EA8(D_L18_001BFC00.normal);
    }
    if (angle >= 0.8726647f || material == 8 || material == 12) {
        u8 *hero = D_00189E20;
        *(s32 *)(hero + 0x270) = D_L18_001BFC00.object;
        func_L00_002D3B58(D_L18_001BFC00.normal, D_L18_001BFC00.normal, 0.0f);
        func_00282F20(D_L18_001BFC00.normal, D_L18_001BFC00.normal, 1.0f);
        dot = func_00282DB0(D_L18_001BFC00.normal, hero + 0xF0);
        if (dot < 0.0f) {
            func_00282D30(D_L18_001BFC00.normal, D_L18_001BFC00.normal, -dot);
            func_00282CC0(hero + 0xF0, hero + 0xF0, D_L18_001BFC00.normal);
        }
    }
}

