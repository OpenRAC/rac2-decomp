/* 28 October 2026: 544/568 bytes in all US placements tested,
 * default -O2 -G8 -ffunction-sections; three checks. The current RAC1
 * setup_level_cameras donor guides the measured 0xA0 slot/0x20 definition
 * layouts. Raw-array versus typed owner declarations and the donor's
 * -fno-force-mem profile tie. Remaining differences include owner-base
 * lifetimes, initialization scheduling and folded addresses.
 * All qcopy/qzero accesses span complete aligned 16-byte vectors; no nc.
 * 2D7068 returns int; 2D75F0/2D9D98 return void from existing C.
 * No local/strict match. Reopen with measured source/lifetime evidence. */
/* Adapted from rac1-decomp's level_camera_setup.c (GPL-3.0), revision
 * 8bbc6b38d1136b66391241e660043c9136ebb518. RAC2 offsets and references
 * are independently measured from the retail body. */
#include "common.h"

typedef struct { float value[4]; } CameraVector __attribute__((aligned(16)));
typedef struct CameraSlot CameraSlot;
typedef struct {
    char reserved00[4];
    CameraSlot *slot;
    char reserved08[0x14];
    unsigned char priority, blendKind, reserved1E, activation;
} CameraInfo;
typedef struct {
    char reserved00[0xC];
    unsigned short id;
    char reserved0E[0xE];
    CameraInfo *info;
} CameraDefinition;
struct CameraSlot {
    char reserved00[0x74];
    int activation;
    float blendTime;
    unsigned char priority, handoff;
    short transition, unknown80, unknown82, definitionIndex;
    unsigned short id;
    unsigned char reserved88, hitWall;
    short snap, type, hardCut;
    char reserved90[0x10];
};
typedef struct {
    char reserved00[0x20];
    CameraVector up, targetUp, previousUp, upVelocity, previousHero;
    char reserved70[0x3C];
    float yaw[5];
    int collisionBits;
    void *collisionObject;
    int unknownC8, unknownCC;
    char reservedD0[0x14];
    int unknownE4, unknownE8;
    char reservedEC[4];
} CameraFollow;
typedef struct {
    char reserved000[0x194];
    void *previous;
    char reserved198[8];
    CameraFollow follow;
    short blendPhase;
    char reserved292[0x3A0 - 0x292];
    int controls[5];
    char reserved3B4[0xC];
    CameraVector clear3C0;
    char reserved3D0[0x30];
    int flags400, flags404;
} CameraSystemPrefix;
typedef struct {
    char reserved00[0x80];
    CameraVector position;
    float rotation[4];
    char reservedA0[0x2290 - 0xA0];
    char *object;
} CameraHeroPrefix;

extern CameraSystemPrefix D_L00_001B8C80;
extern CameraSlot D_L00_001B91D0[];
extern int D_L00_001BB930[];
extern int D_L00_001B1840;
extern CameraDefinition *D_L00_001B1844;
extern int D_L00_001B1848;
extern float D_L00_001A8900 __attribute__((sda));
extern CameraHeroPrefix D_00189E20;
extern int func_L00_002D7068(void);
extern void func_L00_002D75F0(void);
extern void func_00282F20(void *, void *, float);
extern void func_00282C88(void *);
extern int func_L00_002D9D48(int);
extern void func_L00_002D9D98(void);

void func_L00_002D9E80(void)
{
    CameraSystemPrefix *camera = &D_L00_001B8C80;
    CameraHeroPrefix *hero;
    CameraFollow *follow;
    CameraVector *up;
    int i, k;
    camera->flags404 = 0;
    D_L00_001A8900 = 0.85f;
    camera->flags400 = 0;
    D_L00_001B1840 = 0;
    for (k = 0; k < 48; k++) {
        D_L00_001B91D0[k].hardCut = 0;
        D_L00_001BB930[k] = 0;
    }
    func_L00_002D7068();
    func_L00_002D75F0();
    camera->previous = 0;
    camera->blendPhase = 0;
    qzero(&camera->clear3C0);
    hero = &D_00189E20;
    follow = &camera->follow;
    up = &follow->up;
    func_00282F20(up, hero->object + 0xE0, 1.0f);
    qcopy(&follow->targetUp, up);
    qcopy(&follow->previousUp, up);
    func_00282C88(&follow->upVelocity);
    qcopy(&follow->previousHero, &hero->position);
    {
        float yaw = hero->rotation[2];
        follow->collisionObject = 0;
        follow->unknownE4 = 0;
        follow->collisionBits = 0;
        follow->unknownCC = 0;
        follow->unknownE8 = 0;
        follow->yaw[0] = yaw;
        follow->yaw[4] = yaw;
        follow->yaw[3] = yaw;
        follow->yaw[2] = yaw;
        follow->yaw[1] = yaw;
    }
    i = 0;
    if (D_L00_001B1848 > 0) {
        do {
            CameraDefinition *definition = &D_L00_001B1844[i];
            CameraInfo *info = definition->info;
            CameraSlot *slot = &D_L00_001B91D0[i];
            int id;
            slot->definitionIndex = i;
            info->slot = slot;
            slot->hardCut = 0;
            slot->hitWall = 0;
            slot->snap = 0;
            slot->unknown82 = -1;
            slot->unknown80 = -1;
            slot->handoff = 0;
            slot->transition = 0;
            slot->blendTime = -1.0f;
            slot->priority = info->priority;
            slot->activation = info->activation;
            id = definition->id;
            D_L00_001BB930[i] = 1;
            slot->id = id;
            slot->type = func_L00_002D9D48((short)id);
            i++;
        } while (i < D_L00_001B1848);
    }
    func_L00_002D9D98();
    camera->blendPhase = 0;
    camera->controls[0] = 0;
    camera->controls[3] = 0;
    camera->controls[1] = 0;
    camera->controls[4] = 0;
}
