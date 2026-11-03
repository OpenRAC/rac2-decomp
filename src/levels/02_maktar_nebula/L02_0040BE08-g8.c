#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 quad; float f[4]; u32 word[4]; } PatrolVector;
typedef struct {
    char pad0[0x80];
    PatrolVector pos;
    char pad1[0x249C - 0x90];
    u8 *contact;
} HeroBlock;
extern HeroBlock D_00189E20;
extern u8 *D_L02_001FF1C0[];
extern float D_L02_001B1970 __attribute__((sda));
extern float D_L02_001B1974[] __attribute__((sda));
extern float D_L02_001B1978[] __attribute__((sda));
extern float D_L02_001B1930 __attribute__((sda));
extern float D_L02_001B1934 __attribute__((sda));
extern float D_L02_001B1938 __attribute__((sda));
extern float D_L02_001B193C __attribute__((sda));
extern float D_L02_001B1940 __attribute__((sda));
extern float D_L02_001B1944 __attribute__((sda));
extern float D_L02_001B1948 __attribute__((sda));
extern void func_L02_0040CAF0(u8 *);
extern float func_00283248(float, float);
extern float func_00282E80(void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern s32 func_002761F8(void *, void *, s32, void *, s32);
extern s32 func_00277258(void *, s32, void *, float);
extern s32 func_002A77E0(s32);
extern s32 func_002A8C28(void *, void *, u32, float, float, float, s32, s32, s32);
extern void func_002A7750(u8 *, u8, s32);
extern void func_002A7470(void *, s32, s32, s32);
extern void func_L02_003FC248(void *, s32, s32);
extern void func_L02_0040D180(u8 *);
extern char *func_L02_003FC098(char *);
extern s32 func_002B3868(u8 *);
extern s32 func_002B3890(u8 *);
extern void func_002B60B0(u8 *, float, float, float, float);
extern s32 func_L02_003FC0B8(char *);
extern s32 func_L00_003206B8(void *, s32);
extern void func_L01_00321178(char *, char *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002A677C(void *);
extern s32 func_002B4FF0(char *, float *, float);
extern float func_002AA548(float *, float *, float, float, float, float);
extern float func_002A7878(float, float);
extern float func_00282C48(float);
/* The second GPR is a bone index, consumed by func_0029FCC0. */
extern s32 func_002A8D70(float, float, float, void *, s32, s32, s32, s32, s32);
extern float func_002AA150(float, float, float);
extern float func_00283B98(float, float);
extern void func_002A7A00(float *, float, float);
extern void *func_002C2210(float, float, float, void *, s32, u32, s32, s32, float *, s32);
extern void func_L02_0040CEE8(u8 *);

/* Follow the patrol path, handle landing and contact states, then emit the trail. */
void func_L02_0040BE08(u8 *object)
{
    PatrolVector target;
    PatrolVector point;
    PatrolVector velocity;
    u8 *state;
    u8 *ground;
    float range;
    float height;
    s32 i;

    if (object[0x20] == 1 || object == 0 || object[0x20] == 0xFE || object[0x20] == 0xFD)
        return;
    state = *(u8 **)(object + 0x68);
    func_L02_0040CAF0(object);
    if (*(u8 **)(state + 0x184)) {
        target.quad = *(TI128 *)(*(u8 **)(state + 0x184) + 0x10);
        func_00283248(*(float *)(*(u8 **)(state + 0x184) + 0x10) - *(float *)(object + 0x10), *(float *)(*(u8 **)(state + 0x184) + 0x14) - *(float *)(object + 0x14));
    } else {
        target.quad = *(TI128 *)&D_00189E20.pos;
        func_00283248(D_00189E20.pos.f[0] - *(float *)(object + 0x10), D_00189E20.pos.f[1] - *(float *)(object + 0x14));
    }
    range = func_00282E80(object + 0x10, &target);
    if (object[0x20] == 1 || object == 0 || object[0x20] == 0xFE || object[0x20] == 0xFD)
        return;
    if (object[0x95] == 4) {
        qcopy(&point, object + 0x10);
        *(float *)(state + 0x108) -= *(float *)(state + 0x8C);
        func_00282CC0(object + 0x10, object + 0x10, state + 0x100);
        if (func_002761F8(&point, object + 0x10, 0, object, 0) ||
            func_00277258(object + 0x10, 4, object, 0.3f) || func_002A77E0(30) == 0) {
            func_002A8C28(object, object + 0x10, 0x10000, 0.5f, (float)(state[0x34] * 3), 1.0f, 0, 1, 0);
            if (*(float *)(state + 0x20) > 0.0f) {
                func_002A7750(object, 8, 3);
                if (object[0x43]) func_002A7470(object, 0, 0, 5);
            } else {
                func_L02_003FC248(object, 0, 1);
                func_L02_0040D180(object);
            }
        }
    }
    ground = 0;
    if (*(char **)(object + 0xB8))
        ground = (u8 *)func_L02_003FC098(*(char **)(object + 0xB8));
    switch (object[0x20]) {
    case 3:
        if (func_002B3868(object)) {
            func_002B60B0(object, 0.016666668f, 0.33333334f, 0.001163553f, 0.10471977f);
            object[0xBC] = 0;
        }
        if (!object[0xBC] && (s32)*(u16 *)(object + 0x96) > *(s16 *)(state + 0x1BA))
            object[0xBC] = 1;
        else if (object[0xBC] == 1) {
            if (func_L00_003206B8(object + 0x10, func_L02_003FC0B8(*(char **)(object + 0xB8))))
                func_002A7750(object, 7, 3);
            func_L01_00321178((char *)object, func_L02_003FC098(*(char **)(object + 0xB8)));
        }
        break;
    case 4:
        if (*(u16 *)(object + 0x96) > 25) {
            if (object[0x43]) func_002A7470(object, 0, 0, 5);
            func_002A7750(object, 8, 3);
        }
        break;
    case 7:
        {
            u8 *path = D_L02_001FF1C0[*(s32 *)(state + 0x180)];
            if (func_002B3868(object)) {
                u8 *cursor = path + 0x10;
                s32 closest = 0;
                s32 index;
                float best;
                func_002B60B0(object, 0.027777778f, 3.3333335f, 0.001163553f, 0.10471977f);
                *(float *)(state + 0x188) = *(float *)(ground + 8) + func_002A7878(1.0f, 3.0f);
                best = func_00282E80(object + 0x10, cursor);
                for (index = 0; index < *(s32 *)path - 1; index++) {
                    float next = func_00282E80(object + 0x10, cursor);
                    if (next < best) { best = next; closest = index; }
                    cursor += 0x10;
                }
                *(s32 *)(state + 0x194) = closest;
                *(u16 *)(state + 0x1B4) = func_002A77E0(2);
            } else {
                qcopy(&point, &((PatrolVector *)(path + 0x10))[*(s32 *)(state + 0x194)]);
                point.f[2] = *(float *)(state + 0x188);
                func_00282CF0(&velocity, &point, object + 0x10);
                func_00282F20(&velocity, &velocity, *(float *)(state + 0x198));
                func_00282CC0(object + 0x10, object + 0x10, &velocity);
                if (*(s16 *)(state + 0x1B4)) {
                    if (func_00282E80(object + 0x10, &point) < 2.0f)
                        --*(s32 *)(state + 0x194);
                    if (*(s32 *)(state + 0x194) < 0)
                        *(s32 *)(state + 0x194) = *(s32 *)path - 1;
                } else {
                    if (func_00282E80(object + 0x10, &point) < 2.0f)
                        ++*(s32 *)(state + 0x194);
                    if (*(s32 *)(state + 0x194) >= *(s32 *)path)
                        *(s32 *)(state + 0x194) = 0;
                }
                if (*(s32 *)(state + 0x194) >= *(s32 *)path - 6 && *(float *)(state + 0x198) >= 0.10000001f)
                    *(float *)(state + 0x198) -= 0.0025f;
                func_002A677C(object);
                func_002B4FF0((char *)object, point.f, *(float *)(state + 0x190));
                func_002AA548((float *)(object + 0x18), (float *)(state + 0x108), *(float *)(state + 0x188), 0.0027777778f, 0.0027777778f, 0.16666667f);
            }
            if (*(s16 *)(state + 0x1B8)) func_002A7750(object, 8, 3);
        }
        break;
    case 8:
        if (func_002B3868(object))
            func_002B60B0(object, 0.008333334f, 1.0f, 0.001163553f, 0.10471977f);
        if (range >= 1.7f)
            func_002B4FF0((char *)object, target.f, *(float *)(state + 0x190));
        height = *(float *)(ground + 8) + 0.7f;
        func_002AA548((float *)(object + 0x18), (float *)(state + 0x108), height, 0.0027777778f, 0.0027777778f, 0.16666667f);
        if (range < 1.7f && func_00282C48(*(float *)(object + 0x18) - height) < 0.1f) {
            *(u16 *)(object + 0x96) = 0;
            func_002A7750(object, 10, -1);
        }
        break;
    case 9:
        if (func_002B3868(object) && object[0x43] != 2) func_002A7470(object, 2, 0, 3);
        if (object[0x60] & 2) {
            if (object[0x43] != 3) func_002A7470(object, 3, 0, 5);
            func_002A7750(object, 11, -1);
        }
        /* Emits nothing, but keeps a label here, so case 9's tail stays apart from case 12's. */
        height = 0.0f;
        break;
    case 11:
        if (func_002B3890(object)) {
            func_002B60B0(object, 0.0011111111380159855f, 0.033333335f, 0.001163553f, 0.10471977f);
            *(u16 *)(object + 0x96) = 0;
        }
        *(float *)(object + 0x48) = 1.75f;
        func_002AA548((float *)(object + 0x18), (float *)(state + 0x108), *(float *)(ground + 8) + 0.7f, 0.0027777778f, 0.0027777778f, 0.16666667f);
        if (range >= 1.7f)
            func_L01_00321178((char *)object, (char *)&target);
        else if (range < 1.7f) {
            func_00282CF0(&point, object + 0x10, &target);
            func_00282F20(&point, &point, 2.0f);
            func_00282CC0(&point, &point, object + 0x10);
            func_L01_00321178((char *)object, (char *)&point);
        }
        i = 0;
        do {
            func_002A8D70(0.5f, (float)state[0x34], 1.0f, object, i, 0x4000001, 0, 1, 0);
        } while (++i < 4);
        if (D_00189E20.contact == object) {
            func_002A7750(object, 12, -1);
            if (object[0x43] != 4) func_002A7470(object, 4, 0, 5);
            *(float *)(object + 0x48) = 1.0f;
        }
        if (range > 4.0f && *(u16 *)(object + 0x96) > 120) {
            if (object[0x43] != 5) func_002A7470(object, 5, 0, 15);
            func_002A7750(object, 4, -1);
            *(float *)(object + 0x48) = 1.0f;
        }
        break;
    case 12:
        if (object[0x60] & 2) {
            if (object[0x43]) func_002A7470(object, 0, 0, 15);
            func_002A7750(object, 8, -1);
        }
        break;
    case 10:
        if (*(u16 *)(object + 0x96) > 44) {
            func_002A7750(object, 9, -1);
            if (object[0x43] != 2) func_002A7470(object, 2, 0, 2);
            *(float *)(object + 0x48) = 1.0f;
        }
        break;
    }
    *(float *)(state + 0x170) = func_002AA150(*(float *)(state + 0x170), D_L02_001B1970 * 0.00029088825f, 0.0625f);
    *(float *)(state + 0x174) = func_002AA150(*(float *)(state + 0x174), D_L02_001B1974[0] * 0.00029088825f, 0.0625f);
    *(float *)(state + 0x178) = func_002AA150(*(float *)(state + 0x178), D_L02_001B1978[0] * 0.00029088825f, 0.0625f);
    *(float *)(object + 0xF0) = func_00283B98(*(float *)(object + 0xF0), *(float *)(state + 0x170));
    *(float *)(object + 0xF4) = func_00283B98(*(float *)(object + 0xF4), *(float *)(state + 0x174));
    *(float *)(object + 0xF8) = func_00283B98(*(float *)(object + 0xF8), *(float *)(state + 0x178));
    if (ground && *(float *)(object + 0x18) <= *(float *)(ground + 8) + 0.4f) {
        if (!object[0x31]) {
            *(float *)(state + 0x108) = 0.016666668f;
            *(float *)(object + 0x18) = *(float *)(ground + 8) + 0.3f;
        } else if (func_00277258(object + 0x10, 6, 0, 0.3f)) {
            float size;
            s32 side;
            *(float *)(state + 0x108) = 0.016666668f;
            *(float *)(object + 0x18) = *(float *)(ground + 8) + 0.3f;
            point.f[0] = *(float *)(object + 0x10) + func_002A7878(-0.01f, 0.01f);
            point.f[1] = *(float *)(object + 0x14) + func_002A7878(-0.01f, 0.01f);
            point.f[2] = *(float *)(object + 0x18) - 0.3f;
            size = func_002A7878(D_L02_001B1930, D_L02_001B1934);
            side = func_002A77E0(2);
            if (!side) side--;
            func_002A7A00(velocity.f, D_L02_001B1938 * 0.016666668f, D_L02_001B193C * 0.016666668f);
            velocity.f[2] = func_002A7878(D_L02_001B1940, D_L02_001B1944) * 0.016666668f;
            func_002C2210(size * 0.1f, size, D_L02_001B1948, &point, 60, 0x7F007F7F, 0, side, velocity.f, 0);
        }
    }
    if (*(s32 *)(state + 0xE0) > 180) {
        func_L02_003FC248(object, 0, 1);
        func_L02_0040D180(object);
        *(s32 *)(state + 0xE0) = 0;
    }
    func_002A8C28(object, object + 0x10, 0x4000000, 0.8f, 1.0f, 1.0f, 0, 1, 0);
    func_L02_0040CEE8(object);
}
