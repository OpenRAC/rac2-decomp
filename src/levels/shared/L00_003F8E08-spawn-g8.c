#include "common.h"

typedef int SpawnVectorWord __attribute__((mode(TI)));
/* One of the 30 slots of the level's attached-effect table, as in L00_003F87B0.c. */
typedef struct { int timer, first, second; float phase, damage; char *object; int owner, hold; } Slot;
typedef struct { u32 color[2]; } EffectPalette;

extern Slot g_health_l00_drain_slots[30];
extern EffectPalette g_effect_palette_table[];
extern void cam_compute_view_direction(char *, char *, int);
extern void FastVecScale(void *, void *, float);
extern void vec_clear_128(SpawnVectorWord *);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(float *, float, float, float);
extern int math_random_int_range(int, int);
extern char *SpawnSpinningSparkParticle(float, float, float, float, char *, int, char *, unsigned int, int);
extern int func_001163B0(void);
extern int FloatToInt(float);
extern float IntToFloat(int);

/* Scheduled by func_L00_003F87B0. Emits two randomized spark particles around the object of each
   occupied slot, tinted with one of the palette's two colours. */
void SpawnHealthDrainSparks(char *object)
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
        if (g_health_l00_drain_slots[i].object != 0) {
            Slot *slot = &g_health_l00_drain_slots[i];

            cam_compute_view_direction(slot->object + 0x10, (char *)reference, 1);
            FastVecScale(reference, reference, *(float *)(slot->object + 0xC) * 0.0007812f);
            owner = slot->object;
            reference[0] += *(float *)(owner + 0) * 0.0009765f;
            reference[1] += *(float *)(owner + 4) * 0.0009765f;
            reference[2] += *(float *)(owner + 8) * 0.0009765f;
            for (j = 0; j < 2; j++) {
                vec_clear_128((SpawnVectorWord *)direction);
                direction[2] = math_random_float_range(0.016666668f, 0.025000002f);
                magnitude = math_random_float_range(0.5f, 0.75f);
                magnitude = *(float *)(slot->object + 0xC) * (magnitude * 0.0009765f);
                angle = math_random_angle();
                elevation = math_random_angle();
                vec_build_spherical_offset(position, magnitude, angle, elevation);
                owner = slot->object;
                position[0] += *(float *)(owner + 0) * 0.0009765f;
                position[1] += *(float *)(owner + 4) * 0.0009765f;
                position[2] += *(float *)(owner + 8) * 0.0009765f;
                kind = math_random_int_range(1, 5);
                particle = SpawnSpinningSparkParticle(0.0f, 1.0f, 1.01f,
                                         math_random_float_range(0.25f, 1.0f) * 210000.0f,
                                         (char *)position, kind, (char *)direction, 0x5A182, 1);
                palette = g_effect_palette_table[0];
                if (particle != 0) {
                    char *properties = particle + 0x20;

                    index = func_001163B0() % 2;
                    particle[3] = palette.color[index];
                    *(u16 *)(particle + 10) = 35;
                    particle[9] = FloatToInt(4.0f) + 64;
                    *(float *)(properties + 0x1C) = IntToFloat(5);
                    *(int *)(properties + 4) = 3;
                    properties[0xA] = math_random_int_range(64, 128);
                    properties[0xB] = particle[10];
                }
            }
        }
    }
}
