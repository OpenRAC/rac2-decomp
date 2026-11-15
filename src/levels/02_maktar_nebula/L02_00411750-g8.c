/* The incomplete SDA array keeps the particle vector address together;
 * -frac2-hazard-labels retains the visibility join on its required hazard nop.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 quad; float f[4]; s32 i[4]; } ControllerScratch;
extern u8 *D_L02_001B359C;
extern u8 *D_L02_001B368C;
extern u8 D_L02_001BA500[];
extern u8 D_0019B2E8[];
extern s32 D_001A79F0 __attribute__((sda));
typedef union { u8 b[0x2400]; u8 *ptr[0x900]; void *v[0x900]; TI128 q[0x240]; } Hero;
extern Hero D_00189E20;
extern TI128 D_L02_001C0960;
extern float D_L02_001A8F20[] __attribute__((sda));
extern void func_L02_0031F858(s32, s32);
extern float func_002A7940(void);
extern float func_00282E80(void *, void *);
extern void func_002A7750(u8 *, u8, s32);
extern s32 func_L02_004127F8(u8 *);
extern float func_002AA2E8(float *, float, float);
extern void func_0029F338(void *);
extern void func_002A0430(u32);
extern void func_002DF3F8(void *, void *);
extern s32 func_002761F8(void *, void *, s32, void *, s32);
extern float func_002A7878(float, float);
extern s32 func_002A7820(s32, s32);
extern s32 func_002A77E0(s32);
extern void *func_002C3150(void *, void *, u32, s32, s32, s32, float);
extern void func_00282D60(float *, u8 *, float);
extern s32 func_00283DB8(float *, float);
extern float func_00283B98(float, float);
extern void func_L00_002E6CF0(void *, void *);
extern void func_L02_00411D18(u8 *);

/* Track the four linked actors and fade the controller's visible effect. */
/* Update handler of moby class 3201: it removes itself and its four partners once they are all gone. */
void func_L02_00411750(u8 *object)
{
    ControllerScratch scratch[2];
    u8 *state = *(u8 **)(object + 0x68);
    s32 *ids;
    float *phase;

    switch (object[0x20]) {
    case 0:
        {
        s32 i;
        if (D_0019B2E8[object[0xB0] + (gCurrentMapIndex << 4)] & 0x80) {
            SetGroupObjectsEnabled(*(s32 *)(state + 0x10), 1);
            MarkMobySpawned(object);
            return;
        }
        *(float *)(state + 0x1C) = 1.0f;
        *(float *)(state + 0x2C) = RandomAngle();
        *(s32 *)(state + 0x20) = 0;
        *(float *)(state + 0x24) = 0.5f;
        {
        float visible = vec_distance_xy(gCameraPosition_L02, object + 0x10) > 66.0f ? 0.0f : 1.0f;
        *(float *)(state + 0x1C) = visible;
        }
        i = 3;
        phase = (float *)(state + 0x3C);
        do { *phase-- = 1.0f; } while (--i >= 0);
        object[0x30] = 0x65;
        SetMobyState(object, 1, -1);
        object[0x31] = 0;
        *(u16 *)(object + 0x34) |= 1;
        break;
        }
    case 1:
        {
            s32 ready = 1;
            s32 i;
            for (i = 0, ids = (s32 *)state; i < 4; i++) {
                if (!IsMobyInStateTwo(gMobyPool_L02 + (*ids << 8))) {
                    ready = 0;
                    break;
                }
                ids++;
            }
            if (ready)
                SetMobyState(object, 2, -1);
        }
        break;
    case 2:
        ApproachValue((float *)(state + 0x1C), 0.0f, 0.016666668f);
        if (*(float *)(state + 0x1C) <= 0.0f) {
            s32 i;
            ids = (s32 *)state;
            i = 3;
            do { MarkMobySpawned(gMobyPool_L02 + (*ids++ << 8)); } while (--i >= 0);
            SetGroupObjectsEnabled(*(s32 *)(state + 0x10), 1);
            MarkTableEntryFlagged(object[0xB0]);
            {
                u8 *record = D_L02_001B368C + (*(s32 *)(state + 0x14) << 7);
                CaptureCheckpointState(record + 0x30, record + 0x70);
            }
            MarkMobySpawned(object);
            return;
        }
        break;
    }
    if (*(float *)(state + 0x1C) != 0.0f) {
        if (gHeroState.ptr[0x270 / 4] == object || gHeroState.ptr[0x26C / 4] == object) {
            scratch[0].quad = gHeroState.q[0xE0 / 16];
            scratch[0].f[0] = *(float *)(object + 0x10);
            if (CollLine(&gHeroState.q[0xE0 / 16], scratch[0].f, 2, gHeroState.v[0x2290 / 4], 0)) {
                s32 lifetime;
                s32 shade;
                scratch[1].quad = D_L02_001C0960;
                scratch[1].f[2] += RandomFloatRange(-0.5f, 0.5f);
                lifetime = (u8)RandomIntRange(30, 60);
                shade = (u8)RandomIntBelow(255);
                SpawnHeroRelativeParticle(scratch[1].f, D_L02_001A8F20, 0x60106070, lifetime, shade, 0, 1.0f);
            }
        }
        scale_vector(scratch[0].f, object, 0.0009765625f);
        if (FastMathHelperA(scratch[0].f, 80.0f) != -1) {
            *(float *)(state + 0x2C) = FastAddRotations(*(float *)(state + 0x2C), 0.040724356f);
            *(float *)(state + 0x28) += 0.020833334f;
            if (*(float *)(state + 0x28) > 1.0f)
                *(float *)(state + 0x28) -= 1.0f;
            {
            s32 i;
            phase = (float *)(state + 0x20);
            i = 1;
            do {
                *phase += 0.011100001f;
                if (*phase > 1.0f)
                    *phase -= 1.0f;
                phase++;
            } while (--i >= 0);
            }
            AddDrawCallbackToList1(DrawEnergyGateEffect, object);
        }
        if (vec_distance_xy(object + 0x10, gCameraPosition_L02) > 68.0f)
            ApproachValue((float *)(state + 0x1C), 0.0f, 0.008333334f);
        else
            ApproachValue((float *)(state + 0x1C), 1.0f, 0.008333334f);
    } else if (*(float *)(state + 0x1C) < 1.0f && vec_distance_xy(object + 0x10, gCameraPosition_L02) < 64.0f)
        ApproachValue((float *)(state + 0x1C), 1.0f, 0.008333334f);

    {
    s32 *out = (s32 *)scratch;
    s32 i;
    ids = (s32 *)state;
    i = 3;
    do {
    *out = !IsMobyInStateTwo(gMobyPool_L02 + (*ids++ << 8));
    out++;
    } while (--i >= 0);
    }
    if (*(float *)(state + 0x34) != 0.0f && ((s32 *)scratch)[0] == 0 && ((s32 *)scratch)[1] == 0)
        *(float *)(state + 0x34) = 0.0f;
    if (*(float *)(state + 0x38) != 0.0f && ((s32 *)scratch)[2] == 0 && ((s32 *)scratch)[3] == 0)
        *(float *)(state + 0x38) = 0.0f;
    if (*(float *)(state + 0x30) != 0.0f && ((s32 *)scratch)[0] == 0)
        *(float *)(state + 0x30) = 0.0f;
    if (*(float *)(state + 0x3C) != 0.0f && ((s32 *)scratch)[3] == 0)
        *(float *)(state + 0x3C) = 0.0f;
}
