#include "include_asm.h"
#include "names.h"

typedef struct {
    char pad[0x50];
    float angle;
    char tail[0x8C];
} AngleRecord_262570;

typedef struct {
    char pad[0x760];
    char pad2[0xBF8 - 0x760];
    void *pBF8;
    char pad3[0x2294 - 0xBFC];
    int i2294;
    char pad4[0x24EC - 0x2298];
    short h24EC;
} Res_189E20;

extern unsigned char D_00139580[];
extern AngleRecord_262570 D_L00_00262570[];
extern Res_189E20 D_00189E20;
extern char D_L00_001B8FF0[];
extern void func_00282F20(void *, void *, float);
extern void func_L00_0032A1A8(void *, void *, void *, int, float);
extern void func_L00_003AA4C8(void *, void *, void *, void *);

/* Fires a weapon effect from the hero in the direction the hero is facing. */
void func_L00_003AB8B8(char *position, char *moby) {
    float velocity[4];
    float angle;
    AngleRecord_262570 *timing;
    Res_189E20 *hero;
    void *owner;

    timing = &gWeaponTable_L00[D_00139580[0]];
    angle = timing->angle * 0.01666666753590107f;
    if (gHeroState.i2294 == 0x1D) {
        vec_scale_to_length(velocity, D_L00_001B8FF0, angle);
    } else if (gHeroState.h24EC == 1) {
        vec_scale_to_length(velocity, moby + 0xD0, -angle);
    } else {
        vec_scale_to_length(velocity, (char *)&gHeroState + 0x760, angle);
    }
    hero = &gHeroState;
    owner = 0;
    if (hero->pBF8 != 0) {
        ComputeObjectToTargetVector(hero->pBF8, position, velocity, 0, angle);
        owner = hero->pBF8;
    }
    SpawnOwnedEffectMoby(position, velocity, moby, owner);
}


