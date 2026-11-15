#include "common.h"

/* Measured prefixes of the hit packet, material entry and selector. */
typedef struct {
    char prefix[24];
    unsigned char field_18, field_19;
    unsigned short id;
    char tail[20];
} EffectHitPacket;

typedef struct {
    char prefix[0x70];
    float scale;
    char tail[0x6C];
} EffectMaterialEntry;

typedef struct { int x, y, z; } EffectAngles;

/* The effect object and the state block it points to; only the fields used here. */
typedef struct {
    char pad00[0x34];
    int timer;
    char pad38[0x4C - 0x38];
    float intensity;
    int f50;
    int f54;
    int f58;
    int light_index;
} EffectState;

typedef struct {
    char pad00[0x10];
    float position[4];
    unsigned char phase;
    char pad21[0x68 - 0x21];
    EffectState *state;
    char pad6C[0xAA - 0x6C];
    unsigned short id;
    char padAC[0xB8 - 0xAC];
    int f_B8;
    char padBC[0xC0 - 0xBC];
    float f_C0[4];
} EffectObject;
typedef struct {
    unsigned char prefix[0x1C];
    unsigned char index;
} EffectMaterialSelector;

extern EffectAngles D_L00_001AFDA8;
extern EffectMaterialSelector D_00139568;
extern EffectMaterialEntry D_L00_00262570[];
extern int D_L00_001AFDA0 __attribute__((sda));
extern char *func_L00_003BB1F8(EffectObject *);
extern void func_00282F20(void *, void *, float);
extern void func_002A8C00(void *, void *, int, float, void *);

extern void func_002A8E20(void *, void *);
extern void func_0032D758(void *, int, int);
/* The integer and FP register banks retain their own argument order. */
extern void func_002AF580(void *, float, void *, float, float, float, void *,
                          void *, int, int, float, int, void *);
extern int func_L00_0037DD80(void *, void *);
extern void func_L00_0037DD18(void *, void *, int);
extern void func_L00_003BB8B8(void *, void *, int);
extern int func_002E5CF8(int, int, void *);
extern int func_00282948(void *);
extern float func_00283CE0(int);
extern float func_002A7878(float, float);
extern void func_00282C88(void *);
extern void func_002C2210(void *, float, float, int, unsigned int, int, int,
                          void *, float, int);
extern void func_002FE8D8(void *, void *);
extern void func_L00_003BD510(void *, void *, int, int);
extern void func_002FEE50(int);
extern void func_L00_0037E0C0(void *);
extern void func_00291450(int);
extern void func_0029F338(void *);
extern void func_L00_003BBB68(void *);
extern void func_L00_003BCC10(void *);
extern void ref_L00_003BAC30_00(void *, EffectObject *);
extern void func_L00_003BB668(void *);

/* Updates motion and hits, then shrinks, emits particles and releases resources. */
/* Per-frame update of the moby class 2473 effect: it hurts and pushes nearby things, fades out,
   then removes itself. */
void func_L00_003BAC30(EffectObject *self)
{
    EffectAngles angles;
    char *hits[16];
    char vector[16];
    EffectHitPacket packet;
    int hitCount;
    EffectState *state = self->state;
    char *hitTarget;
    int i;
    int lightHandle;
    int classIndex;
    EffectMaterialEntry *classEntry;
    float scale;
    float ratio;

    angles = D_L00_001AFDA8;
    switch (self->phase) {
    case 0:
    case 1:
        state->intensity += (0.6f - state->intensity) * 0.125f;
        hitTarget = MoveSparkProjectile(self);
        if (hitTarget) {
            qcopy(vector, state);
            vec_scale_to_length(vector, vector, 0.033333335f);
            classIndex = gItemSlotToRecord.index;
            classEntry = gWeaponTable_L00 + classIndex;
            scale = classEntry->scale;
            make_hit_descriptor(&packet, self, 0x210000, scale, vector);
            packet.field_18 = 1;
            packet.field_19 = 3;
            packet.id = self->id;
            QueueMobyImpact(hitTarget, &packet);
            StartAttachedEffect(hitTarget, 0x3E, self->f_B8);
        }
        SelectBestTargetInCone(self->position, 6.2831855f, self->f_C0, 6.2831855f, 15.0f, 0.0f,
                      &hitCount, hits, 15, 0, 0.0f, 0, &angles);
        for (i = 0; i < hitCount; i++) {
            if (state->f54 < 15 && IsOwnerKeyPairFree(self, hits[i])) {
                KeyOwnerTableInsert(self, hits[i], 120);
                SpawnOrbitingSparkRecord(self, hits[i], 10);
                PlayMobySound(0, 0, self);
            }
        }
        if (FastFloatHelperD(&state->timer)) {
            self->phase = 2;
            state->timer = 40;
        }
        break;
    case 2:
        MoveSparkProjectile(self);
        ratio = IntToFloat(state->timer) / IntToFloat(40);
        state->intensity = ratio * 0.5900000333786011f + 0.01f;
        self->position[0] += RandomFloatRange(-0.1f, 0.1f);
        self->position[1] += RandomFloatRange(-0.1f, 0.1f);
        self->position[2] += RandomFloatRange(-0.1f, 0.1f);
        ClearVector128(vector);
        SpawnGroundEffectParticle(self->position, 0.15f, 1.5f, 60, 0x4FFF0000, 0, 2, vector, 0.0013888889225199819f, 1);
        SpawnGroundEffectParticle(self->position, 0.125f, 1.25f, 60, 0x7FFFFFFF, 0, 2, vector, 0.0013888889225199819f, 1);
        if (FastFloatHelperD(&state->timer))
            self->phase = 3;
        break;
    case 3:
        if (state->f54 == 0 && state->f58 == 0) {
            GetObjectFacingDirection(self->position, &packet);
            SpawnSparkBurst_L00_3(self->position, &packet, 6, 0x72FF);
            SpawnSparkBurst_L00_3(self->position, &packet, 6, 0xFF0000);
            ClearEntryFlag(state->f50);
            ClearOwnerKeyEntries(self);
            lightHandle = state->light_index;
            D_L00_001AFDA0--;
            if (lightHandle != -1)
                FreePointLight(lightHandle);
            MarkMobySpawned(self);
            return;
        }
        break;
    }
    UpdateEffectSparkSlots(self);
    UpdateOrbitSparks(self);
    ref_L00_003BAC30_00(DrawSparkProjectile, self);
}
