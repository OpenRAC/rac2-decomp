#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L18_001B1B40[16] __attribute__((sda));
extern int D_L18_001B1B30 __attribute__((sda));
extern float D_L18_001B1B08[2] __attribute__((sda));
extern float D_L18_001B1B00[2] __attribute__((sda));
extern float D_L18_001B1B10[4] __attribute__((sda));

extern void func_00282D30(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_L00_00324F18(void *, void *, float, float, float);
extern void func_L17_00326F38(void *, void *, float, float, float);
extern void func_L00_0033E220(void *, void *, int, int, int, int, int, int, float, float);
extern void func_L00_0032A258(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern void func_0032C700(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern int func_002A7750(void *, int, int);
extern void *func_002A9640(void *, int, int);
extern float func_002A7878(float, float);
extern void func_0029F338(void *);

/* Updates a breakable object (moby class 4484): it sets up its glow, waits to be hit, then releases a burst and an explosion and disappears. */
void func_L18_0043C778(u8 *obj) {
    float offset[4] __attribute__((aligned(16)));
    float posA[4] __attribute__((aligned(16)));
    float posB[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj + 0x68), *hit;
    int i, xOffset, yOffset;
    float *corner, *posACursor, *posBCursor;

    switch (obj[0x20]) {
    case 0:
        i = 0;
        posBCursor = posB;
        posACursor = posA;
        yOffset = 20;
        xOffset = 4;
        corner = D_L18_001B1B40;
        for (; i < 4; i++, yOffset -= 8, xOffset -= 8, corner += 4) {
            FastVecScale(offset, corner, *(float *)(obj + 0x2C));
            SpawnObjectFollowingEffect(offset, obj, 0x28808080, -1, 0, -1, 0, 0x60,
                             *(float *)(obj + 0x2C) * 1050000.f, .15f);
            LocalOffsetToWorld(obj, posACursor, corner[0], corner[1], corner[2]);
            qcopy(posBCursor, posACursor);
            if (i < 2) {
                TransformLocalPointToWorld(obj, posBCursor, (float)xOffset, 0, -4.f);
            } else {
                TransformLocalPointToWorld(obj, posBCursor, 0, (float)yOffset, -4.f);
            }
            posA[3] = .2f;
            posB[3] = 1.f;
        }
        SetMobyState(obj, 1, -1);
        break;
    case 1:
        hit = FindOwnedEffectSlot(obj, 0x4010000, 0);
        if (hit && !*(int *)state) {
            *(TI128 *)posB = 0;
            posB[0] = 3.f;
            posB[1] = 3.f;
            *(float *)(hit + 0x18) = .75f;
            FastVecScale(offset, hit + 0x10, RandomFloatRange(6.f, 8.f));
            qcopy(posA, offset);
            FastVecSub(offset, offset, posB);
            FastVecAdd(posA, posA, posB);
            ExplodeObjectIntoPieces(obj, offset, D_L18_001B1B08, D_L18_001B1B00,
                             0xFFFF, -1, D_L18_001B1B30, 9, -128, 255, 0);
            SetMobyState(obj, 2, -1);
        }
        obj[0xA8] = 255;
        break;
    case 2:
        ExplodeObjectIntoPieces(obj, D_L18_001B1B10, D_L18_001B1B08, D_L18_001B1B00,
                         0xFFFF, 0, D_L18_001B1B30, 6, 0xFA7F, 255, 0);
        LocalOffsetToWorld(obj, offset, 0, 0, 20.f);
        SpawnExplosion(offset, 0, 5, 5, 5, 5, 5, 0, 1, 0, 1, 0,
                      *(float *)(obj + 0x2C) * 2.f, 20.f);
        MarkMobySpawned(obj);
        break;
    }
}
