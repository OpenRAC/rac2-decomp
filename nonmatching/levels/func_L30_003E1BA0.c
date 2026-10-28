/* Nonmatching museum launch/reset reconstruction, 2026-10-28.
 * No C coverage credit. Three bounded probes. Retained truthful body:
 * -O2 -G0 -ffunction-sections, US0/1,708/716B, frame0x80 exact.
 * The first diagnostic712B body incorrectly returned early on empty events;
 * branch audit corrected every path to the common object+0xA8=255 write.
 * Pure TI copies and no-split addresses worsen the corrected body to696B.
 * Remaining: copy address registers, reset-vector absolute store lifetime,
 * constructor preparation and switch transition scheduling. Reopen with an
 * independent source/lifetime witness for these operations.
 *
 * Contracts audited:002A9640 returns pointer;00273B70 returns int.
 * 003263D0 accepts a0 actor,a1 position,a2 signed count,a3 integer mode,
 * t0 full16B input vector,t1 color,t2 optional16B pointer, and f12..f15
 * four floats. Its complete592B body mutates spawned objects and has no
 * common result. 00273978 consumes actor,a1/a2 signed ints,f12 angle,
 * a3 full16B velocity,t0 full16B quaternion,t1 low8 color and returns void.
 * All locals are full vectors: subtract/XY normalize fills velocity,
 * 00282C98 writes axis, cross writes rotation, transform/add writes position.
 * Cross/normalize W is not used arithmetically before explicit quaternion W
 * overwrite; every byte read by the final velocity/quaternion consumer has
 * been initialized. Global vector/tuning extents remain incomplete. Copies
 * use approved memory-clobbering qcopy; no aliases or invented volatility.
 */

#include "common.h"
extern unsigned char D_00189EA0[];
extern unsigned char D_L30_001B3AE0[], D_L30_001B3AF0[];
extern float D_L30_001B3B20[];
extern float D_L30_001B0B78[] SDATA(D_L30_001B0B78);
extern float D_L30_001B0B7C[] SDATA(D_L30_001B0B7C);
extern float D_L30_001B0B80[] SDATA(D_L30_001B0B80);
extern float D_L30_001B0B90[] SDATA(D_L30_001B0B90);
extern float D_L30_001B0BA0[] SDATA(D_L30_001B0BA0);
extern float D_L30_001B0BB0[] SDATA(D_L30_001B0BB0);
extern int D_L30_001B0BB4[] SDATA(D_L30_001B0BB4);
extern int D_L30_001B0BB8[] SDATA(D_L30_001B0BB8);
extern float D_L30_001B0BBC[] SDATA(D_L30_001B0BBC);
extern float D_L30_001B0BC0[] SDATA(D_L30_001B0BC0);
extern float D_L30_001B0BC4[] SDATA(D_L30_001B0BC4);
extern void func_002A7750(void *, int, int);
extern void *func_002A9640(void *, unsigned int, int);
extern void func_00282C88(void *), func_00282C98(void *);
extern void func_00282CF0(void *, const void *, const void *);
extern void func_00282CC0(void *, const void *, const void *);
extern void func_00282DD8(void *, const void *, const void *);
extern void func_00282F20(void *, const void *, float), func_00282F70(void *, const void *, float);
extern void func_00283098(void *, const void *, const void *);
extern void func_002833F0(void *, const void *);
extern float func_00283198(float), func_00283180(float);
extern void func_L00_003263D0(void *, void *, float, int, int, void *, float, float, float, unsigned int, void *);
extern void func_00273978(void *, int, int, float, void *, void *, unsigned char);
extern int func_00273B70(void *);

void func_L30_003E1BA0(unsigned char *object)
{
    float velocity[4] __attribute__((aligned(16)));
    float rotation[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    switch (object[0x20]) {
    case 0:
        object[0x30] = 0xFF;
        func_002A7750(object, 1, -1);
        *(unsigned short *)(object + 0x34) |= 0x100;
        qcopy(D_L30_001B3AE0, object + 0x10);
        qcopy(D_L30_001B3AF0, object + 0xF0);
        func_00282C88(D_L30_001B3B20);
        D_L30_001B3B20[2] = 0.4f;
        break;
    case 1:
        if (!func_002A9640(object, 0x10000, 0)) break;
        func_00282CF0(velocity, object + 0x10, D_00189EA0);
        func_00282F70(velocity, velocity, D_L30_001B0B78[0] * 0.01666666753590107f);
        velocity[2] = D_L30_001B0B7C[0] * 0.01666666753590107f;
        func_00282C98(axis);
        func_00282DD8(rotation, velocity, axis);
        func_00282F20(rotation, rotation, func_00283198(-D_L30_001B0B80[0] * 0.0002908882452175021f));
        rotation[3] = func_00283180(D_L30_001B0B80[0] * 0.0002908882452175021f);
        func_00283098(position, D_L30_001B0B90, object + 0xC0);
        func_00282CC0(position, position, object + 0x10);
        func_L00_003263D0(object, position, D_L30_001B0BB0[0], D_L30_001B0BB4[0], D_L30_001B0BB8[0], D_L30_001B0BA0,
                         D_L30_001B0BBC[0], D_L30_001B0BC0[0], D_L30_001B0BC4[0], 0x50404040, 0);
        func_00273978(object, 0, -1, 15.0f, velocity, rotation, 0xFF);
        *(int *)(object + 0x98) = 0;
        func_002A7750(object, 2, -1);
        break;
    case 2:
        if (!func_00273B70(object)) break;
        func_002A7750(object, 3, -1);
        break;
    case 3:
        if (object[0x23] < 2) {
            qcopy(object + 0x10, D_L30_001B3AE0);
            func_002833F0(object + 0xC0, D_L30_001B3AF0);
            object[0x23] = 0x80;
            *(int *)(object + 0x98) = *(int *)(*(unsigned char **)(object + 0x24) + 0x10);
            func_002A7750(object, 1, -1);
        } else object[0x23] -= 2;
        break;
    default:
        break;
    }
    object[0xA8] = 0xFF;
}
