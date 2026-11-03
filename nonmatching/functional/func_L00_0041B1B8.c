/* functional: high. The near-miss draft (1656/1672 bytes; allocation and spills differ) with its ref_ placeholders named from level 00's places in functions.tsv (0x2E67A0 func_0027C878, 0x31A7C0 func_002A7878, 0x41AEF8 func_L00_0041AEF8, 0x2EE138 func_00282CF0, 0x2EE3D0 func_00282F20, 0x2EE220 func_00282DD8, 0x2EE178 func_00282D30, 0x2EE5D8 func_002830C0, 0x2EAC30 func_00280B90), func_0027C878 returning a 64-bit word (retail stores it with sd), func_00280B90 declared as the port's host routine defines it (host/render.c: gaddr, int, int), and the signature its caller func_L00_0041AE28 uses (the colour and count arguments are never read; retail reads only $a0 and $f12). Retail's MMI words are por zero clears of the two offset quadwords, plain zero stores here. */
/* func_L00_0041B1B8 (shared, 27 places): draws a three-layer trail along the 35-entry position ring at
 * *0x1B144C (64-byte entries, newest at pvars+0x48, pvars+0x44 points). Three packets (shaders 10, 14,
 * 43; colours 0x609F9F9F, 0x507F7F7F, 0x55103080; UVs from pvars+0x58/+0x5C), a random half-width
 * (func_002A7878(width/2, width)) for the narrow layers and six times that for the glow; each segment builds
 * a camera-facing basis (eye 0x1B8DC0) at the ring point, transforms its two new corners, draws the three
 * packets (func_00280B90 with no matrix), then shifts the corners, tapers both widths by 0.94 and copies the
 * far colour to the near corners. The last segment's corners are transformed once more after the loop.
 * From the near-miss draft nonmatching/levels/func_L00_0041B1B8.c. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } TrailVector;
typedef struct { TrailVector v[4]; int color[4]; float uv[8]; unsigned long tag[4]; } TrailPacket;
/* A ring entry is 64 bytes; only its first position is used here. */
typedef struct { TrailVector position, other; char pad[32]; } TrailPoint;
typedef struct { TrailVector position; char pad[0x34]; int count, index; char pad4C[12]; float u, v; } TrailState;

extern TrailPoint *D_L00_001B144C __attribute__((sda));
extern TrailVector D_L00_001B8DC0;
extern unsigned long func_0027C878(int);
extern float func_002A7878(float, float);
extern void func_L00_0041AEF8(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(unsigned int, int, int); /* as the port's host routine (host/render.c) defines it */

void func_L00_0041B1B8(char *self, unsigned int color, int count, float width)
{
    TrailPacket core, streak, glow;
    /* func_002830C0 reads all four consecutive columns. */
    TrailVector basis[4], narrowOffset, wideOffset, first, second;
    TrailState *p = *(TrailState **)(self + 0x68);
    int index, prev, next, i;
    float half;

    if (p->count == 0)
        return;
    core.tag[1] = func_0027C878(10);
    core.tag[3] = 0x4000000064UL;
    core.color[0] = core.color[3] = core.color[2] = core.color[1] = 0x609F9F9F;
    core.tag[2] = 0xFF9000000260UL;
    core.tag[0] = 0;
    streak.tag[1] = func_0027C878(14);
    streak.tag[3] = 0x4000000068UL;
    streak.color[0] = streak.color[3] = streak.color[2] = streak.color[1] = 0x507F7F7F;
    streak.tag[2] = 0xFF9000000260UL;
    streak.tag[0] = 0;
    glow.tag[1] = func_0027C878(43);
    narrowOffset.q = 0;
    half = width * 0.5f;
    glow.tag[3] = 0x5000000068UL;
    glow.tag[2] = 0xFF9000000260UL;
    glow.color[0] = glow.color[3] = glow.color[2] = glow.color[1] = 0x55103080;
    glow.tag[0] = 0;
    narrowOffset.f[3] = 1.0f;
    narrowOffset.f[2] = func_002A7878(half, width);
    wideOffset.q = 0;
    wideOffset.f[3] = 1.0f;
    wideOffset.f[2] = narrowOffset.f[2] * 6.0f;
    func_L00_0041AEF8(&core);
    core.uv[0] = p->u;        core.uv[1] = p->v;
    core.uv[2] = p->u;        core.uv[3] = p->v + 1.0f;
    core.uv[4] = p->u + 1.0f; core.uv[5] = p->v;
    core.uv[6] = p->u + 1.0f; core.uv[7] = p->v + 1.0f;
    streak.uv[0] = p->u;        streak.uv[1] = 0.0f;
    streak.uv[2] = p->u;        streak.uv[3] = 1.0f;
    streak.uv[4] = p->u + 1.0f; streak.uv[5] = 0.0f;
    streak.uv[6] = p->u + 1.0f; streak.uv[7] = 1.0f;
    glow.uv[0] = p->u;        glow.uv[1] = 0.0f;
    glow.uv[2] = p->u;        glow.uv[3] = 1.0f;
    glow.uv[4] = p->u + 1.0f; glow.uv[5] = 0.0f;
    glow.uv[6] = p->u + 1.0f; glow.uv[7] = 1.0f;
    first.q = p->position.q;
    index = p->index;
    second.q = D_L00_001B144C[index].position.q;
    func_00282CF0(&basis[0], &second, &first);
    func_00282F20(&basis[0], &basis[0], 1.0f);
    func_00282CF0(&basis[1], &D_L00_001B8DC0, &first);
    func_00282DD8(&basis[2], &basis[1], &basis[0]);
    func_00282F20(&basis[2], &basis[2], 1.0f);
    func_00282DD8(&basis[1], &basis[0], &basis[2]);
    basis[3].q = first.q;
    core.v[0].q = narrowOffset.q;
    func_00282D30(&core.v[1], &core.v[0], -1.0f);
    func_002830C0(&core.v[0], &core.v[0], &basis[0]);
    func_002830C0(&core.v[1], &core.v[1], &basis[0]);
    streak.v[0].q = core.v[0].q;
    streak.v[1].q = core.v[1].q;
    glow.v[0].q = wideOffset.q;
    func_00282D30(&glow.v[1], &glow.v[0], -1.0f);
    func_002830C0(&glow.v[0], &glow.v[0], &basis[0]);
    func_002830C0(&glow.v[1], &glow.v[1], &basis[0]);
    for (i = 1; i < p->count; i++) {
        core.v[2].q = narrowOffset.q;
        func_00282D30(&core.v[3], &core.v[2], -1.0f);
        glow.v[2].q = wideOffset.q;
        func_00282D30(&glow.v[3], &glow.v[2], -1.0f);
        prev = index - 1;
        next = (-1 < prev) ? prev : 34;
        first.q = D_L00_001B144C[index].position.q;
        second.q = D_L00_001B144C[next].position.q;
        func_00282CF0(&basis[0], &second, &first);
        func_00282F20(&basis[0], &basis[0], 1.0f);
        func_00282CF0(&basis[1], &D_L00_001B8DC0, &first);
        func_00282DD8(&basis[2], &basis[1], &basis[0]);
        func_00282F20(&basis[2], &basis[2], 1.0f);
        func_00282DD8(&basis[1], &basis[0], &basis[2]);
        basis[3].q = first.q;
        func_002830C0(&core.v[2], &core.v[2], &basis[0]);
        func_002830C0(&core.v[3], &core.v[3], &basis[0]);
        func_002830C0(&glow.v[2], &glow.v[2], &basis[0]);
        func_002830C0(&glow.v[3], &glow.v[3], &basis[0]);
        streak.v[2].q = core.v[2].q;
        streak.v[3].q = core.v[3].q;
        func_00280B90((unsigned int)&core, 0, 0);
        func_00280B90((unsigned int)&streak, 0, 0);
        func_00280B90((unsigned int)&glow, 0, 0);
        core.v[0].q = core.v[2].q;
        core.v[1].q = core.v[3].q;
        streak.v[0].q = streak.v[2].q;
        streak.v[1].q = streak.v[3].q;
        glow.v[0].q = glow.v[2].q;
        glow.v[1].q = glow.v[3].q;
        index = (-1 < prev) ? prev : 34;
        width = width * 0.94f;
        half = half * 0.94f;
        core.color[0] = core.color[1] = core.color[2];
        streak.color[0] = streak.color[1] = streak.color[2];
        glow.color[0] = glow.color[1] = glow.color[2];
        narrowOffset.f[2] = func_002A7878(half, width);
        wideOffset.f[2] = narrowOffset.f[2] * 6.0f;
    }
    basis[3].q = second.q;
    func_002830C0(&core.v[2], &core.v[2], &basis[0]);
    func_002830C0(&core.v[3], &core.v[3], &basis[0]);
}
