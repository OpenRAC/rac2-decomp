/* func_L05_00397B30: near miss, 1048/1048 bytes, 0 of 4 places (USA v1.01, 31 October 2026).

   Profile: a -G8 unit (`L05_00397B30-g8.c`, default `-O2 -G8 -ffunction-sections`); the four
   floats at 0x1AEBDC..0x1AEBE8 are read through $gp, also outside delay slots.

   Same size; every branch, call, constant and both trail-clearing loops match. Left:
   - in the second-timer block retail forms `obj + 0x10` in $s0 (used for the aim point and
     func_002761F8) and copies it at once to $s4 (the hit record's position); here the copy
     goes the other way, after the second random call, and the aim buffer's address is set
     after the first call instead of in the branch delay slot. An inlined copy of
     func_L05_00397F48 (whose body this block repeats) made it worse.
   - two scheduling details: the hit record's address into $a3 before the E0/DC choice, and
     `lw $a2,0x20($s3)` against `hit = 0` before func_00277258. */

#include "common.h"

extern f32 D_L05_001AEBE8 __attribute__((sda));
extern f32 D_L05_001AEBE4 __attribute__((sda));
extern f32 D_L05_001AEBE0 __attribute__((sda));
extern f32 D_L05_001AEBDC __attribute__((sda));
typedef struct { char pad[0x9C]; s32 f9C; char tail[0x10]; } Trail97B30;
extern Trail97B30 D_L05_00233560[];
extern char D_L05_001BFB20[];
extern char D_L05_001BFB30[];

typedef struct { f32 a, b, c, d; } SpawnVector97B30;

typedef struct {
    SpawnVector97B30 v;
    s32 s10;
    s32 s14;
    u8 b18;
    u8 b19;
    u16 h1A;
    f32 f1C;
    s32 s20;
} SpawnRecord97B30;

extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283B98(float, float);
extern int func_00282948(void *);
extern void func_L05_003D1E60(void *, int, int);
extern void func_0029F338(void *);
extern float func_002A7940(void);
extern void func_002AF000(void *, float, float, float);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_L05_00398378(u8 *, void *, int);
extern void func_L05_00398618(u8 *);
extern void func_L05_00398018();
extern void func_L00_002E6EF8(void *, void *);
extern void func_00277F48(void *, s32, s32, SpawnRecord97B30 *, f32);
extern int func_00278E78(void);
extern int func_00277258(void *, int, int, float);
extern void func_L05_00397F48(u8 *, u8 *, u8 *);
extern void func_L05_00424990(void *, int, int, int, int, int, int, int, int, int, int, float);

/* Moves the projectile along its velocity, slowing it and spinning its two angles. It explodes
   (clearing the twenty-four trail records first when it timed out or left the 2..1021 box) when
   its life runs out; each time its second timer expires it throws a hit record to a random
   point 21 units away; on hitting the world it submits its hit record, bursts and removes
   itself. */
void func_L05_00397B30(u8 *obj)
{
    u8 *st = *(u8 **)(obj + 0x68);
    f32 old[4];
    f32 aim[4];
    SpawnRecord97B30 t;
    u8 *pos;
    u8 *at;
    int hit;
    int j;
    f32 a;
    f32 r;
    u16 id;

    qcopy(old, obj + 0x10);
    func_00282CC0(obj + 0x10, obj + 0x10, st);
    r = func_00282DF0(st);
    if (*(s32 *)(st + 0x24) != 0)
        r *= 0.986f;
    else
        r *= 0.982f;
    func_00282F20(st, st, r);
    *(f32 *)(obj + 0xF8) = func_00283B98(*(f32 *)(obj + 0xF8), 0.05f);
    *(f32 *)(obj + 0xF4) = func_00283B98(*(f32 *)(obj + 0xF4), 0.03f);
    if (func_00282948(st + 0x18)) {
        pos = obj + 0x10;
        for (j = 0x17; j >= 0; j--)
            D_L05_00233560[j].f9C = 0;
        func_L05_003D1E60(pos, 0, 0);
        func_0029F338(obj);
        return;
    }
    if (*(f32 *)(obj + 0x10) < 2.0f || 1021.0f < *(f32 *)(obj + 0x10) ||
        *(f32 *)(obj + 0x14) < 2.0f || 1021.0f < *(f32 *)(obj + 0x14) ||
        *(f32 *)(obj + 0x18) < 2.0f || 1021.0f < *(f32 *)(obj + 0x18)) {
        pos = obj + 0x10;
        for (j = 0x17; j >= 0; j--)
            D_L05_00233560[j].f9C = 0;
        func_L05_003D1E60(pos, 0, 0);
        func_0029F338(obj);
        return;
    }
    if (func_00282948(st + 0x28)) {
        at = obj + 0x10;
        a = func_002A7940();
        pos = at;
        func_002AF000(aim, 21.0f, a, func_002A7940());
        func_00282CC0(aim, aim, at);
        if (func_002761F8(at, aim, 0, obj, 0))
            qcopy(aim, D_L05_001BFB20);
        func_L05_00398378(obj, aim, 1);
        func_L05_00398618(obj);
        func_L00_002E6EF8(func_L05_00398018, obj);
        t.s10 = (s32)obj;
        t.s14 = 0x810000;
        if (*(s32 *)(st + 0x24))
            t.f1C = D_L05_001AEBE8;
        else
            t.f1C = D_L05_001AEBE4;
        t.s20 = 1;
        qcopy(&t.v, st);
        func_00282F20(&t, &t, 1.0f);
        id = *(u16 *)(obj + 0xAA);
        t.v.d = 5627.9248046875f;
        t.b18 = 3;
        t.b19 = 2;
        t.h1A = id;
        func_00277F48(pos, 1, *(s32 *)(st + 0x20), &t,
                      *(s32 *)(st + 0x24) ? D_L05_001AEBE0 : D_L05_001AEBDC);
    }
    if (func_00278E78() == 6)
        return;
    pos = obj + 0x10;
    hit = 0;
    if (func_00277258(pos, 0x10, *(s32 *)(st + 0x20), 1.0f)) {
        hit = 1;
        qcopy(pos, D_L05_001BFB30);
    }
    if (!hit && !func_002761F8(old, pos, 0x10, (void *)*(s32 *)(st + 0x20), 0))
        return;
    qcopy(pos, D_L05_001BFB20);
    func_L05_00397F48(obj, st, pos);
    if (*(s32 *)(st + 0x24))
        func_L05_00424990(pos, 0, 0x32, 0x1E, 0x1E, 0x1E, 0x28, 1, 1, 1, 1, 2.0f);
    func_L05_003D1E60(pos, 0, 0);
    func_0029F338(obj);
}
