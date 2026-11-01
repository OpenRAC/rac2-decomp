/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/*
 * GPT-6.1 Sol (high), USA v1.01, 2026-10-29.
 * Profile: -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier.
 * check.py: 976/984 bytes, 0 of 28 places match; no linked build.
 * Remaining: the far-distance count update reuses its address and occupies
 * branch slots; retail materializes the store address separately and restores
 * s0 in the early exit slot. Byte-store scheduling around the parent/basis
 * setup also differs. Prologue allocation and denomination-case order agree.
 * New ABI evidence: all seven direct boot calls (0x002AE560..0x002AE688)
 * pass signed immediate denominations in t0; existing matched callers declare
 * int, as does RAC1's spawn_bolt_by_value in bolts_and_wrench.c. The old long
 * declaration added two narrowing shifts not present in retail's count update.
 * Data layouts follow the measured offsets and RAC1's Moby/BoltVars views.
 * Seven scalar scale symbols preserve each observed GP load and its schedule.
 * The retained source includes its required declarations. The previous draft
 * recompiles to 992/984 with its recorded G32 profile. This draft improves
 * ordered identical nonrelocated words from 143 to 198 (diagnostic only).
 * Reopen with independently measured count/address or store-lifetime evidence;
 * no flag sweep or added volatile accesses. Existing name: SpawnBoltByValue.
 */
#include "common.h"

typedef int ParticleWord __attribute__((mode(TI)));
typedef union { ParticleWord word; float f[4]; } ParticleVector;
extern float ref_00302470_03 SDATA(ref_00302470_03);
extern float ref_00302470_04 SDATA(ref_00302470_04);
extern float ref_00302470_05 SDATA(ref_00302470_05);
extern float ref_00302470_06 SDATA(ref_00302470_06);
extern float ref_00302470_07 SDATA(ref_00302470_07);
extern float ref_00302470_08 SDATA(ref_00302470_08);
extern float ref_00302470_09 SDATA(ref_00302470_09);
extern int ref_00302470_01 SDATA(ref_00302470_01);
extern ParticleVector ref_00302470_02 __attribute__((nosda));
extern int D_001A7A14 __attribute__((nosda));
extern char *D_0018C0B0 __attribute__((nosda));
extern float func_00282E48(void *, void *);
extern char *func_0029EFD0(int);
extern void func_002833F0(void *, void *);
extern void func_002AEC18(void *, int);
extern void func_002A04B8(void *, u32 *, u32 *, u32 *);
extern void func_002A0468(unsigned long long *, unsigned long long,
    unsigned long long, unsigned long long, unsigned long long);
extern void func_002A0488(void *, u32, u32, u32);
extern int func_002A77E0(int);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002AB668(void *, int, float);
extern int func_003022A0(char *, char *, float, float);
extern void func_002A0F48(void *);

typedef struct BoltVars {
    u8 pad00[0x20];
    ParticleVector velocity, spin;
    u8 kind;
    u8 pad41[0xF];
    float angle;
    u8 pad54;
    u8 flags;
    u8 pad56[2];
    float phase;
    u8 pad5c[0xC];
    float startZ;
} BoltVars;
typedef struct BoltClass { u8 pad00[0x24]; float scale; } BoltClass;
typedef struct BoltSpawnObject {
    u8 pad00[0x10];
    ParticleVector position;
    u8 state, pad21[3];
    BoltClass *objectClass;
    u8 pad28[4];
    float scale;
    u8 updateDistance, visible;
    short drawDistance;
    unsigned short flags;
    u8 pad36[0x2d];
    u8 life;
    u8 pad64[4];
    BoltVars *vars;
    u8 pad6c[0x4c];
    struct BoltSpawnObject *parent;
    u8 padbc[4];
    ParticleVector orientation[3];
    ParticleVector rotation;
} BoltSpawnObject;
/* Allocate the denomination near the camera and initialize its pickup motion. */
BoltSpawnObject *func_00302470(BoltSpawnObject *source, void *position, void *velocity, u32 flags, int value, int kind)
{
    BoltSpawnObject *object, *parent;
    BoltVars *state;
    ParticleVector *orientation;
    ParticleVector crossed, difference;
    u32 red, green, blue;
    float scale, spin, angle;
    if (func_00282E48(position,&ref_00302470_02)>=64.0f) {
        D_001A7A14+=value;
        return 0;
    }
    switch (value) {
    default:
    case 1: object=(BoltSpawnObject *)func_0029EFD0(13); scale=ref_00302470_03; break;
    case 5: object=(BoltSpawnObject *)func_0029EFD0(14); scale=ref_00302470_04; break;
    case 20: object=(BoltSpawnObject *)func_0029EFD0(15); scale=ref_00302470_05; break;
    case 50: object=(BoltSpawnObject *)func_0029EFD0(16); scale=ref_00302470_06; break;
    case 100: object=(BoltSpawnObject *)func_0029EFD0(17); scale=ref_00302470_07; break;
    case 500: object=(BoltSpawnObject *)func_0029EFD0(18); scale=ref_00302470_08; break;
    case 1000: object=(BoltSpawnObject *)func_0029EFD0(19); scale=ref_00302470_09; break;
    }
    if (object) {
    state=object->vars;
    state->kind=(u8)kind;
    orientation=object->orientation;
    parent=source;
    if (parent) while (parent->parent) parent=parent->parent;
    object->parent=parent;
    object->flags|=0x100;
    object->life=0x14; object->visible=1; object->state=1;
    object->updateDistance=0x40; object->drawDistance=0x40;
    object->scale=object->objectClass->scale*scale;
    func_002833F0(orientation,&object->rotation);
    func_002AEC18(object,ref_00302470_01);
    func_002A04B8(object,&red,&green,&blue);
    func_002A0468((unsigned long long *)object,0,13,0,0);
    func_002A0488(object,red,green,blue);
    qcopy(&object->position,position);
    qcopy(&state->velocity,velocity);
    if (func_002A77E0(2)) state->flags|=1;
    state->angle=func_002A7940();
    state->phase=func_002A7940();
    state->startZ=object->position.f[2];
    spin=func_002A7878(0.0f,720.0f)*0.00029088825f;
    func_00282CF0(&difference,&source->position,&object->position);
    func_00282DD8(&crossed,&state->velocity,&difference);
    func_00282F20(&state->spin,&crossed,1.0f);
    func_002AB668(&state->spin,(int)(&state->spin),spin);
    if (flags&2) {
        angle=0.0f;
        if (flags&0x10) angle=func_002A7878(-30.0f,30.0f)*0.017453294f;
        func_003022A0((char *)object,D_0018C0B0,angle,0.0f);
    }
    func_002A0F48(object);
    }
    return object;
}
