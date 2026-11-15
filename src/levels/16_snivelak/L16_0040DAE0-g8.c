#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct { TI128 row[4]; } SnivelakMatrix;
extern void func_002A7470(void *, s32, s32, s32);
extern void *func_0029EFD0(s32);
extern float func_L07_003F90E8(s32, s32, float, float);
extern void func_L00_00310748(void *, s32, float, float, void *);
extern void func_002B37E8(void *, void *);
extern void func_002AAC80(void *, float, float, float, float);
extern u8 *func_0032C700(void *, s32, s32, s32, s32, s32, s32, s32, float, float,
                          s32, s32, s32, void *);
extern u8 D_L16_001A8F20[] __attribute__((sda));
extern float D_L16_001B1648 __attribute__((sda));
extern float D_L16_001B1658 __attribute__((sda));
extern float D_L16_001B1668 __attribute__((sda));

/* Creates a small shot object owned by another object, starting at the given position and facing. */
u8 *func_L16_0040DAE0(u8 *owner, SnivelakMatrix *matrix)
{
    u8 *obj;
    u8 *state;
    u8 *pos;
    float scale;
    s32 n;
    TI128 *dst;
    TI128 *src;
    obj = CreateMoby(0xF4E);
    if (obj) {
        scale = InterpolateBetweenLimits(0, 15, 0.125f, 0.3f);
        StoreTransformedTableEntry(obj, 0, scale, 0.0f, D_L16_001A8F20);
        state = *(u8 **)(obj + 0x68);
        *(s32 *)(state + 0x68) = -1;
        InitChildObjectFromParent(obj, owner);
        pos = obj + 0x10;
        qcopy(pos, matrix->row);
        SpawnExplosion(pos, 0, 0, 0, 0, 20, 45, 1, 2.0f, 20.0f, 1, 0, 0, 0);
        dst = (TI128 *)state;
        src = matrix->row;
        n = 3;
        do { qcopy(dst, src); src++; dst++; } while (--n >= 0);
        ApproachTargetWithBraking(state + 0x50, 1.0f, 1.0f,
                      D_L16_001B1648 * 0.00027777778f,
                      D_L16_001B1658 * 0.016666668f);
        if (obj[0x43] != 1) StartAnimationBlended(obj, 1, 0, 1);
        *(float *)(obj + 0x2C) = *(float *)(*(u8 **)(obj + 0x24) + 0x24) * D_L16_001B1668;
    }
    return obj;
}
