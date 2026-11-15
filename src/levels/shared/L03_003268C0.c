/* func_L03_003268C0: spawn the level's effect bursts over the configured range. */
#include "common.h"

typedef struct { float x, y, z, w; } L03EffectVector;
typedef struct { float x, y; } L03EffectRange;
extern L03EffectRange D_L03_001AA2E8;
extern unsigned char D_L03_001A8F20[] MACRO_ADDR;
extern void func_002A7A00(L03EffectVector *, float, float);
extern float func_002A7940(void);
extern void func_00282C88(L03EffectVector *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282C48(float);
extern int func_002A77E0(int);
extern int func_002A99A0(void *, int, void *, int, float);
extern void func_L02_0032B468(void *, int, void *, void *, int, int, void *, void *, void *, float);

/* Launches a burst of small effect objects from an object, some at set places and some at random nearby points. */
void func_L03_003268C0(unsigned char *object, int first, int count, int randomFirst,
                        int randomCount, int limit, int alternate, void *offset) {
    L03EffectVector velocity;
    L03EffectRange range = D_L03_001AA2E8;
    L03EffectVector points[16];
    L03EffectVector rotation;
    int flags = alternate ? 2 : 0;
    int i, found;
    if (first > 0 && count > 0) {
        for (i = 0; i < count; i++) {
            RandomDirectionVector(&velocity, range.x, range.y);
            velocity.z = FloatAbs(velocity.z) * 1.5f;
            FastVecAdd(&velocity, &velocity, offset);
            SpawnFlyingFragment(object, first + i, object + 0x10, object + 0xF0,
                            0, flags, &velocity, D_L03_001A8F20, D_L03_001A8F20, 0.0f);
        }
    }
    if (randomFirst > 0 && randomCount > 0) {
        found = ScatterPointsInCollisionShapes(object, limit, points, 0xFFFF, 1000.0f);
        if (found) {
            for (i = 0; i < limit && i < found; i++) {
                RandomDirectionVector(&velocity, range.x, range.y);
                velocity.z = FloatAbs(velocity.z) * 1.5f;
                FastVecAdd(&velocity, &velocity, offset);
                ClearVector128(&rotation);
                rotation.x = RandomAngle();
                rotation.y = RandomAngle();
                rotation.z = RandomAngle();
                SpawnFlyingFragment(object, randomFirst + RandomIntBelow(randomCount),
                                &points[i], &rotation, 0, flags, &velocity,
                                D_L03_001A8F20, D_L03_001A8F20, 0.0f);
            }
        }
    }
}
