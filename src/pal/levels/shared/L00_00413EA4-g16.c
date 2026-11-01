#include "include_asm.h"

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
    Moby *target;
    int lockTimer;
    float lockHeight;
    s16 light;
    s16 flash;
    Moby *candidate;
    int candidateTimer;
    s16 aiming;
    s16 charge;
    float cooldown;
    int unknown20;
    int sound;
    int beam;
    int beamTimer;
    int chargeSound;
    int unknown34;
} BlasterVars;
typedef struct { u8 pad00[4]; u8 active; u8 pad05[0x13]; Moby *owner; u8 pad1C[0x54]; } SoundSlot;
typedef struct { u8 pad00[0x54]; float rate; u8 pad58[0x88]; } WeaponEntry;
typedef struct { int unknown00[6]; Moby *hit; } CollisionResult;
extern u8 D_00189E20[], D_00139568[];
extern u32 D_00138180[];
extern int D_00139688[];
extern u16 D_0018C958[];
extern SoundSlot D_00188660[];
extern int D_L00_001A8F00 MACRO_ADDR;
extern Vector D_L00_001B1270 __attribute__((sda));
extern float D_L00_001B8DC0[];
extern Moby *D_L00_001C3280[];
extern CollisionResult D_L00_001BF200;
extern WeaponEntry D_00262570[];
extern u8 D_0029FCC8[];
extern void func_PAL_L00_002C4480(int, int);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002829D8(void *);
extern void func_002A75E0(void *, int, int, int, int);
extern int func_L00_002D4040(int);
extern void func_00273318(void *, float, unsigned int, void *, int, float, int, float, int);
extern Moby *func_L00_00324D18(void *, void *, float, float, float, float, float, int);
extern float *func_002AB1F0(Moby *);
extern int func_002ABB78(Moby *);
extern float func_00282E48(void *, void *);
extern float func_00282C48(float);
extern int func_00282948(int *);
extern int func_002E5CF8(int, int, void *);
extern void func_002E59F8(int);
extern void ref_L00_0040F6A0_00(void (*)(Moby *), Moby *);
extern void func_PAL_L00_00415498(Moby *);
extern float func_002A7940(void);
extern void func_002ACEC0(void *, void *, void *, float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern int func_00283CF0(float);
extern void *func_PAL_002C23B8(void *, void *, int, int, unsigned int, int, float, float, float, float, float);
extern int func_PAL_L00_00415648(Moby *);
extern int func_00277F48(float, void *, int, void *, void *);
extern void func_PAL_L00_00415690(Moby *, int);
extern void func_PAL_L00_00415238(Moby *, Vector *, int);
extern void func_PAL_L00_002AF458(void);
extern int func_L00_002D6998(void *);
extern int func_PAL_00289730(int, int);
extern void func_L00_002D6B70(int);
extern void func_PAL_L00_00415310(Moby *, Vector *);
extern void func_PAL_L00_00414F80(Moby *, Vector *);
#define HERO ((Hero *)D_00189E20)

/* Charges and fires the blaster: target acquisition, charge sparks and release. */
void func_PAL_L00_004144A8(Moby *moby)
{
    BlasterVars *vars = moby->vars;
    Vector nozzle, direction, origin, aim, work, spark;
    int ready, released, charged;
    float spread;
    Moby *candidate; /* the cone pick, then the locked target */

    if (moby->state == 0) {
        moby->state = 1;
        vars->light = -1;
        vars->candidateTimer = 4;
        vars->flash = 0;
        vars->target = 0;
        vars->candidate = 0;
        vars->aiming = 0;
        vars->charge = 0;
        vars->unknown20 = 0;
        vars->sound = -1;
        vars->unknown34 = -1;
        vars->beam = -1;
        vars->chargeSound = -1;
    }
    if (HERO->i[0x2294 / 4] == 1)
        func_PAL_L00_002C4480(0x1D, 1);
    func_00283098(&nozzle, &D_L00_001B1270, &moby->right);
    func_00282CC0(&nozzle, &nozzle, &moby->position);
    if (HERO->i[0x1450 / 4] != 0)
        HERO->i[0xBF8 / 4] = HERO->i[0x1450 / 4];

    if (HERO->i[0x2294 / 4] == 0x1D && (*(u16 *)(HERO->ptr[0x2290 / 4] + 0x34) & 1)) {
        unsigned int color;
        if (vars->aiming == 0) {
            vars->target = 0;
            vars->candidateTimer = 4;
        }
        vars->aiming = 1;
        spread = 0.06981317699f;
        if (vars->cooldown > 0.0f && func_L00_002D4040(-1))
            color = 0x600000FF;
        else
            color = 0x600FFF0F;
        func_00273318(moby, 1.25f, color, 0, 0x27, 0.0f, -1, 90.0f, 4);
        qcopy(&direction, &HERO->q[0x760 / 16]);
        func_00282D30(&origin, HERO->ptr[0x2290 / 4] + 0xE0, 0.75f);
        func_00282CC0(&origin, &HERO->q[0x80 / 16], &origin);
    } else {
        vars->aiming = 0;
        spread = 0.349065899848938f;
        if (HERO->h[0x24EC / 2] != 0) {
            func_00282D30(&direction, &moby->forward, -1.0f);
            } else {
            qcopy(&direction, &HERO->q[0x760 / 16]);
            }
        func_00282D30(&origin, HERO->ptr[0x2290 / 4] + 0xE0, 0.75f);
        func_00282CC0(&origin, &HERO->q[0x80 / 16], &origin);
    }
    func_002829D8(&vars->cooldown);
    if (moby->animation == moby->nextAnimation && (moby->flags & 2))
        func_002A75E0(moby, 1, 0, 2, 0);
    candidate = func_L00_00324D18(&origin, &direction, spread, spread, 75.0f, spread, spread, 1);

    if (vars->target != 0) {
        float *hp = func_002AB1F0(vars->target);
        if (vars->target == 0 || vars->target->state == 0xFE || vars->target->state == 0xFD ||
            (hp != 0 && *hp <= 0.0f) || vars->target->alive == 0 || HERO->h[0x24EC / 2] != 0) {
            vars->target = 0;
            vars->candidateTimer = 4;
        } else if (candidate != vars->target) {
            if (func_00282948(&vars->lockTimer)) {
                vars->target = 0;
                vars->candidateTimer = 4;
            }
        } else {
            float distance;
            vars->lockTimer = 4;
            distance = func_00282E48(D_L00_001B8DC0, &candidate->position) * 0.006666667f;
            func_00282D30(&aim, &candidate->up, vars->lockHeight);
            func_00282CC0(&aim, &candidate->position, &aim);
            func_00273318(moby, func_00282C48(0.9f - distance * 0.65f), 0xFF0FFF0F, &aim, 0x26, 0.0f, -1, 90.0f, 4);
            HERO->ptr[0xBF8 / 4] = (char *)candidate;
        }
    } else if (candidate == vars->candidate) {
        if (func_00282948(&vars->candidateTimer)) {
            float *health;
            vars->target = candidate;
            vars->lockTimer = 4;
            health = func_002AB1F0(candidate);
            if (health == 0)
                vars->lockHeight = 0.1f;
            else
                vars->lockHeight = health[4];
        }
    } else {
        vars->candidateTimer = 4;
    }
    vars->candidate = candidate;
    candidate = vars->target;

    ready = 1;
    if (HERO->i[0x2294 / 4] == 0x1D) {
        if (!func_00282948(&HERO->i[0x2534 / 4]))
            ready = 0;
    } else {
        HERO->i[0x2534 / 4] = 0x21;
    }

    released = 0;
    charged = 0;
    if ((D_00138180[0x1A0 / 4] & HERO->u[0x1230 / 4]) && func_L00_002D4040(-1)) {
        SoundSlot *slot = &D_00188660[vars->chargeSound];
        int level;
        vars->charge++;
        if (slot[1].owner != moby || !slot[1].active)
            vars->chargeSound = func_002E5CF8(6, 4, moby);
        ref_L00_0040F6A0_00(func_PAL_L00_00415498, moby);
        level = D_00139688[HERO->i[0x1248 / 4]];
        if (level >= 5)
            level = 4;
        if (level * 18 < vars->charge) {
            float size;
            int life;
            func_002ACEC0(&work, &moby->up, &moby->forward, func_002A7940());
            func_00282D30(&work, &work, func_002A7878(1.5f, 2.0f) * 0.020000001f);
            life = func_00283CF0(func_002A78D8(1.0f, 3.0f));
            size = func_002A7878(0.45f, 0.75f) * 210000.0f;
            spark.f[0] = nozzle.f[0] + func_002A78D8(0.0f, 0.1f);
            spark.f[1] = nozzle.f[1] + func_002A78D8(0.0f, 0.1f);
            spark.f[2] = nozzle.f[2] + func_002A78D8(0.0f, 0.1f);
            func_PAL_002C23B8(&spark, &work, 12, 0x7F, 0x7F7F7F, life, size, 500.0f, 1.0f, 0.0f, 0.0f);
        }
    } else {
        if (vars->chargeSound != -1) {
            SoundSlot *slot = &D_00188660[vars->chargeSound];
            if (slot[1].owner == moby && slot[1].active)
                func_002E59F8(vars->chargeSound);
        }
        vars->chargeSound = -1;
        if ((D_00138180[0x1A4 / 4] & HERO->u[0x1230 / 4]) && !func_L00_002D4040(-1))
            func_002E5CF8(1, 0, moby);
        if (vars->charge != 0) {
            released = 1;
            charged = func_PAL_L00_00415648(moby);
        }
        vars->charge = 0;
        vars->unknown20 = 0;
    }

    if (D_L00_001A8F00 == 0 && vars->cooldown == 0.0f && HERO->b[0x22BC] == 0 && ready && released &&
        HERO->i[0x1240 / 4] >= 19) {
        if (func_L00_002D4040(-1)) {
            if (candidate == 0) {
                int count, i;
                func_00282D30(&work, &moby->forward, -1.0f);
                func_00282CC0(&work, &work, &moby->position);
                func_00282D30(&spark, &moby->right, 0.275f);
                func_00282CC0(&work, &work, &spark);
                count = func_00277F48(1.0f, &work, 1, HERO->ptr[0x2290 / 4], 0);
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
            vars->flash = 12;
            func_PAL_L00_00415690(moby, charged);
            func_PAL_L00_00415238(moby, &nozzle, charged);
            func_002A75E0(moby, 2, 0, 2, 0);
            func_PAL_L00_002AF458();
            vars->sound = func_L00_002D6998(D_0029FCC8);
            if (charged)
                D_0018C958[0x3A8 / 2] = 0xFFFF;
            else if (D_0018C958[0x3A8 / 2] < 40 && ++D_0018C958[0x3A8 / 2] == 40)
                func_PAL_00289730(0x9F7, 0x4E);
        }
        if (!((D_00138180[0x1A0 / 4] & HERO->u[0x1230 / 4]) && func_L00_002D4040(-1) && HERO->b[0x22B8]) &&
            vars->sound >= 0) {
            func_L00_002D6B70(vars->sound);
            vars->sound = -1;
        }
        {
            WeaponEntry *weapon = D_00262570 + D_00139568[0x1B];
            vars->cooldown = 1.0f / weapon->rate;
        }
    }

    if (vars->beam >= 0 && func_00282948(&vars->beamTimer))
        func_PAL_L00_00415310(moby, &nozzle);
    func_PAL_L00_00414F80(moby, &nozzle);
}
