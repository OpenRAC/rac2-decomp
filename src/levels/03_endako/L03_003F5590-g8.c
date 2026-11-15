/* func_L03_003F5590 needs its own unit: -G8 for its $gp-relative scale and -frac2-zero-ti-por
 * (config/cflags.txt) for the local quadword clear, which retail keeps as `por` + `sq`.
 *
 * The first frame initialises the entity; then every frame takes the damage it was dealt. The
 * death test and the threshold test each read the health from memory: retail's `mov.s $f2,$f0`
 * is gcse's copy of the first load, which replaces the second one, and the two tests join after
 * the death test's arms, so cse cannot share the zero constant and it is loaded twice.
 */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef struct {
    u8 pad00[0x20];
    float health;
    s16 maxHealth;
    u8 pad26[2];
    u8 mode28;
    u8 pad29[0x2E - 0x29];
    u8 hitMode;
    u8 pad2F[0x48 - 0x2F];
    u8 timer48;
    u8 pad49;
    u8 timer4A;
    u8 pad4B[0x70 - 0x4B];
    u8 hit70[7];
    u8 timer77;
    u8 pad78[0x88 - 0x78];
    int path;
    u8 pad8C[0xA4 - 0x8C];
    int spawnRecord;
    int startRecord;
    u8 padAC[0x290 - 0xAC];
    Quad home;
    u8 pad2A0[0x2B0 - 0x2A0];
    Quad start;
    u8 pad2C0[0x2CC - 0x2C0];
    int *route;
    u8 pad2D0[0x2DC - 0x2D0];
    int routeIndex;
    u8 pad2E0[0x308 - 0x2E0];
    u8 stage;
    u8 pad309[2];
    u8 flag30B;
    u8 pad30C[0x314 - 0x30C];
    int entries[7];
    int active;
    float threshold;
    u8 pad338[0x3C2 - 0x338];
    s16 difficulty;
    u8 pad3C4[0x3CC - 0x3C4];
    int target;
} DamageState;
typedef struct { int count; u8 pad[0xC]; float point[1][4]; } EntityPath;
extern int func_00283CF0(float);
extern void func_L00_003294F0(void *, int);
extern void func_0029F338(void *);
extern int func_L00_002E3B38(int);
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern void func_L03_003F66D8(void *);
extern void *func_002A9640(void *, int, int);
extern float func_002A96A0(void *, void *);
extern int func_002E5CF8(int, int, void *);
extern void func_002AB800(void *, void *);
extern void func_002AA2E8(void *, float, float);
extern void func_00283098(void *, void *, void *);
extern u8 *func_00273730(void *, int, int, int, void *, void *, void *, int, float, float);
extern void func_00310C88(void);
extern void func_002B3BA8(void *, int, int, int, float, float);
extern void func_L03_003F6E88(void *);
/* Incomplete arrays: retail reaches these two with `lui` + `lw`, not through $gp. */
extern u8 *D_L03_001B2A1C[] __attribute__((sda));
extern u8 D_0019B2E8[] NOT_SDA;
extern int D_001A79F0[] __attribute__((sda));
extern u8 *D_L03_001FE700[] NOT_SDA;
extern float D_L03_001B1070 __attribute__((sda));

/* Sets up the boss on its first frame, then handles the damage it takes each frame:
 * it hurts, loses armor pieces at set health levels, and dies at zero health. */
void func_L03_003F5590(u8 *entity) {
    DamageState *state = *(DamageState **)(entity + 0x68);
    u8 *hit, *effect;
    EntityPath *path;
    int index, count, part, i, bit;
    float amount;
    union { Quad q; float f[4]; } local;

    if (entity[0x20] == 0) {
        state->timer48 = FloatToInt(30);
        state->timer4A = FloatToInt(32);
        state->hitMode = 1;
        SetObjectFlagBit(D_L03_001B2A1C[0] + (state->startRecord << 8), 1);
        if (D_0019B2E8[(entity[0xB0] & 0x7F) + (gCurrentMapIndex[0] << 4)] & 0x80) {
            MarkMobySpawned(entity);
            return;
        }
        state->difficulty = GetDifficultyScaledLevel(entity[0xB0]);
        switch (state->difficulty) {
        case 2:
            state->maxHealth = FloatToInt(state->maxHealth * 0.9f);
            break;
        case 1:
            state->maxHealth = FloatToInt(state->maxHealth * 0.7f);
            break;
        }
        state->target = -1;
        state->health = state->maxHealth;
        *(u16 *)(entity + 0x7C) = 0x3F;
        entity[0x30] = 255;
        *(u16 *)(entity + 0x32) += 0x40;
        state->mode28 = 3;
        state->threshold = state->health * 0.75f;
        qcopy(&state->home, entity + 0x10);
        qcopy(&state->start, entity + 0x10);
        *(int *)(entity + 0x98) = 0;
        *(u16 *)(entity + 0x34) = (*(u16 *)(entity + 0x34) | 0x41) & 0xEFFF;
        SetMobyState(entity, 1, 0);
        if (entity[0x43]) {
            StartAnimationBlended(entity, 0, 0, 0);
        }
        state->flag30B = 1;
        state->active = 1;
        path = (EntityPath *)D_L03_001FE700[state->path];
        for (index = 0, count = 0; index < path->count; index++) {
            if (path->point[index][3] >= 0) {
                state->entries[count] = index;
                count++;
                if (count >= 7) {
                    break;
                }
            }
        }
        SetObjectFlagBit(D_L03_001B2A1C[0] + (state->spawnRecord << 8), 1);
        ProcessBossGroupObjects(entity);
    }
    *(float *)(entity + 0x2C) = *(float *)(*(u8 **)(entity + 0x24) + 0x24) * D_L03_001B1070;

    hit = FindOwnedEffectSlot(entity, 0x10000, 0);
    if (hit && *(u8 **)(hit + 0x20) && *(s16 *)(*(u8 **)(hit + 0x20) + 0xAA) == 0x9DF /* moby class 2527 */) {
        hit = 0;
    }
    amount = UpdateAimTargetStrength(entity, hit);
    if (amount != 0 || state->hitMode == 2) {
        state->timer77 = 150;
        PlayMobySound(1, 0, entity);
        StartColorFade(entity, state->hit70);
        if (entity[0x95]) {
            if (state->hitMode == 2) {
                state->health = 0;
            } else {
                ApproachValue(&state->health, 0, amount);
            }
            if (state->health == 0 && entity[0x20] != 14 && entity[0x20] != 15) {
                SetMobyState(entity, 14, 1);
            } else if (state->threshold > 0 && state->health < state->threshold) {
                for (part = 0; part < 2; part++) {
                    i = state->stage * 2 + part;
                    bit = 1 << i;
                    local.q = 0;
                    local.f[1] = 0.116666675f;
                    local.f[2] = 0.083333336f;
                    if (part) {
                        local.f[1] = -0.116666675f;
                    }
                    matrix_mul_vec3(&local, &local, entity + 0xC0);
                    effect = CreateCameraMoby(entity, 1, *(s16 *)(entity + 0xAA), i, entity + 0x10,
                                           entity + 0xF0, &local, 255, 30, 15);
                    *(void **)(effect + 0x64) = UpdateFadeOutMoby;
                    *(u16 *)(entity + 0x7C) &= ~bit;
                }
                state->stage++;
                SetMobyState(entity, 13, 6);
                state->threshold = (FloatToInt(state->health * 4 / state->maxHealth) * state->maxHealth) * 0.25f;
            }
        } else if (entity[0x20] == 2) {
            SetMobyState(entity, 3, -1);
            state->routeIndex = *state->route - 1;
        }
    }
    if ((unsigned)(entity[0x20] - 6) < 8) {
        SelectAimTarget_002B3BA8(entity, -1, 0, 0, 16, 8);
    }
    state->hitMode = 1;
    PlayBossVoiceLines(entity);
    entity[0xA8] = 255;
}
