#include "include_asm.h"
#include "common.h"
extern s32 func_L17_00340DD0(f32, s32, s32, s32);
extern f32 D_L17_001B04B8 __attribute__((sda));
extern void func_002A7750(void *, s32, s32);
extern s32 func_002A9640(void *, s32, s32);
extern void func_L00_0032A258(void *, void *, void *, void *, s32, s32, s32, s32, s32, s32, s32);
extern void func_0032C700(void *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32, s32, s32);
extern void func_0029F338(void *);
extern s32 D_L17_001B1E00 __attribute__((sda));
extern s32 D_L17_001B1DE0 __attribute__((sda));
extern s32 D_L17_001B1DD8 __attribute__((sda));
extern s32 D_L17_001B1DD0 __attribute__((sda));

/* Sets the object's stage up: the first stage asks the level's own spawner for a child and
   gives up its handle, the second one only releases the handle. */
void func_PAL_L17_0041E460(s32 a0)
{
    u8 v = *(u8 *)(a0 + 0x20);

    switch (v) {
    case 0:
        func_002A7750(a0, 1, -1);
        break;
    case 1:
        if (func_002A9640(a0, 0x4010001, 0) != 0) {
            func_002A7750(a0, 2, -1);
            *(u8 *)(a0 + 0xA8) = 0xFF;
        }
        break;
    case 2:
        func_L00_0032A258(a0, &D_L17_001B1DE0, &D_L17_001B1DD8, &D_L17_001B1DD0,
                          0xFFFF, 0, D_L17_001B1E00, 0, 0xFFFF, 0xFF, 0);
        func_0032C700(a0 + 0x10, 0, 12, 10, 10, 10, 0, 0,
                      *(f32 *)(a0 + 0x2C) * 10.0f, 20.0f, 1, 0, 0, 0);
        func_0029F338(a0);
        break;
    }
}

typedef int Quad __attribute__((mode(TI)));
#define F(p, o) (*(float *)((char *)(p) + (o)))
#define I(p, o) (*(int *)((char *)(p) + (o)))
#define H(p, o) (*(unsigned short *)((char *)(p) + (o)))
#define B(p, o) (*(unsigned char *)((char *)(p) + (o)))
typedef struct {
    char pad[0x74];
    unsigned char active;
    char pad75[0x13];
    void *owner;
} SoundAnchor;
extern unsigned char D_00188660[];
extern char *D_L17_001B2C1C;
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00282C48(float);
extern int func_002AD0B0(void *);
extern void func_002AD0E0(void *, void *, void *, void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_002E59F8(int);
extern int func_002E5CF8(int, int, void *);

/* Steers toward the linked object and maintains its movement sound. */
void func_PAL_L17_0041E1B8(char *obj)
{
    float v[4] __attribute__((aligned(16)));
    float target[4] __attribute__((aligned(16)));
    float dir[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    char *state = *(char **)(obj + 0x68);

    if (!B(obj, 0x20)) {
        I(state, 0xA0) = -1;
        B(obj, 0x20) = 1;
    }
    I(state, 0x8C) |= 4;
    H(state, 0x3E) |= 8;
    v[0] = func_00283180(F(obj, 0xF8)) * (0.080000006f);
    v[1] = func_00283198(F(obj, 0xF8)) * (0.080000006f);
    v[2] = 0;
    func_002AD6F0(state + 0x50, v, obj + 0xF0, obj + 0xF0);

    if (I(state, 0x90) == -1 ||
        !func_002AD0B0(D_L17_001B2C1C + (I(state, 0x90) << 8))) {
        F(state, 0x9C) = F(state, 0x98) * (0.020000001f);
    } else {
        func_002AD0E0(obj, D_L17_001B2C1C + (I(state, 0x90) << 8),
                      obj + 0x10, obj + 0xF0, target, dir);
        target[2] = 0;
        func_00282CF0(delta, target, obj + 0x10);
        *(Quad *)target = *(Quad *)delta;
        dir[0] = func_00283180(F(obj, 0xF8));
        dir[1] = func_00283198(F(obj, 0xF8));
        dir[2] = 0;
        F(state, 0x9C) = func_00282DB0(target, dir);
    }
    v[0] = func_00283180(F(obj, 0xF8)) * F(state, 0x9C);
    v[1] = func_00283198(F(obj, 0xF8)) * F(state, 0x9C);
    v[2] = 0;
    func_002AD6F0(state + 0x50, v, obj + 0xF0, obj + 0xF0);
    F(obj, 0x48) = F(state, 0x9C) * 12.499999f;

    if (func_00282C48(F(obj, 0x48)) < 0.1f) {
        if (I(state, 0xA0) != -1) {
            SoundAnchor *effect = (SoundAnchor *)(D_00188660 + I(state, 0xA0) * 0x70);
            if (effect->owner == obj && effect->active)
                func_002E59F8(I(state, 0xA0));
        }
        I(state, 0xA0) = -1;
    } else {
        SoundAnchor *effect = (SoundAnchor *)(D_00188660 + I(state, 0xA0) * 0x70);
        if (effect->owner != obj || !effect->active)
            I(state, 0xA0) = func_002E5CF8(0, 4, obj);
    }
}
