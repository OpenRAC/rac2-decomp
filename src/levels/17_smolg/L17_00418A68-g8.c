#include "common.h"

typedef int Quad __attribute__((mode(TI)));
#define F(p, o) (*(float *)((char *)(p) + (o)))
#define I(p, o) (*(int *)((char *)(p) + (o)))
#define H(p, o) (*(unsigned short *)((char *)(p) + (o)))
#define B(p, o) (*(unsigned char *)((char *)(p) + (o)))

/* Partial view from a sound-slot anchor; anchors are spaced 0x70 bytes apart. */
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
void func_L17_00418A68(char *obj)
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
    v[0] = func_00283180(F(obj, 0xF8)) * (1.0f / 15.0f);
    v[1] = func_00283198(F(obj, 0xF8)) * (1.0f / 15.0f);
    v[2] = 0;
    func_002AD6F0(state + 0x50, v, obj + 0xF0, obj + 0xF0);

    if (I(state, 0x90) == -1 ||
        !func_002AD0B0(D_L17_001B2C1C + (I(state, 0x90) << 8))) {
        F(state, 0x9C) = F(state, 0x98) * (1.0f / 60.0f);
    } else {
        func_002AD0E0(obj, D_L17_001B2C1C + (I(state, 0x90) << 8),
                      obj + 0x10, obj + 0xF0, target, dir);
        target[2] = 0;
        FastVecSub(delta, target, obj + 0x10);
        *(Quad *)target = *(Quad *)delta;
        dir[0] = func_00283180(F(obj, 0xF8));
        dir[1] = func_00283198(F(obj, 0xF8));
        dir[2] = 0;
        F(state, 0x9C) = FastVecDot(target, dir);
    }
    v[0] = func_00283180(F(obj, 0xF8)) * F(state, 0x9C);
    v[1] = func_00283198(F(obj, 0xF8)) * F(state, 0x9C);
    v[2] = 0;
    func_002AD6F0(state + 0x50, v, obj + 0xF0, obj + 0xF0);
    F(obj, 0x48) = F(state, 0x9C) * 14.999999f;

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
            I(state, 0xA0) = PlayMobySound(0, 4, obj);
    }
}
