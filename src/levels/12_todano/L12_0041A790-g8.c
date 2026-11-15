#include "common.h"

typedef struct {
    f32 x, y, z, w;
} V __attribute__((aligned(16)));

typedef struct {
    u8 pad00[0x34];
    u8 damage;
    u8 pad35[0x1b];
    V origin;
    f32 heightSpeed;
    f32 angularSpeed;
    s32 timer;
    f32 radius;
    f32 age;
} Vars;

extern u8 *D_L12_001B090C;
extern u8 *D_L12_001B1360 MACRO_ADDR;
extern V D_00189EA0;
extern V D_L12_001A8F20 MACRO_ADDR;
extern f32 D_L12_001B1C78 __attribute__((sda));
extern f32 D_L12_001B1C7C __attribute__((sda));
extern f32 D_L12_001B1C80 __attribute__((sda));
extern f32 D_L12_001B1C84 __attribute__((sda));
extern f32 D_L12_001B1C88 __attribute__((sda));
extern s32 D_L12_001B1C94 __attribute__((sda));
extern s32 D_L12_001B1C98 __attribute__((sda));
extern f32 D_L12_001B1C9C __attribute__((sda));
extern f32 D_L12_001B1CA0 __attribute__((sda));
extern f32 D_L12_001B1CA4 __attribute__((sda));
extern s32 D_L12_001B1CA8 __attribute__((sda));
extern s32 D_L12_001B1CAC __attribute__((sda));
extern void func_L12_0041AEF0(void *);
extern s32 func_L12_003DE4B0(void);
extern void func_L00_003DF6B0(s32, s32);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern void func_00282CC0(void *, void *, void *);
extern s32 func_002761F8(void *, void *, s32, void *, void *);
extern void func_002A8C00(void *, void *, s32, f32, void *);

extern s32 func_L12_00404778(void), func_002A9640(void *, s32, s32), func_002B3868(void *), func_00282948(s32 *);
extern f32 func_00282E48(void *, void *), func_00282E80(void *, void *), func_00283B98(f32, f32);
extern f32 func_002A7878(f32, f32), func_00283198(f32), func_00283180(f32), func_002A7940(void);
extern s32 func_00283CF0(f32), func_00283D38(s32, s32, f32), func_002A77E0(s32);
extern void func_002E5CF8(s32, s32, void *), func_002AA548(f32 *, f32 *, f32, f32, f32, f32), func_002AA2E8(f32 *, f32, f32);
extern void func_00282F20(void *, void *, f32), func_002A7A00(void *, f32, f32);
/* The EE keeps integer and FP argument banks independent in this interleaving. */
extern void *func_002C3150(void *, void *, s32, f32, u8, u8, s32);
extern void func_L02_0032B468(void *, s32, void *, void *, s32, s32, void *, void *, void *, f32);
extern void func_L00_004028C0(s32, s32);

typedef struct {
    u8 pad00[0x10];
    V position;
    u8 state;
    u8 pad21[3];
    u8 *classData;
    u8 pad28[0xc];
    u16 flags;
    u8 pad36[0x32];
    Vars *vars;
    u8 pad6c[0x2c];
    s32 collision;
    u8 pad9c[0x54];
    f32 rotation[4];
} Obj;

/* Raises the object, emits particles, and expands a damaging ring before reset. */
void func_L12_0041A790(Obj *self)
{
    V vec;
    u8 damage[0x30] __attribute__((aligned(16)));
    V next;
    Vars *vars = self->vars;

    switch (self->state) {
    case 0:
        qcopy(&vars->origin, &self->position);
        self->state = 1;
        break;
    case 1: {
        f32 distance;
        distance = 100000;
        if (IsTrackedObjectOpen())
            distance = fast_vec_dist(&self->position, D_L12_001B090C + 0x10);
        else if (IsSecondTrackedObjectOpen())
            distance = fast_vec_dist(&self->position, D_L12_001B1360 + 0x10);
        if (vec_distance_xy(&self->position, &gHeroPosition) < D_L12_001B1C7C ||
           FindOwnedEffectSlot(self, 0x30000, 0) || distance < D_L12_001B1C7C * 0.5f) {
            self->state = 2;
            vars->timer = FloatToInt(D_L12_001B1C84 * 60);
            vars->radius = D_L12_001B1C78;
            vars->age = 0;
        }
        break;
    }
    case 2: {
        f32 step, ratio, angle, cosine, sine, size;
        s32 color, i;
        u8 life, alpha;
        if (SetFirstPendingFlag(self))
            PlayMobySound(0, 0, self);
        AddDrawCallbackToList1(DrawAnimatedRings, self);
        vars->age += D_L12_001B1C88 * 0.016666668f;
        StepValueTowardTarget(&self->position.z, &vars->heightSpeed, vars->origin.z + 0.5f, 1, 0.008333334f, 1);
        ApproachValue(&vars->angularSpeed, 0.4188791f, 0.1f);
        self->rotation[2] = FastAddRotations(self->rotation[2], vars->angularSpeed);
        step = D_L12_001B1C88 * 0.016666668f;
        ratio = D_L12_001B1C80 / step;
        angle = RandomFloatRange(-15, 15) * 0.017453294f;
        sine = FastSinOrCosB(angle);
        cosine = FastSinOrCosA(angle);
        angle = RandomAngle();
        vec.x = FastSinOrCosA(angle) * cosine;
        vec.y = FastSinOrCosB(angle) * cosine;
        vec.z = sine;
        vec_scale_to_length(&vec, &vec, step);
        color = FastTweenColor(D_L12_001B1C94, D_L12_001B1C98, RandomFloatRange(0, 1));
        size = RandomFloatRange(D_L12_001B1C9C, D_L12_001B1CA0);
        life = FloatToInt(RandomFloatRange(1, 1.5f) * 7) & 255;
        alpha = RandomIntBelow(255) & 255;
        SpawnHeroRelativeParticle(&self->position, &vec, color, size, life, alpha, 0);
        if (FastFloatHelperD(&vars->timer)) {
            self->state = 3;
            vars->timer = 20;
            for (i = 0; i < D_L12_001B1CA8; i++) {
                f32 angle, sine, cosine, size;
                s32 color;
                u8 life, alpha;
                angle = RandomFloatRange(-D_L12_001B1CA4, D_L12_001B1CA4) * 0.017453294f;
                sine = FastSinOrCosB(angle);
                cosine = FastSinOrCosA(angle);
                angle = RandomAngle();
                vec.x = FastSinOrCosA(angle) * cosine;
                vec.y = FastSinOrCosB(angle) * cosine;
                vec.z = sine;
                vec_scale_to_length(&vec, &vec, step);
                color = FastTweenColor(D_L12_001B1C94, D_L12_001B1C98, RandomFloatRange(0, 1));
                size = RandomFloatRange(D_L12_001B1C9C, D_L12_001B1CA0);
                life = FloatToInt(ratio * RandomFloatRange(1, 1.5f)) & 255;
                alpha = RandomIntBelow(255) & 255;
                SpawnHeroRelativeParticle(&self->position, &vec, color, size, life, alpha, 0);
            }
            RandomDirectionVector(&vec, 0.016666668f, 0.033333335f);
            vec.z = RandomFloatRange(5, 8) * 0.016666668f;
            SpawnFlyingFragment(self, 0xFF6, &self->position, self->rotation, 0, 0, &vec, &D_L12_001A8F20, &D_L12_001A8F20, 0);
        }
        break;
    }
    case 3: {
        f32 step, angle;
        s32 i;
        self->flags = (self->flags | 0x41) & 0xEFFF;
        self->collision = 0;
        if (D_L12_001B1C80 < vars->radius) {
            if (D_L12_001B1CAC) {
                self->flags = (self->flags & 0xEFBE) | 0x1000;
                self->collision = *(s32 *)(self->classData + 0x10);
                qcopy(&self->position, &vars->origin);
                self->state = 1;
                vars->angularSpeed = 0;
                vars->radius = 0;
            }
            break;
        }
        AddDrawCallbackToList1(DrawAnimatedRings, self);
        step = D_L12_001B1C88 * 0.016666668f;
        vars->radius += step;
        vars->age += step;
        make_hit_descriptor(damage, self, 0x10001, (f32)vars->damage, &D_L12_001A8F20);
        angle = 0;
        vec.x = FastSinOrCosA(angle) * vars->radius;
        vec.y = FastSinOrCosB(angle) * vars->radius;
        vec.z = 0;
        FastVecAdd(&vec, &vec, &self->position);
        angle = 0.52359885f;
        for (i = 11; i >= 0; i--) {
            next.x = FastSinOrCosA(angle) * vars->radius;
            next.y = FastSinOrCosB(angle) * vars->radius;
            next.z = 0;
            FastVecAdd(&next, &next, &self->position);
            CollLine(&next, &vec, 9, self, damage);
            angle = FastAddRotations(angle, 0.52359885f);
            qcopy(&vec, &next);
        }
        if (IsTrackedObjectOpen() && fast_vec_dist(&self->position, D_L12_001B090C + 0x10) < vars->radius)
            SetTrackedObjectState(1, 0);
        if (IsSecondTrackedObjectOpen() && fast_vec_dist(&self->position, D_L12_001B1360 + 0x10) < vars->radius)
            StartGlobalObject(1, 0);
        break;
    }
    }
}
