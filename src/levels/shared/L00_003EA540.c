#include "include_asm.h"
#include "names.h"

typedef struct {
    char pad_000[0xBF8];
    int heldWeapon;
    char pad_BFC[0x1230 - 0xBFC];
    int buttonMask;
    char pad_1234[0x1240 - 0x1234];
    int frameCount;
    char pad_1244[0x1450 - 0x1244];
    int selectedWeapon;
    char pad_1454[0x2294 - 0x1454];
    int mode;
    char pad_2298[0x22BC - 0x2298];
    unsigned char locked;
    char pad_22BD[0x2534 - 0x22BD];
    int cooldown;
} HeroState;

typedef struct {
    char pad[0x1A0];
    int pressed, released;
} InputState;

typedef struct {
    char pad[0x1D];
    unsigned char selected;
} Selection3EA540;

typedef struct {
    char pad[0x54];
    float rate;
    char rest[0x88];
} Entry;

extern HeroState D_00189E20;
extern InputState D_00138180;
extern Selection3EA540 D_00139568;
extern Entry D_L00_00262570[];
extern char D_L00_001B2B90[] __attribute__((sda));

extern void func_L00_003EA7D0(void);
extern int func_00282948(void *), func_002829D8(void *);
extern int func_L00_002D3F30(int, int), func_L00_002D4040(int);
extern void func_002A75E0(char *, int, int, int, int);
extern void func_002E5CF8(int, int, char *), func_002A7470(char *, int, int, int);
extern int func_L00_00329E90(char *, int, void *), func_L00_0032A088(int, int);
extern void func_00282C88(void *), func_00283098(void *, void *, void *);
extern void func_0029FCC0(char *, int, void *);
extern char *func_L00_003DBF50(char *, int, void *, void *);
extern void ref_L00_003EA540_00(void *, char *);

/* Updates the Meteor Gun weapon: fires a shot when the player presses the button and the gun is ready. */
void func_L00_003EA540(char *self)
{
    float v[4];
    int tmp[4];
    char *vars = *(char **)(self + 0x68);
    int ready = 1;
    char *shot;

    if (gHeroState.mode == 0x1D) {
        if (!FastFloatHelperD(&gHeroState.cooldown))
            ready = 0;
    } else {
        gHeroState.cooldown = 40;
    }
    if (*(unsigned char *)(self + 0x42) == *(unsigned char *)(self + 0x43) &&
        (*(unsigned char *)(self + 0x60) & 2))
        StartAnimationBlendedWithFlags(self, 1, 0, 2, 0);
    if (gHeroState.selectedWeapon)
        gHeroState.heldWeapon = gHeroState.selectedWeapon;

    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        self[0x20] = 1;
        *(int *)(vars + 0xC) = 0;
        *(int *)vars = 0;
        *(int *)(vars + 4) = AcquireEntitySlot(self, 0, tmp);
        *(int *)(vars + 8) = GetSlotBody(*(short *)(self + 0xAA), *(int *)(vars + 4));
        /* Fall through. */
    case 1:
        if (FastVectorHelperB(vars) && ready && gHeroState.frameCount >= 23 &&
            (gPadState.pressed & gHeroState.buttonMask) &&
            !gHeroState.locked && SpendWeaponAmmo(-1, 1)) {
            ClearVector128(v);
            v[1] = -1.0f;
            matrix_mul_vec3(v, v, self + 0xC0);
            TransformMobyJointToWorld(self, 0, D_L00_001B2B90);
            shot = SpawnSmallProjectile(self, *(int *)(vars + 4), D_L00_001B2B90, v);
            PlayMobySound(0, 0, self);
            if (*(unsigned char *)(self + 0x43) != 2)
                StartAnimationBlended(self, 2, 0, 0);
            *(float *)(self + 0x48) = 2.0f;
            if (shot)
                *(char **)(shot + 0xB8) = self;
            {
                int selected = gItemSlotToRecord.selected;
                Entry *entry = &gWeaponTable_L00[selected];
                *(float *)vars = 1.0f / entry->rate;
            }
        } else if ((gPadState.released & gHeroState.buttonMask) &&
                   !get_ammo(-1) && !gHeroState.locked) {
            PlayMobySound(2, 0, self);
        }
    }
    ref_L00_003EA540_00(DrawMeteorGunGlow, self);
}
