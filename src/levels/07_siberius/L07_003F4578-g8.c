#include "include_asm.h"

#include "common.h"

extern f32 func_2E5318(f32 a, f32 b);

extern f32 func_2E4918(f32 a, f32 b);

extern f32 D_L07_001B0F84 __attribute__((sda));

extern u8 *D_L07_001B22DC __attribute__((sda));

extern void func_317520(u8 *a, u8 *b, u8 *c, u8 *d, u8 *e, u8 *f);

extern void func_421288(s32 a, f32 b, f32 c);

extern void func_4212D0(f32 a, f32 b);

extern u8 *func_2CD050(s32 a);

extern void func_3109C8(u8 *a, s32 b, s32 c);

extern s32 func_312FA8(u8 *a, s32 b, s32 c);

extern f32 func_313008(u8 *a, s32 b);

extern void func_313DD8(void *a, f32 b, f32 c);

extern f32 D_L07_001B10B8 __attribute__((sda));

extern f32 D_L07_001B10BC __attribute__((sda));

extern u32 D_L07_001B10C0 __attribute__((sda));

extern f32 D_L07_001B0FD0 __attribute__((sda));

extern f32 D_L07_001B0E98 __attribute__((sda));

extern f32 D_L07_001B0E9C __attribute__((sda));

extern f32 D_L07_001B0EA0 __attribute__((sda));

extern f32 func_002AA2E8(f32 *value, f32 target, f32 step);

extern void func_002A7750(u8 *a, u8 b, s32 c);

extern void func_0029F338(void *a);

extern f32 func_00283B98(f32 a, f32 b);

extern void func_L00_002E6CF0(void *a, void *b);

extern void func_L07_003F4C18(void *a, void *b, void *c);

extern s32 func_L01_003120A8(void *a, void *b, void *c, s32 d, f32 e, f32 f, s32 g, s32 h, s32 i);

extern char func_L07_003F4CC0[];

/* Advances the object's own state: three step kinds by the 0x20 flag, then the shared
   spin and the two sampled vectors. */
/* Updates the beam: fades it in, then fades it out and removes it. While alive it spins, draws itself and hurts what it touches. */
void func_L07_003F4970(u8 *moby)
{
    u8 *beamMoby = moby;
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 state = *(u8 *)(moby + 0x20);
    f32 startPoint[4];
    f32 endPoint[4];

    switch (state) {
    case 0:
        {
            u32 frameCount = *(u16 *)(beamMoby + 0x96) + 1;

            *(u16 *)(beamMoby + 0x96) = frameCount;
            if ((u16)frameCount == 1) {
                break;
            }
            ApproachValue((f32 *)(vars + 0x24), 1.0f, D_L07_001B0E98 * (1.0f / 60.0f));
            if (1.0f <= *(f32 *)(vars + 0x24)) {
                SetMobyState(beamMoby, 1, -1);
            }
        }
        break;
    case 1:
        ApproachValue((f32 *)(vars + 0x24), 0.0f, D_L07_001B0E9C * (1.0f / 60.0f));
        if (*(f32 *)(vars + 0x24) <= 0.0f) {
            MarkMobySpawned(beamMoby);
            return;
        }
        break;
    }
    *(f32 *)(vars + 0x28) = FastAddRotations(*(f32 *)(vars + 0x28), D_L07_001B0EA0 * 0.00029088825f);
    AddDrawCallbackToList1(DrawSegmentedBeam, beamMoby);
    if (0.333f < *(f32 *)(vars + 0x24)) {
        GetBeamEndPoints(beamMoby, startPoint, endPoint);
        CastObjectCollisionLine(*(u32 *)(beamMoby + 0xB8), startPoint, endPoint, 1, *(f32 *)(vars + 0x2C), 1.0f, 0, 1, 0);
    }
}


typedef int TI128 __attribute__((mode(TI)));

/* The object up to its flag word, its state pointer and its counter. */
typedef struct {
    u8 pad00[0x34];
    u16 flags34;
    u8 pad36[0x68 - 0x36];
    u8 *state;
    u8 pad6c[0x98 - 0x6C];
    s32 f98;
} SibObj;

/* The state record up to its two group words. */
typedef struct {
    u8 pad00[0xCC];
    s32 groupCC;
    s32 groupD0;
} SibGroups;

extern f32 D_L07_001B173C;

extern u8 D_L07_001B1730 __attribute__((sda));

extern u16 **D_L07_001A9014;

extern u8 *D_L07_001B2954;

extern u8 *D_L07_001B295C;

extern s32 D_L07_001B1E90;

extern void func_L00_002B9D60(void *obj, void *pos, s32 a2, s32 a3);

extern void func_L00_0036AE00(s32 id, s32 a1);

/* Switches the object to its second phase. */
void func_L07_00410930(SibObj *moby)
{
    f32 offsetCopy[4];
    f32 offset[4];
    SibGroups *state;
    u16 *idList;
    u16 *idListB;
    u8 *entry;

    *(TI128 *)offset = 0;
    offset[2] = D_L07_001B173C;
    *(TI128 *)offsetCopy = *(TI128 *)offset;
    state = (SibGroups *)moby->state;
    ResetHeroPositionAndDirection(&D_L07_001B1730, offsetCopy, 0, 1);
    moby->flags34 |= 2;
    moby->f98 = 0;
    for (idList = D_L07_001A9014[state->groupD0];
         idList != 0 && ((s16)idList[-1] >= 0 || idList == D_L07_001A9014[state->groupD0]) &&
         (entry = D_L07_001B2954 + ((*idList & 0x7FFF) << 5)) != 0;
         idList++) {
        entry[0x1E] &= 0xFB;
    }
    for (idList = D_L07_001A9014[state->groupCC];
         idList != 0 && ((s16)idList[-1] >= 0 || idList == D_L07_001A9014[state->groupCC]) &&
         (entry = D_L07_001B2954 + ((*idList & 0x7FFF) << 5)) != 0;
         idList++) {
        entry[0x1E] |= 4;
    }
    for (idListB = D_L07_001A9014[state->groupCC];
         idListB != 0 && ((s16)idListB[-1] >= 0 || idListB == D_L07_001A9014[state->groupCC]) &&
         (entry = D_L07_001B295C + ((*idListB & 0x7FFF) << 6)) != 0;
         idListB++) {
        *(f32 *)(entry + 0x38) -= 100.0f;
        SetupScaleRecord(*idListB & 0x7FFF, 1);
    }
    D_L07_001B1E90 = 2;
}


/* Seeds the two shared field defaults, then fills the 0x450 record once. */
extern void func_L00_00424A08(s32, f32, f32);
extern void func_L00_00424A50(f32, f32);
extern u8 *func_L00_002D70A0(s32);

typedef struct { f32 x, y; u8 pad08[0x2C]; u32 color; } Effect;
typedef struct { u8 pad[0x450]; Effect *effect; } EffectState;
/* Sets up the screen effect of the boss. For one variant it also creates the effect record once and fills it in. */
void func_L07_003F8780(u8 *moby)
{
    EffectState *vars = *(EffectState **)(moby + 0x68);

    follow_camera_set_distance(0, D_L07_001B10B8, 0.003f);
    follow_camera_set_height(D_L07_001B10BC, 0.003f);
    if (*(u8 *)(moby + 0x95) != 0) {
        if (vars->effect == 0)
            vars->effect = (Effect *)AllocCameraOverrideSlot(5);
        {
            f32 x = D_L07_001B10B8;
            f32 y = D_L07_001B10BC;
            u32 color;
            vars->effect->x = x;
            color = D_L07_001B10C0;
            vars->effect->y = y;
            vars->effect->color = color;
        }
    }
}

/* Arms the spinner on the first pass, otherwise steers its 0x20 angle down. */
/* func_L07_003F6CF0 is defined in L07_003F4578-spin-g8.c. */

/* Steers the 0x54 yaw toward the argument and refreshes the two 0xF8 angles. */

/* Feeds the four 0xA8 ids to the shared geometry pass. */
/* func_L07_0040F6B8 is defined in L07_003F4578-geometry-g8.c. */

extern f32 func_2E49C8(f32 a, f32 b);

extern f32 func_2E5360(f32 a, f32 b);

extern void func_3144F0(void *a0, void *a1, f32 a2, f32 a3, f32 a4, f32 a5, s32 a6);

/* The two level floats the scaling uses; the pointers are reached absolutely. */
extern f32 D_L07_001B17D4 __attribute__((sda));

extern f32 D_L07_001B17D8 __attribute__((sda));

extern u8 *D_L07_001B9250 __attribute__((nosda));

extern u8 *D_L07_001ADAAC MACRO_ADDR;

extern u8 D_L07_001B31A9;

/* Steers the object's two angles: the yaw toward the argument, the pitch from the shared
   record, and the two scaled fields of the state record. */
void func_L07_0040F468(u8 *moby)
{
    u8 *owner;
    u8 *vars;
    u8 *record;
    u8 *worldInfo;
    u8 *targetObj;
    f32 *dirXY;
    f32 aimAngle;
    f32 targetYaw;
    f32 dirAngle;
    f32 maxTurnSpeed;
    f32 turnAccel;
    f32 pi;

    worldInfo = D_L07_001B9250;
    if (*(s16 *)(worldInfo + 0x86) != 0) {
        return;
    }
    targetObj = D_L07_001ADAAC;
    if (targetObj == 0) {
        return;
    }
    pi = 3.14159274f;
    owner = *(u8 **)(worldInfo + 0x70);
    vars = *(u8 **)(moby + 0x68);
    dirXY = (f32 *)(owner + 0x160);
    targetYaw = func_2E5318(*(f32 *)(targetObj + 0xF8), pi);
    record = owner + 0x1C0;
    dirAngle = func_2E49C8(dirXY[0], dirXY[1]);
    aimAngle = func_2E5360(targetYaw, dirAngle);
    turnAccel = D_L07_001B17D4 * 0.0000048481375f;
    maxTurnSpeed = D_L07_001B17D8 * 0.000290888245f;
    if (D_L07_001B31A9 == 0) {
        aimAngle = func_2E5318(aimAngle, pi);
    }
    func_3144F0(&aimAngle, vars + 0x1A8, 0.0f, turnAccel, turnAccel, maxTurnSpeed, 0);
    *(f32 *)(record + 0x1C) = 1.0f;
    *(f32 *)(record + 0x14) = -*(f32 *)(vars + 0x1A8);
}

extern u8 D_00189E20[];
extern u32 D_L07_001B1E08 MACRO_ADDR;
extern int func_002AD470(u8 *a, u8 *b, u8 *c, u8 *d, u8 *e, u8 *f);
extern void func_002A0F48(u8 *a);
extern f32 func_00282E48(u8 *a, u8 *b);

typedef struct { u8 pad[0xA8]; s32 ids[4]; } Rec;

/* Updates the four attached parts of the object: places each one, and lets the player grab a Swingshot Node part or shows and hides it. */
void func_L07_0040F760(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    u32 frameSlot = ((s32)moby >> 8) & 7;
    s32 i;

    for (i = 0; i < 4; i++) {
        s32 id = ((Rec *)vars)->ids[i];
        u8 *part;
        if (id == -1)
            continue;
        part = gMobyArray_L07 + (id << 8);
        ApplyCollisionPushToObject(part, moby, vars + 0x120 + i * 0x10, vars + 0x160 + i * 0x10, part + 0x10, part + 0xF0);
        func_002A0F48(part);
        if (*(s16 *)(part + 0xAA) == 0x2F6 /* Swingshot Node */) {
            u8 *hero = gHeroState;
            if (*(s32 *)(hero + 0x229C) == 13 && *(u8 **)(hero + 0xAA4) == part && *(u8 **)(hero + 0x3A0) != moby) {
                if (fast_vec_dist(hero + 0x80, part + 0x10) < 8.0f)
                    *(u8 **)(hero + 0x3A0) = moby;
                continue;
            }
        }
        if ((D_L07_001B1E08 & 7) == frameSlot && *(s16 *)(part + 0xAA) == 0x2F6 /* Swingshot Node */) {
            u8 *heroB = gHeroState;
            if (*(s32 *)(heroB + 0x229C) != 13) {
                if (D_L07_001ADAAC == moby)
                    *(u16 *)(part + 0x34) &= 0xEFFF;
                else
                    *(u16 *)(part + 0x34) |= 0x1000;
            }
        }
    }
}

extern f32 D_L07_001B0FD0 __attribute__((sda));
extern char D_00189EA0[];
extern char D_L07_001B9200[];
extern u8 *D_L07_001C36C0[];
extern int func_00277F48(void *, float, int, char *, void *);
extern int func_002E5DA0(int, int, char *, int);
extern int func_002A8C28(char *, char *, int, float, float, float, int, int, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_0032DA58(char *, char *, char *, float);
extern void func_L07_003F6CF0(u8 *a);
extern void func_L07_003F6DC0(u8 *self, float *target);
extern void func_L07_003F6F00(u8 *a0);

/* Updates the homing bomb: it flies toward the player and, when it touches something, explodes with a sound and damage, then waits to be reset. */
void func_L07_003F6960(u8 *moby)
{
    u8 *vars;
    u8 *hitCursor;
    char *pos;
    char *tuningBase;
    f32 dir[4];
    s32 hitCount, remaining;

    vars = *(u8 **)(moby + 0x68);
    if (moby[0x20] != 1)
        TickHomingBombFuse(moby);
    switch (moby[0x20]) {
    case 2:
        *(f32 *)(moby + 0x2C) = *(f32 *)(*(u8 **)(moby + 0x24) + 0x24) * D_L07_001B0FD0;
        MoveHomingBombTowardTarget(moby, (float *)gHeroPosition);
        SpawnFallingParticlePuff(moby);
        hitCount = ProcessCollisionHit(moby + 0x10, 0.333f, 0, (char *)moby, 0);
        if (hitCount > 0) {
            hitCursor = (u8 *)D_L07_001C36C0;
            for (remaining = hitCount; remaining != 0; remaining--, hitCursor += 4) {
                u8 *other = *(u8 **)hitCursor;
                if (other == moby)
                    continue;
                if (other != *(u8 **)(moby + 0xB8))
                    SetMobyState(moby, 3, -1);
            }
        }
        break;
    case 3:
        PlaySoundFromClassBank(6, 0, (char *)moby, 0xE5F);
        pos = (char *)moby + 0x10;
        SweepCollisionFromObject((char *)moby, pos, 0x10000, 6.0f, 5.0f, 1.0f, 0, 1, 0);
        SweepCollisionFromObject((char *)moby, pos, 1, 4.0f, (f32)vars[0x34], 1.0f, 0, 1, 0);
        FastVecSub(dir, D_L07_001B9200, pos);
        vec_scale_to_length(dir, dir, 1.0f);
        SpawnBlastEffectMoby((char *)moby, pos, (char *)dir, 0.0f);
        tuningBase = D_L07_001B9200 - 0x140;
        *(f32 *)(tuningBase + 0x180) = 0.1f;
        *(s32 *)(tuningBase + 0x188) = 0x5A;
        *(f32 *)(tuningBase + 0x160) = 0.2f;
        *(s32 *)(tuningBase + 0x168) = 0x3C;
        *(s32 *)(tuningBase + 0x16C) = 0;
        *(s32 *)(moby + 0x98) = 0;
        *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
        SetMobyState(moby, 1, -1);
        break;
    }
}
