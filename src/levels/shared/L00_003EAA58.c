#include "include_asm.h"
#include "names.h"

extern void func_L00_003EAC88(char *);
/* Partial resident state layout measured from this handler's accesses. */
typedef struct {
    char p0[0xBF8];
    int heldWeapon;
    char p1[0x1230 - 0xBFC];
    int buttonMask;
    char p2[0x1240 - 0x1234];
    int frameCount;
    char p3[0x1450 - 0x1244];
    int selectedWeapon;
    char p4[0x2294 - 0x1454];
    int mode;
    char p5[0x22BC - 0x2298];
    unsigned char locked;
    char p6[0x2534 - 0x22BD];
    int cooldown;
} HeroState;
extern HeroState D_00189E20;

extern char D_00138180[];
extern void func_0029FCC0(char *, int, void *), func_002FDF40(void *, void *, float, float, float, float, int, int);
extern int func_002FE5A0(void *, void *, void *, void *, char *, int, int, float);
extern int func_00282948(void *), func_L00_002D3F30(int, int);
extern void func_L00_002AF568(void), func_002E5CF8(int, int, char *), func_L00_002AF7D0(void), ref_L00_003EAA58_00(void *, char *);
extern char *func_L00_00387CA8(void *, void *);
/* Updates the Miniturret Glove: it aims, then shoots a miniturret after a short wind-up. */
void func_L00_003EAA58(char *self)
{
    char muzzlePos[16], aimPos[16];
    char *aimPosPtr;
    char *vars = *(char **)(self + 0x68);
    int ready;
    float reach;
    char *shot;
    TransformMobyJointToWorld(self, 0, muzzlePos);
    aimPosPtr = aimPos;
    reach  =  gHeroState.mode == 29 ? 11.0f : 4.5f;
    CalculateAimedLaunchVelocity(aimPosPtr, muzzlePos, 1.5f, reach, 0.25f, 0.003055555745959282f, 0, 0);
    *(int *)(vars + 0x24) = TraceProjectileToImpact(muzzlePos, aimPosPtr, vars, vars + 0x10, self, 0, 0, 0.003055555745959282f);
    ready = 1;
    if (gHeroState.mode == 29) {
        if (!FastFloatHelperD(&gHeroState.cooldown)) ready = 0;
    } else gHeroState.cooldown = 40;
    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        self[0x20] = 1;
        *(int *)(vars + 0x24) = 0;
        /* Fall through. */
    case 1:
        if ((*(int *)(gPadState + 0x1A4) & gHeroState.buttonMask) &&
            !gHeroState.locked && ready) {
            if (SpendWeaponAmmo(-1, 1)) {
                start_equipped_item_animation();
                self[0x20] = 2;
                *(int *)(vars + 0x20) = 20;
            } else PlayMobySound(2, 0, self);
        }
        break;
    case 2:
        if (FastFloatHelperD(vars + 0x20)) {
            PlayMobySound(0, 0, self);
            shot = SpawnMiniturretShot(muzzlePos, aimPosPtr);
            *(char **)(shot + 0xB8) = self;
            cancel_hero_item_animation();
            self[0x20] = 3;
            *(int *)(vars + 0x20) = 10;
        }
        break;
    case 3:
        if (FastFloatHelperD(vars + 0x20)) self[0x20] = 1;
        break;
    }
    ref_L00_003EAA58_00(DrawMiniturretGloveEffect, self);
}
