/* Complete nonmatching reconstruction; 1120/1112 bytes.
 * -O2 -G8 -ffunction-sections.
 * Local release results: US 0/3, US2 0/3, PAL absent.
 * 3 bounded source hypotheses. Remaining: Projectile scratch ownership, query setup and addressed transfers.
 * Reopen with independent original lifetime/control-flow evidence.
 * Full aligned 48-byte query covers the 40-byte collision-helper read.
 * The exclusive emission alternative shares the same storage; the seed is
 * another complete 16-byte vector. A natural frame view gives 1140 bytes.
 * The retained early sparse read is equivalent: audited 00282CC0 writes
 * only its local output. Particle constructors return pointers; query and
 * timer helpers retain their real integer returns and every live argument.
 */
#include "common.h"
typedef int ProjectileQuad __attribute__((mode(TI)));
typedef union { ProjectileQuad bits; float v[4]; } ProjectileVector __attribute__((aligned(16)));
typedef struct {
    ProjectileVector direction;
    void *owner;
    u32 flags;
    u8 kind, subtype;
    u16 classId;
    float damage;
    int enabled;
} ProjectileQuery;
typedef union {
    ProjectileQuery query;
    struct { ProjectileVector point, velocity, random; } emission;
} ProjectileWorkspace;
typedef char ProjectileQueryExtent[sizeof(ProjectileQuery) == 0x30 ? 1 : -1];
extern float D_L18_001B234C, D_L18_001B2350;
extern int D_L18_001B2348 __attribute__((sda));
extern u8 D_L18_002BDA10[], D_L18_001BFC18[], D_L18_001A8F10[];
extern void func_00282CC0(void *, const void *, const void *), func_00282F20(void *, const void *, float);
extern void func_00282D30(void *, const void *, float), func_00283098(void *, const void *, const void *);
extern void func_002ACEC0(void *, const void *, const void *, float);
extern float func_00282DF0(void *), func_002A7878(float, float), func_002A7940(void);
extern void *func_002C16C0(void *, void *, int, int, int, int, float, float, float, float, float);
extern void *func_002BD8B0(void *, void *, int, int, int, int, float);
extern int func_001163B0(void), func_002761F8(void *, void *, int, void *, void *);
extern int func_00277258(void *, int, void *, float), func_00282948(int *);
extern int func_00277F48(void *, int, void *, void *, float);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void func_0029F338(void *);

/* Advance the projectile, emit its trail, and apply the collision query on impact. */
void func_L18_004401E0(u8 *object)
{
    ProjectileVector next, seed;
    ProjectileWorkspace workspace;
    u8 *state = *(u8 **)(object + 0x68);
    u8 *tuning = D_L18_002BDA10;
    float length;
    int sparse = D_L18_001B234C > 0.9f || D_L18_001B2350 > 0.9f;
    func_00282CC0(&next, object + 0x10, state);
    if (!(sparse && (D_L18_001B2348 & 1))) {
        length = func_00282DF0(state);
        workspace.emission.random.bits = 0;
        workspace.emission.random.v[0] = func_002A7878(-1.0f, 1.0f);
        workspace.emission.random.v[1] = func_002A7878(-1.0f, 1.0f);
        workspace.emission.random.v[2] = func_002A7878(-1.0f, 1.0f);
        workspace.emission.velocity.bits = workspace.emission.random.bits;
        func_00282F20(&workspace.emission.velocity, &workspace.emission.velocity,
                      func_002A7878(*(float *)tuning, *(float *)(tuning + 4)) * 0.016666668f);
        func_00282D30(&workspace.emission.point, state,
                      func_002A7878(*(float *)(tuning + 8), *(float *)(tuning + 0xC)));
        func_00282CC0(&workspace.emission.velocity, &workspace.emission.velocity, &workspace.emission.point);
        func_00282F20(&workspace.emission.point, state, func_002A7878(0.0f, 1.0f) * length);
        func_00282CC0(&workspace.emission.point, &workspace.emission.point, object + 0x10);
        func_002C16C0(object + 0x10, &workspace.emission.velocity,
                      *(int *)(tuning + 0x10), *(int *)(tuning + 0x14), *(int *)(tuning + 0x18), *(int *)(tuning + 0x1C),
                      *(float *)(tuning + 0x20), *(float *)(tuning + 0x24), *(float *)(tuning + 0x28), *(float *)(tuning + 0x2C), 0.0f);
        seed.bits = 0;
        seed.v[2] = *(float *)(tuning + 0x30);
        workspace.emission.random.bits = seed.bits;
        func_00283098(&workspace.emission.random, &workspace.emission.random, object + 0xC0);
        func_002ACEC0(&workspace.emission.random, &workspace.emission.random, object + 0xC0, func_002A7940());
        if (func_001163B0() & 1)
            func_002BD8B0(&workspace.emission.point, &workspace.emission.random,
                          *(int *)(tuning + 0x34), *(int *)(tuning + 0x38), *(int *)(tuning + 0x40), *(int *)(tuning + 0x44),
                          (float)*(int *)(tuning + 0x3C));
    }
    workspace.query.owner = object;
    workspace.query.flags = 0x10001;
    workspace.query.enabled = 1;
    workspace.query.damage = *(float *)(state + 0x20);
    qcopy(&workspace.query.direction, state);
    func_00282F20(&workspace.query.direction, &workspace.query.direction, *(float *)(state + 0x24));
    workspace.query.direction.v[3] = 5627.9248046875f;
    workspace.query.kind = state[0x28];
    workspace.query.subtype = state[0x2C];
    workspace.query.classId = *(u16 *)(object + 0xAA);
    if (func_002761F8(object + 0x10, &next, 0, *(void **)(state + 0x10), &workspace.query) ||
        func_00277258(&next, 0, *(void **)(state + 0x10), 0.2f) || func_00282948((int *)(state + 0x34))) {
        if (*(void **)D_L18_001BFC18) {
            if (*(void **)D_L18_001BFC18 == *(void **)(state + 0x10)) return;
            func_00277F48(object + 0x10, 0, *(void **)(state + 0x10), &workspace.query, 0.5f);
            func_002ABBB8(object, D_L18_001A8F10, 0, 0.0f, 0.0f, 0, 2, 10,
                          0.0f, 0.0f, 9.0f, 0.6660000085830688f, 0, 0.0f, 0, 1, -1, 0, 0x810001);
        } else {
            func_002ABBB8(object, D_L18_001A8F10, 0, 0.0f, 0.0f, 0, 2, 8,
                          0.0f, 0.0f, 9.0f, 0.5f, 0, 0.0f, 0, 1, -1, 0, 0x810001);
        }
        func_0029F338(object);
    } else qcopy(object + 0x10, &next);
}
