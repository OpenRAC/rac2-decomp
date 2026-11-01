#include "include_asm.h"

#include "common.h"
typedef int MissileQuadword __attribute__((mode(TI)));
typedef union { MissileQuadword q; float f[4]; } PositionVector;
typedef struct { float progress[3]; u8 gap4C[4]; float rate[3]; } MissileTiming;
typedef struct {
    PositionVector point[4]; MissileTiming timing; u8 gap5C[12]; int sound;
} MissileState;
extern u8 D_00188660[];
typedef union { u8 b[0x2600]; f32 f[0x980]; } Hero;
extern Hero D_00189E20;
extern float D_L16_001B9B00[4] NOT_SDA;
extern int D_L16_001A8F00;
extern u8 *D_L16_001BFF58 NOT_SDA;
extern float D_L16_001B1648[3] __attribute__((sda));
extern float D_L16_001B1658[3] __attribute__((sda));
extern float D_L16_001B1664 __attribute__((sda));
extern int func_002E5CF8(int, int, void *);
extern void func_002E59F8(int), func_PAL_002A7E68(void *, int, int, int);
extern void func_002AA548(float *, float *, float, float, float, float);
extern void func_00282CF0(void *, void *, void *), func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float), func_00282F20(void *, void *, float);
extern float func_00283248(float, float), func_002A78D8(float, float), func_002A7878(float, float);
extern void func_002AA800(float *, int, float, float), func_PAL_L16_00412C28(u8 *);
extern void *func_002A9640(void *, int, int);
extern u8 *func_PAL_002735D0(void *, int, int, int, void *, void *, void *, int, float, float);
extern void *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern void func_0029F338(void *), func_002A7750(void *, int, int);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00277258(void *, int, void *, float);
extern void func_PAL_0032F3B8(void *, void *, void *, float);
extern int func_002A8C28(void *, void *, float, int, int, float, float, int, int);

/* The sound handle indexes 0x70-byte resident records. The sound owner and
 * active byte are checked before stopping a handle that may have been reused. */
void func_PAL_L16_004124A0(u8 *moby)
{
    MissileState *state = *(MissileState **)(moby + 0x68);
    float oldPosition[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    int handle, i;
    MissileTiming *timing;
    float *rate;
    PositionVector *segmentEnd;
    switch (moby[0x20]) {
    case 0: {
        u8 *rec = D_00188660 + state->sound * 0x70;
        if (*(u8 **)(rec + 0x88) != moby || !rec[0x74])
            state->sound = func_002E5CF8(0, 4, moby);
        qcopy(oldPosition, (moby + 0x10));
        qcopy((moby + 0x10), &state->point[0]);
        timing = &state->timing;
        rate = state->timing.rate;
        segmentEnd = &state->point[1];
        for (i = 0; i < 3; i++) {
            if (i == 0 || timing->progress[i-1] > D_L16_001B1664) {
                func_002AA548(&timing->progress[i],
                    &rate[i], 1.0f,
                    D_L16_001B1648[i] * 0.00040000002f,
                    D_L16_001B1648[i] * 0.00040000002f,
                    D_L16_001B1658[i] * 0.020000001f);
                if (i == 2 && state->timing.progress[1] > 0.95f && moby[0x43])
                    func_PAL_002A7E68(moby, 0, 0, 17);
            }
            func_00282CF0(delta, &segmentEnd[i], &state->point[i]);
            func_00282D30(delta, delta, timing->progress[i]);
            func_00282CC0(moby + 0x10, moby + 0x10, delta);
        }
        func_002AA800((float *)(moby + 0xf8), 0,
            func_00283248(D_00189E20.f[0x80 / 4] - *(float *)(moby + 0x10),
                D_00189E20.f[0x84 / 4] - *(float *)(moby + 0x14)), 0.25132746f);
        func_PAL_L16_00412C28(moby);
        if (func_002A9640(moby, 0x10000, 0) || D_L16_001A8F00 == 2) {
            func_002E5CF8(2, 0, moby);
            handle = state->sound;
            if (handle != -1) {
                u8 *rec = D_00188660 + handle * 0x70;
                if (*(u8 **)(rec + 0x88) == moby && rec[0x74]) func_002E59F8(handle);
            }
            state->sound = -1;
            for (i = 0; i < 3; i++) {
                switch (i) {
                case 0: func_00282D30(velocity, moby + 0xd0, 0.18f); break;
                case 1: func_00282D30(velocity, moby + 0xd0, -0.18f); break;
                case 2: func_00282D30(velocity, moby + 0xe0, 0.120000005f); break;
                default: qzero(velocity); break;
                }
                func_PAL_002735D0(moby, 1, *(short *)(moby + 0xaa), i,
                    moby + 0x10, moby + 0xf0, velocity, 255, func_002A78D8(90.0f, 180.0f), func_002A7878(5.0f, 15.0f));
            }
            func_PAL_L00_003FB330(moby + 0x10, 0, 0, 0, 0, 20, 45, 1,
                1.0f, 20.0f, 1, 0, 0, 0);
            func_0029F338(moby);
        } else {
            if (state->timing.progress[2] >= 1.0f) func_002A7750(moby, 1, -1);
            if (func_002761F8(oldPosition, moby + 0x10, 0, moby, 0)) {
                if (D_L16_001BFF58 &&
                    (*(short *)(D_L16_001BFF58 + 0xaa) == 0xf78 ||
                     *(short *)(D_L16_001BFF58 + 0xaa) == 0x7e8)) return;
            } else {
                if (!(state->timing.progress[1] >= 0.9f)) return;
                if (!func_00277258(moby + 0x10, 0, moby, 1.5f)) return;
            }
            func_002A7750(moby, 1, -1);
        }
        break;
    }
    case 1: {
        u8 *rec;
        handle = state->sound;
        if (handle != -1) {
            rec = D_00188660 + handle * 0x70;
            if (*(u8 **)(rec + 0x88) == moby && rec[0x74]) func_002E59F8(handle);
        }
        state->sound = -1;
        func_002E5CF8(1, 0, moby);
        func_00282CF0(oldPosition, D_L16_001B9B00, moby + 0x10);
        func_00282F20(oldPosition, oldPosition, 1.0f);
        func_PAL_0032F3B8(moby, moby + 0x10, oldPosition, 0.0f);
        func_002A8C28(moby, moby + 0x10, 2.0f, 0x10001, 0, 5.0f, 1.0f, 1, 0);
        func_0029F338(moby);
        break;
    }
    }
}
