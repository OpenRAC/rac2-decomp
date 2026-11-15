#include "include_asm.h"
#include "names.h"
typedef int Quadword __attribute__((mode(TI)));
typedef struct { char pad[23]; unsigned char selected; } Selection;
extern Selection D_00139568;
typedef struct { char pad[4]; unsigned char enabled; char body[111]; float scale; char tail[104]; } EffectConfig;
extern EffectConfig D_L00_00262570[];
extern void *D_0018C0B0;
extern void func_002AFFD8(void *, void *, int);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void func_00282F20(void *, void *, float);
extern void func_00277F48(void *, int, float, void *, void *);
extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern float func_002A78D8(float, float);
extern void func_002C2210(void *, int, float, float, int, int, int, void *, float, int);

/* Emits impact effects using the current selection's effect configuration. */
void func_L00_003A8238(char *object, void *point)
{
    float position[4];
    float normal[4];
    char query[48];
    char *state = *(char **)(object + 104);
    int i, effect, sign;
    *(Quadword *)position = *(Quadword *)point;
    if (gWeaponTable_L00[gItemSlotToRecord.selected].enabled) {
        ComputeViewDirection(position, normal, 1);
        SpawnExplosionEffects(object, normal, position, 0.0f, 0.0f, 10, 3, 16, 4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f, 1, 1, -1, 0, 0x810001);
        *(int *)(query + 20) = 0x810000;
        *(int *)(query + 32) = 1;
        *(char **)(query + 16) = object;
        *(float *)(query + 28) = gWeaponTable_L00[gItemSlotToRecord.selected].scale;
        *(Quadword *)query = *(Quadword *)state;
        vec_scale_to_length(query, query, 1.0f);
        *(float *)(query + 12) = 5627.925f;
        query[24] = 3;
        query[25] = 2;
        *(unsigned short *)(query + 26) = *(unsigned short *)(object + 170);
        ProcessCollisionHit(position, 1, 2.0f, gHeroMoby_0018C0B0, query);
    } else {
        int negative;
        char *spark;
        float *velocity;
        *(Quadword *)normal = 0;
        negative = -1;
        spark = query;
        velocity = normal;
        i = 7;
        do {
            effect = RandomIntRange(6, 16);
            sign = 1;
            if (RandomIntBelow(2))
                sign = negative;
            *(float *)(query + 0) = position[0] + RandomSignedFloatRange(0.0f, 0.5f);
            *(float *)(query + 4) = position[1] + RandomSignedFloatRange(0.0f, 0.5f);
            *(float *)(query + 8) = position[2] + RandomSignedFloatRange(0.0f, 0.5f);
            SpawnGroundEffectParticle(spark, effect, 10.0f, 0.1f, 0x4010ff10, 2, sign, velocity, 0.0f, 1);
            SpawnGroundEffectParticle(spark, effect, 2.0f, 0.1f, 0xc0ffffff, 2, sign, velocity, 0.0f, 1);
        } while (--i >= 0);
    }
}
