/* Near miss: unit of its own, -O2 -G0 -ffunction-sections -g -frac2-hazard-labels. us 0/27, 2708/2708 bytes,
 * 6 raw lines: one insn out of place. PAL has no such function. Measured 2026-11-01:
 * func_002829D8 returns int; declaring it void was the whole of the old +0x88 $v0/$v1 swap, so no pin is needed.
 * The label before the row loop is 8-aligned, so its nop came back with the size.
 * `o = &origin` set before the aim arm's qcopy gives retail's size and the cross-jump, with no always-true test.
 * Left: retail has `addiu s1, sp, 0x10` after the lq/sq and `lw a1`; here it stays above the qcopy. Set after
 * the qcopy, the size falls to 2700. qcopy_nc changes nothing, a TImode copy moves other rows.
 * 2026-11-01: set after the qcopy, sched2 gives retail's order (lw a1, addiu s1, const, a0), but jump2 merges the
 * arms from `daddu a0, s1` back to front and reorg then takes `addiu s1` over the two-word const into the `b` slot,
 * so the shared tail starts one insn early (2700). Retail keeps s1 in place and has a0 in the slot. Above the qcopy
 * the volatile asm stops reorg's scan, which is why that spelling gets the size. So either something stops the
 * scan in retail or a0 is not merged there; a shared `point` local in both arms keeps the order but stops the
 * cross-jump (2732). Not the arm order: sched2's a0 has priority 6 against the const's 7 here.
 */
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

extern void func_L00_003A41F0(Moby *);
extern int func_002829D8(void *);
extern void func_L00_002C42E0(int, int);
extern void func_002A75E0(void *, int, int, int, int);
extern void func_002A7470(void *, int, int, int);
extern int func_L00_002D4040(int);
extern int func_L00_002D3F30(int, int);
extern void func_00273318(void *, float, unsigned int, void *, int, float, int, float, int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern Moby *func_L00_00324D18(void *, void *, float, float, float, float, float, int);
extern float *func_002AB1F0(Moby *);
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


#define HERO ((Hero *)D_00189E20)

/* Acquires a stable target, fires and drives the short muzzle light. */
void func_L00_003A48D0(Moby *moby)
{
    Vector *o;
    TurretVars *vars = moby->vars;
    Vector direction, origin, aim, muzzle, offset, lift;
    float horizontal, vertical;
    Moby *candidate;
    int ready;
    Vector *point;

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
        o = &origin;
        qcopy(&direction, &HERO->q[0x760 / 16]);
        func_00282D30(&origin, HERO->ptr[0x2290 / 4] + 0xE0, 0.75f);
        func_00282CC0(&origin, &HERO->q[0x80 / 16], o);
        point = &origin;
    } else {
        vars->aiming = 0;
        horizontal = 0.3141593039f;
        vertical = 0.2967059910f;
        if (HERO->h[0x24EC / 2] != 0)
            func_00282D30(&direction, &moby->forward, -1.0f);
        else
            qcopy(&direction, &HERO->q[0x760 / 16]);
        { Vector *o = &origin;
        func_00282D30(o, HERO->ptr[0x2290 / 4] + 0xE0, 0.75f);
        func_00282CC0(o, &HERO->q[0x80 / 16], o);
        point = o; }
    }
    candidate = func_L00_00324D18(point, &direction, horizontal, vertical, 75.0f, horizontal, horizontal, 1);

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
                        Moby *hit = D_L00_001C3280[i];
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
            vars->sound = func_L00_002D6998(D_00294880);
            {
                WeaponEntry *weapon = D_00262570 + D_00139568[0x1B];
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
        Vector *off;
        Vector *pos;
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
            qcopy(&offset, &HERO->q[0x760 / 16]);
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
            MuzzleLight *light = &D_L00_001C6F40[vars->light];
            qcopy(&light->position, pos);
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
