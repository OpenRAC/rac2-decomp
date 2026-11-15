#include "common.h"

typedef int SpawnVectorWord __attribute__((mode(TI)));
/* One of the 30 slots of the level's attached-effect table, as in L00_003F87B0.c. */
typedef struct { int timer, first, second; float phase, damage; char *object; int owner, hold; } Slot;
typedef struct { u32 color[2]; } EffectPalette;

extern Slot D_L00_002533B0[30];
extern EffectPalette D_L00_001B0A48[];
extern void func_002AFFD8(char *, char *, int);
extern void func_00282D30(void *, void *, float);
extern void func_00282C88(SpawnVectorWord *);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern void func_002AF000(float *, float, float, float);
extern int func_002A7820(int, int);
extern char *func_002BDCE8(float, float, float, float, char *, int, char *, unsigned int, int);
extern int func_001163B0(void);
extern int func_00283CF0(float);
extern float func_00283CE0(int);

/* Scheduled by func_L00_003F87B0. Emits two randomized spark particles around the object of each
   occupied slot, tinted with one of the palette's two colours. */
void func_L00_003F9040(char *object)
{
    float reference[4];
    float position[4];
    float direction[4];
    EffectPalette palette;
    char *particle;
    char *owner;
    float magnitude;
    float angle;
    float elevation;
    int kind;
    int i;
    int j;
    int index;

    for (i = 0; i < 30; i++) {
        if (gHealthDrainSlots_L00[i].object != 0) {
            Slot *slot = &gHealthDrainSlots_L00[i];

            ComputeViewDirection(slot->object + 0x10, (char *)reference, 1);
            FastVecScale(reference, reference, *(float *)(slot->object + 0xC) * 0.0007812f);
            owner = slot->object;
            reference[0] += *(float *)(owner + 0) * 0.0009765f;
            reference[1] += *(float *)(owner + 4) * 0.0009765f;
            reference[2] += *(float *)(owner + 8) * 0.0009765f;
            for (j = 0; j < 2; j++) {
                ClearVector128((SpawnVectorWord *)direction);
                direction[2] = RandomFloatRange(0.016666668f, 0.025000002f);
                magnitude = RandomFloatRange(0.5f, 0.75f);
                magnitude = *(float *)(slot->object + 0xC) * (magnitude * 0.0009765f);
                angle = RandomAngle();
                elevation = RandomAngle();
                BuildSphericalOffset(position, magnitude, angle, elevation);
                owner = slot->object;
                position[0] += *(float *)(owner + 0) * 0.0009765f;
                position[1] += *(float *)(owner + 4) * 0.0009765f;
                position[2] += *(float *)(owner + 8) * 0.0009765f;
                kind = RandomIntRange(1, 5);
                particle = SpawnSpinningSparkParticle(0.0f, 1.0f, 1.01f,
                                         RandomFloatRange(0.25f, 1.0f) * 210000.0f,
                                         (char *)position, kind, (char *)direction, 0x5A182, 1);
                palette = D_L00_001B0A48[0];
                if (particle != 0) {
                    char *properties = particle + 0x20;

                    index = Rand() % 2;
                    particle[3] = palette.color[index];
                    *(u16 *)(particle + 10) = 35;
                    particle[9] = FloatToInt(4.0f) + 64;
                    *(float *)(properties + 0x1C) = IntToFloat(5);
                    *(int *)(properties + 4) = 3;
                    properties[0xA] = RandomIntRange(64, 128);
                    properties[0xB] = particle[10];
                }
            }
        }
    }
}
