/* Adapted from OpenRAC/rac1-decomp src/game/mobyfunc.c,
 * InitMobyInstance, GPL-3.0, revision
 * 8bbc6b38d1136b66391241e660043c9136ebb518.
 * RAC2 has different animation/default-field offsets, a packed slot id, and
 * a fallback dispatch table when a class id is not the resident slot owner.
 */
#include "common.h"

typedef struct {
    u8 prefix00[0x10];
    u8 frameCount;
    s8 flags;
    u8 triggerCount, unknown13;
    int unknown14, unknown18;
    void *frames[1];
} InitialSequence;

typedef struct {
    u8 prefix00[6];
    u8 hasOverlay;
    u8 gap07[5];
    u8 animationMode;
    u8 gap0D;
    u8 meshCount;
    u8 hasJoints;
    int renderData;
    u8 gap14[0x10];
    float radius;
    u8 gap28[0x18];
    void *animationData;
    u16 flags;
    u8 gap46[2];
    InitialSequence *sequences[1];
} InitialClass;

typedef void (*MobyUpdate)(char *);
typedef struct {
    u8 prefix00[0x21];
    u8 unknown21, classSlot, unknown23;
    InitialClass *pClass;
    u8 gap28[4];
    float radius;
    u8 gap30[4];
    u16 flags, opacity;
    u64 drawFlags;
    u8 gap40[8];
    float animationSpeed, animationScale;
    u8 gap50[0x11];
    u8 unknown61, meshCount, unknown63;
    MobyUpdate update;
    u8 gap68[4];
    u8 sound, voice, triggerCount, jointCount;
    int jointFirst, jointLast;
    void *animationData;
    u8 gap7C[0x1C];
    int renderData;
    u8 gap9C[8];
    u8 red, green, blue, alpha, unknownA8;
    u8 gapA9;
    s16 classId;
    int packedSlot;
    u8 gapB0[0xD];
    u8 unknownBD;
    u8 gapBE[0x42];
} InitialMoby;

/* The constructor clears a full pool slot. The first sequence/table entries
 * cover every read by 29F390: cleared frame/sequence indices are all zero.
 * Class/sequence types are prefix views of resident resource allocations. */
typedef char InitialMobyExtent[(sizeof(InitialMoby) == 0x100) ? 1 : -1];
typedef char InitialClassPrefix[(sizeof(InitialClass) == 0x4C) ? 1 : -1];
typedef char InitialSequencePrefix[(sizeof(InitialSequence) == 0x20) ? 1 : -1];

extern u8 D_001CE4E0[];
extern s16 D_001CE300[];
extern MobyUpdate D_001CDF40[];
extern MobyUpdate D_001D04E0[];
extern InitialClass *D_001CDB80[];
extern u8 *D_001B1B5C __attribute__((sda));
extern void func_00282A60(void *, int, int);
extern void func_0029F390(u8 *);

void func_0029F0C8(void *object, int classId)
{
    InitialMoby *m = object;
    u8 slot;
    int index;
    InitialClass *resource;

    func_00282A60(m, 0, 0x100);
    slot = D_001CE4E0[classId];
    m->unknown23 = 0x80;
    m->classSlot = slot;
    m->unknownA8 = 0xFF;
    m->unknown21 = 0xFF;
    m->unknown61 = 0xFF;
    m->meshCount = 0xFF;
    m->classId = classId;
    m->drawFlags = 0x40404000000000ULL;
    m->opacity = 0x7F80;
    index = ((u8 *)m - D_001B1B5C) >> 8;
    m->packedSlot = index << 16;
    m->triggerCount = 0;
    m->sound = 0xFF;
    m->red = 0x7F;
    m->blue = 0x80;
    m->voice = 0xFF;
    m->green = 0x7F;
    m->alpha = 0x80;
    if (D_001CE300[m->classSlot] != classId) {
        m->pClass = 0;
        m->flags |= 5;
        m->renderData = 0;
        m->update = D_001D04E0[m->classSlot];
        if (m->update == 0)
            m->flags |= 2;
        return;
    }
    m->update = D_001CDF40[m->classSlot];
    if (m->update == 0)
        m->flags |= 2;
    resource = D_001CDB80[m->classSlot];
    m->pClass = resource;
    m->meshCount = resource->meshCount;
    m->flags |= resource->flags;
    m->renderData = resource->renderData;
    m->radius = resource->radius;
    m->animationSpeed = 1.0f;
    m->animationScale = 1.0f;
    if (resource->animationData != 0) {
        m->flags |= 0x10;
        m->animationData = resource->animationData;
    }
    if (m->pClass->hasJoints != 0) {
        m->jointCount = 0x18;
        m->flags |= 0x400;
        m->jointFirst = 0;
        m->jointLast = 0;
        m->unknownBD = 0;
    }
    if (m->pClass->hasOverlay != 0)
        m->unknown63 = 0x18;
    if (m->pClass->sequences[0] == 0)
        return;
    func_0029F390((u8 *)m);
    if (m->pClass->sequences[0]->frameCount >= 2)
        m->flags &= 0xFFFD;
    {
        InitialClass *p = m->pClass;
        if (p->animationMode == 1 && p->sequences[0]->frameCount < 2) {
            m->animationSpeed = 0.0f;
            if (p->sequences[0]->flags < 0)
                m->flags |= 0x40;
        }
    }
}
