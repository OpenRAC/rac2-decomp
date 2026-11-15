#include "common.h"
typedef struct {
    char pad0000[0xBF8];
    char *f0BF8;
    char pad0BFC[0x1230 - 0xBFC];
    u32 buttons;
    char pad1234[0xC];
    int resource;
    char pad1244[0x1450 - 0x1244];
    char *target;
    char pad1454[0x2294 - 0x1454];
    int level;
    char pad2298[0x22B8 - 0x2298];
    u8 f22B8;
    char pad22B9[3];
    u8 busy;
    char pad22BD[0x2534 - 0x22BD];
    int cooldown;
} AimHero;
extern AimHero D_00189E20;
typedef struct { char pad000[0x1A0]; u32 held; u32 pressed; } AimPad;
extern AimPad D_00138180;
extern u8 D_00139581;
extern u8 D_0013958D[];
extern int D_L00_001A8F00;
extern int D_L00_001B2BE4;
extern int D_L00_001B2BE8 __attribute__((sda));
extern char D_L00_001B0BF0[] __attribute__((sda));
extern u16 D_L00_001B0C00 __attribute__((sda));
extern u16 D_L00_001B0C04 __attribute__((sda));
extern u16 D_L00_001B0C08 __attribute__((sda));
extern int D_L00_001B0C0C __attribute__((sda));
typedef struct { char pad00[0x54]; float rate; char pad58[0xE0 - 0x58]; } AimEntry;
extern AimEntry D_L00_00262570[];
extern void func_L00_003FE8D0(char *);
extern void func_L00_002C42E0(int a0, int a1);
extern void func_002A75E0(void *, int, int, int, int);
extern int func_00282978(s16 *);
extern int func_00282948(int *);
extern void func_002829D8(float *);
extern void func_L00_002AF7D0(void);
extern void func_L00_002AF568(void);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_L00_002D4040(int);
extern int func_L00_002D3F30(int, int);
/* The caller deliberately supplies a sixth GPR word (4) in the call slot;
 * retail overwrites it before consumption. Original return/unused-formal
 * intent remains unqualified, but the observed call prefix is preserved. */
extern void func_00273318(float, float, float, void *, u32, void *, int, int, int);
extern int func_002E5CF8(int, int, char *);
extern void func_L00_003FE920(char *, void *, int, void *);
extern void func_L00_003FEAC8(char *, void *, void *, int);
extern void func_L00_003FE280(char *, char *);
extern s32 func_002AB1F0(u8 *);
extern void func_002FDF40(float, float, float, float, void *, void *, void *, void *);
extern int func_002FE5A0(float, void *, void *, void *, void *, void *, int *, int *);
extern void func_L00_003FE310(void *, void *, void *);
extern int func_L00_003FE2D0(int, int, int);
struct Rac2Native_5f824a0e369ccf7b_src_record;
extern struct Rac2Native_5f824a0e369ccf7b_src_record D_L00_0029F210;
extern int func_L00_002D6998(struct Rac2Native_5f824a0e369ccf7b_src_record *);
extern void func_L00_002D6B70(int);
extern void ref_L00_003FDE48_00(void *, void *);
extern void func_L00_003FE490(void *);

/* Coordinate the multi-object interaction and its repeat/cooldown timers. */

/* Per-frame update of the Bouncer weapon (also used by the Heavy Bouncer): aims, fires and runs the reload timer. */
void func_L00_003FDE48(unsigned char *object) {
    float origin[4];
    float aim[4];
    AimEntry *entry;
    char *state = *(char **)(object + 0x68);
    char *target;
    s32 target_data;
    int allowed;
    int was_running;
    int handle;

    if (object[0x20] == 0) {
        object[0x20] = 1;
        *(int *)(state + 0x28) = -1;
        *(float *)(state + 0x20) = 0.0f;
        *(int *)(state + 0x2C) = 0;
        D_L00_001B2BE4 = 20;
    }
    if (gHeroState.level == 1) SetHeroAction_L00(29, 1);
    if (object[0x42] == object[0x43] && (object[0x60] & 2)) StartAnimationBlendedWithFlags(object, 1, 0, 2, 0);
    ComputeMobyOffsetPoint(object, (char *)origin);
    target = 0;
    if (gHeroState.target != 0 && (u8)gHeroState.target[0x20] != 0xFE && (u8)gHeroState.target[0x20] != 0xFD) {
        target_data = GetMobyPrivateValue0((u8 *)gHeroState.target);
        if (target_data != 0 && *(float *)target_data > 0.0f) target = gHeroState.target;
    }
    allowed = 1;
    if (gHeroState.level == 29) {
        if (!FastFloatHelperD(&gHeroState.cooldown)) allowed = 0;
    }
    else gHeroState.cooldown = 40;
    CalculateAimedLaunchVelocity(1.6f, 10.0f, 0.25f, 0.004055555909872055f, aim, origin, target, 0);
    *(int *)(state + 0x24) = TraceProjectileToImpact(0.004055555909872055f, origin, aim, state, state + 0x10, object, 0, 0);
    was_running = *(float *)(state + 0x20) > 0.0f;
    FastVectorHelperB((float *)(state + 0x20));
    if (was_running && *(float *)(state + 0x20) <= 0.0f && get_ammo(-1)) PlayMobySound(3, 0, object);
    if (*(int *)(state + 0x2C) != 0 && FastFloatHelperD((int *)(state + 0x2C))) cancel_hero_item_animation();
    if ((gPadState.pressed & gHeroState.buttons) && !get_ammo(-1)) {
        PlayMobySound(1, 0, object);
        D_L00_001B2BE4 = 20;
    }
    if (D_L00_001A8F00 == 0 && *(float *)(state + 0x20) == 0.0f && gHeroState.busy == 0 &&
        (u8)object[0x42] <= 1 && (gPadState.held & gHeroState.buttons) && gHeroState.resource >= 23 && allowed) {
        if (get_ammo(-1)) {
            PlayMobySound(0, 0, object);
            SpendWeaponAmmo(-1, 1);
            SpawnMuzzleSparkBurst(object, origin, aim);
            StartAnimationBlendedWithFlags(object, 2, 0, 2, 0);
            SpawnBouncerDebris((int)object, (int)origin, (int)aim);
            start_equipped_item_animation();
            *(int *)(state + 0x2C) = 16;
            *(int *)(state + 0x28) = CopyRecordsToFreeSlots(&D_L00_0029F210);
        }
        if (!(gPadState.held & gHeroState.buttons) || !get_ammo(-1) || gHeroState.f22B8 == 0) {
            handle = *(int *)(state + 0x28);
            if (handle >= 0) {
                ResetActiveSlots(handle);
                *(int *)(state + 0x28) = -1;
            }
        }
        entry = gWeaponTable_L00 + D_0013958D[0];
        *(float *)(state + 0x20) = 1.0f / entry->rate;
    }
    ref_L00_003FDE48_00(DrawAttachedEffect, object);
}
