/* 3 November 2026 contract review; no new compilation or match.
 * Current 002A8C00 produces fields through +0x20 but not request +0x24.
 * Current 002A8E20 reads request +0x24 into the persistent queue +0x34.
 * This caller does not initialize contact.secondaryDamage. Fresh retail
 * confirms the request at sp+0x20, only kind/source/id stores after its
 * constructor, and no producer at sp+0x44. Its later meaning has not been
 * qualified as an opaque transfer. A typed-owner probe was kept private.
 * Resolve that producer/lifecycle before promotion; do not invent zero.
 * The original allocation/setup residual is not recompiled past this
 * unresolved input contract. No callee or reserved donor is changed.
 */
/* Claude Opus 5.5 (opus-1), 2026-10-29; upstream pinned game compiler,
 * -O2 -G0 -ffunction-sections (a unit of its own that includes common.h):
 * 688/688 bytes, 0/28 USA v1.01 places. First difference +0x4.
 * Closer than the sol-high draft: the loop now forms retail's mtlo/madd
 * table address (the table base is a local set before the loop, so combine
 * sees a loop-invariant base), and trail/snapshot/hit get retail's s0/s1/s1
 * (one char * temporary holds the snapshot source and then the hit moby;
 * global.c then ranks trail 30 refs/81 above that temporary 20/58).
 * The impact position is written &ref_003054E8_00.position in all three
 * paths: CSE's related-value turns it into collision+0x20 where the
 * collision pointer is known (damage and null paths) and leaves the
 * constant in the shared not-damageable path, as retail does.
 * Remaining (14 instructions): owner/collision s4/s5 versus retail s5/s4,
 * and the func_002A8E20 delay slot (retail sb kind, ours daddu a1).
 * The allocation is a priority tie-break: object 12 refs/125 live (2880)
 * against collision 8 refs/2x43 live (REG_EQUIV doubled, 2790); retail
 * needs collision first, i.e. collision live <= 41 or object live >= 130
 * at local-alloc time. Tried without effect: inline KillTrail helper,
 * effect-position temporary, do-while loop, contact store order,
 * descriptor scope; a common effect tail regresses to 676 bytes.
 * Needed declarations are included below. No linked or native credit.
 */
#include "common.h"
typedef int ParticleWord __attribute__((mode(TI)));
typedef union { ParticleWord word; float f[4]; } ParticleVector;
typedef struct { int a,b,c,d; } __attribute__((aligned(16))) Quad16;
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_00277258(void *, int, void *, float);
extern char ref_00305798_00[][0x30];

typedef struct {
    ParticleVector position, velocity;
    float timer;
    char *owner;
    u8 reserved28[8];
} ParticleTrail;
typedef struct {
    Quad16 normal;
    int owner, flags;
    u8 kind, source;
    unsigned short objectClass;
    float damage;
    int mode;
    float secondaryDamage;
} HitContactView;
typedef struct { u8 prefix[0x70]; float damage; u8 remainder[0xe0 - 0x74]; } ParticleDamageDescriptor;
typedef struct { u8 prefix[0x18]; char *hit; u8 pad1C[4]; ParticleVector position; } ParticleHit;
extern ParticleHit ref_003054E8_00;
extern ParticleDamageDescriptor ref_003054E8_02[];
extern u8 D_00139568[];
typedef struct { u8 prefix[0x2290]; char *moby; } ParticlePlayer;
extern ParticlePlayer D_00189E20;
extern int func_002829D8(float *);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002A8C00(char *, int, int, float, Quad16 *);
extern void func_002A8E20(char *, void *);
extern void func_00334160(char *, int, int);
extern void func_00306680(void *, int);

/* Advance owned particle trails and turn a collision into a contact and impact. */
void func_003054E8(char *object)
{
    char *state = *(char **)(object+0x68);
    ParticleVector previous, normal;
    HitContactView contact;
    ParticleTrail *trail;
    char *hit;
    ParticleHit *collision;
    int index;
    char (*table)[0x30] = ref_00305798_00;
    for (index=0; index<100; ++index) {
        trail = (ParticleTrail *)table[index];
        if (trail->owner != object) continue;
        hit = (char *)&trail->position; /* one temporary: snapshot source, then the hit moby */
        if (func_002829D8(&trail->timer) || trail->position.f[0]<2.0f || trail->position.f[0]>1021.0f ||
            trail->position.f[1]<2.0f || trail->position.f[1]>1021.0f ||
            trail->position.f[2]<2.0f || trail->position.f[2]>1021.0f) {
            trail->owner=0;
            --*(int *)(state+0x64);
            continue;
        }
        qcopy(&previous, hit);
        func_00282CC0(&trail->position,&trail->position,&trail->velocity);
        if (!func_002761F8(&previous,&trail->position,0,object,0)) continue;
        collision = &ref_003054E8_00;
        hit=collision->hit;
        if (hit) {
            if (((*(unsigned short *)(hit+0x34)&0x1000) || *(short *)(*(char **)(hit+0x24)+0x46)==5) &&
                hit!=D_00189E20.moby && *(short *)(hit+0xaa)!=0x1366) {
                ParticleDamageDescriptor *descriptor;
                func_00282F20(&normal,&trail->velocity,1.0f);
                descriptor = &ref_003054E8_02[D_00139568[0x29]];
                func_002A8C00((char *)&contact,(int)object,0x210000,
                    descriptor->damage,(Quad16 *)&normal);
                contact.objectClass=*(unsigned short *)(object+0xaa);
                contact.source=3; contact.kind=5;
                func_002A8E20(hit,&contact);
                func_00334160(hit,0x29,*(int *)(object+0xb8));
                trail->owner=0;
                            --*(int *)(state+0x64);
                func_00306680(&ref_003054E8_00.position,6);
            } else {
                trail->owner=0;
                --*(int *)(state+0x64);
                func_00306680(&ref_003054E8_00.position,3);
            }
        } else {
            trail->owner=0;
            --*(int *)(state+0x64);
            func_00306680(&ref_003054E8_00.position,3);
        }
    }
}
