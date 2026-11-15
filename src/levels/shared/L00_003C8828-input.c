#include "common.h"

#define FIELD(p, type, offset) (*(type *)((char *)(p) + (offset)))

typedef struct {
    char pad0000[0x1230];
    int input;
    char pad1234[0x1060];
    int state;
    char pad2298[0x24];
    unsigned char flag;
    char pad22BD[0x277];
    int timer;
} HeroInputState;

typedef struct {
    float v[4];
} InputVector __attribute__((aligned(16)));

extern HeroInputState D_00189E20;
extern int D_00138324;
extern void func_0029FCC0(void *, int, void *);
extern void func_002FDF40(void *, void *, int, int, float, float, float, float);
extern int func_002FE5A0(void *, void *, void *, void *, void *, int, int, float);
extern int func_00282948(void *);
extern int func_L00_002D3F30(int, int);
extern void func_L00_002AF568(void);
extern int func_002E5CF8(int, int, void *);
extern void func_L00_0038A748(void *, void *, void *);
extern void func_L00_002AF7D0(void);
extern void ref_L00_003C8828_00(void (*)(void *), void *);
extern void func_L00_003C8A58(void *);

/* Per-frame update of the Megaturret Glove weapon (moby class 2661). It aims, waits for the fire button, then after a short delay launches the turret and cools down. */
void func_L00_003C8828(char *owner)
{
    InputVector origin, target;
    InputVector *targetVector;
    char *context = FIELD(owner, char *, 0x68);
    int allowed;
    float radius;

    TransformMobyJointToWorld(owner, 0, &origin);
    targetVector = &target;
    radius = gHeroState.state == 29 ? 11.0f : 4.5f;
    CalculateAimedLaunchVelocity(targetVector, &origin, 0, 0, 1.5f, radius, 0.25f, 0.0030555557f);
    allowed = 1;
    FIELD(context, int, 0x24) = TraceProjectileToImpact(&origin, targetVector, context,
        context + 0x10, owner, 0, 0, 0.0030555557f);

    if (gHeroState.state == 29) {
        if (!FastFloatHelperD(&gHeroState.timer))
            allowed = 0;
    } else {
        gHeroState.timer = 40;
    }

    switch (FIELD(owner, unsigned char, 0x20)) {
    case 0:
        FIELD(owner, unsigned char, 0x20) = 1;
        FIELD(context, int, 0x24) = 0;
        /* Fall through. */
    case 1:
        if ((D_00138324 & gHeroState.input) && !gHeroState.flag && allowed) {
            if (SpendWeaponAmmo(-1, 1)) {
                start_equipped_item_animation();
                FIELD(owner, unsigned char, 0x20) = 2;
                FIELD(context, int, 0x20) = 20;
            } else {
                PlayMobySound(2, 0, owner);
            }
        }
        break;
    case 2:
        if (FastFloatHelperD(context + 0x20)) {
            PlayMobySound(0, 0, owner);
            SpawnMegaturretShot(owner, &origin, targetVector);
            cancel_hero_item_animation();
            FIELD(owner, unsigned char, 0x20) = 3;
            FIELD(context, int, 0x20) = 10;
        }
        break;
    case 3:
        if (FastFloatHelperD(context + 0x20))
            FIELD(owner, unsigned char, 0x20) = 1;
        break;
    }
    ref_L00_003C8828_00(DrawActiveOwnerEffect, owner);
}
