/* func_PAL_0031C1B8, the PAL copy of func_0031ABE0 in its own unit: the state
   routine of a hovering enemy, the same C with its timers and blends at 50 Hz.
   The steering target the turn calls read is the hero field at 0x2290 (a
   struct field of D_00189E20, not a separate symbol): its first read, in
   state 5, records the hero's split high part in gcse's expression table
   before the position self+0x10, which gives retail's insertion order at
   the head of state 13. */
#include "common.h"

typedef unsigned int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float v[4]; } Vector;

typedef struct {
    u8 pad000[0x60];
    u8 dispatch[0x1E0];
    s16 timer;          /* 0x240 */
    s16 pad242;
    s16 mode;           /* 0x244 */
    s16 alerted;        /* 0x246 */
    u8 pad248[0x8];
    u8 height[4];       /* 0x250 */
    float range;        /* 0x254 */
    int path;           /* 0x258 */
    u8 turn[4];         /* 0x25C */
    u8 pitch[4];        /* 0x260 */
    int active;         /* 0x264 */
    u8 sway[4];         /* 0x268 */
    u8 tilt[4];         /* 0x26C */
    void *parts[3];     /* 0x270 */
    u8 pad27C[0x4];
    int hold;           /* 0x280 */
    u8 pad284[0x8];
    int ticks;          /* 0x28C */
    u8 pad290[0x4];
    int open;           /* 0x294 */
    u8 pad298[0x4];
    float fade;         /* 0x29C */
    u8 pad2A0[0xB0];
    Vector home;        /* 0x350 */
} Vars;

typedef struct {
    u8 pad00[0x10];
    float pos[4];       /* 0x10 */
    u8 state;           /* 0x20 */
    u8 pad21[0x21];
    u8 anim;            /* 0x42 */
    u8 animNext;        /* 0x43 */
    u8 pad44[0x1C];
    u8 flags;           /* 0x60 */
    u8 pad61[0x7];
    Vars *vars;         /* 0x68 */
    u8 pad6C[0x29];
    u8 mode;            /* 0x95 */
    u8 pad96[0x2A];
    u8 basis[0x30];     /* 0xC0 */
    float rot[3];       /* 0xF0 */
} Object;

typedef struct {
    u8 pad0000[0x80];
    float pos[4];       /* 0x80 */
    u8 pad0090[0x2200];
    void *f2290;        /* 0x2290 */
    u8 pad2294[0x208];
    Object *target;     /* 0x249C */
} HeroView;

extern HeroView D_00189E20;
extern char D_001AFAE0[];

extern void func_0026FEB8(const char *, ...);
extern void func_0027CDC8(void (*)(Object *), Object *);
extern void func_0027CFD0(void (*)(Object *), Object *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282E20(void *);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern void func_002833F0(void *, void *);
extern float func_00283C80(float, float);
extern void func_0029F338(void *);
extern float func_0029F530(Object *);
extern void func_PAL_002A7E68(Object *, int, int, int);
extern void func_002A7750(Object *, int, int);
extern int func_002A7820(int, int);
extern float func_002A7E08(Object *, void *, void *, float, float, float);
extern float func_002A89A8(void *, int, float);
extern int func_002A8D70(Object *, int, float, float, int, float, int, int, int);
extern float func_002AA3A8(s32, float, s32, float, float, float);
extern float func_002AA458(s32, s32, s32, float, float, float);
extern float func_002AA548(float *, void *, float, float, float, float);
extern void func_002AEF28(Object *, void *, void *, float, float, float);
extern int func_PAL_002B27B8(Object *, void *);
extern s32 func_002B3890(Object *);
extern int func_PAL_002B5BA8(Object *, float *, float);
extern int func_PAL_002B5C98(Object *, void *, float);
extern void func_002B60B0(Object *, float, float, float, float);
extern void func_PAL_0031D2E8(Object *);
extern void func_PAL_0031DAB8(Object *);
extern void func_0031C7A0(Object *);
extern void func_0031D268(Object *);
extern void func_0031D308(Object *);

void func_PAL_0031C1B8(Object *self)
{
    Vars *vars = self->vars;
    Vector target, delta;
    float ground, frame, drop;
    int result;

    func_PAL_0031D2E8(self);
    switch (self->mode) {
    case 0:
        if (func_002B3890(self))
            func_002B60B0(self, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
        if (vars->mode == 2 && vars->active) {
            func_002A7750(self, 11, 4);
            if (self->animNext != 1) func_PAL_002A7E68(self, 1, 0, 3);
            if (vars->path != -1) {
                func_002A7750(self, 10, 1);
                if (self->animNext != 26) func_PAL_002A7E68(self, 26, 0, 3);
            }
        } else if (vars->alerted) {
            func_002A7750(self, 9, 3);
            vars->alerted = 0;
            if (vars->timer < 250) vars->timer = ((s32)(func_002A7820(480, 600)) * 5 + 2) / 6;
        }
        break;
    case 2:
        if (func_002B3890(self))
            func_002B60B0(self, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
        if (vars->mode == 2 && vars->active) {
            func_002A7750(self, 5, 4);
            if (self->animNext != 25) func_PAL_002A7E68(self, 25, 0, 3);
        } else if (vars->alerted && vars->active) {
            vars->alerted = 0;
            func_002A7750(self, 5, 4);
            if (self->animNext != 25) func_PAL_002A7E68(self, 25, 0, 3);
        }
        break;
    case 3:
        if (func_002B3890(self))
            func_002B60B0(self, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
        if (vars->mode == 2 && vars->active) {
            func_002A7750(self, 11, 4);
            if (self->animNext != 1) func_PAL_002A7E68(self, 1, 0, 3);
        } else if (vars->timer == 0) {
            func_002A7750(self, 2, 0);
            if (self->animNext != 4) func_PAL_002A7E68(self, 4, 0, 8);
        }
        break;
    case 4:
        if (func_002B3890(self))
            func_002B60B0(self, 0.0064000003f, 0.16000001f, 0.0016755164f, 0.12566373f);
        if (vars->mode != 1 && vars->mode != 2) {
            if (self->state != 5) {
                if (self->state != 4) {
                    func_002A7750(self, 9, 3);
                    if (self->animNext != 7) func_PAL_002A7E68(self, 7, 0, 8);
                    vars->timer = ((s32)(func_002A7820(580, 600)) * 5 + 2) / 6;
                }
            }
        }
        break;
    case 5:
        result = func_PAL_002B27B8(self, vars->dispatch);
        if (result & 1) {
            func_0029F338(vars->parts[0]);
            func_0029F338(vars->parts[1]);
            func_0029F338(vars->parts[2]);
            func_0029F338(self);
            return;
        }
        if (result & 2) {
            if (vars->mode == 1 || vars->mode == 2) {
                func_002A7750(self, 12, 4);
                if (self->animNext != 11) func_PAL_002A7E68(self, 11, 0, 8);
            } else {
                func_002A7750(self, 9, 3);
                if (self->animNext != 7) func_PAL_002A7E68(self, 7, 0, 8);
                vars->timer = ((s32)(func_002A7820(580, 600)) * 5 + 2) / 6;
            }
            if (vars->active != 1) vars->active = 1;
        }
        break;
    }

    switch (self->state) {
    case 2:
        break;
    case 3:
        func_002AEF28(self, vars->sway, vars->tilt, 0.06981318f, 0.062831864f, 0.015707966f);
        break;
    case 5:
        vars->ticks++;
        func_002A7E08(self, D_00189E20.f2290, vars->turn, 0.001f, 0.01f, 0.1f);
        func_002AA3A8((s32)&self->rot[1], 0.0f, (s32)vars->pitch, 0.020000001f, 0.0f, 0.080000006f);
        func_002AA3A8((s32)&self->rot[0], 0.0f, (s32)vars->pitch, 0.020000001f, 0.0f, 0.080000006f);
        {
        float level = func_002A89A8(self->pos, 0, 0.5f);
        if (self->pos[2] - level > 0.05f) {
            self->pos[2] = self->pos[2] - level * 0.00025f;
        } else {
            func_002A7750(self, 8, -1);
            if (self->animNext != 15) func_PAL_002A7E68(self, 15, 0, 2);
        }
        }
        if (self->flags & 2) {
            func_002A7750(self, 4, -1);
            if (self->animNext != 26) func_PAL_002A7E68(self, 26, 0, 12);
        }
        break;
    case 4:
        vars->ticks++;
        func_002A7E08(self, D_00189E20.f2290, vars->turn, 0.001f, 0.01f, 0.1f);
        func_002AA3A8((s32)&self->rot[1], 0.0f, (s32)vars->pitch, 0.020000001f, 0.0f, 0.080000006f);
        func_002AA3A8((s32)&self->rot[0], 0.0f, (s32)vars->pitch, 0.020000001f, 0.0f, 0.080000006f);
        ground = func_002A89A8(self->pos, 0, 0.5f);
        drop = ground - 3.0f;
        if (self->pos[2] - ground > 0.05f) {
            func_002AA548(&self->pos[2], vars->height, drop, 0.020000001f, 0.19600002f, 0.20000002f);
        } else {
            func_0026FEB8(D_001AFAE0, vars->ticks);
            func_002A7750(self, 8, -1);
            if (self->animNext != 15) func_PAL_002A7E68(self, 15, 0, 2);
        }
        break;
    case 6:
        if (self->flags & 2) {
            func_002A7750(self, 7, -1);
            if (self->animNext != 14) func_PAL_002A7E68(self, 14, 0, 12);
        }
        break;
    case 7:
        func_002AA3A8((s32)&self->rot[1], 0.0f, (s32)vars->pitch, 0.020000001f, 0.0f, 0.080000006f);
        func_002833F0(self->basis, self->rot);
        func_002A7E08(self, D_00189E20.f2290, vars->turn, 0.001f, 0.01f, 0.1f);
        ground = func_002A89A8(self->pos, 0, 0.5f);
        drop = ground - 3.0f;
        if (self->pos[2] - ground > 0.05f) {
            func_002AA548(&self->pos[2], vars->height, drop, 0.030000001f, 0.19600002f, 0.3f);
        } else {
            func_002A7750(self, 8, -1);
            if (self->animNext != 15) func_PAL_002A7E68(self, 15, 0, 2);
        }
        break;
    case 8:
        if (self->flags & 2) {
            func_002A7750(self, 12, 4);
            if (self->animNext != 8) func_PAL_002A7E68(self, 8, 0, 12);
            self->pos[2] = func_002A89A8(self->pos, 0, 0.5f);
        }
        break;
    case 10:
        target.q = vars->home.q;
        target.v[2] -= 3.0f;
        func_00282CF0(&delta, &target, self->pos);
        self->rot[2] = func_00283248(delta.v[0], delta.v[1]);
        self->rot[1] = func_00283248(func_00282E20(&delta), delta.v[2]);
        func_002833F0(self->basis, self->rot);
        func_002AA458((s32)self->pos, (s32)&target, (s32)vars->height, 0.020000001f, 0.0f, 0.40000004f);
        if (func_00282E48(self->pos, &target) < 0.4f) {
            if (self->animNext != 14) func_PAL_002A7E68(self, 14, 0, 8);
            func_002A7750(self, 7, -1);
        }
        break;
    case 11:
        if (self->flags & 2) {
            func_002B60B0(self, 0.0064000003f, 0.16000001f, 0.0016755164f, 0.12566373f);
            func_002A7750(self, 12, -1);
            if (self->animNext != 11) func_PAL_002A7E68(self, 11, 0, 12);
        }
        break;
    case 12:
        if (func_00282E80(self->pos, D_00189E20.pos) < 2.8f
            && func_00283C80(self->rot[2], func_00283248(D_00189E20.pos[0] - self->pos[0], D_00189E20.pos[1] - self->pos[1])) < 0.38397247f) {
            func_002A7750(self, 13, -1);
            if (self->animNext != 16) func_PAL_002A7E68(self, 16, 4, 2);
            vars->hold = 0;
        } else if (func_00282E80(self->pos, D_00189E20.pos) > 2.8f) {
            func_PAL_002B5BA8(self, D_00189E20.pos, vars->range);
        } else {
            func_PAL_002B5C98(self, self->pos, func_00283248(D_00189E20.pos[0] - self->pos[0], D_00189E20.pos[1] - self->pos[1]));
        }
        if (func_00282E80(self->pos, D_00189E20.pos) > 5.0f && self->anim == 8) {
            if (self->animNext != 11) func_PAL_002A7E68(self, 11, 0, 3);
            func_002B60B0(self, 0.0064000003f, 0.16000001f, 0.0016755164f, 0.12566373f);
        }
        break;
    case 13:
        if (self->flags & 2) {
            if (D_00189E20.target == self) {
                func_002A7750(self, 14, -1);
                if (self->animNext != 17) func_PAL_002A7E68(self, 17, 0, 6);
            } else if (func_00282E80(self->pos, D_00189E20.pos) > 4.0f) {
                func_002B60B0(self, 0.0064000003f, 0.16000001f, 0.0016755164f, 0.12566373f);
                func_002A7750(self, 12, -1);
                if (self->animNext != 11) func_PAL_002A7E68(self, 11, 0, 8);
            } else {
                func_002B60B0(self, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
                func_002A7750(self, 12, -1);
                if (self->animNext != 8) func_PAL_002A7E68(self, 8, 0, 8);
            }
        }
        frame = func_0029F530(self);
        if (self->anim == 16) {
            if (frame >= 19.0f && frame <= 25.0f) {
                func_002A8D70(self, 0, 0.35f, vars->fade, 1, 1.0f, 0, 1, 0);
                func_002A8D70(self, 1, 0.15f, vars->fade, 1, 1.0f, 0, 1, 0);
                func_002A8D70(self, 2, 0.15f, vars->fade, 1, 1.0f, 0, 1, 0);
            }
            if (self->anim == 16 && frame >= 17.0f && frame <= 25.0f) {
                func_0027CDC8(func_0031D308, self);
                func_0031D268(self);
            }
        }
        func_PAL_002B5C98(self, self->pos, func_00283248(D_00189E20.pos[0] - self->pos[0], D_00189E20.pos[1] - self->pos[1]));
        break;
    case 14:
        if (self->flags & 2) {
            if (func_00282E80(self->pos, D_00189E20.pos) > 4.0f) {
                func_002B60B0(self, 0.0064000003f, 0.16000001f, 0.0016755164f, 0.12566373f);
                func_002A7750(self, 12, -1);
                if (self->animNext != 11) func_PAL_002A7E68(self, 11, 0, 8);
            } else {
                func_002B60B0(self, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
                func_002A7750(self, 12, -1);
                if (self->animNext != 8) func_PAL_002A7E68(self, 8, 0, 8);
            }
        }
        {
            float at = func_0029F530(self);
            if (self->anim == 17 && (at <= 5.0f || (at >= 12.0f && at <= 15.0f)))
                vars->open = 1;
            else
                vars->open = 0;
        }
        break;
    }
    func_PAL_0031DAB8(self);
    func_0027CFD0(func_0031C7A0, self);
}
