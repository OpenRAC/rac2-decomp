#include "common.h"
typedef int ParticleWord __attribute__((mode(TI)));
typedef union { ParticleWord word; float f[4]; } ParticleVector;
typedef struct { int a,b,c,d; } __attribute__((aligned(16))) Quad16;
extern void func_00282CC0(void *, void *, void *);
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
extern int func_00334160(char *, int, int);
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
        if (func_002829D8(&trail->timer)) {
            trail->owner=0;
            --*(int *)(state+0x64);
            continue;
        }
        if (trail->position.f[0]<2.0f || trail->position.f[0]>1021.0f ||
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
                /* Set at the top of the arm; func_00306680 takes it after the release. */
            void *position = &ref_003054E8_00.position;
                trail->owner=0;
                --*(int *)(state+0x64);
                func_00306680(position,3);
            }
        } else {
            trail->owner=0;
            --*(int *)(state+0x64);
            func_00306680(&ref_003054E8_00.position,3);
        }
    }
}
