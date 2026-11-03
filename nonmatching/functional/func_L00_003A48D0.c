/* functional: high. From the 2708/2708-byte near miss (one instruction out of place); the matching-only spellings (qcopy asm, the early `o` pointer) are plain C here. */
/*
 * func_L00_003A48D0 (2708 bytes): the hover/turret gadget's update. Picks a
 * target with the cone search func_L00_00324D18 (aimed from the camera when
 * the hero is in mode 0x1D), holds the lock with countdown timers and draws
 * the lock marker, fires (func_002E5CF8, sound, cooldown 1/rate from the
 * weapon table) on the fire button, falls back to a sphere query for a target
 * when nothing is locked, and drives the short muzzle light (func_L00_002FCF18
 * / D_L00_001C6F40) while the flash counter runs.
 */
#include "common.h"

typedef struct { float f[4]; } __attribute__((aligned(16))) Vector_3A48D0;
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; char *ptr[0x980]; Vector_3A48D0 q[0x260]; } Hero_3A48D0;

typedef struct Moby_3A48D0 Moby_3A48D0;
struct Moby_3A48D0 {
    u8 pad00[0x10];
    Vector_3A48D0 position;
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
    Vector_3A48D0 right;
    Vector_3A48D0 forward;
    Vector_3A48D0 up;
};

typedef struct {
    float cooldown;
    u8 pad04[0xC];
    Moby_3A48D0 *target;
    int lockTimer;
    float lockHeight;
    s16 light;
    s16 flash;
    Moby_3A48D0 *candidate;
    int candidateTimer;
    int aiming;
    int sound;
} TurretVars_3A48D0;

typedef struct { float radius, spread, power, reserved; Vector_3A48D0 position; } MuzzleLight_3A48D0;
typedef struct { u8 pad00[0x54]; float rate; u8 pad58[0x88]; } WeaponEntry_3A48D0;
typedef struct { int unknown00[6]; Moby_3A48D0 *hit; } CollisionResult_3A48D0;

extern u8 D_00189E20[], D_00139568[];
extern u32 D_00138180[];
extern int D_L00_001A8F00 MACRO_ADDR;
extern int D_L00_001B2864 MACRO_ADDR;
extern float D_L00_001B8DC0[];
extern Moby_3A48D0 *D_L00_001C3280[];
extern CollisionResult_3A48D0 D_L00_001BF200;
extern MuzzleLight_3A48D0 D_L00_001C6F40[];
extern WeaponEntry_3A48D0 D_L00_00262570[];
extern u8 D_L00_00294880[];

extern void func_L00_003A41F0(Moby_3A48D0 *);
extern int func_002829D8(void *);
extern void func_L00_002C42E0(int, int);
extern void func_002A75E0(void *, int, int, int, int);
extern void func_002A7470(void *, int, int, int);
extern int func_L00_002D4040(int);
extern int func_L00_002D3F30(int, int);
extern void func_00273318(void *, float, unsigned int, void *, int, float, int, float, int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern Moby_3A48D0 *func_L00_00324D18(void *, void *, int, float, float, float, float, float);
extern float *func_002AB1F0(Moby_3A48D0 *);
extern int func_002ABB78(Moby_3A48D0 *);
extern float func_00282E48(void *, void *);
extern float func_00282C48(float);
extern float func_00283CE0(int);
extern int func_00282948(int *);
extern int func_00282978(short *);
extern int func_002E5CF8(int, int, void *);
extern int func_00277F48(float, void *, int, void *, void *);
extern void func_L00_003A4480(Moby_3A48D0 *);
extern void func_L00_003A5370(Moby_3A48D0 *);
extern void func_L00_002D2168(int, int, float);
extern void func_L00_002AF568(void);
extern void func_L00_002D6B70(int);
extern int func_L00_002D6998(void *);
extern void func_0029FCC0(void *, int, void *);
extern int func_L00_002FCF18(void *, float, float, float, float, float);
extern void func_00291450(int);


#define HERO ((Hero_3A48D0 *)D_00189E20)

/* Acquires a stable target, fires and drives the short muzzle light. */
void func_L00_003A48D0(Moby_3A48D0 *moby)
{
    TurretVars_3A48D0 *vars = moby->vars;
    Vector_3A48D0 direction, origin, aim, muzzle, offset, lift;
    float horizontal, vertical;
    Moby_3A48D0 *candidate;
    int ready;
    Vector_3A48D0 *point;

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
    func_L00_003A41F0(moby);
    func_002829D8(vars);
    if (HERO->i[0x2294 / 4] == 1)
        func_L00_002C42E0(0x1D, 1);
    if (moby->animation == moby->nextAnimation && (moby->flags & 2))
        func_002A75E0(moby, 1, 0, 2, 0);
    if (HERO->i[0x1450 / 4] != 0)
        HERO->i[0xBF8 / 4] = HERO->i[0x1450 / 4];

    if (HERO->i[0x2294 / 4] == 0x1D && (*(u16 *)(HERO->ptr[0x2290 / 4] + 0x34) & 1)) {
        unsigned int color;
        if (vars->aiming == 0) {
            vars->target = 0;
            vars->candidateTimer = 5;
        }
        vars->aiming = 1;
        horizontal = vertical = 0.06981317699f;
        if (vars->cooldown > 0.0f && func_L00_002D4040(-1))
            color = 0x600000FF;
        else
            color = 0x600FFF0F;
        func_00273318(moby, 1.25f, color, 0, 0x27, 0.0f, -1, 90.0f, 4);
        direction = HERO->q[0x760 / 16];
        func_00282D30(&origin, HERO->ptr[0x2290 / 4] + 0xE0, 0.75f);
        func_00282CC0(&origin, &HERO->q[0x80 / 16], &origin);
        point = &origin;
    } else {
        vars->aiming = 0;
        horizontal = 0.3141593039f;
        vertical = 0.2967059910f;
        if (HERO->h[0x24EC / 2] != 0)
            func_00282D30(&direction, &moby->forward, -1.0f);
        else
            direction = HERO->q[0x760 / 16];
        func_00282D30(&origin, HERO->ptr[0x2290 / 4] + 0xE0, 0.75f);
        func_00282CC0(&origin, &HERO->q[0x80 / 16], &origin);
        point = &origin;
    }
    candidate = func_L00_00324D18(point, &direction, 1, horizontal, vertical, 75.0f, horizontal, horizontal);

    if (vars->target != 0) {
        float *hp = func_002AB1F0(vars->target);
        if (vars->target == 0 || vars->target->state == 0xFE || vars->target->state == 0xFD ||
            (hp != 0 && *hp <= 0.0f) || vars->target->alive == 0 || HERO->h[0x24EC / 2] != 0) {
            vars->target = 0;
            vars->candidateTimer = 5;
        } else if (candidate != vars->target) {
            if (func_00282948(&vars->lockTimer)) {
                vars->target = 0;
                vars->candidateTimer = 5;
            }
        } else {
            float distance;
            float *health;
            vars->lockTimer = 5;
            distance = func_00282E48(D_L00_001B8DC0, &candidate->position) * 0.006666667f;
            health = func_002AB1F0(candidate);
            vars->lockHeight = health ? health[4] : 0.1f;
            func_00282D30(&aim, &candidate->up, vars->lockHeight);
            func_00282CC0(&aim, &candidate->position, &aim);
            func_00273318(moby, func_00282C48(0.9f - distance * 0.65f), 0xFF0FFF0F, &aim, 0x26, 0.0f, -1, 90.0f, 4);
            HERO->ptr[0xBF8 / 4] = (char *)candidate;
        }
    } else if (candidate == vars->candidate) {
        if (func_00282948(&vars->candidateTimer)) {
            float *health;
            vars->target = candidate;
            vars->lockTimer = 5;
            health = func_002AB1F0(candidate);
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
    if (HERO->i[0x2294 / 4] == 0x1D) {
        if (!func_00282948(&HERO->i[0x2534 / 4]))
            ready = 0;
    }
    else
        HERO->i[0x2534 / 4] = 0x28;

    if (D_L00_001A8F00 != 2 && vars->cooldown == 0.0f && HERO->b[0x22BC] == 0 && moby->animation < 2 &&
        (D_00138180[0x1A0 / 4] & HERO->u[0x1230 / 4]) && HERO->i[0x1240 / 4] >= 23 && ready) {
        if (moby->nextAnimation == 0)
            func_002A7470(moby, 1, 0, 4);
        if (func_L00_002D3F30(-1, 1)) {
            D_L00_001B2864 = 1;
            if (candidate == 0) {
                int count, i;
                func_00282D30(&muzzle, &moby->forward, -1.0f);
                func_00282CC0(&muzzle, &muzzle, &moby->position);
                func_00282D30(&offset, &moby->right, 0.275f);
                func_00282CC0(&muzzle, &muzzle, &offset);
                count = func_00277F48(1.0f, &muzzle, 1, HERO->ptr[0x2290 / 4], 0);
                if (count != 0) {
                    for (i = 0; i < count; i++) {
                        Moby_3A48D0 *hit = D_L00_001C3280[i];
                        float *hp = func_002AB1F0(hit);
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
                        if (hit->objectClass == 0xC87)
                            continue;
                        if (hit->objectClass == 0xECC)
                            continue;
                        if (hp == 0)
                            continue;
                        if (!(*hp > 0.0f) && !func_002ABB78(hit))
                            continue;
                        if (hit->model == 0 || hit->model->kind != 5) {
                            candidate = D_L00_001BF200.hit;
                            vars->target = candidate;
                            break;
                        }
                    }
                }
            }
            func_002E5CF8(0, 0, moby);
            vars->flash = 15;
            func_L00_003A4480(moby);
            func_L00_003A5370(moby);
            if (HERO->i[0x229C / 4] == 0 || (HERO->i[0x2294 / 4] == 2 && HERO->f[0x24B8 / 4] < 0.7f))
                func_L00_002D2168(0x36, 1, 10.0f);
            else
                func_L00_002AF568();
            func_002A7470(moby, 2, 0, 0);
            vars->sound = func_L00_002D6998(D_L00_00294880);
            {
                WeaponEntry_3A48D0 *weapon = D_L00_00262570 + D_00139568[0x1B];
                vars->cooldown = 1.0f / weapon->rate;
            }
        } else if ((D_00138180[0x1A4 / 4] & HERO->u[0x1230 / 4]) || D_L00_001B2864 == 1) {
            func_002E5CF8(1, 0, moby);
            D_L00_001B2864 = 0;
        }
        if (!((D_00138180[0x1A0 / 4] & HERO->u[0x1230 / 4]) && func_L00_002D4040(-1) && HERO->b[0x22B8]) &&
            vars->sound >= 0) {
            func_L00_002D6B70(vars->sound);
            vars->sound = -1;
        }
    }

    if (moby->animation != 2 && vars->flash > 0) {
        float alpha, width, power;
        Vector_3A48D0 *off;
        Vector_3A48D0 *pos;
        if (vars->flash >= 13) {
            float scale = 1.0f / func_00283CE0(3);
            alpha = func_00283CE0(15 - vars->flash) * scale;
            width = func_00283CE0(15 - vars->flash) * (scale * 0.8f);
            power = func_00283CE0(15 - vars->flash) * (scale * 0.5f);
        } else {
            float scale = 1.0f / func_00283CE0(12);
            alpha = func_00283CE0(vars->flash) * scale;
            width = func_00283CE0(vars->flash) * (scale * 0.8f);
            power = func_00283CE0(vars->flash) * (scale * 0.5f);
        }
        if (HERO->h[0x24EC / 2] != 0) {
            func_00282D30(&offset, &moby->forward, -1.0f);
            func_0029FCC0(moby, 0, &muzzle);
            pos = &muzzle;
            off = &offset;
        } else {
            offset = HERO->q[0x760 / 16];
            func_0029FCC0(moby, 0, &muzzle);
            pos = &muzzle;
            off = &offset;
        }
        func_00282CC0(pos, pos, off);
        func_00282D30(&lift, HERO->ptr[0x2290 / 4] + 0xE0, 0.3f);
        func_00282CC0(pos, pos, &lift);
        if (vars->light == -1) {
            vars->light = func_L00_002FCF18(pos, 8.0f, 0.0f, alpha, width, power);
        } else {
            MuzzleLight_3A48D0 *light = &D_L00_001C6F40[vars->light];
            light->position = *pos;
            light->position.f[3] = 8.0f;
            light->radius = alpha;
            light->spread = width;
            light->power = power;
        }
        func_00282978(&vars->flash);
    } else if (vars->light != -1) {
        func_00291450(vars->light);
        vars->light = -1;
        vars->flash = 0;
    }

    if (moby->nextAnimation == 2) {
        if (vars->light != -1)
            func_00291450(vars->light);
        vars->light = -1;
        vars->flash = 0;
    }
}
