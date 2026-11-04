/* func_L02_0040A4A8: own unit for -frac2-gcse-unsplit-edges (hero %hi kept in $s1 across case 7).
 * The second particle loop's preheader follows loop.c move_movables: a movable is hoisted in
 * the first pass only while threshold * savings * lifetime >= the loop's insn count, with the
 * threshold starting at 61 and dropping by 3 per hoisted insn. Retail hoists all seven
 * constants in one pass in the order palette %hi/%lo, 0x44, 0x48, 0x7F, 0x70707F, 0x70, so
 * 127 is set before 0x70707F (alpha, set after the 0x48 store) and the loop has at most 46
 * insns: the particle template is passed through tmpl, a register argument, which drops the
 * argument copy gcse leaves for &particle.
 * Also needed: hero target/heading through one symbol (D_00189E20 + 0x80 and
 * ((Hero *)D_00189E20)->f[0x20]), qcopy() for the matrix row copy, the D_L02_00200080
 * palette struct (+0x5C), the tail = part + 0x20 local, separate loop counters,
 * func_L00_0042AB40 taking one argument, func_002A8C28 with its first float before the int,
 * int flags from func_002B1C20, and an explicit goal = state + 0x2C0 local.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 quad; float f[4]; } ActorVector;
typedef struct {
    u8 reserved_00[0x18]; u8 enabled; u8 count; u8 kind;
    u8 reserved_1b[0x65]; u8 payload[1];
} Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext;
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;
extern u8 D_00189E20[];
typedef struct { u8 pad00[0x5C]; u8 *ids; } L02_Palette;
extern L02_Palette D_L02_00200080;
extern void func_L02_0040B0F8(u8 *);
extern void func_002A7750(u8 *, u8, s32);
extern s32 func_002A77E0(s32);
extern void func_002A7470(void *, s32, s32, s32);
extern float func_00283248(float, float);
extern float func_00282E80(void *, void *);
extern void func_L01_00321178(char *, char *);
extern void func_002B60B0(u8 *, float, float, float, float);
extern char *func_L02_003FC098(char *);
extern void func_L02_0040BAB8(u8 *, void *);
extern void func_L02_0040BBA0(u8 *);
extern float func_00283C80(float, float);
extern s32 func_002B1C20(void *, Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext *);
extern void func_L02_003FC248(void *, s32, s32);
extern void func_L02_0040B980(u8 *);
extern s32 func_002B3868(u8 *);
extern s32 func_002B3890(u8 *);
extern s32 func_L02_003FC0B8(char *);
extern s32 func_L00_003206B8(void *, s32);
extern s32 func_L00_0042AB40(char *);
extern void func_002B5278(void *, float);
extern s32 func_002B4FF0(char *, float *, float);
extern s32 func_002B50E0(void *, void *, float);
extern s32 func_L02_0040BBD8(u8 *);
extern s32 func_00283DB8(void *, float);
extern void func_0029FC20(char *, s32, char *);
extern void func_0029FCC0(char *, s32, char *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACB48(float *, float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void *func_002C65A0(void *, void *, s32, u32, s32, s32, s32, float, float, float, s32);
extern s32 func_002A8C28(void *, void *, float, u32, float, float, s32, s32, s32);
extern void *func_002C16C0(void *, void *, s32, s32, u32, s32, float, float, float, float, float);
extern s32 func_002A7820(s32, s32);
extern void func_L02_0040B420(u8 *);
extern void func_L02_0040B4B0(u8 *);
extern void func_L00_002E6EF8(void (*)(u8 *), void *);

/* Update the sentry's patrol, alert state and close-range flame effect. */
void func_L02_0040A4A8(u8 *object)
{
    ActorVector target;
    ActorVector bounds[2];
    ActorVector matrix[4];
    ActorVector effect;
    ActorVector near_point;
    ActorVector far_point;
    ActorVector velocity;
    ActorVector particle;
    u8 *state;
    float heading;
    float range;
    float angle;
    s32 selection;
    u8 *hp;
    float dx;
    float dy;
    u8 *goal;

    if (object[0x20] == 1 || object == 0 || object[0x20] == 0xFE || object[0x20] == 0xFD)
        return;
    state = *(u8 **)(object + 0x68);
    func_L02_0040B0F8(object);
    if (object[0x20] == 1 || object[0x20] == 0xFE || object[0x20] == 0xFD)
        return;
    if (*(s16 *)(state + 0x2E2) == 0 && object[0x95] == 3) {
        func_002A7750(object, 4, 2);
        if (func_002A77E0(2)) {
            if (object[0x43] != 2)
                func_002A7470(object, 2, 0, 10);
        } else if (object[0x43] != 3)
            func_002A7470(object, 3, 0, 10);
    }
    if (*(u8 **)(state + 0x2D4)) {
        target.quad = *(TI128 *)(*(u8 **)(state + 0x2D4) + 0x10);
        heading = func_00283248(*(float *)(*(u8 **)(state + 0x2D4) + 0x10) - *(float *)(object + 0x10), *(float *)(*(u8 **)(state + 0x2D4) + 0x14) - *(float *)(object + 0x14));
    } else {
        target.quad = *(TI128 *)(D_00189E20 + 0x80);
        heading = func_00283248(((Hero *)D_00189E20)->f[0x20] - *(float *)(object + 0x10), ((Hero *)D_00189E20)->f[0x21] - *(float *)(object + 0x14));
    }
    range = func_00282E80(object + 0x10, &target);
    switch (object[0x95]) {
    case 2: {
        if (func_002B3890(object)) {
            if (object[0x43] != 10)
                func_002A7470(object, 10, 0, 10);
            object[0xBC] = 0;
            func_002B60B0(object, 0.0044444446f, 0.13333334f, 0.0005817765f, 0.052359886f);
            func_L02_0040BAB8(object, func_L02_003FC098(*(char **)(object + 0xB8)));
            *(u16 *)(object + 0x96) = 10000;
        }
        if (object[0xBC] == 1 && *(u16 *)(object + 0x96) >= 301) {
            selection = func_002A77E0(5);
            switch (selection) {
            case 0: if (object[0x43] != 2) func_002A7470(object, 2, 0, 10); break;
            case 1: if (object[0x43] != 3) func_002A7470(object, 3, 0, 10); break;
            case 2: if (object[0x43] != 5) func_002A7470(object, 5, 0, 10); break;
            case 3: if (object[0x43] != 6) func_002A7470(object, 6, 0, 10); break;
            }
            *(u16 *)(object + 0x96) = func_002A77E0(100);
        }
        if (*(s16 *)(state + 0x2E2)) {
            func_002A7750(object, 5, 3);
            if (func_002A77E0(2)) {
                if (object[0x43] != 1) func_002A7470(object, 1, 0, 10);
            } else if (object[0x43] != 4) func_002A7470(object, 4, 0, 10);
        }
        angle = func_00283248(target.f[0] - *(float *)(object + 0x10), target.f[1] - *(float *)(object + 0x14));
        if (func_00283C80(*(float *)(object + 0xF8), angle) > 2.7925272f)
            func_L02_0040BBA0(object);
        goal = state + 0x2C0;
        if (!object[0xBC] && func_00282E80(object + 0x10, goal) < 0.5f)
            object[0xBC] = 1;
        else
            func_L01_00321178((char *)object, (char *)goal);
        break;
    }
    case 4: {
        s32 flags = func_002B1C20(object, (Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext *)(state + 0x50));
        if ((object[0x42] == 16 && func_002A77E0(30) == 0) || (flags & 1)) {
            func_L02_003FC248(object, 0, -1);
            func_L02_0040B980(object);
        } else if (flags & 2)
            func_002A7750(object, 7, 3);
    }
        break;
    }
    switch (object[0x20]) {
    case 3:
        if (func_002B3868(object)) {
            object[0xBC] = 0;
            if (object[0x43] != 2) func_002A7470(object, 2, 0, 0);
            *(s32 *)(state + 0x13C) = -1;
        }
        if (object[0xBC] == 0 && (s32)*(u16 *)(object + 0x96) > *(s16 *)(state + 0x2E8)) {
            if (object[0x43] != 10) func_002A7470(object, 10, 0, 10);
            object[0xBC] = 1;
        } else if (object[0xBC] == 1) {
            if (func_L00_003206B8(object + 0x10, func_L02_003FC0B8(*(char **)(object + 0xB8)))) {
                func_002A7750(object, 4, 2);
                *(s32 *)(state + 0x13C) = func_L00_0042AB40(*(char **)(object + 0xB8));
            }
            func_L01_00321178((char *)object, func_L02_003FC098(*(char **)(object + 0xB8)));
        }
        break;
    case 6:
        if (func_002B3868(object)) {
            if (object[0x43] != 9) func_002A7470(object, 9, 0, 10);
            func_002B60B0(object, 0.0044444446f, 0.13333334f, 0.003490659f, 0.4188791f);
        }
        func_002B5278(object, heading);
        /* Fall through: both states leave when the movement flag is set. */
    case 5:
        if (object[0x60] & 2)
            func_002A7750(object, 7, -1);
        break;
    case 7:
        if (func_002B3868(object)) {
            func_002B60B0(object, 0.0044444446f, 0.13333334f, 0.0005817765f, 0.052359886f);
            if (object[0x43] != 10) func_002A7470(object, 10, 0, 15);
        }
        if (object[0x42] != 13 && func_00282E80(object + 0x10, &((Hero *)D_00189E20)->q[8]) < 15.0f &&
            func_00283C80(*(float *)(object + 0xF8), func_00283248(((Hero *)D_00189E20)->f[0x20] - *(float *)(object + 0x10), ((Hero *)D_00189E20)->f[0x21] - *(float *)(object + 0x14))) < 1.5707965f) {
            if (object[0x43] != 13) func_002A7470(object, 13, 0, 10);
            func_002B60B0(object, 0.0011111111f, 0.033333335f, 0.0005817765f, 0.052359886f);
        } else if (func_00282E80(object + 0x10, &((Hero *)D_00189E20)->q[8]) > 2.8f) {
            if (!func_L02_0040BBD8(object))
                func_002B4FF0((char *)object, target.f, *(float *)(state + 0x2D8));
        } else {
            angle = func_00283248(((Hero *)D_00189E20)->f[0x20] - *(float *)(object + 0x10), ((Hero *)D_00189E20)->f[0x21] - *(float *)(object + 0x14));
            func_002B50E0(object, object + 0x10, angle);
        }
        angle = func_00283248(target.f[0] - *(float *)(object + 0x10), target.f[1] - *(float *)(object + 0x14));
        if (func_00283C80(*(float *)(object + 0xF8), angle) > 2.7925272f)
            func_L02_0040BBA0(object);
        if (object[0x42] == 13) {
            bounds[1].quad = 0;
            bounds[1].f[0] = *(float *)(object + 0x10);
            bounds[1].f[1] = *(float *)(object + 0x14);
            bounds[1].f[2] = *(float *)(object + 0x18);
            bounds[1].f[3] = 2.0f;
            bounds[0].quad = bounds[1].quad;
            if (func_00283DB8(bounds, 128.0f) > 0) {
                s32 i;
                s32 j;
                ActorVector *tmpl;
                func_0029FC20((char *)object, 4, (char *)matrix);
                qcopy(&bounds[1], &matrix[1]);
                func_0029FCC0((char *)object, 4, (char *)&effect);
                func_00282F20(&near_point, bounds + 1, 0.85f);
                func_00282F20(&far_point, bounds + 1, 1.6f);
                func_00282F20(&velocity, matrix + 1, 0.25f);
                func_00282F20(bounds + 1, bounds + 1, 3.0f);
                func_00282CC0(&near_point, &near_point, &effect);
                func_00282CC0(&far_point, &far_point, &effect);
                near_point.f[2] -= 0.1f;
                tmpl = &particle;
                far_point.f[2] -= 0.1f;
                i = 2;
                do {
                    float first;
                    float second;
                    float third;
                    func_002ACB48(effect.f, 0.1f);
                    first = func_002A7878(0.2f, 0.4f) * 210000.0f;
                    second = func_002A7878(1.0f, 1.5f) * 210000.0f;
                    third = func_002A78D8(0.0f, 0.01f);
                    func_002C65A0(&effect, &velocity, 9, 0x808080, 30, 127, 32, first, second, third, 0);
                    if (range < 3.0f) {
                        func_002A8C28(object, &effect, 0.3f, 0x4000001, (float)state[0x34], 1.0f, 0, 1, 0);
                        func_002A8C28(object, &near_point, 0.3f, 0x4000001, (float)state[0x34], 1.0f, 0, 1, 0);
                        func_002A8C28(object, &far_point, 0.3f, 0x4000001, (float)state[0x34], 1.0f, 0, 1, 0);
                    }
                } while (--i >= 0);
                particle.f[0] = 0.0f;
                particle.f[1] = 0.0f;
                particle.f[2] = 0.1f;
                particle.f[3] = 1.0f;
                for (j = 0; j < 2; j++) {
                    u8 *part = func_002C16C0(&near_point, tmpl, 15, 60, 0x606060, 3,
                        105000.0f, 21000.0f, 1.0f, -0.0002f, 0.0f);
                    if (part) {
                        part[2] = *D_L02_00200080.ids;
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
    }
    func_L02_0040B420(object);
    func_L00_002E6EF8(func_L02_0040B4B0, object);
}
