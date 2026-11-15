#include "common.h"

extern float func_00283B98(float, float);
extern float func_00283198(float);
extern float func_00282E80(void *, void *);
extern int func_00283CF0(float);
extern int func_002E5CF8(int, int, void *);
extern void func_002A7750(void *, int, int);
extern void func_0029FCC0(void *, int, void *);
extern void func_002E59F8(int);
extern void func_L00_003294F0(void *, int);
extern void func_002A0430(int);

typedef struct {
    char pad[0x80];
    float pos[4];
    char gap[0x2AC];
    void *owner;
    int active;
} PrisonHero;

extern PrisonHero D_00189E20;
extern unsigned char D_00188660[];
extern unsigned char *D_L14_001B259C __attribute__((sda));
/* The second read of the same pointer uses absolute addressing. */
extern unsigned char *D_L14_001B259C_1[] __attribute__((sda));
extern unsigned char D_001395E3 NOT_SDA;

/* Pulses a glowing marker with a looping sound. When the player reaches it, the sound stops and the linked objects are triggered. */
void func_L14_0042FB10(unsigned char *object)
{
    float pos[4];
    unsigned char *state = *(unsigned char **)(object + 0x68), *entry, *soundSlot;
    int glow, soundId;
    float distance;

    if (!state)
        return;
    *(float *)(state + 8) = FastAddRotations(*(float *)(state + 8), 0.10471977293491364f);
    glow = FloatToInt((FastSinOrCosB(*(float *)(state + 8)) * 4.0f - 3.0f) * 128.0f);
    if (glow > 128)
        glow = 128;
    else if (glow < 32)
        glow = 32;

    if (object[0x20] == 0) {
        *(unsigned short *)(object + 0x34) |= 16;
        SetMobyState(object, 1, -1);
        *(int *)(state + 0x14) = -1;
    } else if (object[0x20] == 1) {
        soundSlot = gSoundState + *(int *)(state + 0x14) * 112;
        if (*(void **)(soundSlot + 0x88) != object || !soundSlot[0x74])
            *(int *)(state + 0x14) = PlayMobySound(1, 4, object);
        TransformMobyJointToWorld(object, 0, pos);
        distance = vec_distance_xy(gHeroState.pos, pos);
        *(int *)(state + 0xC) = 0;
        if (gHeroState.owner == object && gHeroState.active && distance < 0.5f) {
            SetMobyState(object, 2, -1);
            soundId = *(int *)(state + 0x14);
            if (soundId != -1) {
                entry = gSoundState + soundId * 112;
                if (*(void **)(entry + 0x88) == object && entry[0x74])
                    StopSoundVoice(soundId);
            }
            *(int *)(state + 0x14) = -1;
            PlayMobySound(0, 0, object);
            PlayMobySound(2, 0, object);
            D_001395E3 = 1;
            if (*(int *)state != -1) {
                SetObjectFlagBit(gMobyPool_L14 + (*(int *)state << 8), 1);
                {
                    int child = *(int *)(state + 4);
                    unsigned char *base = D_L14_001B259C_1[0];
                    SetObjectFlagBit(base + (child << 8), 1);
                }
            }
            MarkTableEntryFlagged(*(int *)(state + 0x10));
        }
        *(unsigned int *)(object + 0x78) = glow | (int)0x80000000;
    } else if (object[0x20] == 2) {
        if (!*(int *)(state + 0xC))
            *(int *)(state + 0xC) = 1;
        {
            unsigned int green = (glow << 8) | 0x80000000;
            *(unsigned int *)(object + 0x78) = (glow << 16) | green;
        }
    }
}
