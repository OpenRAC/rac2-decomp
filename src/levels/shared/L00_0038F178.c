#include "include_asm.h"
#include "names.h"

extern int func_002A77E0(int mode);

extern float func_002A90F8(char *object, char *local);

extern void func_00282D30_7(char *local, int value, float scale);

extern float func_002A7878_1(float low, float high);

extern void func_002BF728(char *object, char *local, float amount, float base);

extern char *func_0029EFD0_1(int);

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner {
    unsigned char prefix_00[0x68];
    void *context_68;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner;

typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext {
    unsigned char prefix_00[0x10];
    float vector_10[4];
    unsigned int field_20;
    unsigned int active_24;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext;

extern void func_002FDBD8(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

extern void func_002FDBD8_1(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

typedef int TI128 __attribute__((mode(TI)));

extern int D_18C0A0;

extern int D_18C0B4;

extern int D_L00_001B9080;

extern void func_002A7470(char *object, int mode, int a2, int a3);

extern void func_002FEE50(int value);

extern void func_00282C88(char *quad);

extern void func_002A10E8(char *object);

extern void func_002A0F48(char *object);

extern void func_L00_004283C8(int value);

extern void func_L00_002C42E0(int a, int b);

extern void func_L00_002F4720(void);

extern void func_L00_00390F28(char *object, int mode);

/* Level state saved by func_L00_00390E10 and restored by func_L00_00390F28. */
typedef struct {
    char pad0[0x30];
    float f30;
    float f34;
    float f38;
    float f3C;
    unsigned char b40;
    unsigned char b41;
    unsigned char b42;
} LevelSavedState_390E10;

extern int D_L00_001A8A44 __attribute__((section(".sdata")));
extern float D_L00_001B1984 __attribute__((section(".sdata")));
extern float D_L00_001B1988 __attribute__((section(".sdata")));
extern float D_L00_001B198C __attribute__((section(".sdata")));
extern float D_L00_001B1990 __attribute__((section(".sdata")));
extern unsigned char D_L00_001B1980 __attribute__((section(".sdata")));
extern unsigned char D_L00_001B1981 __attribute__((section(".sdata")));
extern unsigned char D_L00_001B1982 __attribute__((section(".sdata")));
extern float D_L00_001B2500 __attribute__((section(".sdata")));
extern float D_L00_001B2408 __attribute__((section(".sdata")));
extern int D_L00_001B1EB4 __attribute__((section(".sdata")));
extern int D_L00_001B20C0 __attribute__((section(".sdata")));
extern int D_L00_001B255C __attribute__((section(".sdata")));
extern void func_00284E18(int, int, int);

typedef unsigned char u8;

typedef float f32;

/* Prototype775 is a research label. Field names below describe only the
 * independently observed byte23 and binary32 word2C operations. */
typedef struct {
    u8 pad00[0x23];
    u8 field23;
    u8 pad24[8];
    f32 field2C;
} NativeUpdate775View;

extern void func_0029F338(NativeUpdate775View *object);

typedef struct {
    char prefix[0x760];
    float aimAxis[4];
    char pad770[0xAC0];
    unsigned int buttons;
    char pad1234[0xC];
    int resource;
    char pad1244[0x1050];
    int level;
    char pad2298[0x24];
    unsigned char busy;
    char pad22BD[0x277];
    int cooldown;
} LaunchHero;
extern LaunchHero D_00189E20;
extern unsigned int D_00138320;
extern void func_0029FCC0(char *, int, char *);
/* Interleaved declarations preserve the EE ABI's independent GPR and FP argument order. */
extern void func_002FDF40(void *, void *, void *, float, float, float, float, void *);
extern int func_002FE5A0(void *, void *, void *, void *, void *, int, int, float);
extern int func_00282948(int *), func_L00_002D3F30(int, int);
extern void func_L00_002AF7D0(void), func_L00_002AF568(void);
extern int func_002E5CF8(int, int, char *);
extern char *func_L00_00398810(char *, char *);
extern void ref_L00_0039D110_00(void *, void *);
extern void func_L00_0039D340(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *);

typedef struct { float value[3]; } QuerySettings;
extern QuerySettings D_L00_001AF410;
typedef struct { char prefix[0x1A0]; unsigned int held, pressed; } LaunchInput;
extern LaunchInput D_00138180;
extern char *func_002AF580(void *, void *, int *, void *, int, int, float, float, float, float, float, int, void *);
extern char *func_L00_0038D530(char *, char *);
extern void ref_L00_00397E60_00(void *, void *);
extern void func_L00_00398118(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *);

/* func_L00_0038F178 is defined in L00_0038F178-effects.c. */

/* Family 6eb4f363e5305bed: seed body at func_L00_00387408. */
/* Spawns a small puff of sparks at the object, unless the random check says to skip it. */
void func_L00_0038F3D8(char *object)
{
    char local[16];
    float base;
    int value = *(int *)(object + 104);

    if (RandomIntBelow(5))
        return;
    base = GetGroundHeightAtPosition(object + 16, local);
    func_00282D30_7(local, value, 0.25f);
    SpawnBubbleParticle(object + 16, local, func_002A7878_1(0.05f, 0.1f) * 210000.0f, base);
}

typedef union { TI128 quad; float f[4]; } ParticleUpdateVector;
typedef struct { int color[4]; } ParticleUpdateColors;
extern ParticleUpdateColors D_L00_001AF010;
extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern int func_002AAFA0(int, int);
extern void func_002BAE50(void *, void *, int, int, int, int, int, int);
extern float func_00283B98(float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_L00_003253A0(void *, void *, void *, float);
extern float func_00283CE0(int);
extern int func_00282978(short *);

/* Per-frame update of a drifting spark particle: sheds colored sparks, slows down, and removes itself when it fades or leaves the map. */
void func_L00_0038F5F0(char *object)
{
    ParticleUpdateColors colors;
    ParticleUpdateVector direction, random;
    char *state = *(char **)(object + 0x68);
    int enabled = 1;
    if (*(int *)(state + 0x20) != 0)
        if (RandomIntBelow(2))
            enabled = 0;
    if ((*(unsigned char *)(object + 0xBC) & 1) && enabled) {
        int color;
        colors = D_L00_001AF010;
        random.quad = 0;
        random.f[0] = RandomFloatRange(-1.0f, 1.0f);
        random.f[1] = RandomFloatRange(-1.0f, 1.0f);
        random.f[2] = RandomFloatRange(-1.0f, 1.0f);
        direction.quad = random.quad;
        vec_scale_to_length(&direction, &direction, 1.0f / 60.0f);
        if (*(unsigned char *)(object + 0xBC) & 0xFE) {
            color = SwapPackedColorChannels(colors.color[RandomIntBelow(4)],
                                *(unsigned char *)(object + 0xBC) >> 1);
            SpawnScalingParticle(object + 0x10, &direction, color,
                         SwapPackedColorChannels(0x4FFF, *(unsigned char *)(object + 0xBC) >> 1),
                         45, 50, 120, 1);
        } else {
            SpawnScalingParticle(object + 0x10, &direction, colors.color[RandomIntBelow(4)],
                         0x4FFF, 45, 50, 120, 1);
        }
    }
    *(float *)(object + 0xF0) = FastAddRotations(*(float *)(object + 0xF0), *(float *)(state + 0x10));
    *(float *)(object + 0xF4) = FastAddRotations(*(float *)(object + 0xF4), *(float *)(state + 0x14));
    FastVecAdd(object + 0x10, object + 0x10, state);
    MixOnInnerData(object, state, state, 0.0040555559f);
    if (*(float *)(object + 0x10) < 0.0f || *(float *)(object + 0x14) < 0.0f ||
        *(float *)(object + 0x18) < 0.0f) {
        MarkMobySpawned((NativeUpdate775View *)object);
        return;
    }
    if (*(short *)(state + 0x18) < *(short *)(state + 0x1A) / 4) {
        float amount = IntToFloat(*(short *)(state + 0x18));
        *(float *)(object + 0x2C) = *(float *)(state + 0x1C) * amount /
                                  IntToFloat(*(short *)(state + 0x1A) / 4);
    }
    if (FastDecTimer((short *)(state + 0x18)))
        MarkMobySpawned((NativeUpdate775View *)object);
}

/* func_L00_0038F8B8 is defined in L00_0038F8B8.c. */

/* func_L00_0038FC48 is defined in L00_0038FC48-g8.c. */


/* Calls a callee with the constant 167 and, when it returns a non-zero object, stores the argument pointer at +4 of the object held at +104, clears the words at +0, +8 and +12 of that object, sets byte +48 to 255, the halfword at +50 to 126 and bytes +49 and +32 to 0, then returns the object. */
char *func_L00_00390938(char *owner)
{
    char *object = func_0029EFD0_1(167 /* moby class 167 */);
    int *vars;

    if (object != 0) {
        vars = *(int **)(object + 104);
        vars[1] = (int)owner;
        vars[0] = 0;
        vars[2] = 0;
        vars[3] = 0;
        *(unsigned char *)(object + 48) = 255;
        *(short *)(object + 50) = 126;
        object[49] = 0;
        object[32] = 0;
    }
    return object;
}

/* Saves the current lighting and fog settings into the object, then switches the level to a dim, close-range look. */
void func_L00_00390E10(char *object)
{
    LevelSavedState_390E10 *st = *(LevelSavedState_390E10 **)(object + 0x68);
    float f30 = D_L00_001B1984;
    float f34 = D_L00_001B1988;
    float f38 = D_L00_001B198C;
    float f3C = D_L00_001B1990;

    D_L00_001A8A44 = 1;
    st->f30 = f30;
    st->f34 = f34;
    st->f38 = f38;
    st->f3C = f3C;
    st->b40 = D_L00_001B1980;
    st->b41 = D_L00_001B1981;
    st->b42 = D_L00_001B1982;
    D_L00_001B1980 = 0x40;
    D_L00_001B1981 = 0x60;
    D_L00_001B1982 = 0x40;
    D_L00_001B1984 = 0.0f;
    D_L00_001B1988 = 131072.0f;
    D_L00_001B198C = 255.0f;
    D_L00_001B2500 = 147456.0f;
    D_L00_001B2408 = 144.0f;
    D_L00_001B255C = 144;
    D_L00_001B1EB4 = 144;
    D_L00_001B20C0 = 0x50000;
    D_L00_001B1990 = 0.0f;
    SetBackgroundColor(D_L00_001B1980, D_L00_001B1981, D_L00_001B1982);
}



/* Releases the second argument's object: clears a word of the sub-object at +0x68, clears
 * two globals, hands its +0x14 word over before clearing it, then runs five helpers and the
 * first argument through one more. */
void func_L00_00391310(char *actor, char *tether)
{
    char *tetherRef = tether;
    char *actorRef = actor;
    int *vars = *(int **)tetherRef;

    vars = (int *)*(int *)((char *)vars + 0x68);
    if (vars != 0)
        vars[1] = 0;
    D_18C0A0 = 0;
    PickCameraStateFromHeroTurn(*(int *)(tetherRef + 0x14));
    *(int *)(tetherRef + 0x14) = 0;
    SetHeroAction_L00(0, 1);
    RestoreLevelLighting(actorRef, 1);
    ClearSecondLevelTableEntry();
    ClearEntryFlag(*(int *)(tetherRef + 0x4C));
    MarkMobySpawned((NativeUpdate775View *)actorRef);
    D_L00_001B9080 = 0;
}





/* Gates on the sub-object's tag byte, mirrors one status bit from that object into its own
 * halfword, clamps the wrapped value at +4 against a signed window and finishes with the
 * three transform helpers; original game role is unknown. */
extern int D_0018B060;

extern void func_310440(char *object);

extern void func_310838(char *object, int mode, int delta);

extern float func_31A7C0(float low, float high);

extern float func_31F1C8(float angle);

extern float func_2EF0F8(float value, float amount);

extern void func_312D18(char *object);

void func_L00_003952E0(char *object)
{
    char *vars = *(char **)(object + 0x68);
    char *other = *(char **)(vars + 8);
    unsigned char tag = *(unsigned char *)(other + 0x20);

    if (tag == 0 || (tag & 0xF0) == 0xF0) {
        func_310440(object);
        return;
    }
    if (other != 0) {
        if ((*(unsigned short *)(object + 0x34) & 1) != (*(unsigned short *)(other + 0x34) & 1)) {
            unsigned short bits = *(unsigned short *)(object + 0x34) & 0xFFFE;

            *(unsigned short *)(object + 0x34) = bits;
            bits |= *(unsigned short *)(*(char **)(vars + 8) + 0x34) & 1;
            *(unsigned short *)(object + 0x34) = bits;
        }
    }
    if (D_0018B060 < 0x19)
        *(unsigned short *)(object + 0x34) |= 0x41;
    {
        int current = *(int *)(vars + 4);
        int next = current - 0xC0;
        int delta = -0xC0;

        *(int *)(vars + 4) = next;
        if (next >= 0x1001) {
            delta = -0x10C0;
            *(int *)(vars + 4) = current - 0x10C0;
        } else if (next < 0) {
            delta = 0xF40;
            *(int *)(vars + 4) = current + 0xF40;
        }
        func_310838(*(char **)(object + 0x24), 0, delta);
    }
    *(float *)(object + 0x2C) = *(float *)(*(char **)(object + 0x24) + 0x24)
                                * *(float *)(vars + 0xC) * func_31A7C0(0.5f, 1.0f);
    *(float *)(object + 0xF4) = func_2EF0F8(*(float *)(object + 0xF4),
                                             func_31F1C8(*(float *)(vars + 0xC)));
    func_312D18(object);
}

/* Builds the object for type 0xB3 and, when the constructor returns one, fills its fields,
 * clears a quad at +0xF0, records the argument in the sub-object at +0x68 and copies three
 * quads from the argument before running two helpers. Returns the object. */
char *func_L00_00395240(char *source)
{
    char *p = source;
    char *object = func_0029EFD0_1(0xB3 /* moby class 179 */);

    if (object != 0) {
        int *vars = *(int **)(object + 0x68);
        *(unsigned char *)(object + 0x30) = 0xFF;
        *(unsigned short *)(object + 0x32) = 0xFF;
        *(unsigned char *)(object + 0x31) = 1;
        *(unsigned short *)(object + 0x34) = 0x204;
        *(unsigned char *)(object + 0x23) = 0x50;
        *(char *)(object + 0x20) = 0;
        vars[2] = (int)p;
        ClearVector128(object + 0xF0);
        *(TI128 *)(object + 0xC0) = *(TI128 *)(p + 0xC0);
        *(TI128 *)(object + 0xD0) = *(TI128 *)(p + 0xD0);
        *(TI128 *)(object + 0xE0) = *(TI128 *)(p + 0xE0);
        func_002A10E8(object);
        func_002A0F48(object);
    }
    return object;
}

/* func_L00_003959C0 is defined in L00_003959C0-g8.c. */

/* func_L00_00395A88 is defined in L00_00395A88-g8.c. */

/* func_L00_00396078 is defined in L00_00396078-g64.c. */


/* func_L00_003973E8 is defined in L00_003973E8-g8.c. */

/* Selects an aim target before advancing the projectile launcher state. */
/* Per-frame update of the Bomb Glove moby. */
void func_L00_00397E60(char *actor)
{
    char *state = *(char **)(actor + 0x68);
    char position[16];
    QuerySettings settings;
    char direction[16];
    int foundCount;
    char *target;
    int ready;
    TransformMobyJointToWorld(actor, 0, position);
    settings = D_L00_001AF410;
    target = SelectBestTargetInCone(actor + 0x10, gHeroState.aimAxis, &foundCount, 0, 0, 0,
                          0.3926991f, 0.7853982f, 11.1f, 0.0f, 0.0f, 0, &settings);
    CalculateAimedLaunchVelocity(direction, position, target, 1.5f, gHeroState.level == 29 ? 11.0f : 10.0f, 0.16666667f, 0.003055555745959282f, 0);
    ready = 1;
    *(int *)(state + 0x24) = TraceProjectileToImpact(position, direction, state, state + 0x10, actor, 0, 0, 0.003055555745959282f);
    if (gHeroState.level == 29) {
        if (!FastFloatHelperD(&gHeroState.cooldown)) ready = 0;
    }
    else gHeroState.cooldown = 40;
    switch (*(unsigned char *)(actor + 0x20)) {
    case 0:
        *(unsigned char *)(actor + 0x20) = 1;
        *(int *)(state + 0x24) = 0;
    case 1:
        if ((gPadState.held & gHeroState.buttons) == 0 || gHeroState.busy || gHeroState.resource < 23 || !ready) break;
        if (SpendWeaponAmmo(-1, 1)) {
            start_equipped_item_animation();
            *(unsigned char *)(actor + 0x20) = 2;
            *(int *)(state + 0x20) = 20;
            break;
        }
        if (gPadState.pressed & gHeroState.buttons) PlayMobySound(2, 0, actor);
        break;
    case 2:
        if (!FastFloatHelperD((int *)(state + 0x20))) break;
        *(char **)(SpawnSpinningDebris(position, direction) + 0xB8) = actor;
        cancel_hero_item_animation();
        *(unsigned char *)(actor + 0x20) = 3;
        *(int *)(state + 0x20) = 10;
        break;
    case 3:
        if (FastFloatHelperD((int *)(state + 0x20))) *(unsigned char *)(actor + 0x20) = 1;
        break;
    }
    ref_L00_00397E60_00(DrawBombGloveProjectile, actor);
}


/* When the context flag at offset 0x24 is nonzero, pass scale 1.0, the context, its vector at offset 0x10 and mode zero to the bound helper; original game role is unknown. */
void func_L00_00398118(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        DrawSpinningBillboardPair(1.0f, context, context->vector_10, 0);
    }
}




/* func_L00_0039B288 is defined in L00_0039B288-g8.c. */


/* Aims and launches the actor's projectile in response to the shared input gate. */
/* Per-frame update of the Decoy Glove moby. */
void func_L00_0039D110(char *actor)
{
    char *state = *(char **)(actor + 0x68);
    char position[16], direction[16];
    int ready;
    TransformMobyJointToWorld(actor, 0, position);
    CalculateAimedLaunchVelocity(direction, position, 0, 1.5f, gHeroState.level == 29 ? 11.0f : 5.0f, 0.16666667f, 0.003055555745959282f, 0);
    ready = 1;
    *(int *)(state + 0x24) = TraceProjectileToImpact(position, direction, state, state + 0x10, actor, 0, 0, 0.003055555745959282f);
    if (gHeroState.level == 29) {
        if (!FastFloatHelperD(&gHeroState.cooldown)) ready = 0;
    }
    else gHeroState.cooldown = 40;
    switch (*(unsigned char *)(actor + 0x20)) {
    case 0:
        *(unsigned char *)(actor + 0x20) = 1;
        *(int *)(state + 0x24) = 0;
    case 1:
        if ((D_00138320 & gHeroState.buttons) == 0 || gHeroState.busy || gHeroState.resource < 9 || !ready) break;
        if (SpendWeaponAmmo(-1, 1)) {
            start_equipped_item_animation();
            *(unsigned char *)(actor + 0x20) = 2;
            *(int *)(state + 0x20) = 20;
            break;
        }
        PlayMobySound(2, 0, actor);
        break;
    case 2:
        if (!FastFloatHelperD((int *)(state + 0x20))) break;
        *(char **)(CreateDecoyProjectile(position, direction) + 0xB8) = actor;
        cancel_hero_item_animation();
        *(unsigned char *)(actor + 0x20) = 3;
        *(int *)(state + 0x20) = 10;
        break;
    case 3:
        if (FastFloatHelperD((int *)(state + 0x20))) *(unsigned char *)(actor + 0x20) = 1;
        break;
    }
    ref_L00_0039D110_00(DrawDecoyGloveProjectile, actor);
}

/* When the context flag at offset 0x24 is nonzero, pass scale 1.0, the context, its vector at offset 0x10 and mode zero to the bound helper; original game role is unknown. */
void func_L00_0039D340(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        func_002FDBD8_1(1.0f, context, context->vector_10, 0);
    }
}

/* The mode word at 0x18C0B4 must be 8 and the object's byte 0x43 must not be 6; the
 * helper then takes the object with mode 6, zero and ten. */
/* Per-frame update of the Helipack moby: keeps the hero in the flying pose. */
void func_L00_0039D378(char *object)
{
    if (D_18C0B4 == 8) {
        if (*(unsigned char *)(object + 0x43) != 6)
            StartAnimationBlended(object, 6, 0, 10);
    }
}

/* func_L00_0039E158 is defined in L00_0038F178-rail.c. */

/* multiply binary32 field2C by exact1.025f then subtract3 modulo256 from byte23; call original pointer helper if updated byte below4; no original semantic field names recovered */
void func_L00_0039E5B0(NativeUpdate775View *object)
{
    object->field2C *= 1.025f;
    object->field23 -= 3;
    if (object->field23 < 4)
        MarkMobySpawned(object);
}

/* func_L00_0039E600 is defined in L00_0039E600.c. */


/* func_L00_003A09F8 is defined in L00_0038F178-tile.c. */

/* func_L00_003A0C00 is in L00_003A0C00.c. */

