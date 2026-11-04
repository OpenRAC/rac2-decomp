#include "include_asm.h"

typedef unsigned char u8;
typedef short s16;

extern u8 *D_L04_001B24DC;
extern u8 *D_L04_001FE340[];
extern int D_L04_001A8FE4[] __attribute__((sda));
extern int D_L04_001A8FE8[] __attribute__((sda));
extern float func_002A7878(float, float);
extern int func_00283CF0(float);

/* Collects the racers, sorts their recorded times, and records each rank and
   the next racer in the ordered list. */
void func_L04_00410F80(u8 *object) {
    u8 *list[24], **out;
    u8 *state = *(u8 **)(object + 0x68), *obj, *p, *route;
    int *slot = (int *)(state + 0x1E4);
    int i, j, n = 1, a, b, k;
    float length, distance;

    out = list + 1;
    *(u8 **)(state + 0x39C) = object;
    list[0] = object;
    for (k = 19; k >= 0; k--, slot++) {
        if (*slot != -1) {
            obj = D_L04_001B24DC + (*slot << 8);
            p = *(u8 **)(obj + 0x68);
            *out++ = obj;
            n++;
            if (*(int *)(p + 0x1A0) == 0) {
                route = D_L04_001FE340[*(int *)(state + 0x1A8)];
                length = (float)*(int *)route * *(float *)(route + 0x1C);
                distance = length - *(float *)(p + 0x11C) +
                           length * (float)(D_L04_001A8FE4[0] - *(int *)(p + 0x160));
                if (distance <= 0.0f) {
                    distance = func_002A7878(10.0f, 20.0f);
                }
                *(int *)(p + 0x1A0) = func_00283CF0(distance * 3.0f);
                if (*(int *)(p + 0x1A0) < 6) {
                    *(int *)(p + 0x1A0) = 6;
                }
                *(int *)(p + 0x1A0) += D_L04_001A8FE8[0];
            }
        }
    }
    {
        int i;
        for (i = 0; i < n - 1; i++) {
            for (j = 0; j < n - i - 1; j++) {
                a = 0;
                b = 0;
                {
                    u8 *obj = list[j];
                    if (*(s16 *)(obj + 0xAA) == 0xBBC) {
                        a = D_L04_001A8FE8[0];
                    } else if (*(s16 *)(obj + 0xAA) == 0xB2D) {
                        a = *(int *)(*(u8 **)(obj + 0x68) + 0x1A0);
                    }
                }
                {
                    u8 *obj = list[j + 1];
                    if (*(s16 *)(obj + 0xAA) == 0xBBC) {
                        b = D_L04_001A8FE8[0];
                    } else if (*(s16 *)(obj + 0xAA) == 0xB2D) {
                        b = *(int *)(*(u8 **)(obj + 0x68) + 0x1A0);
                    }
                }
                if (b < a) {
                    u8 *obj = list[j];
                    list[j] = list[j + 1];
                    list[j + 1] = obj;
                }
            }
        }
    }
    *(u8 **)(state + 0x39C) = list[0];
    for (i = 0; i < n; i++) {
        u8 *obj, *p;
        obj = list[i];
        if (*(s16 *)(obj + 0xAA) == 0xBBC) {
            *(int *)(state + 0x320) = i + 1;
            if (i == n - 1) {
                *(u8 **)(state + 0x3A0) = 0;
            } else {
                *(u8 **)(state + 0x3A0) = list[i + 1];
            }
        } else if (*(s16 *)(obj + 0xAA) == 0xB2D) {
            p = *(u8 **)(obj + 0x68);
            p[0xA2] = i + 1;
            if (i == n - 1) {
                *(u8 **)(p + 0x1A4) = 0;
            } else {
                *(u8 **)(p + 0x1A4) = list[i + 1];
            }
        }
    }
}

typedef unsigned int u32;

static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}

/* Eight-sample trail records; the retail loop visits 140 entries of stride 0x150. */
typedef struct Trail416018 {
    float points[8][4];
    float velocities[8][4];
    float origin[4];
    float *offset, *impulse;
    short ages[8], landed[8];
    int count, lifetime;
    u32 colour;
    int active;
    char *owner;
    int tail;
} Trail416018;
extern Trail416018 D_L04_00254E10[] __attribute__((sda));
extern unsigned char D_00189E20[];
extern int D_L04_001B08F0 __attribute__((sda));
extern void *D_L04_001B0914 __attribute__((sda));
extern void func_00282CC0(float *, float *, float *);
extern void func_00282D30(float *, float *, float);
extern void func_00283098(float *, float *, char *);
extern int func_00282948(int *);
extern int func_00283D38(int, int, float);
extern void func_L04_00415E28(void *);
extern void func_L00_002E6CF0(void (*)(void *), void *);
void func_L04_00416018(void)
{
    float local[4] __attribute__((aligned(16)));
    float floorZ, scale;
    Trail416018 *trail;
    float *point, *velocity;
    float gravity;
    short *age;
    int i, j, count;
    char *owner;
    for (i = 0; i < 140; i++) {
        trail = &D_L04_00254E10[i];
        if (!trail->active)
            continue;
        owner = trail->owner;
        count = trail->count;
        if (*(short *)(owner + 0xaa) == 0xbbc) {
            /* Through a pointer, as retail keeps the hero base in a register. */
            unsigned char *hero = D_00189E20;
            floorZ = *(float *)(hero + 0x318) + 0.1f;
        } else {
            floorZ = *(float *)(owner + 0x18) - 0.25f;
        }
        for (j = 0; j < count; j++) {
            float widthStep = 0.0009f;
            gravity = 0.0019444445f;
            point = trail->points[j];
            age = &trail->ages[j];
            velocity = trail->velocities[j];
            /* velocities[j][2], addressed from the point as retail does. */
            if ((*age)++ > 10)
                ((float *)((char *)point + 0x80))[2] -= gravity;
            scale = 1.0f;
            scale -= (*age - 5) * 0.01f;
            func_00282CC0(point, point, velocity);
            func_00282D30(local, trail->impulse, scale);
            func_00282CC0(point, point, local);
            if (point[2] < floorZ) {
                point[2] = floorZ;
                trail->landed[j] = 1;
            }
            point[3] = trail->ages[0] * widthStep + 0.01f + *age * widthStep;
        }
        if (count < 8 &&
            ((*(short *)(trail->owner + 0xaa) == 0xbbc && D_L04_001B08F0) ||
             (*(short *)(trail->owner + 0xaa) == 0xb2d &&
              *(int *)(*(char **)(trail->owner + 0x68) + 0x244)))) {
            if (trail->ages[count - 1] < 3)
                continue;
            point = trail->points[count];
            func_00283098(local, trail->origin, trail->owner + 0xc0);
            func_00282CC0(point, trail->offset, local);
            func_00282CC0(point, point, trail->impulse);
            qcopy(trail->velocities[count], local);
            point[3] = 0.005f;
            trail->ages[count] = 0;
            trail->count++;
        } else if (trail->landed[count - 1] == 1) {
            if (func_00282948(&trail->lifetime)) {
                trail->active = 0;
            } else {
                trail->colour = func_00283D38(0x00858585, 0x80858585,
                    trail->lifetime * 0.033333335f);
            }
        }
    }
    func_L00_002E6CF0(func_L04_00415E28, D_L04_001B0914);
}
