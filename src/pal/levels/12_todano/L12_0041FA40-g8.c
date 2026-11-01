#include "include_asm.h"

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
extern void func_PAL_L00_003E38E8(s32, s32);
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
extern void *func_002C3150(void *, void *, s32, f32, u8, u8, s32);
extern void func_PAL_L02_0032D5F8(void *, s32, void *, void *, s32, s32, void *, void *, void *, f32);
extern void func_PAL_L00_004071F0(s32, s32);
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
void func_PAL_L12_0041FA40(Obj *self)
{
    V v;
    u8 damage[0x30] __attribute__((aligned(16)));
    V next;
    Vars *s = self->vars;

    switch (self->state) {
    case 0:
        qcopy(&s->origin, &self->position);
        self->state = 1;
        break;
    case 1: {
        f32 distance;
        distance = 100000;
        if (func_L12_003DE4B0())
            distance = func_00282E48(&self->position, D_L12_001B090C + 0x10);
        else if (func_L12_00404778())
            distance = func_00282E48(&self->position, D_L12_001B1360 + 0x10);
        if (func_00282E80(&self->position, &D_00189EA0) < D_L12_001B1C7C ||
           func_002A9640(self, 0x30000, 0) || distance < D_L12_001B1C7C * 0.5f) {
            self->state = 2;
            s->timer = ((s32)(func_00283CF0(D_L12_001B1C84 * 60)) * 5 + 2) / 6;
            s->radius = D_L12_001B1C78;
            s->age = 0;
        }
        break;
    }
    case 2: {
        f32 step, ratio, angle, cosine, sine, size;
        s32 color, i;
        u8 life, alpha;
        if (func_002B3868(self))
            func_002E5CF8(0, 0, self);
        func_L00_002E6CF0(func_L12_0041AEF0, self);
        s->age += D_L12_001B1C88 * 0.020000001f;
        func_002AA548(&self->position.z, &s->heightSpeed, s->origin.z + 0.5f, 1, 0.012f, 1);
        func_002AA2E8(&s->angularSpeed, 0.5026549f, 0.14400001f);
        self->rotation[2] = func_00283B98(self->rotation[2], s->angularSpeed);
        step = D_L12_001B1C88 * 0.020000001f;
        ratio = D_L12_001B1C80 / step;
        angle = func_002A7878(-15, 15) * 0.017453294f;
        sine = func_00283198(angle);
        cosine = func_00283180(angle);
        angle = func_002A7940();
        v.x = func_00283180(angle) * cosine;
        v.y = func_00283198(angle) * cosine;
        v.z = sine;
        func_00282F20(&v, &v, step);
        color = func_00283D38(D_L12_001B1C94, D_L12_001B1C98, func_002A7878(0, 1));
        size = func_002A7878(D_L12_001B1C9C, D_L12_001B1CA0);
        life = func_00283CF0(func_002A7878(1, 1.5f) * 7) & 255;
        alpha = func_002A77E0(255) & 255;
        func_002C3150(&self->position, &v, color, size, life, alpha, 0);
        if (func_00282948(&s->timer)) {
            self->state = 3;
            s->timer = 17;
            for (i = 0; i < D_L12_001B1CA8; i++) {
                f32 angle, sine, cosine, size;
                s32 color;
                u8 life, alpha;
                angle = func_002A7878(-D_L12_001B1CA4, D_L12_001B1CA4) * 0.017453294f;
                sine = func_00283198(angle);
                cosine = func_00283180(angle);
                angle = func_002A7940();
                v.x = func_00283180(angle) * cosine;
                v.y = func_00283198(angle) * cosine;
                v.z = sine;
                func_00282F20(&v, &v, step);
                color = func_00283D38(D_L12_001B1C94, D_L12_001B1C98, func_002A7878(0, 1));
                size = func_002A7878(D_L12_001B1C9C, D_L12_001B1CA0);
                life = func_00283CF0(ratio * func_002A7878(1, 1.5f)) & 255;
                alpha = func_002A77E0(255) & 255;
                func_002C3150(&self->position, &v, color, size, life, alpha, 0);
            }
            func_002A7A00(&v, 0.020000001f, 0.040000003f);
            v.z = func_002A7878(5, 8) * 0.020000001f;
            func_PAL_L02_0032D5F8(self, 0xFF6, &self->position, self->rotation, 0, 0, &v, &D_L12_001A8F20, &D_L12_001A8F20, 0);
        }
        break;
    }
    case 3: {
        f32 step, angle;
        s32 i;
        self->flags = (self->flags | 0x41) & 0xEFFF;
        self->collision = 0;
        if (D_L12_001B1C80 < s->radius) {
            if (D_L12_001B1CAC) {
                self->flags = (self->flags & 0xEFBE) | 0x1000;
                self->collision = *(s32 *)(self->classData + 0x10);
                qcopy(&self->position, &s->origin);
                self->state = 1;
                s->angularSpeed = 0;
                s->radius = 0;
            }
            break;
        }
        func_L00_002E6CF0(func_L12_0041AEF0, self);
        step = D_L12_001B1C88 * 0.020000001f;
        s->radius += step;
        s->age += step;
        func_002A8C00(damage, self, 0x10001, (f32)s->damage, &D_L12_001A8F20);
        angle = 0;
        v.x = func_00283180(angle) * s->radius;
        v.y = func_00283198(angle) * s->radius;
        v.z = 0;
        func_00282CC0(&v, &v, &self->position);
        angle = 0.52359885f;
        for (i = 11; i >= 0; i--) {
            next.x = func_00283180(angle) * s->radius;
            next.y = func_00283198(angle) * s->radius;
            next.z = 0;
            func_00282CC0(&next, &next, &self->position);
            func_002761F8(&next, &v, 9, self, damage);
            angle = func_00283B98(angle, 0.52359885f);
            qcopy(&v, &next);
        }
        if (func_L12_003DE4B0() && func_00282E48(&self->position, D_L12_001B090C + 0x10) < s->radius)
            func_PAL_L00_003E38E8(1, 0);
        if (func_L12_00404778() && func_00282E48(&self->position, D_L12_001B1360 + 0x10) < s->radius)
            func_PAL_L00_004071F0(1, 0);
        break;
    }
    }
}
