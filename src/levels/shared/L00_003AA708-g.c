/* Updates a homing projectile: acquires a target, flies its launch, turn and seek phases, rebuilds
   its orientation, and detonates on a hit, on expiry or at the level bounds. */
#include "common.h"
typedef struct {
    u8 pad0[0x18];
    char *moby;
    s32 count;
    f32 pos[4];
    f32 normal[4];
} CollResult;

extern char D_00189E20[];
extern CollResult D_L00_001BF200 __attribute__((aligned(16)));
extern u8 D_00188660[];

extern void func_00300190(void *, void *);
extern void func_00282A88(void *, int);
extern int func_00282948(void *);
extern int func_00282978(void *);
extern char *func_002AF580(void *, void *, int *, float, float, void *, int, int, float, float, float, int, int);
extern char *func_L00_0037DEF8(char *, char **, int, int *, int);
extern void func_L00_0037DD18(char *, char *, int);
extern void func_002A7470(void *, int, int, int);
extern void func_002AFFD8(void *, void *, int);
extern void func_002FEE70(int, void *, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern float func_00282DF0(void *);
extern float func_00282DB0(void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282E48(void *, void *);
extern float func_00282C48(float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_002AA3A8(float *, float, float *, float, float, float);
extern int func_002E59B0(void *, int);
extern int func_002E5CF8(int, int, void *);
extern void func_002E59F8(int);
extern void func_L00_003AB388(char *, char *, void *);
extern void func_L00_003AB618(void *, char *, char *, void *, int, float, float, float);
extern void func_L00_003AB6F0(char *, void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_002A7C00(float, float, float);
extern float *func_002AB1F0(char *);
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern void func_002AEF28(char *, char *, char *, float, float, float);
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern void func_002A9288(char *, float);
extern void func_L00_0031BDC0(void *, void *, void *, void *);
extern int func_00277258(void *, int, void *, float);
extern void func_002FEE50(int);
extern void func_0029F338(void *);

#define HERO_PLAYER (*(char **)(D_00189E20 + 0x2290))
#define F(p, o) (*(float *)((char *)(p) + (o)))
#define I(p, o) (*(int *)((char *)(p) + (o)))
#define H(p, o) (*(short *)((char *)(p) + (o)))
#define P(p, o) (*(char **)((char *)(p) + (o)))
#define B(p, o) (*(u8 *)((char *)(p) + (o)))

/* Moby update: Seeker Projectile (class 1497, PS3 name). */
void func_L00_003AA708(char *moby)
{
    struct {
        float saved[4];
        union {
            struct { char *list[32]; int count, found; } search;
            struct { float dir[4], a[4], b[4], c[4], d[4], e[4]; } flight;
        } phase;
        int hitPlayer;
    } work __attribute__((aligned(16)));
    char *state = P(moby, 0x68);
    int moved;
    char *hero;
    float magnitude;

    func_00300190(moby + 0x10, moby + 0x10);
    qcopy(work.saved, moby + 0x10);
    if (!P(state, 0x14)) {
        work.phase.search.count = 0;
        func_00282A88(work.phase.search.list, 0x80);
        if (P(state, 0x74)) {
            if (func_00282948(state + 0x78)) {
                P(state, 0x14) = P(state, 0x74);
                P(state, 0x74) = 0;
            }
        } else {
            char *target;
            char *hero;
            SelectBestTargetInCone(moby + 0x10, state, &work.phase.search.count, 3.14159298f, 3.14159298f, work.phase.search.list, 0x20, 0, 8.0f, 0.0f, 0.0f, 0, 0);
            work.phase.search.found = 0;
            hero = D_00189E20;
            target = func_L00_0037DEF8(P(hero, 0x2290), work.phase.search.list, work.phase.search.count, &work.phase.search.found, -1);
            P(state, 0x14) = target;
            if (!target)
                goto acquired;
            if (work.phase.search.found)
                KeyOwnerTableInsert(P(hero, 0x2290), target, 0x14);
        }
        if (P(state, 0x14)) {
            B(moby, 0x20) = 1;
            func_002A7470(moby, 0, 0, 10);
            qcopy(state + 0x40, state);
            H(state, 0x54) = 20;
        }
    }
acquired:
    func_002AFFD8(moby + 0x10, work.phase.flight.dir, 1);
    func_002FEE70(I(state, 0x70), state, 0);
    switch (B(moby, 0x20)) {
    case 0: {
        float step;
        FastVecAdd(moby + 0x10, moby + 0x10, state);
        qcopy(work.phase.flight.a, moby + 0x10);
        moved = 0;
        FastVecScale(work.phase.flight.b, work.phase.flight.dir, 0.5f);
        FastVecSub(work.phase.flight.c, moby + 0x10, work.phase.flight.b);
        if (CollLine(work.phase.flight.a, work.phase.flight.c, 0x12, HERO_PLAYER, 0)) {
            FastVecSub(work.phase.flight.d, moby + 0x10, D_L00_001BF200.pos);
            step = 0.5f - FastVecLength(work.phase.flight.d);
            if (step > 0.06666667f)
                step = 0.06666667f;
            if (F(state, 0x7C) < step) {
                moved = 1;
                FastVecScale(work.phase.flight.b, work.phase.flight.b, step + step);
                FastVecAdd(moby + 0x10, moby + 0x10, work.phase.flight.b);
                F(state, 0x7C) = step;
            }
        }
        if (!moved && F(state, 0x7C) != 0.0f) {
            FastVecScale(work.phase.flight.d, work.phase.flight.dir, F(state, 0x7C));
            FastVecAdd(moby + 0x10, moby + 0x10, work.phase.flight.d);
            func_002AA3A8((float *)(state + 0x7C), 0.0f, (float *)(state + 0x58), 0.02f, 0.2f, 0.0f);
            if (F(state, 0x7C) < 0.001f)
                F(state, 0x7C) = 0.0f;
        }
        if (!func_002E59B0(moby, I(state, 0x5C)))
            I(state, 0x5C) = PlayMobySound(0, 4, moby);
        if (FastDecTimer(state + 0x18)) {
            D_L00_001BF200.moby = 0;
            func_L00_003AB388(moby, state, moby + 0x10);
            func_002FEE50(I(state, 0x70));
            func_0029F338(moby);
            return;
        }
        break;
    }
    case 3: {
        char *target;
        if (FastDecTimer(state + 0x54)) {
            D_L00_001BF200.moby = 0;
            func_L00_003AB388(moby, state, moby + 0x10);
            func_002FEE50(I(state, 0x70));
            func_0029F338(moby);
            return;
        }
        {
            float now = IntToFloat(H(state, 0x54));
            float total = IntToFloat(10);
            float ratio = now / total;
            F(state, 0x50) = func_002A7C00(0.5f, 1.5f, ratio);
        }
        target = P(state, 0x14);
        if (target) {
            u8 kind = B(target, 0x20);
            if (kind == 0xFE)
                goto drift;
            if (kind == 0xFD)
                goto drift;
            if (!I(target, 0x98))
                goto drift;
        }
        func_L00_003AB618(moby + 0x10, state, target, state + 0x30, 1, 0.02f, 0.3f, 0.0f);
    drift:
        FastVecAdd(moby + 0x10, moby + 0x10, state);
        break;
    }
    case 1:
        if (FastDecTimer(state + 0x54)) {
            B(moby, 0x20) = 2;
            H(state, 0x56) = 10;
        }
        func_L00_003AB618(moby + 0x10, state, P(state, 0x14), state + 0x30, 0, 0.04f, 0.3f, 0.0f);
        FastVecScale(state + 0x40, state + 0x40, 0.85f);
        FastVecAdd(moby + 0x10, moby + 0x10, state + 0x40);
        {
            float now = IntToFloat(H(state, 0x54));
            float total = IntToFloat(20);
            float ratio = now / total;
            F(state, 0x50) = func_002A7C00(1.5f, 0.5f, ratio);
        }
        if (P(state, 0x14)) {
            FastVecSub(work.phase.flight.a, moby + 0x10, P(state, 0x14) + 0x10);
            vec_scale_to_length(work.phase.flight.a, work.phase.flight.a, 0.083333336f);
            FastVecAdd(moby + 0x10, moby + 0x10, work.phase.flight.a);
        }
        break;
    case 2: {
        float half = IntToFloat(10) * 0.5f;
        float t = IntToFloat(H(state, 0x56)) - half;
        float ratio = t / half;
        float scale;
        if (ratio < 0.0f)
            ratio = 0.0f;
        scale = ratio * 0.083333336f;
        if (P(state, 0x14)) {
            FastVecSub(work.phase.flight.a, moby + 0x10, P(state, 0x14) + 0x10);
            vec_scale_to_length(work.phase.flight.a, work.phase.flight.a, scale);
            FastVecAdd(moby + 0x10, moby + 0x10, work.phase.flight.a);
        }
        if (FastDecTimer(state + 0x56)) {
            B(moby, 0x20) = 3;
            vec_scale_to_length(state, state, 1.0f);
            if (P(state, 0x14)) {
                float targetScale;
                func_002AFFD8(moby + 0x10, work.phase.flight.a, 1);
                targetScale = func_002AB1F0(P(state, 0x14))[4];
                FastVecScale(work.phase.flight.b, work.phase.flight.a, targetScale);
                FastVecAdd(work.phase.flight.c, P(state, 0x14) + 0x10, work.phase.flight.b);
                H(state, 0x54) = FloatToInt(fast_vec_dist(work.phase.flight.c, moby + 0x10) + 5.0f);
            } else {
                H(state, 0x54) = 10;
            }
            if (I(state, 0x5C) != -1) {
                u8 *slot = D_00188660 + I(state, 0x5C) * 0x70;
                if (*(char **)(slot + 0x88) == moby && slot[0x74])
                    func_002E59F8(I(state, 0x5C));
            }
            I(state, 0x5C) = -1;
            PlayMobySound(1, 0, moby);
        }
        break;
    }
    }
    if (F(moby, 0x10) < 2.0f || F(moby, 0x10) > 1021.0f || F(moby, 0x14) < 2.0f || F(moby, 0x14) > 1021.0f
        || F(moby, 0x18) < 2.0f || F(moby, 0x18) > 1021.0f) {
        func_002FEE50(I(state, 0x70));
        func_0029F338(moby);
        return;
    }
    qcopy(work.phase.flight.a, moby + 0x10);
    FastVecScale(work.phase.flight.b, work.phase.flight.dir, -2.0f);
    FastVecAdd(work.phase.flight.b, moby + 0x10, work.phase.flight.b);
    if (CollLine(work.phase.flight.a, work.phase.flight.b, 0x12, moby, 0)) {
        float length, limit;
        FastVecSub(work.phase.flight.c, work.phase.flight.a, D_L00_001BF200.pos);
        length = FastVecLength(work.phase.flight.c);
        if (length < 0.0001f) {
            D_L00_001BF200.moby = 0;
            func_L00_003AB388(moby, state, moby + 0x10);
            func_002FEE50(I(state, 0x70));
            func_0029F338(moby);
            return;
        }
        limit = 0.025000002f;
        FastVecScale(work.phase.flight.c, work.phase.flight.c, 1.0f / length);
        FastVecAdd(work.phase.flight.d, D_L00_001BF200.pos, work.phase.flight.c);
        FastVecSub(work.phase.flight.e, work.phase.flight.d, moby + 0x10);
        if (FastVecDot(work.phase.flight.e, work.phase.flight.dir) > 0.0f) {
            float distance = FastVecLength(work.phase.flight.e);
            if (distance > limit)
                FastVecScale(work.phase.flight.e, work.phase.flight.e, limit / distance);
            FastVecAdd(moby + 0x10, moby + 0x10, work.phase.flight.e);
        }
    }
    magnitude = 1.0f;
    vec_scale_to_length(moby + 0xC0, state, magnitude);
    FastVecCross(moby + 0xD0, moby + 0xC0, work.phase.flight.dir);
    vec_scale_to_length(moby + 0xD0, moby + 0xD0, magnitude);
    magnitude = 0.00001f;
    FastVecCross(moby + 0xE0, moby + 0xD0, moby + 0xC0);
    F(state, 0x20) = FastAddRotations(F(state, 0x20), 0.06f);
    FastVecScale(work.phase.flight.c, work.phase.flight.dir, F(state, 0x24));
    FastVecSub(moby + 0x10, moby + 0x10, work.phase.flight.c);
    F(state, 0x24) = func_00283198(F(state, 0x20)) * 0.15f;
    FastVecScale(work.phase.flight.c, work.phase.flight.dir, F(state, 0x24));
    FastVecAdd(moby + 0x10, moby + 0x10, work.phase.flight.c);
    func_002AEF28(moby, state + 0x28, state + 0x2C, 0.5f, 0.1f, 0.025f);
    if (func_00282C48(F(moby, 0xF0)) > magnitude) {
        func_002AB668(work.phase.flight.c, moby + 0xC0, F(moby, 0xF0));
        func_002ACDE8(moby + 0xD0, moby + 0xD0, work.phase.flight.c);
        func_002ACDE8(moby + 0xE0, moby + 0xE0, work.phase.flight.c);
    }
    if (func_00282C48(F(moby, 0xF4)) > magnitude) {
        func_002AB668(work.phase.flight.c, moby + 0xD0, F(moby, 0xF4));
        func_002ACDE8(moby + 0xC0, moby + 0xC0, work.phase.flight.c);
        func_002ACDE8(moby + 0xE0, moby + 0xE0, work.phase.flight.c);
    }
    work.hitPlayer = 0;
    moved = 0;
    func_002A9288(moby, 0.2f);
    hero = D_00189E20;
    if (CollLine(work.saved, moby + 0x10, 0x10, P(hero, 0x2290), 0)) {
        work.hitPlayer = 1;
    } else if (B(moby, 0x20) == 3) {
        FastVecScale(work.phase.flight.c, work.phase.flight.dir, func_002AB1F0(P(state, 0x14))[4]);
        FastVecAdd(work.phase.flight.d, P(state, 0x14) + 0x10, work.phase.flight.c);
        func_L00_0031BDC0(work.phase.flight.e, work.saved, moby + 0x10, work.phase.flight.d);
        if (fast_vec_dist(work.phase.flight.e, work.phase.flight.d) <= 0.5f) {
            moved = 1;
            qcopy(moby + 0x10, work.phase.flight.e);
            D_L00_001BF200.moby = P(state, 0x14);
        }
    } else if (func_00277258(moby + 0x10, 0x10, P(hero, 0x2290), 0.2f)) {
        moved = 1;
        qcopy(moby + 0x10, D_L00_001BF200.normal);
    }
    if (moved || work.hitPlayer) {
        func_L00_003AB388(moby, state, moby + 0x10);
        func_002FEE50(I(state, 0x70));
        func_0029F338(moby);
        return;
    }
    if (F(moby, 0x10) < 2.0f || F(moby, 0x10) > 1021.0f || F(moby, 0x14) < 2.0f || F(moby, 0x14) > 1021.0f
        || F(moby, 0x18) < 2.0f || F(moby, 0x18) > 1021.0f) {
        func_002FEE50(I(state, 0x70));
        func_0029F338(moby);
        return;
    }
    FastVecScale(work.phase.flight.c, moby + 0xC0, -0.25f);
    FastVecAdd(work.phase.flight.c, work.phase.flight.c, moby + 0x10);
    func_L00_003AB6F0(moby, work.phase.flight.c);
}
