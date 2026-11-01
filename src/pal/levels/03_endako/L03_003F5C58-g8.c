#include "include_asm.h"

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
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_L03_003F66D8(void *);
extern void *func_002A9640(void *, int, int);
extern float func_PAL_002AA108(void *, void *);
extern int func_002E5CF8(int, int, void *);
extern void func_PAL_002AC290(void *, void *);
extern void func_002AA2E8(void *, float, float);
extern void func_00283098(void *, void *, void *);
extern u8 *func_PAL_002735D0(void *, int, int, int, void *, void *, void *, int, float, float);
extern void func_PAL_003120C0(void);
extern void func_002B3BA8(void *, int, int, int, float, float);
extern void func_PAL_L03_003FB700(void *);
extern u8 *D_L03_001B2A1C[] __attribute__((sda));
extern u8 D_0019B2E8[] NOT_SDA;
extern int D_001A79F0[] __attribute__((sda));
extern u8 *D_L03_001FE700[] NOT_SDA;
extern float D_L03_001B1070 __attribute__((sda));

void func_PAL_L03_003F9DE0(u8 *entity) {
    DamageState *state = *(DamageState **)(entity + 0x68);
    u8 *hit, *effect;
    EntityPath *path;
    int index, count, part, i, bit;
    float amount;
    union { Quad q; float f[4]; } local;

    if (entity[0x20] == 0) {
        state->timer48 = func_00283CF0(30);
        state->timer4A = func_00283CF0(32);
        state->hitMode = 1;
        func_L00_003294F0(D_L03_001B2A1C[0] + (state->startRecord << 8), 1);
        if (D_0019B2E8[(entity[0xB0] & 0x7F) + (D_001A79F0[0] << 4)] & 0x80) {
            func_0029F338(entity);
            return;
        }
        state->difficulty = func_L00_002E3B38(entity[0xB0]);
        switch (state->difficulty) {
        case 2:
            state->maxHealth = func_00283CF0(state->maxHealth * 0.9f);
            break;
        case 1:
            state->maxHealth = func_00283CF0(state->maxHealth * 0.7f);
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
        func_002A7750(entity, 1, 0);
        if (entity[0x43]) {
            func_PAL_002A7E68(entity, 0, 0, 0);
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
        func_L00_003294F0(D_L03_001B2A1C[0] + (state->spawnRecord << 8), 1);
        func_L03_003F66D8(entity);
    }
    *(float *)(entity + 0x2C) = *(float *)(*(u8 **)(entity + 0x24) + 0x24) * D_L03_001B1070;

    hit = func_002A9640(entity, 0x10000, 0);
    if (hit && *(u8 **)(hit + 0x20) && *(s16 *)(*(u8 **)(hit + 0x20) + 0xAA) == 0x9DF) {
        hit = 0;
    }
    amount = func_PAL_002AA108(entity, hit);
    if (amount != 0 || state->hitMode == 2) {
        state->timer77 = 150;
        func_002E5CF8(1, 0, entity);
        func_PAL_002AC290(entity, state->hit70);
        if (entity[0x95]) {
            if (state->hitMode == 2) {
                state->health = 0;
            } else {
                func_002AA2E8(&state->health, 0, amount);
            }
            if (state->health == 0 && entity[0x20] != 14 && entity[0x20] != 15) {
                func_002A7750(entity, 14, 1);
            } else if (state->threshold > 0 && state->health < state->threshold) {
                for (part = 0; part < 2; part++) {
                    i = state->stage * 2 + part;
                    bit = 1 << i;
                    local.q = 0;
                    local.f[1] = 0.14000002f;
                    local.f[2] = 0.10000001f;
                    if (part) {
                        local.f[1] = -0.14000002f;
                    }
                    func_00283098(&local, &local, entity + 0xC0);
                    effect = func_PAL_002735D0(entity, 1, *(s16 *)(entity + 0xAA), i, entity + 0x10,
                                           entity + 0xF0, &local, 255, 30, 15);
                    *(void **)(effect + 0x64) = func_PAL_003120C0;
                    *(u16 *)(entity + 0x7C) &= ~bit;
                }
                state->stage++;
                func_002A7750(entity, 13, 6);
                state->threshold = (func_00283CF0(state->health * 4 / state->maxHealth) * state->maxHealth) * 0.25f;
            }
        } else if (entity[0x20] == 2) {
            func_002A7750(entity, 3, -1);
            state->routeIndex = *state->route - 1;
        }
    }
    if ((unsigned)(entity[0x20] - 6) < 8) {
        func_002B3BA8(entity, -1, 0, 0, 16, 8);
    }
    state->hitMode = 1;
    func_PAL_L03_003FB700(entity);
    entity[0xA8] = 255;
}
