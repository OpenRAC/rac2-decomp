/* func_PAL_L11_0043D438, the PAL copy of func_L11_00437EA8: the same C with gravity -1/720 per
   frame squared becomes -1/500. */
#include "common.h"
struct RotorPath {
    int count;
    char pad04[12];
    float points[0][4];
};

struct RotorState {
    /* 0x000 */ char pad00[0x35];
    /* 0x035 */ u8 f35;
    /* 0x036 */ char pad36[0x1A];
    /* 0x050 */ float aim[4];
    /* 0x060 */ int f60;
    /* 0x064 */ char pad64[0x9C];
    /* 0x100 */ float points[13][4];
    /* 0x1D0 */ float oldPoints[13][4];
    /* 0x2A0 */ char pad2A0[0x10];
    /* 0x2B0 */ int choices[4][4];
    /* 0x2F0 */ char pad2F0[0x30];
    /* 0x320 */ int pathIndex;
    /* 0x324 */ struct RotorPath *path;
    /* 0x328 */ char pad328[8];
    /* 0x330 */ int records[10];
    /* 0x358 */ int linked;
    /* 0x35C */ char pad35C[0xC];
    /* 0x368 */ int projectileClass;
    /* 0x36C */ char pad36C[4];
    /* 0x370 */ s16 pathPoint;
    /* 0x372 */ char pad372[2];
    /* 0x374 */ s16 projectileIndex;
    /* 0x376 */ s16 projectileDelay;
    /* 0x378 */ s16 ropeCount;
    /* 0x37A */ u16 toggle;
    /* 0x37C */ char pad37C[4];
    /* 0x380 */ u8 disabled[10];
};

struct RotorAxis {
    float x, y, z;
    int w;
};

struct RotorObject {
    /* 0x00 */ char pad00[0x10];
    /* 0x10 */ float pos[4];
    /* 0x20 */ u8 mode;
    /* 0x21 */ char pad21[0x13];
    /* 0x34 */ u16 flags;
    /* 0x36 */ char pad36[0x32];
    /* 0x68 */ struct RotorState *state;
    /* 0x6C */ char pad6C[0x4C];
    /* 0xB8 */ int fB8;
    /* 0xBC */ char padBC[4];
    /* 0xC0 */ struct RotorAxis basis[3];
};

extern char D_00188660[];
extern void func_3739C0(int);
extern float func_00283CE0(int);
extern float func_002AA140(float, float, float);

extern int D_L11_001B359C __attribute__((sda));

typedef int TI128 __attribute__((mode(TI)));

extern void func_00282CF0(void *, const void *, const void *);
extern void func_00282CC0(void *, void *, void *);

static inline void stop_owned_sound(char *state, char *p)
{
    int slot = *(int *)(state + 0x14);

    if (slot != -1) {
        char *e = D_00188660 + slot * 0x70;

        if (*(char **)(e + 0x88) == p && *(unsigned char *)(e + 0x74))
            func_3739C0(slot);
    }
    *(int *)(state + 0x14) = -1;
}

extern void func_00282C88(void *);
extern void func_00282D30(void *, void *, float);

typedef union Quad {
    TI128 q;
    float f[4];
} Quad;

/* Advances the thirteen chain points one Verlet step: each moves by its damped displacement
   from its old position plus a small downward pull, and the old position takes the point's
   previous value. The damping blends 0.97 to 0.98 with the count at 0x378. */
void func_PAL_L11_0043D438(void *object)
{
    struct RotorObject *obj = object;
    struct RotorState *state = obj->state;
    float (*pos)[4];
    float (*old)[4];
    Quad saved;
    Quad delta;
    Quad gravity;
    float t;
    float damping;
    int i;

    func_00282C88(&gravity);
    pos = state->points;
    old = state->oldPoints;
    gravity.f[2] = -1.0f / 500.0f;

    t = func_00283CE0(state->ropeCount);
    damping = func_002AA140(0.97f, 0.98f, (t -= 2.0f) / func_00283CE0(8));

    for (i = 12; i >= 0; i--, pos++, old++) {
        qcopy(&saved, pos);
        func_00282CF0(delta.f, *pos, *old);
        func_00282D30(&delta, &delta, damping);
        func_00282CC0(pos, pos, &delta);
        func_00282CC0(pos, pos, &gravity);
        qcopy(old, &saved);
    }
}

#define STORED_RECORD(index) \
    ((struct RotorObject *)(((index) << 8) + D_L11_001B359C))
#define LISTED_STORE(obj, i) STORED_RECORD((obj)->state->records[i])
