/* func_PAL_L11_00456D04, the PAL copy of func_L11_00451178: the Joba sentry's patrol, alert, attack
 * and launch states. The same C with 50 Hz values, where:
 * - Case 7's cooldown is rescaled in place and D_L11_001B1D10 is read as a word.
 * - Case 7's first particle loop counts up: dbra reversal sets i = 2 after the preheader's other
 *   insns, which orders the $f22 copy before it in sched2 and gives gcse retail's bucket count.
 * - Case 9 replaces the func_002AEB60 test with a one-shot flag at state + 0x2DA and dist > 17.0f.
 *   cse reuses the known object[0xBC] == 1 for the flag's store.
 * - -frac2-hazard-labels: that test's false branch lands on the nop after the 17.0f mtc1.
 * - Spill slots: tmpl 0xC4, then case 12's reaching registers state + 0x2B0, object + 0xC0,
 *   object + 0xF0, &work[1] and &work[4] from 0xC8 to 0xD8, in hash-bucket order.
 * - work[6] is one function-scope scratch array: retail reuses sp+0x10..0x5F across the head
 *   and cases 7, 9 and 12.
 * - Case 12 sets spin = state + 0x2B0 before its loop, as func_L11_0044AFC8 does: the address
 *   then enters gcse's expression table before object+0xF0, which orders the PRE copies.
 * - Case 11 preserves func_002B1C20's unsigned 64-bit return. Its early exit keeps the
 *   low-bit test in control flow; the compound OR spelling adds a 32-bit normalization.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 quad; float f[4]; } ActorVector;
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;
extern u8 D_00189E20[];
typedef struct { u8 pad00[0x5C]; u8 *ids; } L11_Palette;
extern L11_Palette D_L11_00200440;
extern s32 D_L11_001A8FF4 __attribute__((sda));
extern float D_L11_001B1D04 __attribute__((sda));
extern float D_L11_001B1D08 __attribute__((sda));
extern s32 D_L11_001B1D0C __attribute__((sda));
extern s32 D_L11_001B1D10 __attribute__((sda));
extern float D_L11_001B1D14 __attribute__((sda));
extern float D_L11_001B1D18 __attribute__((sda));
extern float D_L11_001B1D1C __attribute__((sda));
extern float D_L11_001B1D20 __attribute__((sda));
extern float D_L11_001B1D24 __attribute__((sda));
extern u8 *D_L11_001C0D18[];
extern u8 *D_0018C0B0 __attribute__((nosda));
extern u8 *D_0018C2BC __attribute__((nosda));
extern char D_L11_001A8F20[] MACRO_ADDR;

extern void func_PAL_L11_00458020(u8 *);
extern void func_002A7750(u8 *, s32, s32);
extern s32 func_002A77E0(s32);
extern void func_PAL_002A7E68(u8 *, s32, s32, s32);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_002B04E0(u8 *, void *, u8 *);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern s32 func_002B3890(u8 *);
extern s32 func_002B3868(u8 *);
extern void func_002B60B0(u8 *, float, float, float, float);
extern u8 *func_L11_004417E8(u8 *);
extern void func_L11_00452F30(u8 *, u8 *);
extern void func_L11_004530C0(u8 *);
extern void func_PAL_L02_00335630(u8 *, void *);
extern int func_PAL_L01_00323068(u8 *, void *);
extern s32 func_L11_00441808(u8 *, u8 *);
extern void func_PAL_002B5E30(u8 *, float);
extern s32 func_00282978(void *);
extern s32 func_002761F8(void *, void *, s32, void *, void *);
extern s32 func_PAL_L11_00458CB0(u8 *);
extern s32 func_PAL_002B5BA8(u8 *, float *, float);
extern int func_PAL_L02_00335678(u8 *, void *, void *);
extern s32 func_PAL_002B5C98(u8 *, void *, float);
extern s32 func_00283DB8(void *, float);
extern void func_0029FC20(u8 *, s32, void *);
extern void func_0029FCC0(u8 *, s32, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACB48(float *, float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void *func_002C65A0(void *, void *, s32, u32, s32, s32, s32, float, float, float, s32);
extern s32 func_002A8C28(void *, void *, float, u32, float, float, s32, s32, s32);
extern void *func_PAL_002C23B8(void *, void *, s32, s32, u32, s32, float, float, float, float, float);
extern s32 func_002A7820(s32, s32);
extern int func_PAL_L11_00342578(u8 *, void *);
extern float func_0029F530(u8 *);
extern void func_00283098(void *, void *, void *);
extern void *func_PAL_00329890(float, u8 *, void *, void *, s32, s32);
extern unsigned long func_002B1C20(u8 *, void *);
extern void func_PAL_L02_004009A0(u8 *, s32, s32);
extern void func_PAL_L11_004589C8(u8 *);
extern void func_002AB6D8(void *, void *);
extern int func_L07_00321D68(u8 *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002A3F10(u8 *, s32, s32 *, void *);
extern void func_002B4090(float, float, float, u8 *, void *);
extern void func_002833F0(void *, void *);
extern void func_L11_00452810(u8 *);
extern void func_L11_004528A0(u8 *);
extern void func_L00_002E6EF8(void (*)(u8 *), void *);

/* Movement tuning with the sentry's usual turn limits. */
static __inline__ void turn(u8 *object, float rate, float speed)
{
    func_002B60B0(object, rate, speed, 0.0008377582f, 0.062831864f);
}

/* Update the Joba sentry's patrol, alert, attack and launch states. */
void func_PAL_L11_00456D04(u8 *object)
{
    ActorVector target;
    ActorVector work[6];
    ActorVector effect;
    ActorVector near_point;
    ActorVector far_point;
    ActorVector velocity;
    ActorVector particle;
    s32 count;
    ActorVector *tmpl;
    u8 *state;
    u8 *pos;
    float heading;
    float angle;
    float range;

    state = *(u8 **)(object + 0x68);
    if (object[0x20] == 1 || (*(s16 *)(state + 0x2D8) && !D_L11_001A8FF4 && object[0x20] != 12 && object[0x20] != 11))
        return;
    func_PAL_L11_00458020(object);
    if (object[0x20] == 1 || (*(s16 *)(state + 0x2D8) && !D_L11_001A8FF4))
        return;
    if (*(s16 *)(state + 0x2D2) == 0 && object[0x95] == 3) {
        func_002A7750(object, 4, 2);
        if (func_002A77E0(2)) {
            if (object[0x43] != 2)
                func_PAL_002A7E68(object, 2, 0, 8);
        } else if (object[0x43] != 3)
            func_PAL_002A7E68(object, 3, 0, 8);
    }
    if (*(u8 **)(state + 0x2C4))
        target.quad = *(TI128 *)(*(u8 **)(state + 0x2C4) + 0x10);
    else
        target.quad = *(TI128 *)(D_00189E20 + 0x80);
    if (*(s16 *)(state + 0x2D8)) {
        func_00282CF0(&work[0], &target, object + 0x10);
        pos = object + 0x10;
        heading = 0.0f;
        angle = func_002B04E0(object, &work[0], state + 0x230);
    } else {
        pos = object + 0x10;
        heading = func_00283248(target.f[0] - *(float *)(object + 0x10), target.f[1] - *(float *)(object + 0x14));
        angle = func_00283C80(heading, *(float *)(object + 0xF8));
    }
    range = func_00282E48(pos, &target);
    if (object[0x95] == 2) {
        u8 *goal;
        if (func_002B3890(object)) {
            if (object[0x43] != 9)
                func_PAL_002A7E68(object, 9, 0, 8);
            object[0xBC] = 0;
            turn(object, 0.0064000003f, 0.16000001f);
            func_L11_00452F30(object, func_L11_004417E8(*(u8 **)(object + 0xB8)));
            *(u16 *)(object + 0x96) = 10000;
        }
        if (object[0xBC] == 1 && *(u16 *)(object + 0x96) >= 251) {
            switch (func_002A77E0(5)) {
            case 0: if (object[0x43] != 2) func_PAL_002A7E68(object, 2, 0, 8); break;
            case 1: if (object[0x43] != 3) func_PAL_002A7E68(object, 3, 0, 8); break;
            case 2: if (object[0x43] != 5) func_PAL_002A7E68(object, 5, 0, 8); break;
            case 3: if (object[0x43] != 6) func_PAL_002A7E68(object, 6, 0, 8); break;
            }
            *(u16 *)(object + 0x96) = func_002A77E0(83);
        }
        if (*(s16 *)(state + 0x2D2)) {
            func_002A7750(object, 5, 3);
            if (func_002A77E0(2)) {
                if (object[0x43] != 1) func_PAL_002A7E68(object, 1, 0, 8);
            } else if (object[0x43] != 4) func_PAL_002A7E68(object, 4, 0, 8);
        }
        if (angle > 2.7925272f)
            func_L11_004530C0(object);
        goal = state + 0x2A0;
        if (!object[0xBC] && func_00282E80(pos, goal) < 0.5f)
            object[0xBC] = 1;
        else if (*(s16 *)(state + 0x2D8))
            func_PAL_L02_00335630(object, goal);
        else
            func_PAL_L01_00323068(object, goal);
    }
    switch (object[0x20]) {
    case 3:
        if (func_002B3868(object)) {
            object[0xBC] = 0;
            if (object[0x43] != 2) func_PAL_002A7E68(object, 2, 0, 0);
            *(u16 *)(object + 0x96) = 0;
        }
        if (object[0xBC] == 0 && *(s16 *)(state + 0x2D4) < (s32)*(u16 *)(object + 0x96)) {
            if (object[0x43] != 9) func_PAL_002A7E68(object, 9, 0, 8);
            object[0xBC] = 1;
        } else if (object[0xBC] == 1) {
            if (func_L11_00441808(*(u8 **)(object + 0xB8), pos))
                func_002A7750(object, 4, 2);
            func_PAL_L01_00323068(object, func_L11_004417E8(*(u8 **)(object + 0xB8)));
        }
        break;
    case 5:
        if (object[0x60] & 2)
            func_002A7750(object, 7, -1);
        break;
    case 6:
        if (func_002B3868(object)) {
            if (object[0x43] != 8) func_PAL_002A7E68(object, 8, 0, 8);
            func_002B60B0(object, 0.0064000003f, 0.16000001f, 0.005026549f, 0.5026549f);
        }
        func_PAL_002B5E30(object, heading);
        if (object[0x60] & 2)
            func_002A7750(object, 7, -1);
        break;
    case 7:
        if (func_002B3868(object)) {
            if (object[0x43] != 9) func_PAL_002A7E68(object, 9, 0, 12);
            *(u16 *)(state + 0x2D6) = 0;
        }
        if (D_L11_001B1D24 < range)
            turn(object, 0.0064000003f, 0.16000001f);
        else if (range < D_L11_001B1D20)
            turn(object, 0.0016000001f, 0.040000003f);
        if (object[0x42] != 12 && range < D_L11_001B1D18 && angle < 1.5707965f) {
            if (object[0x43] != 12) func_PAL_002A7E68(object, 12, 0, 8);
        } else if (object[0x42] == 12 && D_L11_001B1D1C < range) {
            if (object[0x43] != 9) func_PAL_002A7E68(object, 9, 0, 12);
        } else if (object[0x42] != 12 && D_L11_001B1D04 < range && range < D_L11_001B1D08 && !func_002A77E0(D_L11_001B1D0C)) {
            if (func_00282978(state + 0x2D6) && object[0x31]) {
                u8 *other;
                s16 id;
                if (!func_002761F8(pos, &target, 1, object, 0) ||
                    ((other = D_L11_001C0D18[0]) != 0 && (id = *(s16 *)(other + 0xAA)) != 0xD98 && id != 0xDCF &&
                     id != 0xDF4 && id != 0xDF7 && id != 0xDF9 && id != 0xD37)) {
                    func_002A7750(object, 9, -1);
                    *(u16 *)(state + 0x2D6) = (D_L11_001B1D10 * 5 + 2) / 6;
                }
            }
        } else if (range > 2.8f) {
            if (*(s16 *)(state + 0x2D8))
                func_PAL_L02_00335630(object, &target);
            else if (!func_PAL_L11_00458CB0(object))
                func_PAL_002B5BA8(object, target.f, *(float *)(state + 0x2C8));
        } else if (*(s16 *)(state + 0x2D8)) {
            func_00282CF0(&work[0], &target, pos);
            func_PAL_L02_00335678(object, pos, &work[0]);
        } else
            func_PAL_002B5C98(object, pos, heading);
        if (angle > 2.7925272f)
            func_L11_004530C0(object);
        if (object[0x42] == 12) {
            work[1].quad = 0;
            work[1].f[0] = *(float *)(object + 0x10);
            work[1].f[1] = *(float *)(object + 0x14);
            work[1].f[2] = *(float *)(object + 0x18);
            work[1].f[3] = 2.0f;
            work[0].quad = work[1].quad;
            if (object[0x31] || func_00283DB8(work, 128.0f) > 0) {
                s32 i;
                s32 j;
                func_0029FC20(object, 4, &work[2]);
                qcopy(&work[1], &work[3]);
                func_0029FCC0(object, 4, &effect);
                func_00282F20(&near_point, work + 1, 0.85f);
                func_00282F20(&far_point, work + 1, 1.6f);
                func_00282F20(&velocity, work + 3, 0.3f);
                func_00282F20(work + 1, work + 1, 3.0f);
                func_00282CC0(&near_point, &near_point, &effect);
                func_00282CC0(&far_point, &far_point, &effect);
                near_point.f[2] -= 0.1f;
                far_point.f[2] -= 0.1f;
                for (i = 0; i < 3; i++) {
                    float first;
                    float second;
                    float third;
                    func_002ACB48(effect.f, 0.1f);
                    first = func_002A7878(0.2f, 0.4f) * 210000.0f;
                    second = func_002A7878(1.0f, 1.5f) * 210000.0f;
                    third = func_002A78D8(0.0f, 0.01f);
                    func_002C65A0(&effect, &velocity, 7, 0x808080, 30, 127, 32, first, second, third, 0);
                    if (range < 3.0f) {
                        func_002A8C28(object, &effect, 0.3f, 0x4000001, (float)state[0x34], 1.0f, 0, 1, 0);
                        func_002A8C28(object, &near_point, 0.3f, 0x4000001, (float)state[0x34], 1.0f, 0, 1, 0);
                        func_002A8C28(object, &far_point, 0.3f, 0x4000001, (float)state[0x34], 1.0f, 0, 1, 0);
                    }
                }
                tmpl = &particle;
                particle.f[0] = 0.0f;
                particle.f[1] = 0.0f;
                particle.f[2] = 0.1f;
                particle.f[3] = 1.0f;
                for (j = 0; j < 2; j++) {
                    u8 *part = func_PAL_002C23B8(&near_point, tmpl, 12, 60, 0x606060, 3,
                        105000.0f, 21000.0f, 1.0f, -0.0002f, 0.0f);
                    if (part) {
                        part[2] = *D_L11_00200440.ids;
                        part[3] = 0x44;
                        if (func_002A7820(0, 1)) {
                            u8 *tail;
                            u16 alpha;
                            part[3] = 0x48;
                            alpha = 127;
                            *(u32 *)(part + 4) = 0x70707F;
                            tail = part + 0x20;
                            tail[0x11] = 0x70;
                            tail[0x12] = 0x70;
                            tail[0x13] = 0x70;
                            *(u16 *)(tail + 0x1E) = alpha;
                        }
                    }
                }
            }
        }
        break;
    case 9:
        if (func_002B3868(object)) {
            object[0xBC] = 0;
            if (object[0x43] != 7) func_PAL_002A7E68(object, 7, 0, 8);
            *(s16 *)(state + 0x2DA) = 0;
        }
        if (!object[0xBC] && angle < D_L11_001B1D14 * 0.017453294f) {
            object[0xBC] = 1;
            if (object[0x43] != 17) func_PAL_002A7E68(object, 17, 0, 8);
        } else if (*(s16 *)(state + 0x2D8))
            func_PAL_L11_00342578(object, &target);
        else
            func_PAL_002B5E30(object, heading);
        if (object[0xBC] == 1) {
            float dist = func_0029F530(object);
            if (*(s16 *)(state + 0x2DA) == 0 && 17.0f < dist) {
                *(s16 *)(state + 0x2DA) = 1;
                work[2].quad = 0;
                work[2].f[2] = 1.0f;
                func_0029FCC0(object, 4, &work[0]);
                if (*(u8 **)(state + 0x2C4))
                    func_00283098(&work[2], &work[2], *(u8 **)(state + 0x2C4) + 0xC0);
                else
                    func_00283098(&work[2], &work[2], D_0018C0B0 + 0xC0);
                func_00282CC0(&work[2], &work[2], &target);
                func_00282CF0(&work[1], &work[2], &work[0]);
                func_00282F20(&work[1], &work[1], 0.40000004f);
                func_PAL_00329890((float)state[0x35], object, &work[1], &work[0], 0, 0);
            } else if (dist < 17.0f && object[0x43] == 17) {
                float first;
                float second;
                func_0029FCC0(object, 4, &work[0]);
                first = func_002A7878(1.0f, 1.5f) * 210000.0f;
                second = func_002A7878(0.2f, 0.4f) * 210000.0f;
                func_002C65A0(&work[0], D_L11_001A8F20, 3, 0x808080, 9, 0x4F, 0, first, second, func_002A78D8(0.0f, 0.1f), 0);
            }
            if (object[0x60] & 2) {
                if (D_0018C2BC == object || !func_002A77E0(6))
                    func_002A7750(object, 10, -1);
                else
                    func_002A7750(object, 7, -1);
            }
        }
        break;
    case 10:
        if (func_002B3868(object) && object[0x43] != 11)
            func_PAL_002A7E68(object, 11, 0, 6);
        if (object[0x60] & 2)
            func_002A7750(object, 7, -1);
        break;
    case 11: {
        unsigned long flags = func_002B1C20(object, state + 0x50);
        if (object[0x42] == 15) {
            if (func_002A77E0(30) && (flags & 1UL) == 0)
                break;
            if (func_0029F530(object) < 15.0f && *(s16 *)(state + 0x2D8) && !func_002A77E0(2))
                func_002A7750(object, 12, -1);
            else {
                func_PAL_L02_004009A0(object, 0, -1);
                func_PAL_L11_004589C8(object);
            }
        } else if ((flags & 2UL) != 0)
            func_002A7750(object, 7, 3);
        break;
    }
    case 12: {
        u8 *launch = state + 0x1A0;
        s32 started = func_002B3868(object);
        if (started) {
            s32 k;
            float *spin;
            func_00282CF0(launch, func_L11_004417E8(*(u8 **)(object + 0xB8)), pos);
            *(float *)(state + 0x1A8) = 0.0f;
            func_00282F20(launch, launch, func_002A7878(3.0f, 5.0f) * 0.020000001f);
            *(s16 *)(state + 0x2D8) = 0;
            spin = (float *)(state + 0x2B0);
            for (k = 0; k < 3; k++) {
                spin[k] = func_002A7878(240.0f, 720.0f) * 0.0003490659f;
                qcopy(&work[k], &((ActorVector *)(object + 0xC0))[k]);
            }
            func_002AB6D8(work, object + 0xF0);
            if (object[0x43] != 18) func_PAL_002A7E68(object, 18, 0, 25);
            *(u16 *)(object + 0x34) &= 0xEFFF;
        }
        *(float *)(state + 0x1A8) -= *(float *)(state + 0x12C);
        func_L07_00321D68(object, launch);
        func_00282D30(state + 0x2B0, state + 0x2B0, 0.98f);
        {
            float f = *(float *)(object + 0x2C) * 0.0009765625f;
            count = 3;
            func_002A3F10(object, 1, &count, &work[1]);
            func_00282D30(&work[0], &work[4], f);
        }
        func_002B4090(*(float *)(state + 0x2B0), *(float *)(state + 0x2B4), *(float *)(state + 0x2B8), object, work);
        func_002833F0(object + 0xC0, object + 0xF0);
        if (*(float *)(object + 0x18) < ((float *)func_L11_004417E8(*(u8 **)(object + 0xB8)))[2] + 5.0f ||
            !func_002A77E0(450) || *(u16 *)(object + 0x96) >= 301) {
            func_PAL_L02_004009A0(object, 0, -1);
            func_PAL_L11_004589C8(object);
        }
        break;
    }
    }
    func_L11_00452810(object);
    func_L00_002E6EF8(func_L11_004528A0, object);
}
