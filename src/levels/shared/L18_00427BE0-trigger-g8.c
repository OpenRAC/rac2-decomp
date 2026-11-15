#include "common.h"
typedef struct { float v[4]; } TriggerPoint __attribute__((aligned(16)));
typedef u8 TriggerActor[0x100];
extern TriggerActor *D_L18_001B281C __attribute__((sda));
extern u8 D_00189E20[], D_00189EA0[], D_0019B4A8[], D_0019B2E8[];
typedef struct { u8 p[0x464]; u8 x[1]; } Hist;
extern u8 D_L18_0021E7B0[];
extern int D_001A79F0;
extern float func_00283B98(float, float), func_00282E80(void *, void *), func_00283198(float);
extern int func_00283CF0(float);
extern void func_0029FCC0(void *, int, void *), func_002A0430(int), func_L00_003294F0(void *, int);
extern void func_L18_002CFF48(int), func_L02_0031F858(int, int), func_002A8598(int, int);
extern void func_002DF3F8(void *, void *);
extern int func_002E5DA0(int, int, void *, int);

/* Activate the tagged linkage when the hero touches this rotating trigger. */
/* Per-frame update for moby class 3792 (a rotating trigger): it turns, glows, and switches on its linked objects when touched. */
void func_L18_0042B008(u8 *object)
{
    TriggerPoint point;
    u8 *state = *(u8 **)(object + 0x68);
    int touched, value;
    float distance;
    unsigned short id;
    u8 *counter; u8 *hero0;
    if (!state) return;
    *(float *)(state + 4) = FastAddRotations(*(float *)(state + 4), 0.10471977293491364f);
    if (object[0x20] == 0) {
        TransformMobyJointToWorld(object, 0, &point);
        touched = 0;
        distance = vec_distance_xy(gHeroState + 0x80, &point);
        state[8] = 0;
        hero0 = gHeroState;
        if (*(u8 **)(hero0 + 0x33C) == object && *(int *)(hero0 + 0x340) &&
            distance < (*(float *)(object + 0x2C) * 0.5f) / *(float *)(*(u8 **)(object + 0x24) + 0x24)) {
            touched = 1;
            if (!state[0x10]) {
                unsigned short id2 = *(u16 *)(object + 0xB2);
                if (id2 & 1) {
                    u8 *h = &D_0019B4A8[((short)id2 >> 1) + (gCurrentMapIndex << 10)];
                    if (((*h >> 4) & 7) != 7) *h += 16;
                } else {
                    u8 *h = &D_0019B4A8[((short)id2 >> 1) + (gCurrentMapIndex << 10)];
                    if ((*h & 7) != 7) (*h)++;
                }
            }
            if (state[0x12]) MarkTableEntryFlagged(object[0xB0]);
        }
        if (object[0xB0] != 255 && !state[0x11]) {
            id = *(u16 *)(object + 0xB2);
            if (((Hist *)D_L18_0021E7B0)->x[(short)id]) goto activate;
            { int n = D_0019B4A8[((short)id >> 1) + (gCurrentMapIndex << 10)];
            if (id & 1) { if ((n >> 4) & 7) goto activate; }
            else if (n & 7) goto activate; }
        }
        if ((state[0x13] && (D_0019B2E8[object[0xB0] + (gCurrentMapIndex << 4)] & 0x80)) || touched) {
activate:
            object[0x20] = 1;
            object[0xBC] = 1;
            if (*(int *)state != -1) SetObjectFlagBit(gMobyTable_L18[*(int *)state], 1);
            if (state[9]) DetachHeroFromObject(0);
            if (*(int *)(state + 0xC) != -1) {
                if (state[0xB]) SetGroupObjectsEnabled(*(int *)(state + 0xC), state[0xB]);
                if (state[0xA] != 255) SetByteOnGroupMobys(*(int *)(state + 0xC), state[0xA]);
            }
            if (state[0x12] && touched) {
                if (gHeroState[0x22B4]) {
                    u8 saved = gHeroState[0x22B4];
                    u8 *hero = *(u8 **)(gHeroState + 0xC18);
                    u8 *previous = *(u8 **)(gHeroState + 0x2290);
                    gHeroState[0x22B4] = 0;
                    *(u8 **)(gHeroState + 0x2290) = hero;
                    CaptureCheckpointState(hero + 0x10, hero + 0xF0);
                    gHeroState[0x22B4] = saved;
                    *(u8 **)(gHeroState + 0x2290) = previous;
                } else CaptureCheckpointState(gHeroState + 0x80, gHeroState + 0x90);
            }
        }
        value = FloatToInt((FastSinOrCosB(*(float *)(state + 4)) * 4.0f - 3.0f) * 128.0f);
        if (value > 128) value = 128;
        else if (value < 32) value = 32;
        { u32 color = ((u32)value << 8) | 0x80000000U;
        *(u32 *)(object + 0x78) = (((u32)value << 16) | color) | value; }
    } else {
        if (!state[8]) {
            PlaySoundFromClassBank(0, 0, object, 0x8A1);
            state[8] = 1;
        }
        *(u32 *)(object + 0x78) = 0x80208010;
    }
}
