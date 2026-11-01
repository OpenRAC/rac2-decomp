/* func_L04_004045E0: near miss, 1040/1040 bytes, 0 of 2 places (USA v1.01, 31 October 2026).

   Profile: its own unit, default `-O2 -G0 -ffunction-sections` (no qcopy: the copies here are
   ordinary TImode moves with offsets). The switch is in-order: retail's jtbl_002CA150 sends
   0..4 to the bodies in that order.

   Everything matches but three instructions in state 0: retail schedules the axis-table loads
   as `lq [0x20]; lhu 0x34; lq [0x00]; ori; lq [0x10]`, here `lhu 0x34; lq [0x10]; lq [0x20];
   ori; lq [0x00]` (registers and stores are the same). Tried: every load and declaration
   order of the three temporaries, the flag updates before, between and after them, a split
   read-modify-write, -fno-schedule-insns, -g, -fno-gcse, hazard labels and block order. */

#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef struct { Quad v[3]; } __attribute__((aligned(16))) Axes4045E0;

extern char D_L04_001B9680[];
extern Quad D_L04_001BFAF0;
extern Axes4045E0 D_001B0630;

extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern int func_00277258(void *, int, void *, float);
extern void func_L04_00402C88(u8 *);
extern void func_00282D30(void *, void *, float);
extern float func_002A7878(float, float);
extern void func_L04_00403530(u8 *, u8 *);
extern void func_L04_004027B0(u8 *, u8 *);
extern void func_L04_00400EE0(u8 *, u8 *);
extern void func_L04_004044B8(u8 *, u8 *);
extern void func_L04_00404100(u8 *, u8 *);
extern s32 func_L04_00400AB0(void *, void *, s32);
extern float func_00283CE0(int);
extern void func_002C96F8(float, float, void *, void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern int func_00283DB8(void *, float);
extern float func_00282DB0(void *, void *);
extern void func_L04_00410518(u8 *, u8 *, void *, void *, void *, void *);

/* Update of the path follower: state 0 lands it, scales its three axes and draws six random
   phases; state 2 runs its behaviours while the leader is not waiting; state 3 walks to the
   nearest path node and, after 300 frames, leaves for the leader once it is 5 units away and
   out of sight; state 4 drops both targets. The leader's own state can hold it entirely. */
void func_L04_004045E0(u8 *obj)
{
    u8 *st = *(u8 **)(obj + 0x68);
    u8 *e;
    u8 *es;
    u8 *pos;
    u8 *dst;
    u8 *src;
    f32 *ph;
    union {
        Axes4045E0 axes;
        f32 d[4];
    } u;
    f32 scale;
    f32 f;
    int k;
    int i;
    Quad t0, t1, t2;
    int j;
    f32 *q;

    *(f32 *)(obj + 0x2C) = *(f32 *)(*(u8 **)(obj + 0x24) + 0x24) * 0.25f;
    obj[0x30] = 0xFF;
    *(s16 *)(obj + 0x32) = 0x7F;
    if (obj[0x31] != 0 && func_00282E48(obj + 0x10, D_L04_001B9680) < 9.0f) {
        func_002A93B0(obj);
        obj[0x6F] = 8;
    }
    if (*(u8 **)(st + 0x164) != 0) {
        if ((*(u8 **)(st + 0x164))[0x20] == 1 || (*(u8 **)(st + 0x164))[0x20] == 4 || (*(u8 **)(st + 0x164))[0x20] == 0)
            return;
        if ((*(u8 **)(st + 0x164))[0x20] == 2 && (u8)((*(u8 **)(st + 0x164))[0xBC] - 5) < 2)
            (*(s32 *)(st + 0x1B8))++;
    }
    switch (obj[0x20]) {
    case 0:
        if (func_00277258(obj + 0x10, 4, obj, *(f32 *)(st + 0x90)))
            *(Quad *)(obj + 0x10) = D_L04_001BFAF0;
        *(Quad *)(st + 0xB0) = *(Quad *)(obj + 0x10);
        *(Quad *)(st + 0xC0) = *(Quad *)(obj + 0xF0);
        dst = st + 0x200;
        ph = (f32 *)(st + 0x184);
        func_L04_00402C88(obj);
        obj[0x20] = 1;
        *(s32 *)(st + 0x30) = 0;
        t2 = D_001B0630.v[2];
        t0 = D_001B0630.v[0];
        t1 = D_001B0630.v[1];
        *(u16 *)(obj + 0x34) |= 0x41;
        obj[0x62] = 1;
        u.axes.v[0] = t0;
        u.axes.v[1] = t1;
        u.axes.v[2] = t2;
        scale = *(f32 *)(obj + 0x2C) / *(f32 *)(*(u8 **)(obj + 0x24) + 0x24);
        src = (u8 *)&u.axes;
        for (i = 2; i >= 0; i--) {
            func_00282D30(dst, src, scale);
            src += 0x10;
            dst += 0x10;
        }
        q = ph;
        for (j = 5; j >= 0; j--)
            *q++ = func_002A7878(0.0f, 1.0f);
        return;
    case 1:
        break;
    case 2:
        if (*(u8 **)(st + 0x164) != 0 && (*(u8 **)(st + 0x164))[0x20] == 2 && (*(u8 **)(st + 0x164))[0xBC] == 0)
            return;
        func_L04_00403530(obj, st);
        func_L04_004027B0(obj, st);
        func_L04_00400EE0(obj, st);
        func_L04_004044B8(obj, st);
        func_L04_00404100(obj, st);
        return;
    case 3:
        if (*(u16 *)(obj + 0x96) == 0) {
            k = func_L04_00400AB0(obj, *(u8 **)(st + 0x110), 1);
            *(Quad *)(obj + 0x10) = *(Quad *)(*(u8 **)(st + 0x110) + k * 16 + 0x10);
            f = func_00283CE0(k) * *(f32 *)(*(u8 **)(st + 0x110) + 0x1C) +
                (*(s32 *)(st + 0x244) != 0 ? 15.0f : 5.0f);
            *(f32 *)(st + 0xA8) = f;
            func_002C96F8(f, *(f32 *)(*(u8 **)(st + 0x110) + 0x1C), *(u8 **)(st + 0x110),
                          st + 0x114, st + 0x118, st + 0xF0);
        }
        if (*(u16 *)(obj + 0x96) >= 300 && (e = *(u8 **)(st + 0x164)) != 0) {
            pos = obj + 0x10;
            es = *(u8 **)(e + 0x68);
            func_00282CF0(u.d, pos, e + 0x10);
            if (func_00283DB8(pos, 60.0f) == -1 && func_00282DB0(u.d, u.d) > 25.0f) {
                *(s32 *)(obj + 0x98) = *(s32 *)(*(u8 **)(obj + 0x24) + 0x10);
                *(u16 *)(obj + 0x34) = (*(u16 *)(obj + 0x34) & 0xFFBE) | 0x1400;
                if (*(u8 **)(st + 0x8C) != 0)
                    *(u16 *)(*(u8 **)(st + 0x8C) + 0x34) &= 0xFFBE;
                func_L04_00410518(obj, es, st + 0x120, st + 0x124, st + 0x11C, *(void **)(st + 0x160));
                obj[0x20] = 2;
            }
        }
        (*(u16 *)(obj + 0x96))++;
        break;
    case 4:
        *(s32 *)(obj + 0x48) = 0;
        if (*(u8 **)(st + 0x8C) != 0)
            *(s32 *)(*(u8 **)(st + 0x8C) + 0x48) = 0;
        obj[0x20] = 1;
        break;
    }
}
