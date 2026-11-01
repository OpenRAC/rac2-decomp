#include "include_asm.h"

#include "common.h"
typedef struct {
    char p0[0x1B8];
    s32 i1B8;
    char p1BC[0x34E - 0x1BC];
    s16 i34E;
    char p350[0x49E - 0x350];
    u8 i49E;
    char p49F[0xC38 - 0x49F];
    f32 fC38;
    char pC3C[0x1310 - 0xC3C];
    s32 i1310, i1314;
    char p1318[0x1338 - 0x1318];
    s32 i1338;
    char p133C[0x2290 - 0x133C];
    void *p2290;
    s32 i2294;
} G_4198;
typedef struct {
    s32 i0;
    char pad4[4];
    s32 i8;
    s32 iC;
    char pad10[0x10];
    f32 f20;
    f32 f24;
    f32 f28;
    f32 f2C;
    f32 f30;
    f32 f34;
    f32 f38;
    f32 f3C;
} V_4198;
typedef struct {
    char pad00[0x18];
    f32 f18;
    char pad1C[4];
    u8 state;
    char pad21[0xF];
    u8 u30;
    char pad31[3];
    u16 u34;
    char pad36[0x32];
    V_4198 *v;
} O_4198;
extern G_4198 D_00189E20;
extern s32 D_00138320;
extern s32 func_US2_0026F808(s32), func_00282948(void *);
extern void func_0029F338(void *), func_0027CFD0(void *, void *);
extern void func_00308768(void), func_00308DB8(void *);

/* Adapted from RAC1 update_beam_effect_lifecycle (OpenRAC, GPL-3.0). */
void func_US2_0030A098(void *p) {
    O_4198 *o = (O_4198 *)p;
    V_4198 *v = o->v;
    s32 flag = 0;
    s32 st;

    if ((&D_00189E20)->i1338 == 3 || func_US2_0026F808(3) == 8) {
        if (o->state == 1 || o->state == 3) {
            st = (&D_00189E20)->i2294;
            if ((u32)(st - 0xB) < 4
                || (st == 0x1B && ((u8 *)(&D_00189E20)->p2290)[0x42] == ((u8 *)(&D_00189E20)->p2290)[0x43]
                    && (&D_00189E20)->fC38 >= 6.0f && (&D_00189E20)->fC38 <= 16.0f)) {
                if (!(&D_00189E20)->i49E) flag = 1;
            }
            if ((&D_00189E20)->i2294 == 0x82 && (D_00138320 & 0x40)) flag = 1;
            if ((&D_00189E20)->i2294 == 0x10) {
                if ((&D_00189E20)->i1B8 < 44) {
                    flag = 1;
                }
            }
            if ((&D_00189E20)->i2294 == 0x21) {
                if ((&D_00189E20)->i1B8 < 15
                    || (33 < (&D_00189E20)->i1B8 && (&D_00189E20)->i34E != 0)) {
                    flag = 1;
                }
            }
            if ((&D_00189E20)->i2294 == 8) flag = 1;
            if ((&D_00189E20)->i2294 == 0x82) flag = 1;
        }
    }
    switch (o->state) {
    case 0:
        o->f18 += 0.5f;
        o->state = 1;
        o->u30 = 0xFF;
        o->u34 |= 1;
        break;
    case 1:
        if ((func_US2_0026F808(3) != 3 && func_US2_0026F808(3) != 8) || !D_00189E20.i1314) {
            func_0029F338(o);
        } else if (flag != 0) {
            o->state = 2;
            v->i0 = 2;
            v->f30 = 0.0125f / 2;
            v->f34 = 0.2f / 2;
            v->f38 = 0.05f / 2;
            v->f3C = 0.025f / 2;
            v->f20 = 0.0f;
            v->f24 = 0.0f;
            v->f28 = 0.0f;
            v->f2C = 0.0f;
        }
        break;
    case 2:
        v->f20 += v->f30;
        v->f24 += v->f34;
        v->f28 += v->f38;
        v->f2C += v->f3C;
        v->i8 = (&D_00189E20)->i1310;
        func_0027CFD0(func_00308768, o);
        if (func_00282948(v) != 0) {
            o->state = 3;
            v->f20 = 0.0125f;
            v->f24 = 0.2f;
            v->f28 = 0.05f;
            v->iC = 0;
            v->f2C = 0.025f;
        }
        break;
    case 3:
        v->i8 = (&D_00189E20)->i1310;
        func_0027CFD0(func_00308768, o);
        if (flag == 0) {
            o->state = 4;
            v->i0 = 8;
            v->f30 = 0.0125f / 8;
            v->f34 = 0.2f / 8;
            v->f38 = 0.05f / 8;
            v->f3C = 0.025f / 8;
        } else {
            v->f20 = 0.0125f;
            func_00308DB8(o);
        }
        break;
    case 4:
        if (func_00282948(v) != 0) {
            o->state = 1;
        } else {
            v->f20 -= v->f30;
            v->f24 -= v->f34;
            v->f28 -= v->f38;
            v->f2C -= v->f3C;
            v->i8 = (&D_00189E20)->i1310;
            func_0027CFD0(func_00308768, o);
        }
        break;
    }
}
