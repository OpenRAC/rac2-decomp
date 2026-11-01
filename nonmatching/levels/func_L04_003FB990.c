/* func_L04_003FB990: near miss, 996/1008 bytes, 0 of 2 places (USA v1.01, 31 October 2026).

   Profile: its own unit, default `-O2 -G0 -ffunction-sections` (-fno-gcse is worse).

   Control flow, calls, constants and the 0x30-byte buffer shared by the hit record and the
   three ray vectors follow retail. What differs is allocation:
   - the hit-list pointer and the hoisted 0x230000 swap $s0/$s3, and the hoisted 1.0 and the
     ray angle swap $f21/$f20 (in both loops);
   - the spilled `obj + 0x10` and the second ray vector's address swap stack slots 0x34/0x30;
   - retail copies the count into a fresh register before the loop (`daddu $s2,$v1`).
   The 12 missing bytes are the alignment nops retail has before the three loop heads.
   Tried: a pointer walk with a count-down (988 bytes, the hoisted 0.75 * r returns unless the
   distance call is evaluated first), buffer pointers set at entry (no spills at all). */

#include "common.h"

typedef struct {
    f32 v[4];
    s32 owner;
    s32 flags;
    u8 kind;
    u8 mode;
    u16 source;
    f32 scale;
    s32 extra;
} Hit3FB990;

extern u8 *D_L04_001C3B40[];
extern u8 D_L04_001BFAE0[];

extern int func_00277F48(void *, int, int, int, float);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_00282E80(void *, void *);
extern float func_00282E48(void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_002A8E20(void *, void *);
extern int func_002E5CF8(int, int, int);
extern float func_00283CE0(int);
extern float func_00283C28(float);
extern float func_00283B98(float, float);
extern void func_002AF000(void *, float, float, float);
extern void func_00282CD8(void *, void *, void *);
extern int func_002761F8(void *, void *, int, int, int);
extern void func_L04_0040C0C0(void *, void *, int, int);

/* The blast of the object: every entity within its radius (vars +0x70 times +0x7C, at
   least 0.75) other than the owner, and inside its cone when +0x7C is positive, takes a
   hit; then two fans of five rays, one each side of the facing, spark where they hit the
   world. */
void func_L04_003FB990(u8 *obj, u8 *vars)
{
    f32 r;
    f32 side;
    f32 x;
    f32 y;
    u8 **list;
    u8 *e;
    int n;
    int k;
    int j;
    union {
        Hit3FB990 t;
        f32 v[3][4];
    } u;

    r = *(f32 *)(vars + 0x70) * *(f32 *)(vars + 0x7C);
    if (r < 0.75f)
        r = 0.75f;
    n = func_00277F48(obj + 0x10, 0x10, *(s32 *)(vars + 0x74), 0, r);
    for (j = 0; j < n; j++) {
        {
            list = &D_L04_001C3B40[j];
            e = *list;
            if ((s32)e == *(s32 *)(vars + 0x74))
                continue;
            if (0.0f < *(f32 *)(vars + 0x7C)) {
                x = func_00283248(*(f32 *)(e + 0x10) - *(f32 *)(obj + 0x10),
                                  *(f32 *)(e + 0x14) - *(f32 *)(obj + 0x14));
                if (0.741765f < func_00283C80(x, *(f32 *)(obj + 0xF8)))
                    continue;
                x = func_00282E80(obj + 0x10, *list + 0x10);
                x = func_00283248(x, *(f32 *)(*list + 0x18) - *(f32 *)(obj + 0x18));
                if (0.52359885f < func_00283C80(x, -*(f32 *)(obj + 0xF4)))
                    continue;
            }
            if (!(func_00282E48(obj + 0x10, *list + 0x10) > r * 0.75f))
                continue;
            u.t.owner = *(s32 *)(vars + 0x74);
            u.t.flags = 0x230000;
            u.t.kind = 2;
            u.t.mode = 3;
            u.t.source = *(u16 *)(obj + 0xAA);
            u.t.scale = 1.0f;
            u.t.extra = 0x230000;
            x = func_00283248(*(f32 *)(*list + 0x10) - *(f32 *)(obj + 0x10),
                              *(f32 *)(*list + 0x14) - *(f32 *)(obj + 0x14));
            u.t.v[0] = func_00283180(x);
            u.t.v[1] = func_00283198(x);
            u.t.v[2] = 1.0f;
            u.t.v[3] = 5627.9248046875f;
            func_002A8E20(*list, &u.t);
            func_002E5CF8(10, 0, *(s32 *)(vars + 0x74));
        }
    }
    for (k = 0; k < 2; k++) {
        side = -1.0f;
        if (k & 1)
            side = 1.0f;
        for (j = 0; j < 5; j++) {
            x = func_00283C28(func_00283CE0(j) * side * 0.13962637f);
            y = func_00283C28(func_00283CE0(j + 1) * side * 0.13962637f);
            func_002AF000(u.v[0], r, func_00283B98(x, *(f32 *)(obj + 0xF8)), -*(f32 *)(obj + 0xF4));
            func_002AF000(u.v[1], r, func_00283B98(y, *(f32 *)(obj + 0xF8)), -*(f32 *)(obj + 0xF4));
            func_00282CD8(u.v[2], u.v[0], obj + 0x10);
            func_00282CD8(u.v[2], u.v[1], obj + 0x10);
            if (func_002761F8(u.v[0], u.v[1], 0x12, *(s32 *)(vars + 0x74), 0)) {
                func_002AF000(u.v[2], 1.0f / 3.0f, *(f32 *)(obj + 0xF8), -*(f32 *)(obj + 0xF4));
                func_L04_0040C0C0(D_L04_001BFAE0, u.v[2], 8, 0);
            }
        }
    }
}
