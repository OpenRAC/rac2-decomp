/* func_L00_003C8A90, 2628 bytes, 27 places. USA v1.01, -O2 -G8 -ffunction-sections -g
 * -frac2-zero-ti-por: 2624/2628 bytes, frame 0x190, about 70 rows off, mostly register names.
 * Nested blocks around the two sets of vectors give retail's shared slots. Left:
 * - the hero base wants $s2 and the loop counters $s3, here the reverse: the counter's priority
 *   (7 refs, length 83) beats the base's (4 refs, length 88).
 * - the second offset register: retail keeps $s0 for the first use after the join and $s2, a copy
 *   set in both arms, for the last two. A per-arm copy after the call lets jump2 merge the call, as
 *   retail does, but cprop folds it; one using `offset` at the join gets $s2 but loses the merge.
 *   A trailing call in an arm gets flow's (use 0), so something non-call must end the arm at flow.
 * - the first read of 0x2294 needs $v0 (lui $v1): with $v1 reorg finds the reload redundant.
 * - the weapon table add is index + base in retail; D_L00_001A8F20 is a tied lui/addiu (sda incomplete array; it took 20 rows off, but a delay slot now takes the one-insn form, hence the missing word).
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

extern void func_002829D8(void *);
extern void func_L00_002C42E0(int, int);
extern int func_00282948(void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282A88(void *, int);
extern void func_L00_0037E000(void *);
extern int func_002AF580(void *, void *, float, float, void *, void *, int, int, float, float, float, int, void *);
extern float *func_002AB1F0(void *);
extern float func_00282E48(void *, void *);
extern float func_00282C48(float);
extern void func_00273318(void *, float, unsigned int, void *, int, float, int, float, int);
extern int func_L00_002D4040(int);
extern void func_L00_002AF568(void);
extern int func_00277F48(float, void *, int, void *, void *);
extern int func_002ABB78(void *);
extern int func_002E5CF8(int, int, void *);
extern void func_L00_003C94D8(void *);
extern void func_002A75E0(void *, int, int, int, int);
extern int func_L00_002D6998(void *);
extern void func_00283098(void *, void *, void *);
extern Moby *func_L00_0037DEF8(void *, void *, int, int *, int);
extern void func_L00_0037DD18(void *, void *, int);
extern Moby *func_L00_00409E48(void *, void *, void *, void *, float, float, float, float);
extern int func_L00_002D3F30(int, int);
extern void func_L00_002D6B70(int);
extern void func_L00_002AF7D0(void);
extern float func_00283CE0(int);
extern int func_L00_002FCF18(void *, float, float, float, float, float);
extern int func_00282978(void *);
extern void func_00291450(int);

#define HERO ((Hero *)D_00189E20)

void func_L00_003C8A90(Moby *moby)
{
    Vars *vars = moby->vars;
    Vector direction, origin, aim;
    Moby *list[32];
    int count;
    int ready;
    int i, j;
    Moby *target;
    int animation;

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
        func_L00_002C42E0(0x1D, 1);
    ready = 1;
    if (HERO->i[0x2294 / 4] == 0x1D) {
        if (func_00282948(&HERO->i[0x2534 / 4]) == 0)
            ready = 0;
    } else {
        HERO->i[0x2534 / 4] = 0x28;
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
    {
    {
        AimConfig config = D_L00_001B00F0;

        func_002AF580(&moby->position, &direction, 0.436332345f, 0.436332345f, &count, list, 0x20, 0, 48.0f, 0.785398245f, 0.785398245f, 1, &config);
    }
    }
    for (i = 0; i < count; i++) {
        float height = 0.0f;
        float *info = func_002AB1F0(list[i]);

        if (info != 0)
            height = info[4];
        if (HERO->i[0x1450 / 4] == 0) {
            float distance = func_00282E48(D_L00_001B8DC0, &list[i]->position) * 0.00666666683f;

            func_00282D30(&aim, &list[i]->up, height);
            func_00282CC0(&aim, &list[i]->position, &aim);
            func_00273318(moby, func_00282C48(0.9f - distance * 0.65f), 0xFF0FFF0F, &aim, 0x26, 0.0f, -1, 90.0f, 4);
        }
    }
    target = 0;
    if (D_L00_001A8F00 == 0 && vars->cooldown == 0.0f && HERO->b[0x22BC] == 0 &&
        (D_00138180[0x1A0 / 4] & HERO->u[0x1230 / 4]) && HERO->i[0x1240 / 4] >= 0x17 && ready != 0) {
        if (HERO->i[0x1450 / 4] != 0)
            HERO->i[0xBF8 / 4] = HERO->i[0x1450 / 4];
        {
        if (func_L00_002D4040(-1)) {
            Vec start, step, muzzle, offset;
            int hits;
            float strength;
            float *info;
            Moby *shot;

            func_L00_002AF568();
            func_00282D30(start, &moby->forward, -1.0f);
            func_00282CC0(start, start, &moby->position);
            func_00282D30(step, &moby->right, 0.275f);
            func_00282CC0(start, start, step);
            hits = func_00277F48(1.0f, start, 1, HERO->ptr[0x2290 / 4], 0);
            if (hits != 0) {
                for (j = 0; j < hits; j++) {
                    Moby *hit = D_L00_001C3280[j];
                    float *hp = func_002AB1F0(hit);

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
            vars->timer = 0xF;
            func_L00_003C94D8(moby);
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

                target = func_L00_0037DEF8(moby, list, count, &locked, -1);
                if (target == 0)
                    goto fire;
                if (locked != 0)
                    func_L00_0037DD18(moby, target, 0x14);
            }
            info = func_002AB1F0(target);
            if (info != 0)
                strength = info[4];
        fire:
            if (HERO->ptr[0xBF8 / 4] != 0)
                shot = func_L00_00409E48(moby, muzzle, HERO->ptr[0xBF8 / 4], D_L00_001A8F20, strength, 2.0f, 5.0f, 0.6f);
            else
                shot = func_L00_00409E48(moby, muzzle, target, D_L00_001A8F20, strength, 2.0f, 5.0f, 0.6f);
            if (shot != 0)
                shot->owner = moby;
            func_L00_002D3F30(-1, 1);
            D_L00_001B2AD0 = 1;
        } else if ((D_00138180[0x1A4 / 4] & HERO->u[0x1230 / 4]) || D_L00_001B2AD0 == 1) {
            func_002E5CF8(2, 0, moby);
            D_L00_001B2AD0 = 0;
        }
        }
        if (!(D_00138180[0x1A0 / 4] & HERO->u[0x1230 / 4]) || HERO->b[0x22B8] == 0) {
            if (vars->sound >= 0) {
                func_L00_002D6B70(vars->sound);
                vars->sound = -1;
                func_L00_002AF7D0();
            }
        }
        vars->cooldown = 1.0f / ((WeaponEntry *)(D_00139568[0x2C] * 0xE0 + (char *)D_L00_00262570))->rate;
    }
    animation = moby->animation;
    if (animation == 2) {
        if (moby->flags & 2)
            func_002A75E0(moby, 1, 0, 1, 0);
        if (moby->animation == animation)
            goto done;
    }
    if (vars->timer > 0) {
        float scale, red, green, blue, t;
        float *again, *pf, *po;
        Vec spot, flash, offset;

        if (vars->timer >= 0xD) {
            t = func_00283CE0(3);
            scale = 1.0f;
            scale /= t;
            red = func_00283CE0(0xF - vars->timer) * scale;
            green = func_00283CE0(0xF - vars->timer) * (scale * 0.8f);
            t = func_00283CE0(0xF - vars->timer);
            scale *= 0.5f;
            blue = t * scale;
        } else {
            t = func_00283CE0(0xC);
            scale = 1.0f;
            scale /= t;
            red = func_00283CE0(vars->timer) * scale;
            green = func_00283CE0(vars->timer) * (scale * 0.8f);
            t = func_00283CE0(vars->timer);
            scale *= 0.5f;
            blue = t * scale;
        }
        if (HERO->h[0x24EC / 2] != 0) {
            pf = flash;
            func_00282D30(pf, &moby->forward, -1.0f);
            po = offset;
            *(Quad *)offset = 0;
            offset[0] = 0.513000011f;
            offset[1] = -1.0f;
            offset[2] = 0.182999998f;
            offset[3] = 1.0f;
            func_00283098(po, po, &moby->right);
            again = po;
        } else {
            pf = flash;
            qcopy(pf, &HERO->q[0x760 / 16]);
            po = offset;
            *(Quad *)offset = 0;
            offset[0] = 0.513000011f;
            offset[1] = -1.0f;
            offset[2] = 0.182999998f;
            offset[3] = 1.0f;
            func_00283098(po, po, &moby->right);
            again = po;
        }
        func_00282CC0(spot, &moby->position, po);
        func_00282CC0(spot, spot, pf);
        func_00282D30(again, HERO->ptr[0x2290 / 4] + 0xE0, 0.3f);
        func_00282CC0(spot, spot, again);
        if (vars->light == -1) {
            vars->light = func_L00_002FCF18(spot, 8.0f, 0.0f, red, green, blue);
        } else {
            Light *light = &D_L00_001C6F40[vars->light];

            qcopy(&light->pos, spot);
            light->blue = blue;
            light->pos.f[3] = 8.0f;
            light->red = red;
            light->green = green;
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
