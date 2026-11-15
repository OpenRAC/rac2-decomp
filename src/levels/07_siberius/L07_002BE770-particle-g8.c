#include "include_asm.h"

#include "common.h"

typedef struct {
    float x, y, z, w;
} V;

/* Mixed address forms are deliberate: retail loads these with lui+lw (MACRO_ADDR),
 * a split %sideMax/%sideMin pair (nosda) or $gp (sda/SDATA). */
extern int D_001A79F0 MACRO_ADDR;
extern int D_L07_001B1E08 MACRO_ADDR;
extern int D_L07_001C9780 __attribute__((nosda));
extern char *D_L07_001AEC08 __attribute__((sda));
extern char *D_L07_001ADAAC MACRO_ADDR;
extern float D_L07_001AEC10[] SDATA(D_L07_001AEC10);
extern float D_L07_001AEC14[] MACRO_ADDR;
extern V D_L07_001B9200[];   /* hero position (hero + 0x140) */
extern float D_L07_001B90C0[]; /* hero */
extern V D_L07_001B2550 MACRO_ADDR;

extern void func_L07_00379020(void *);
extern void func_002A7750(void *, int, int);
extern void func_L02_0031E9E8(void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DF0(void *);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_002B3868(void *);
extern int func_L00_00329520(void *, int);
extern char *func_L07_00336860(void *, void *, int, int);

typedef struct {
    char pad00[0x20];
    unsigned char state;
    char pad21[0xF];
    unsigned char alpha;
    char pad31[3];
    unsigned short flags;
    char pad36[0x32];
    void *data;
} Object;

typedef struct {
    float speed;
    float fall;
    int enabled;
    float scale;
    int group;
    char pad14[0x1C];
    V axisA;
    V axisB;
    V origin;
    V previous;
} Data;

/* Makes snow fall around the hero, with a stronger burst when the hero moves fast or is in a snow zone. */
void func_L07_00378AE0(Object *obj) {
    V pos, vel, tmp, point;
    Data *data = (Data *)obj->data;
    int lastIndex, i, burstIndex;
    float sideMin, sideMax;
    V *heroPos;

    switch (obj->state) {
    case 0:
        obj->alpha = 255;
        obj->flags |= 0x100;
        if (gCurrentMapIndex == 7 && D_L07_001B1E08) {
            ScatterParticlesAroundCamera(obj);
            SetMobyState(obj, 1, -1);
        }
        data->speed = 1.5f;
        data->fall = 2.5f;
        data->enabled = 1;
        gSnowfallMoby = (char *)obj;
        break;
    case 1:
        if (gCurrentMapIndex == 7 && D_L07_001C9780 == 1) {
            SetMobyState(obj, 2, -1);
            break;
        }
        for (i = 0; i < RandomIntBelow(2); i++) {
            RandomPlanarOffset(&pos, 15.0f);
            pos.z += 7.0f;
            FastVecAdd(&pos, &pos, &D_L07_001B9200);
            FastVecScale(&tmp, &D_L07_001B9200[35], 4.0f);
            FastVecAdd(&pos, &tmp, &pos);
            RandomPlanarOffset(&vel, data->speed * (1.0f / 60.0f));
            vel.z = -(data->fall * (1.0f / 60.0f)) * RandomFloatRange(0.8f, 1.2f);
            if (!IsPointInsideRegion(&pos, data->group))
                SpawnSnowParticle(&pos, &vel, 0, 0);
        }
        FastVecScale(&point, &D_L07_001B9200[35], 4.0f);
        FastVecAdd(&tmp, &point, &D_L07_001B9200);
        FastVecSub(&D_L07_001B2550, &tmp, &data->previous);
        data->scale = FastVecLength(&D_L07_001B2550) * 4.0f;
        if (data->scale > 1.0f)
            data->scale = 1.0f;
        else if (data->scale < 0.0f)
            data->scale = 0.0f;
        FastVecScale(&D_L07_001B2550, &D_L07_001B2550, data->scale);
        qcopy_nc(&data->previous, &tmp);
        break;
    case 2:
        if (SetFirstPendingFlag(obj))
            D_L07_001B2550.z -= 60.0f;
        if (gCurrentMapIndex == 7 && D_L07_001C9780 != 1) {
            SetMobyState(obj, 1, -1);
            break;
        }
        if (!D_L07_001ADAAC)
            break;
        heroPos = D_L07_001B9200;
        lastIndex = *(short *)(D_L07_001ADAAC + 0xAA) - 0x11D9;
        sideMin = D_L07_001AEC10[lastIndex * 2];
        sideMax = D_L07_001AEC14[lastIndex * 2];
        for (burstIndex = 0; burstIndex < 6; burstIndex++) {
            FastVecScale(&tmp, &data->axisA, RandomFloatRange(-25.0f, 25.0f));
            FastVecAdd(&pos, &tmp, &data->origin);
            FastVecScale(&tmp, &data->axisB, RandomFloatRange(sideMin, sideMax));
            FastVecAdd(&pos, &tmp, &pos);
            FastVecAdd(&pos, &pos, heroPos);
            FastVecSub(&pos, &pos, D_L07_001ADAAC + 0x10);
            pos.z -= D_L07_001B90C0[0x148 / 4] - *(float *)(D_L07_001ADAAC + 0x18);
            RandomPlanarOffset(&vel, 1.0f / 24.0f);
            vel.z = data->fall * (RandomFloatRange(0.8f, 1.2f) * (-1.0f / 120.0f));
            SpawnSnowParticle(&pos, &vel, 1, 0);
        }
        FastVecSub(&D_L07_001B2550, heroPos, &data->previous);
        FastVecScale(&tmp, D_L07_001ADAAC + 0xC0, 1.0f);
        FastVecAdd(&D_L07_001B2550, &tmp, &D_L07_001B2550);
        qcopy_nc(&data->previous, heroPos);
        break;
    }
}
