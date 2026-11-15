#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; char *ptr[0x980]; Quad q[0x260]; } Hero;

typedef struct Moby Moby;
struct Moby {
    u8 pad00[0x10];
    Vector position;
    u8 state;
    u8 pad21[3];
    struct { u8 pad00[0x46]; s16 kind; } *model;
    u8 pad28[9];
    u8 alive;
    s16 health;
    u8 pad34[0xE];
    u8 animation;
    u8 nextAnimation;
    u8 pad44[0x1C];
    u8 flags;
    u8 pad61[7];
    void *vars;
    u8 pad6C[0x3E];
    s16 objectClass;
    u8 padAC[0x14];
    Vector right;
    Vector forward;
    Vector up;
};

typedef struct {
    float cooldown;
    u8 pad04[0xC];
    Moby *target;
    int lockTimer;
    float lockHeight;
    s16 light;
    s16 flash;
    Moby *candidate;
    int candidateTimer;
    int aiming;
    int sound;
} TurretVars;

typedef struct { float radius, spread, power, reserved; Vector position; } MuzzleLight;
typedef struct { u8 pad00[0x54]; float rate; u8 pad58[0x88]; } WeaponEntry;
typedef struct { int unknown00[6]; Moby *hit; } CollisionResult;

extern u8 D_00189E20[], D_00139568[];
extern Vector D_00189EA0;
extern u32 D_00138180[];
extern int D_L00_001A8F00 MACRO_ADDR;
extern int D_L00_001B2864 MACRO_ADDR;
extern float D_L00_001B8DC0[];
extern Moby *D_L00_001C3280[];
extern CollisionResult D_L00_001BF200;
extern MuzzleLight D_L00_001C6F40[];
extern WeaponEntry D_00262570[];
extern u8 D_00294880[];

extern void func_L00_003A41F0(void *);
extern int func_002829D8(void *);
extern int func_L00_002C42E0(int, int);
extern void func_002A75E0(void *, int, int, int, int);
extern void func_002A7470(void *, int, int, int);
extern int func_L00_002D4040(int);
extern int func_L00_002D3F30(int, int);
extern void func_00273318(void *, float, unsigned int, void *, int, float, int, float, int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern Moby *func_L00_00324D18(void *, void *, float, float, float, float, float, int);
extern int func_002AB1F0(Moby *);
extern int func_002ABB78(Moby *);
extern float func_00282E48(void *, void *);
extern float func_00282C48(float);
extern float func_00283CE0(int);
extern int func_00282948(int *);
extern int func_00282978(short *);
extern int func_002E5CF8(int, int, void *);
extern int func_00277F48(float, void *, int, void *, void *);
extern void func_L00_003A4480(Moby *);
extern void func_L00_003A5370(Moby *);
extern void func_L00_002D2168(int, int, float);
extern void func_L00_002AF568(void);
extern void func_L00_002D6B70(int);
extern int func_L00_002D6998(void *);
extern void func_0029FCC0(void *, int, void *);
extern int func_L00_002FCF18(void *, float, float, float, float, float);
extern void func_00291450(int);


/* Acquires a stable target, fires and drives the short muzzle light. */
/* Per-frame update for the Minirocket Tube moby: locks onto an enemy, fires a rocket and flashes the muzzle light. */
void func_L00_003A48D0(Moby *moby)
{
    TurretVars *vars = moby->vars;
    Vector direction, origin, aim, muzzle, offset, lift;
    float horizontal, vertical;
    Moby *candidate;
    int ready;

    if (moby->state == 0) {
        moby->state = 1;
        vars->light = -1;
        vars->candidateTimer = 5;
        vars->sound = -1;
        vars->flash = 0;
        vars->target = 0;
        vars->candidate = 0;
        vars->aiming = 0;
    }
    EmitLayeredSparks(moby);
    FastVectorHelperB(vars);
    if (((Hero *)gHeroState)->i[0x2294 / 4] == 1)
        SetHeroAction_L00(0x1D, 1);
    if (moby->animation == moby->nextAnimation && (moby->flags & 2))
        StartAnimationBlendedWithFlags(moby, 1, 0, 2, 0);
    if (((Hero *)gHeroState)->i[0x1450 / 4] != 0)
        ((Hero *)gHeroState)->i[0xBF8 / 4] = ((Hero *)gHeroState)->i[0x1450 / 4];

    if (((Hero *)gHeroState)->i[0x2294 / 4] == 0x1D && (*(u16 *)(((Hero *)gHeroState)->ptr[0x2290 / 4] + 0x34) & 1)) {
        unsigned int color;
        if (vars->aiming == 0) {
            vars->target = 0;
            vars->candidateTimer = 5;
        }
        vars->aiming = 1;
        horizontal = vertical = 0.06981317699f;
        if (vars->cooldown > 0.0f && get_ammo(-1))
            color = 0x600000FF;
        else
            color = 0x600FFF0F;
        AddMobyMarker(moby, 1.25f, color, 0, 0x27, 0.0f, -1, 90.0f, 4);
        qcopy(&direction, &((Hero *)gHeroState)->q[0x760 / 16]);
        FastVecScale(&origin, ((Hero *)gHeroState)->ptr[0x2290 / 4] + 0xE0, 0.75f);
        FastVecAdd(&origin, &((Hero *)gHeroState)->q[0x80 / 16], &origin);
    } else {
        vars->aiming = 0;
        horizontal = 0.3141593039f;
        vertical = 0.2967059910f;
        if (((Hero *)gHeroState)->h[0x24EC / 2] != 0)
            FastVecScale(&direction, &moby->forward, -1.0f);
        else
            qcopy(&direction, &((Hero *)gHeroState)->q[0x760 / 16]);
        FastVecScale(&origin, ((Hero *)gHeroState)->ptr[0x2290 / 4] + 0xE0, 0.75f);
        FastVecAdd(&origin, &((Hero *)gHeroState)->q[0x80 / 16], &origin);
    }
    candidate = GetOrFindTargetMoby(&origin, &direction, horizontal, vertical, 75.0f, horizontal, horizontal, 1);

    if (vars->target != 0) {
        float *hp = ((float *)GetMobyPrivateValue0(vars->target));
        if (vars->target == 0 || vars->target->state == 0xFE || vars->target->state == 0xFD ||
            (hp != 0 && *hp <= 0.0f) || vars->target->alive == 0 || ((Hero *)gHeroState)->h[0x24EC / 2] != 0) {
            vars->target = 0;
            vars->candidateTimer = 5;
        } else if (candidate != vars->target) {
            if (FastFloatHelperD(&vars->lockTimer)) {
                vars->target = 0;
                vars->candidateTimer = 5;
            }
        } else {
            float distance;
            float *health;
            vars->lockTimer = 5;
            distance = fast_vec_dist(gCameraPosition_L00, &candidate->position) * 0.006666667f;
            health = ((float *)GetMobyPrivateValue0(candidate));
            vars->lockHeight = health ? health[4] : 0.1f;
            FastVecScale(&aim, &candidate->up, vars->lockHeight);
            FastVecAdd(&aim, &candidate->position, &aim);
            AddMobyMarker(moby, FloatAbs(0.9f - distance * 0.65f), 0xFF0FFF0F, &aim, 0x26, 0.0f, -1, 90.0f, 4);
            ((Hero *)gHeroState)->ptr[0xBF8 / 4] = (char *)candidate;
        }
    } else if (candidate == vars->candidate) {
        if (FastFloatHelperD(&vars->candidateTimer)) {
            float *health;
            vars->target = candidate;
            vars->lockTimer = 5;
            health = ((float *)GetMobyPrivateValue0(candidate));
            if (health == 0)
                vars->lockHeight = 0.1f;
            else
                vars->lockHeight = health[4];
        }
    } else {
        vars->candidateTimer = 5;
    }
    vars->candidate = candidate;
    candidate = vars->target;

    ready = 1;
    if (((Hero *)gHeroState)->i[0x2294 / 4] == 0x1D) {
        if (!FastFloatHelperD(&((Hero *)gHeroState)->i[0x2534 / 4]))
            ready = 0;
    }
    else
        ((Hero *)gHeroState)->i[0x2534 / 4] = 0x28;

    if (D_L00_001A8F00 != 2 && vars->cooldown == 0.0f && ((Hero *)gHeroState)->b[0x22BC] == 0 && moby->animation < 2 &&
        (gPadState[0x1A0 / 4] & ((Hero *)gHeroState)->u[0x1230 / 4]) && ((Hero *)gHeroState)->i[0x1240 / 4] >= 23 && ready) {
        if (moby->nextAnimation == 0)
            StartAnimationBlended(moby, 1, 0, 4);
        if (SpendWeaponAmmo(-1, 1)) {
            D_L00_001B2864 = 1;
            if (candidate == 0) {
                int count, i;
                FastVecScale(&muzzle, &moby->forward, -1.0f);
                FastVecAdd(&muzzle, &muzzle, &moby->position);
                FastVecScale(&offset, &moby->right, 0.275f);
                FastVecAdd(&muzzle, &muzzle, &offset);
                count = ProcessCollisionHit(1.0f, &muzzle, 1, ((Hero *)gHeroState)->ptr[0x2290 / 4], 0);
                if (count != 0) {
                    for (i = 0; i < count; i++) {
                        Moby *hit = gAreaHitTargets[i];
                        float *hp = ((float *)GetMobyPrivateValue0(hit));
                        if (hit->alive == 0)
                            continue;
                        if (hit->health <= 0)
                            continue;
                        if (hit == 0)
                            continue;
                        if (hit->state == 0xFE)
                            continue;
                        if (hit->state == 0xFD)
                            continue;
                        if (hit->objectClass == 0xC87 /* moby class 3207 */)
                            continue;
                        if (hit->objectClass == 0xECC /* moby class 3788 */)
                            continue;
                        if (hp == 0)
                            continue;
                        if (!(*hp > 0.0f) && !IsMobyInSpecialClassRange(hit))
                            continue;
                        if (hit->model == 0 || hit->model->kind != 5) {
                            candidate = gCollisionResult.hit;
                            vars->target = candidate;
                            break;
                        }
                    }
                }
            }
            PlayMobySound(0, 0, moby);
            vars->flash = 15;
            SpawnFragmentFanAndSmoke(moby);
            SpawnWeaponMuzzleEffect(moby);
            if (((Hero *)gHeroState)->i[0x229C / 4] == 0 || (((Hero *)gHeroState)->i[0x2294 / 4] == 2 && ((Hero *)gHeroState)->f[0x24B8 / 4] < 0.7f))
                set_hero_animation(0x36, 1, 10.0f);
            else
                start_equipped_item_animation();
            StartAnimationBlended(moby, 2, 0, 0);
            vars->sound = CopyRecordsToFreeSlots(D_00294880);
            {
                WeaponEntry *weapon = D_00262570 + gItemSlotToRecord[0x1B];
                vars->cooldown = 1.0f / weapon->rate;
            }
        } else if ((gPadState[0x1A4 / 4] & ((Hero *)gHeroState)->u[0x1230 / 4]) || D_L00_001B2864 == 1) {
            PlayMobySound(1, 0, moby);
            D_L00_001B2864 = 0;
        }
        if (!((gPadState[0x1A0 / 4] & ((Hero *)gHeroState)->u[0x1230 / 4]) && get_ammo(-1) && ((Hero *)gHeroState)->b[0x22B8]) &&
            vars->sound >= 0) {
            ResetActiveSlots(vars->sound);
            vars->sound = -1;
        }
    }

    if (moby->animation != 2 && vars->flash > 0) {
        float alpha, width, power;
        Vector *off;
        Vector *pos;
        if (vars->flash >= 13) {
            float scale = 1.0f / IntToFloat(3);
            alpha = IntToFloat(15 - vars->flash) * scale;
            width = IntToFloat(15 - vars->flash) * (scale * 0.8f);
            power = IntToFloat(15 - vars->flash) * (scale * 0.5f);
        } else {
            float scale = 1.0f / IntToFloat(12);
            alpha = IntToFloat(vars->flash) * scale;
            width = IntToFloat(vars->flash) * (scale * 0.8f);
            power = IntToFloat(vars->flash) * (scale * 0.5f);
        }
        if (((Hero *)gHeroState)->h[0x24EC / 2] != 0) {
            FastVecScale(&offset, &moby->forward, -1.0f);
            TransformMobyJointToWorld(moby, 0, &muzzle);
            pos = &muzzle;
            off = &offset;
        } else {
            qcopy(&offset, &((Hero *)gHeroState)->q[0x760 / 16]);
            TransformMobyJointToWorld(moby, 0, &muzzle);
            pos = &muzzle;
            off = &offset;
        }
        FastVecAdd(pos, pos, off);
        FastVecScale(&lift, ((Hero *)gHeroState)->ptr[0x2290 / 4] + 0xE0, 0.3f);
        FastVecAdd(pos, pos, &lift);
        if (vars->light == -1) {
            vars->light = AllocateEffectSlot_L00_2(pos, 8.0f, 0.0f, alpha, width, power);
        } else {
            MuzzleLight *light = &D_L00_001C6F40[vars->light];
            qcopy(&light->position, pos);
            light->position.f[3] = 8.0f;
            light->radius = alpha;
            light->spread = width;
            light->power = power;
        }
        FastDecTimer(&vars->flash);
    } else if (vars->light != -1) {
        FreePointLight(vars->light);
        vars->light = -1;
        vars->flash = 0;
    }

    if (moby->nextAnimation == 2) {
        if (vars->light != -1)
            FreePointLight(vars->light);
        vars->light = -1;
        vars->flash = 0;
    }
}
