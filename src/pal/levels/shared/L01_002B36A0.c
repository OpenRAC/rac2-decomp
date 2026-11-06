#include "include_asm.h"


#include "common.h"
extern u8 D_00189E20[];
extern float func_00282E80(void *, void *);
extern float func_002AA2E8(float *, float, float);
extern float func_002AA3A8(float *, float *, float, float, float, float);

/* func_PAL_L01_002B3C40, the PAL copy of func_L01_002B3D28: the same C with the step and rates at 50 Hz. */
void func_PAL_L01_002B3C40(void) {
    int a3;
    int v1;
    float r;

    if (D_00189E20[0x22B4] == 0) {
        *(float *)(D_00189E20 + 0x258) = 0.8f;
        *(float *)(D_00189E20 + 0x25C) = 0.7f;
        *(float *)(D_00189E20 + 0x260) = 0.45f;
    }

    a3 = *(int *)(D_00189E20 + 0x229C);
    if (a3 == 4) {
        if (*(short *)(D_00189E20 + 0x4AC) < *(int *)(D_00189E20 + 0x1B8)) {
            if (D_00189E20[0x49E] == 0) {
                *(float *)(D_00189E20 + 0x25C) = *(float *)(D_00189E20 + 0x4B8);
            }
        }
    } else {
        v1 = *(int *)(D_00189E20 + 0x2294);
        if (v1 == 6) {
            *(float *)(D_00189E20 + 0x25C) = 0.5f;
        } else if (v1 == 4) {
            *(float *)(D_00189E20 + 0x258) = 0.35000002384185791f;
        } else if (v1 == 0x7C) {
            *(float *)(D_00189E20 + 0x260) = 0.8f;
        }
    }

    if (D_00189E20[0x287] == 0)
        goto slow;
    if (*(int *)(D_00189E20 + 0x22A4) == 0x12)
        goto slow;
    if (*(int *)(D_00189E20 + 0x22B0) == 0x12)
        goto slow;
    if (D_00189E20[0x22B4] == 0) {
        if (*(float *)(D_00189E20 + 0x254) < 0.53f)
            goto slow;
    }
    if (*(int *)(D_00189E20 + 0x229C) == 0x11)
        goto slow;
    if (D_00189E20[0x1494] != 0)
        goto slow;

    r = func_00282E80(D_00189E20 + 0x240, D_00189E20 + 0x80);
    if (r > *(float *)(D_00189E20 + 0x264) * 0.5f)
        goto slow;
    return;

slow:
    {
        /* The channel block sits 0x250 into the runtime block; the block pointer
           is taken first and the runtime block is reached back from it. */
        u8 *p = D_00189E20 + 0x250;
        u8 *s = p - 0x250;
        float step = 0.024f;
        func_002AA2E8((float *)p, *(float *)(s + 0x258), step);
        func_002AA2E8((float *)(p + 4), *(float *)(s + 0x25C), step);
        func_002AA3A8(
            (float *)(p + 0x14),
            (float *)(p + 0x18),
            *(float *)(s + 0x260),
            0.028800001f,
            0.43200004f,
            0.080000006f);
    }
}

typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; u8 *ptr[0x980]; } MovementHero;
extern u8 D_00189E20[];
extern float D_001A7DB0[] MACRO_ADDR;
extern void func_L00_002B39F0(int, float);

void func_PAL_L01_002B45C8(void)
{
    func_L00_002B39F0(0, 1.0f);
    if (0.0f < ((MovementHero *)D_00189E20)->f[0x1b0 / 4])
        ((MovementHero *)D_00189E20)->f[0x1b0 / 4] = D_001A7DB0[4] * (((MovementHero *)D_00189E20)->f[0x24b8 / 4] * 0.020000001f);
}


extern float func_00282DB0(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern char D_L01_00189E20[];
extern char D_L01_00189E20[];
typedef struct { char prefix[0x2290]; void *moby; } ProbeHero;
typedef struct { char pad[0x18]; void *moby; int count; char gap[0x20]; float normal[4]; } ProbeResult;
extern ProbeResult D_L01_001BF900;
extern char D_L01_00189F10[];
extern int D_L01_001BF91C;
extern float func_L00_002D3A58(void *);
extern void func_L00_002D36E0(void *, float, float, float, int);
extern float func_00282E20(void *);
extern void func_L00_002D3B58(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00278E78(void);
extern float func_L00_002D3EA8(void *);

/* func_L01_002B3788 is defined in L01_002B3788-contact.c. */

/* func_L01_002B3D28 is defined in L01_002B3D28.c. */



/* Stops the hero against a wall: casts two rays along the movement direction (or the vector at
   the start of the hero's data when forced or nearly still), keeps the moby it hit and takes the
   velocity component into the wall's flattened normal away. */
void func_PAL_L01_002B4CC8(int force)
{
    float origin[4] __attribute__((aligned(16)));
    float endpoint[4] __attribute__((aligned(16)));
    float lowOrigin[4] __attribute__((aligned(16)));
    float farEndpoint[4] __attribute__((aligned(16)));
    float height, radius, slope;
    int material;
    char *base;
    char *velocity = D_L01_00189F10;

    if (func_L00_002D3A58(velocity) < 0.002f)
        return;
    base = velocity - 0xF0;
    height = 0.37f;
    radius = 0.5f;
    if ((unsigned)(*(int *)(base + 0x229C) - 17) < 2) {
        height = 0;
        radius = 0.7f;
    }
    func_L00_002D36E0(origin, 0, 0, height, 1);
    func_L00_002D36E0(lowOrigin, 0, 0, height * 0.3f, 1);
    if (force || func_00282E20(velocity) < 0.01f) {
        func_00282F20(endpoint, base, radius);
        func_00282F20(farEndpoint, base, radius * 1.4f);
    } else {
        func_L00_002D3B58(endpoint, velocity, 0);
        func_00282F20(endpoint, endpoint, radius);
        func_00282D30(farEndpoint, endpoint, 1.4f);
    }
    func_00282CC0(endpoint, endpoint, origin);
    material = -1;
    func_00282CC0(farEndpoint, farEndpoint, lowOrigin);
    {
        char *hero = D_L01_00189E20;

        if (func_002761F8(lowOrigin, farEndpoint, 2, ((ProbeHero *)hero)->moby, 0) && D_L01_001BF91C > 0)
            material = func_00278E78();
    }
    slope = 0;
    {
        char *hero = D_L01_00189E20;

        if (func_002761F8(origin, endpoint, 2, ((ProbeHero *)hero)->moby, 0) && D_L01_001BF900.count > 0)
            slope = func_L00_002D3EA8(D_L01_001BF900.normal);
    }
    if (slope >= 0.8726647f || material == 8 || material == 12) {
        float dot;
        char *hero = D_L01_00189E20;

        *(void **)(hero + 0x270) = D_L01_001BF900.moby;
        func_L00_002D3B58(D_L01_001BF900.normal, D_L01_001BF900.normal, 0);
        func_00282F20(D_L01_001BF900.normal, D_L01_001BF900.normal, 1);
        dot = func_00282DB0(D_L01_001BF900.normal, hero + 0xF0);
        if (dot < 0) {
            func_00282D30(D_L01_001BF900.normal, D_L01_001BF900.normal, -dot);
            func_00282CC0(hero + 0xF0, hero + 0xF0, D_L01_001BF900.normal);
        }
    }
}

