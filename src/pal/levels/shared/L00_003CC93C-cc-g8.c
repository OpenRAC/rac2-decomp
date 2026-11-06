/* func_PAL_L00_003CC93C, the PAL copy of func_L00_003C8A90: the same C, where rename-macro func_L03_002C6F08 and rename func_L00_002C42E0 become func_PAL_L00_002C4480; rename func_L00_002AF568 becomes func_PAL_L00_002AF458; rename func_L00_003C94D8 becomes func_PAL_L00_003CD388; rename func_L00_00409E48 becomes func_PAL_L00_0040E9F0; rename func_L00_002AF7D0 becomes func_PAL_L00_002AF6C0. */
/* func_PAL_L00_003CC93C (UpdateLockOnWeapon): gathers the mobys in a cone ahead of the weapon, marks
 * each one, fires a shot at the target with a cooldown from the weapon table and sets a muzzle
 * light. It needs its own unit for -frac2-zero-ti-por and -frac2-hazard-labels.
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
    u8 pad43[5];
    float scale;
    u8 pad4C[0x14];
    u8 flags;
    u8 pad61[7];
    void *vars;
    u8 pad6C[0x3E];
    s16 objectClass;
    u8 padAC[0xC];
    Moby *owner;
    u8 padBC[4];
    Vector right;
    Vector forward;
    Vector up;
};

typedef struct {
    float cooldown;
    u8 pad04[0xC];
    Moby *target;
    u8 pad14[8];
    s16 light;
    s16 timer;
    int unknown20;
    int sound;
} Vars;

typedef struct { float red, green, blue, pad0C; Vector pos; } Light;
typedef struct { u8 pad00[0x54]; float rate; u8 pad58[0x88]; } WeaponEntry;
typedef struct { int unknown00[6]; Moby *hit; } CollisionResult;
typedef struct { int a, b, c; } AimConfig;
typedef float Vec[4] __attribute__((aligned(16)));

extern u8 D_00189E20[];
extern u32 D_00138180[];
extern u8 D_00139568[];
extern int D_L00_001A8F00;
extern int D_L00_001B2AD0;
extern AimConfig D_L00_001B00F0;
extern float D_L00_001B8DC0[];
extern Moby *D_L00_001C3280[];
extern CollisionResult D_L00_001BF200;
extern WeaponEntry D_L00_00262570[];
extern Light D_L00_001C6F40[];
extern u8 D_L00_002960A0[];
extern u8 D_L00_001A8F20[] __attribute__((sda));

extern int func_002829D8(void *);
extern int func_PAL_L00_002C4480(int, int);
extern int func_00282948(void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282A88(void *, int);
extern void func_L00_0037E000(void *);
extern char *func_002AF580(void *, void *, float, float, void *, void *, int, int, float, float, float, int, void *);
extern int func_002AB1F0(void *);
extern float func_00282E48(void *, void *);
extern float func_00282C48(float);
extern void func_00273318(void *, float, unsigned int, void *, int, float, int, float, int);
extern int func_L00_002D4040(int);
extern void func_PAL_L00_002AF458(void);
extern int func_00277F48(float, void *, int, void *, void *);
extern int func_002ABB78(void *);
extern int func_002E5CF8(int, int, void *);
extern void func_PAL_L00_003CD388(void *);
extern void func_002A75E0(void *, int, int, int, int);
extern int func_L00_002D6998(void *);
extern void func_00283098(void *, void *, void *);
extern int func_L00_0037DEF8(void *, void *, int, int *, int);
extern void func_L00_0037DD18(void *, void *, int);
extern Moby *func_PAL_L00_0040E9F0(void *, void *, void *, void *, float, float, float, float);
extern int func_L00_002D3F30(int, int);
extern void func_L00_002D6B70(int);
extern void func_PAL_L00_002AF6C0(void);
extern float func_00283CE0(int);
extern int func_L00_002FCF18(void *, float, float, float, float, float);
extern int func_00282978(void *);
extern void func_00291450(int);

#define HERO ((Hero *)D_00189E20)

static __inline__ void MarkTarget(void *moby, float alpha, unsigned int color, void *position, int kind, float a, int b, float c, int d)
{
    func_00273318(moby, alpha, color, position, kind, a, b, c, d);
}

void func_PAL_L00_003CC93C(Moby *moby)
{
    Vars *vars = moby->vars;
    Vector direction, origin, aim;
    Moby *list[32];
    int count;
    int ready;
    int i, j;
    Moby *target;
    int animation;
    Moby **mobys;

    if (moby->state == 0) {
        vars->timer = 0;
        vars->light = -1;
        vars->target = 0;
        vars->unknown20 = 0;
        moby->state = 1;
        vars->sound = -1;
    }
    func_002829D8(vars);
    if (HERO->i[0x2294 / 4] == 1)
        func_PAL_L00_002C4480(0x1D, 1);
    ready = 1;
    if (HERO->i[0x2294 / 4] == 0x1D) {
        if (func_00282948(&HERO->i[0x2534 / 4]) == 0)
            ready = 0;
    } else {
        HERO->i[0x2534 / 4] = 0x21;
    }
    if (HERO->i[0x1450 / 4] != 0)
        HERO->i[0xBF8 / 4] = HERO->i[0x1450 / 4];
    vars->unknown20 = 0;
    if (HERO->h[0x24EC / 2] != 0) {
        func_00282D30(&direction, &moby->forward, -1.0f);
    } else {
        qcopy(&direction, &HERO->q[0x760 / 16]);
    }
    func_00282D30(&origin, HERO->ptr[0x2290 / 4] + 0xE0, 0.75f);
    func_00282CC0(&origin, &HERO->q[0x80 / 16], &origin);
    count = 0;
    func_00282A88(list, 0x80);
    func_L00_0037E000(moby);
    /* Two scopes: config shares its slot with the vectors declared further down. */
    {
    {
        AimConfig config = D_L00_001B00F0;

        func_002AF580(&moby->position, &direction, 0.436332345f, 0.436332345f, &count, list, 0x20, 0, 48.0f, 0.785398245f, 0.785398245f, 1, &config);
    }
    }
    i = 0;
    mobys = list;
    if (count > 0) {
        do {
            float height = 0.0f;
            float *info = (float *)func_002AB1F0(mobys[i]);

            if (info != 0)
                height = info[4];
            if (HERO->i[0x1450 / 4] == 0) {
                float distance = func_00282E48(D_L00_001B8DC0, &mobys[i]->position) * 0.00666666683f;

                func_00282D30(&aim, &mobys[i]->up, height);
                func_00282CC0(&aim, &mobys[i]->position, &aim);
                MarkTarget(moby, func_00282C48(0.9f - distance * 0.65f), 0xFF0FFF0F, &aim, 0x26, 0.0f, -1, 90.0f, 4);
            }
            i++;
        } while (i < count);
    }
    target = 0;
    if (D_L00_001A8F00 == 0 && vars->cooldown == 0.0f && HERO->b[0x22BC] == 0 &&
        (D_00138180[0x1A0 / 4] & HERO->u[0x1230 / 4]) && HERO->i[0x1240 / 4] >= 0x13 && ready != 0) {
        if (HERO->i[0x1450 / 4] != 0)
            HERO->i[0xBF8 / 4] = HERO->i[0x1450 / 4];
        if (func_L00_002D4040(-1)) {
            Vec start, step, muzzle, offset;
            int hits;
            float strength;
            float *info;
            Moby *shot;

            func_PAL_L00_002AF458();
            func_00282D30(start, &moby->forward, -1.0f);
            func_00282CC0(start, start, &moby->position);
            func_00282D30(step, &moby->right, 0.275f);
            func_00282CC0(start, start, step);
            hits = func_00277F48(1.0f, start, 1, HERO->ptr[0x2290 / 4], 0);
            if (hits != 0) {
                for (j = 0; j < hits; j++) {
                    Moby *hit = D_L00_001C3280[j];
                    float *hp = (float *)func_002AB1F0(hit);

                    if (hit->alive != 0 && hit->health > 0 && hit != 0 && hit->state != 0xFE && hit->state != 0xFD &&
                        hit->objectClass != 0xC87 && hit->objectClass != 0xECC && hp != 0 &&
                        (*hp > 0.0f || func_002ABB78(hit) != 0) && (hit->model == 0 || hit->model->kind != 5)) {
                        target = D_L00_001BF200.hit;
                        vars->target = target;
                        break;
                    }
                }
            }
            strength = 0.0f;
            func_002E5CF8(1, 0, moby);
            vars->timer = 0xc;
            func_PAL_L00_003CD388(moby);
            func_002A75E0(moby, 2, 0, 1, 0);
            moby->scale = 0.9f;
            vars->sound = func_L00_002D6998(D_L00_002960A0);
            *(Quad *)offset = 0;
            offset[0] = 0.513000011f;
            offset[1] = -1.0f;
            offset[2] = 0.182999998f;
            offset[3] = 1.0f;
            func_00283098(offset, offset, &moby->right);
            func_00282CC0(muzzle, &moby->position, offset);
            if (target == 0) {
                int locked = 0;

                target = (Moby *)func_L00_0037DEF8(moby, list, count, &locked, -1);
                if (target == 0)
                    goto fire;
                if (locked != 0)
                    func_L00_0037DD18(moby, target, 0x11);
            }
            info = (float *)func_002AB1F0(target);
            if (info != 0)
                strength = info[4];
        fire:
            if (HERO->ptr[0xBF8 / 4] != 0)
                shot = func_PAL_L00_0040E9F0(moby, muzzle, HERO->ptr[0xBF8 / 4], D_L00_001A8F20, strength, 2.0f, 5.0f, 0.6f);
            else
                shot = func_PAL_L00_0040E9F0(moby, muzzle, target, D_L00_001A8F20, strength, 2.0f, 5.0f, 0.6f);
            if (shot != 0)
                shot->owner = moby;
            func_L00_002D3F30(-1, 1);
            D_L00_001B2AD0 = 1;
        } else if ((D_00138180[0x1A4 / 4] & HERO->u[0x1230 / 4]) || D_L00_001B2AD0 == 1) {
            func_002E5CF8(2, 0, moby);
            D_L00_001B2AD0 = 0;
        }
        if (!(D_00138180[0x1A0 / 4] & HERO->u[0x1230 / 4]) || HERO->b[0x22B8] == 0) {
            if (vars->sound >= 0) {
                func_L00_002D6B70(vars->sound);
                vars->sound = -1;
                func_PAL_L00_002AF6C0();
            }
        }
        {
            WeaponEntry *weapon = (WeaponEntry *)(D_00139568[0x2C] * 0xE0 + (char *)D_L00_00262570);

            vars->cooldown = 1.0f / weapon->rate;
        }
    }
    animation = moby->animation;
    if (animation == 2) {
        if (moby->flags & 2)
            func_002A75E0(moby, 1, 0, 1, 0);
        if (moby->animation == animation)
            goto done;
    }
    if (vars->timer > 0) {
        float red, green, blue, t;
        Vec spot, flash, offset;

        if (vars->timer >= 0xb) {
            float scale = 1.0f / func_00283CE0(2);

            red = func_00283CE0(0xc - vars->timer) * scale;
            green = func_00283CE0(0xc - vars->timer) * (scale * 0.8f);
            t = func_00283CE0(0xc - vars->timer);
            scale *= 0.5f;
            blue = t * scale;
        } else {
            float scale = 1.0f / func_00283CE0(0xa);

            red = func_00283CE0(vars->timer) * scale;
            green = func_00283CE0(vars->timer) * (scale * 0.8f);
            t = func_00283CE0(vars->timer);
            scale *= 0.5f;
            blue = t * scale;
        }
        if (HERO->h[0x24EC / 2] != 0) {
            func_00282D30(flash, &moby->forward, -1.0f);
            *(Quad *)offset = 0;
            offset[0] = 0.513000011f;
            offset[1] = -1.0f;
            offset[2] = 0.182999998f;
            offset[3] = 1.0f;
            func_00283098(offset, offset, &moby->right);
            func_00282CC0(spot, &moby->position, offset);
        } else {
            qcopy(flash, &HERO->q[0x760 / 16]);
            *(Quad *)offset = 0;
            offset[0] = 0.513000011f;
            offset[1] = -1.0f;
            offset[2] = 0.182999998f;
            offset[3] = 1.0f;
            func_00283098(offset, offset, &moby->right);
            func_00282CC0(spot, &moby->position, offset);
        }
        func_00282CC0(spot, spot, flash);
        func_00282D30(offset, HERO->ptr[0x2290 / 4] + 0xE0, 0.3f);
        func_00282CC0(spot, spot, offset);
        if (vars->light == -1) {
            vars->light = func_L00_002FCF18(spot, 8.0f, 0.0f, red, green, blue);
        } else {
            Light *light = &D_L00_001C6F40[vars->light];

            qcopy(&light->pos, spot);
            light->pos.f[3] = 8.0f;
            light->red = red;
            light->green = green;
            light->blue = blue;
        }
        func_00282978(&vars->timer);
        return;
    }
done:
    if (vars->light != -1) {
        func_00291450(vars->light);
        vars->light = -1;
        vars->timer = 0;
    }
}
