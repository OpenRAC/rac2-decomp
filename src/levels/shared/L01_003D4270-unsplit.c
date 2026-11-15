#include "common.h"

/* Own unit: retail's PRE leaves the `!active && d->state` arm's load in place,
 * which takes gcse on the unsplit flow graph (tools/compiler/README.md). */

typedef int Quad __attribute__((mode(TI)));

typedef struct Row {
    Quad q0;
    char pad[0x20];
    Quad centre;
    char rest[0x40];
} Row;

typedef struct Pool {
    float f0, f4, f8, fc, f10, f14;
    unsigned char b18, b19;
    short s1a;
    unsigned char b1c, b1d, b1e, b1f;
    Quad pos;
    int pad30, f34;
} Pool;

typedef struct TriggerData {
    int conditions[4];
    int volume;
    struct Pool *pool;
    float f18, f1c, f20, f24, f28, f2c;
    unsigned char b30, b31, b32, b33;
    int anchor, target, state, f40;
    unsigned char b44, b45, b46, b47, b48, b49;
} TriggerData;

extern char D_00189EA0[];
extern Row *D_L01_001B264C[] __attribute__((sda));
extern Row *ref_L01_003D4270_00 __attribute__((sda));
extern char *D_L01_001FE180[];
extern char D_L01_001B94C0[];

extern int func_002ACBC8(void *, int);
extern int func_002A8508(int, int);
extern void func_L00_002D7140(void *);
extern Pool *func_L00_002D70A0(int);
extern void func_00282CF0(void *, void *, void *);
extern float func_00283248(float, float);
extern float func_00282E80(void *, void *);
extern void func_00335438(void *, void *, int, int, int);
extern void func_00335370(void *);
extern void func_003353C8(void *);
extern int func_L01_0042A568(void);
extern void func_L01_0042A6F0(int, int);
extern void func_003355A8(int);
extern int func_00283DB8(void *, float);

#define F(p, o) (*(float *)((char *)(p) + (o)))
#define B(p, o) (*(unsigned char *)((char *)(p) + (o)))

/* Watches a trigger area: while the player is inside and its conditions hold, it creates an effect and can take over the camera. */
void func_L01_003D4270(char *moby)
{
    float pos[4] __attribute__((aligned(16)));
    float rot[4];
    int clear = 1;
    TriggerData *trigger = *(TriggerData **)(moby + 0x68);
    int active = IsPointInCuboid(gHeroPosition, trigger->volume);
    Pool *pool;

    if (trigger->conditions[0] == -1 && trigger->conditions[1] == -1 &&
        trigger->conditions[2] == -1 && trigger->conditions[3] == -1)
        clear = 0;
    if (trigger->conditions[0] != -1 && CountMobysInGroupNotInState(trigger->conditions[0], -1))
        clear = 0;
    if (trigger->conditions[1] != -1 && CountMobysInGroupNotInState(trigger->conditions[1], -1))
        clear = 0;
    if (trigger->conditions[2] != -1 && CountMobysInGroupNotInState(trigger->conditions[2], -1))
        clear = 0;
    if (trigger->conditions[3] != -1 && CountMobysInGroupNotInState(trigger->conditions[3], -1))
        clear = 0;

    if (B(moby, 0x20)) {
        if (trigger->pool && (!active || clear)) {
            EndCameraOverride(trigger->pool);
            trigger->pool = 0;
        } else if (!trigger->pool && active && !clear && trigger->target == -1) {
            Pool *created;

            created = AllocCameraOverrideSlot(trigger->b33);
            trigger->pool = created;
            if (!created)
                return;
            created->f0 = trigger->f18;
            created->fc = trigger->f1c == -1.0f ? trigger->f1c : trigger->f1c * 0.01745329424738884f;
            created->f4 = trigger->f20;
            created->f8 = trigger->f24;
            if (!trigger->b45)
                created->f14 = trigger->f28;
            else
                created->f14 = -1.0f;
            created->f10 = trigger->f2c == -1.0f ? trigger->f2c : trigger->f2c * 0.01745329424738884f;
            created->s1a = trigger->b30;
            created->b1e = trigger->b31;
            created->b1f = trigger->b32;
            created->b18 = trigger->b46;
            if (trigger->f40 != -1)
                created->f34 = trigger->f40;
            if (trigger->anchor != -1) {
                if (trigger->b49)
                    created->pos = ref_L01_003D4270_00[trigger->anchor].q0;
                else {
                    FastVecSub(pos, &D_L01_001B264C[0][trigger->anchor].centre, gHeroPosition);
                    created->pos = *(Quad *)(pos);
                }
            }
        } else if (active && !trigger->state && trigger->target != -1) {
            char *camera = D_L01_001FE180[trigger->target];

            *(Quad *)(pos) = *(Quad *)(gHeroPosition);
            pos[2] += 1.25f;
            rot[2] = FastMatrixHelperA(pos[0] - F(camera, 0x10), pos[1] - F(camera, 0x14));
            rot[1] = -FastMatrixHelperA(vec_distance_xy(camera + 0x10, pos), pos[2] - F(camera, 0x18));
            rot[0] = 0;
            SetCamera5Pose(D_L01_001B94C0, D_L01_001B94C0 + 0x10, 3, 120, 0);
            CopyVectorToSelectedObject(camera + 0x10);
            SetCameraStateRotation(rot);
            trigger->state = 1;
        } else if (active && trigger->state) {
            char *camera;

            if (trigger->state == 1 && (GetShipDockingState() & 1)) {
                trigger->state = 2;
                SetCamera5Mode(1, 0);
            }
            camera = D_L01_001FE180[trigger->target];
            *(Quad *)(pos) = *(Quad *)(gHeroPosition);
            pos[2] += 1.25f;
            rot[2] = FastMatrixHelperA(pos[0] - F(camera, 0x10), pos[1] - F(camera, 0x14));
            rot[1] = -FastMatrixHelperA(vec_distance_xy(camera + 0x10, pos), pos[2] - F(camera, 0x18));
            rot[0] = 0;
            CopyVectorToSelectedObject(camera + 0x10);
            SetCameraStateRotation(rot);
        } else if (!active && trigger->state) {
            SetCameraModeState(1);
            trigger->state = 0;
        } else if (trigger->pool && trigger->anchor != -1) {
            pool = trigger->pool;
            if (trigger->b49)
                pool->pos = ref_L01_003D4270_00[trigger->anchor].q0;
            else {
                FastVecSub(pos, &D_L01_001B264C[0][trigger->anchor].centre, gHeroPosition);
                pool->pos = *(Quad *)(pos);
            }
        }

        if (trigger->pool) {
            pool = trigger->pool;
            if (!trigger->b47 && trigger->anchor != -1) {
                qcopy(pos, &ref_L01_003D4270_00[trigger->anchor].centre);
                pos[3] = 1;
                if (FastMathHelperA(pos, 255.0f) != -1) {
                    trigger->b47 = 1;
                    if (trigger->b45)
                        trigger->pool->f14 = trigger->f28;
                    if (trigger->b44) {
                        trigger->pool->b1f = 0;
                        trigger->pool->b1e = 0;
                    }
                    if (trigger->b48)
                        trigger->pool->b18 = 1;
                }
            }
            pool->f10 = trigger->f2c * 0.01745329424738884f;
        }
    } else {
        trigger->pool = 0;
        trigger->state = 0;
        trigger->b47 = 0;
        B(moby, 0x20) = 1;
        B(moby, 0x30) = 255;
    }
}
