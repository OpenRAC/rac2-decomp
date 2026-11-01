#include "include_asm.h"

#include "common.h"
extern struct {
    char pad0[0x1230];
    int input;
    char pad1234[0x10];
    int mode;
    char pad1248[0x104C];
    int planet;
} D_00189E20;
extern int D_00138320;
extern int ref_L24_003EFA38_00[] __attribute__((sda));
extern int ref_L24_003EFA38_01[] __attribute__((sda));
extern void func_0029FCC0(void *, int, void *);
extern float func_003004B0(float);
extern void func_002FDF40(void *, void *, char *, float, float, float, float, char *);
extern int func_PAL_002FF5F8(float *, float *, float *, float *, void *, void *, int *, float);
extern void func_00334050(int, int);
extern float func_00283CE0(int);
extern void func_PAL_L00_002AF458(void);
extern void func_PAL_L00_002AF6C0(void);
extern char *func_PAL_0032B4A8(int, void *, void *);
extern char *func_PAL_00329D88(int, void *, void *);
extern int func_00282948(void *);
extern float func_00282DF0(void *);
extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern int func_002E5DA0(int, int, char *, int);
extern int func_002B0910(int, int, int, int);
extern void func_00290010(int, int, int, float);
extern void func_L00_002E6EF8(void *, void *);
extern void func_PAL_00335D10(char *);
typedef struct TargetClass {
    char pad0[0x46];
    s16 type;
} TargetClass;
typedef struct Target {
    char pad0[0x20];
    u8 state;
    u8 slot;
    char pad22[2];
    TargetClass *class;
    char pad28[0x40];
    void *vars;
    char pad6C[0x50];
    u8 progress;
} Target;
typedef struct TargetVars {
    char pad0[0x14];
    u8 reverse;
    u8 maximum;
    s16 disabled;
} TargetVars;
typedef struct BeamVars {
    float unknown0[4];
    float endpoint[4];
    float normal[4];
    float position[4];
    int valid;
    int unknown44;
    float smoothed;
    float fraction;
    float fade;
    Target *hit;
    int countdown;
    int reverse;
    int disabled;
} BeamVars;

void func_PAL_L24_003F44F8(Target *obj)
{
    BeamVars *v = obj->vars;
    Target *hit;
    float *pos;
    float dir[4] __attribute__((aligned(16)));
    float spread[4] __attribute__((aligned(16)));
    float distance, ratio, length;
    int a, b;

    pos = v->position;
    func_0029FCC0(obj, 0, pos);
    distance = func_003004B0(4.5f);
    if (D_00189E20.planet == 29) {
        distance += 6.5f;
    }
    v->hit = 0;
    v->valid = 0;
    func_002FDF40(dir, pos, 0, 0.00001f, distance, 0.3f, 0.0044f, 0);
    func_PAL_002FF5F8(pos, dir, v->endpoint, v->normal, obj, &v->hit, 0, 0.0044f);
    hit = v->hit;
    if (hit != 0) {
        if (hit->class->type == 18) {
            TargetVars *target = hit->vars;
            target->maximum = 25;
            if (v->hit->slot != 255) {
                func_00334050(v->hit->slot, 25);
            }
            ratio = func_00283CE0(v->hit->progress);
            ratio /= func_00283CE0(target->maximum);
            v->fraction = ratio;
            if (target->reverse) {
                v->fraction = 1.0f - ratio;
                if (v->fraction == 0.0f) {
                    v->fraction = -0.001f;
                }
            }
            v->reverse = target->reverse;
            v->disabled = target->disabled != 0;
            v->valid = 1;
        }
    } else {
        v->fraction = -1000.0f;
    }

    switch (obj->state) {
    case 0:
        obj->state = 1;
        /* fall through: retail's table sends state 0 into state 1's store */
    case 1:
        obj->state = 2;
        break;
    case 2:
        if ((D_00138320 & D_00189E20.input) && v->hit && v->valid && !v->disabled) {
            func_PAL_L00_002AF458();
            obj->state = 3;
            if (!v->reverse) {
                func_PAL_0032B4A8((int)obj, v->position, dir);
            } else {
                func_PAL_00329D88((int)obj, v->position, dir);
            }
            func_002E5DA0(1, 0, (char *)obj, 0xFB0);
            if (v->reverse) {
                v->countdown = 12;
            } else {
                v->countdown = 6;
            }
        }
        break;
    case 3:
        if (!(D_00138320 & D_00189E20.input) || !v->hit || !v->valid || v->disabled) {
            func_PAL_L00_002AF6C0();
            obj->state = 2;
        } else if (func_00282948(&v->countdown)) {
            qcopy(spread, dir);
            length = func_00282DF0(spread);
            spread[0] += func_002A7878(-0.005f, 0.005f);
            spread[1] += func_002A7878(-0.005f, 0.005f);
            spread[2] += func_002A7878(-0.005f, 0.005f);
            func_00282F20(spread, spread, length);
            if (!v->reverse) {
                func_PAL_0032B4A8((int)obj, v->position, spread);
            } else {
                func_PAL_00329D88((int)obj, v->position, spread);
            }
            func_002E5DA0(1, 0, (char *)obj, 0xFB0);
            if (v->reverse) {
                v->countdown = 12;
            } else {
                v->countdown = 6;
            }
        }
        break;
    case 4:
        break;
    }

    if (D_00189E20.mode == 3) {
        obj->state = 4;
        v->fade -= 0.02f;
    } else {
        v->fade += 0.01f;
    }
    if (v->fade > 1.0f) {
        v->fade = 1.0f;
    } else if (v->fade < 0.0f) {
        v->fade = 0.0f;
    }

    if (v->fraction > -100.0f) {
        if (v->smoothed < -100.0f) {
            v->smoothed = v->fraction;
        } else if (v->fraction < v->smoothed - 0.01f) {
            v->smoothed -= 0.01f;
        } else if (v->smoothed + 0.01f < v->fraction) {
            v->smoothed += 0.01f;
        } else {
            v->smoothed = v->fraction;
        }
    } else {
        v->smoothed = v->fraction;
    }

    a = func_002B0910(ref_L24_003EFA38_00[0], 75, ref_L24_003EFA38_01[0], ref_L24_003EFA38_01[1]);
    b = func_002B0910(ref_L24_003EFA38_00[0], 75, ref_L24_003EFA38_01[2], ref_L24_003EFA38_01[3]);
    if (v->smoothed >= 0.0f && v->smoothed <= 1.0f) {
        func_00290010(0, a, b, v->smoothed);
    }
    func_L00_002E6EF8(func_PAL_00335D10, obj);
}
