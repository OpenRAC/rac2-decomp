/* Current retained result, 1 November 2026: 3288/3288 bytes, not exact. The hit request now has its real
 * aligned vector and the extra float at +0x24 read by func_002A8E20; tail alignment is implicit, not dummy
 * bytes. Both matrix consumers were checked: they read/write exactly three quadwords, so the 48-byte
 * matrices are intentional. The PRE spill ordering remains unresolved.
 * Not a functional-port qualification or a complete matching-build result.
 * Profile: -O2 -G64 -Wa,-G64 -ffunction-sections -g -frac2-qcopy -frac2-qcopy-barrier.
 * Earlier measurements below remain historical where superseded by this note.
 */
/* func_L00_003D1D28 (27 levels, 3,288 bytes): turret/beam weapon controller. Opus draft (big35), 2026-10-26; not linked.
 * Profile: -O2 -G64 -Wa,-G64 -ffunction-sections -g -frac2-qcopy -frac2-qcopy-barrier, as its own unit
 * (src/levels/shared/L00_003D1D28-g64.c). 822/822 words, every opcode equal; 46 words differ, check.py 0/27
 * (first difference +0x7AC at every place; symbols derive at all 27).
 * Levers found: the emitter table D_L00_001A8F20 is MACRO_ADDR (cc1 treats it as small data, so gcse leaves
 * its lui/addiu at each call); the gp block D_L00_001B0190.. needs -Wa,-G64 for the 64-byte matrix; the
 * t8/tA pair test is the merged lwu of two adjacent fields of a 16-aligned struct (fold_truthop); weapon
 * entries as (u8 *)table + idx * 0xE0 give retail's mult-first addu; -g gives the single pre-div.s nop
 * once the entry pointer is its own statement; one loop variable per loop; func_002E5CF8 returns int.
 * Left: (1) the spill slots of 14 PRE address pseudos (hit, rot, dir, ... list, saved) at 0x238-0x270.
 * Their numbers follow gcse's expression hash-bucket order: (14030 + offset) % N, N = max_cuid/2 | 1.
 * Ours N = 381 (758 insns after cse), retail's order fits N = 391 only (780-783 insns): retail's
 * source has about 20 more insns at gcse that later passes remove (see ONE-OFF F26 for the same cause).
 * (2) li $v1,30 is scheduled before addiu $v0,%lo(D_L00_001B8C80) in state 2's shake block.
 * In the permuter farm.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef float Vec4[4] __attribute__((aligned(16)));
typedef float Mat3[12] __attribute__((aligned(16)));
typedef float Mat4[16] __attribute__((aligned(16)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; u8 *ptr[0x980]; TI128 q[0x260]; } Hero;

typedef struct {
    float timer;          /* 0x00 */
    s16 t4;               /* 0x04 */
    s16 t6;               /* 0x06 */
    s16 t8;               /* 0x08 */
    s16 tA;               /* 0x0A */
    float fC;             /* 0x0C */
    Vec4 v10; /* 0x10 */
    float f20;            /* 0x20 */
    float f24;            /* 0x24 */
    int t28;              /* 0x28 */
    float f2C;            /* 0x2C */
    Vec4 q30; /* 0x30 */
    int t40;              /* 0x40 */
    int t44;              /* 0x44 */
    float f48;            /* 0x48 */
    int t4C;              /* 0x4C */
    int handle;           /* 0x50 */
} TurretState;

typedef struct {
    Vec4 pos;             /* 0x00: copied by the request consumer as one quadword */
    u8 *source;           /* 0x10 */
    int flags;            /* 0x14 */
    u8 b18;               /* 0x18 */
    u8 b19;               /* 0x19 */
    u16 oclass;           /* 0x1A */
    float damage;         /* 0x1C */
    int count;            /* 0x20 */
    float extra;          /* 0x24: consumed by func_002A8E20 */
} Hit;

typedef struct { u8 pad0[0x28]; int id; u8 pad2C[0x28]; float rate; u8 pad58[0x18]; float damage; u8 pad74[0x6C]; } WeaponEntry;

extern u8 D_00189E20[];
extern u8 D_00138180[];
extern u8 D_00139568[];
extern u8 D_001395AC NOT_SDA;
extern float D_0018A580[4] NOT_SDA;
extern WeaponEntry D_L00_00262570[];
extern u8 D_L00_00296120[];
extern u8 D_L00_001A8F20[] MACRO_ADDR;
typedef struct { u8 pad[0x160]; float f160; int pad164; int i168; int i16C; float f170; int pad174; int i178; } Shake;
extern Shake D_L00_001B8C80;
extern u8 *D_L00_001C3280[];
extern float D_L00_001B0190[16] __attribute__((sda));
extern u16 D_L00_001B01E8 __attribute__((sda));
extern u16 D_L00_001B01EC __attribute__((sda));
extern int D_L00_001B020C __attribute__((sda));
extern u16 D_L00_001B0214 __attribute__((sda));
extern int D_L00_001B021C __attribute__((sda));
extern float D_L00_001B0220 __attribute__((sda));
extern float D_L00_001B0224 __attribute__((sda));
extern float D_L00_001B0228 __attribute__((sda));
extern int D_L00_001B0238 __attribute__((sda));

extern s32 func_00282978(s16 *);
extern int func_00282948(void *);
extern void func_002829D8(void *);
extern void ref_L00_003D1D28_00(int, int);
extern int func_L00_002D4040(int);
extern int func_L00_002D3F30(int, int);
extern void func_00273318(void *, float, u32, void *, int, float, int, float, int);
extern void func_L00_002AF7D0(void);
extern void func_L00_002AF568(void);
extern void func_002A75E0(void *, int, int, int, int);
extern int func_L00_002D6998(void *);
extern void func_L00_002D6B70(int);
extern float func_002A7940(void);
extern float func_00283CE0(int);
extern int func_002E5CF8(int, int, void *);
extern void func_L00_002E6EF8(void *, void *);
extern void func_L00_003D2ED0(u8 *);
extern void func_L00_003D3388(u8 *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern u8 *func_L00_0033EC48(void *, int, float, float, u32, int, int, void *, int, int, int, int);
extern void func_L00_003D2C00(u8 *, void *, int);
extern s32 func_00277F48(f32, void *, s32, void *, s32);
extern void func_002A8E20(u8 *, Hit *);
extern void func_0032D758(u8 *, int, u8 *);
extern void func_00283410(void *, void *);
extern void func_00283678(void *, void *);
extern void func_0029FCC0(u8 *, int, void *);
extern void func_00283738(void *, void *, void *);
extern float func_002A7878(float, float);
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern float func_00283B98(float, float);
extern u8 *func_L00_003D2A00(u8 *, void *, void *, Hit *);

#define HERO ((Hero *)D_00189E20)

void func_L00_003D1D28(u8 *self)
{
    Vec4 a;
    Vec4 b;
    TurretState *st = *(TurretState **)(self + 0x68);
    int ready;
    u8 *p;

    if (self[0x20] == 0) {
        self[0x20] = 1;
        st->handle = -1;
        st->t8 = 0;
        st->tA = 0;
        st->t28 = 0;
        st->t44 = 0;
        st->t4C = 0;
    }
    if (self[0x20] == 6) {
        if (func_00282978(&st->t4))
            self[0x20] = 1;
    }
    if (HERO->i[0x2294 / 4] == 1)
        ref_L00_003D1D28_00(0x1D, 1);
    func_002829D8(st);
    if (HERO->i[0x2294 / 4] == 0x1D) {
        u32 color;
        if (st->timer > 0.0f && func_L00_002D4040(-1))
            color = 0x600000FF;
        else
            color = 0x600FFF0F;
        func_00273318(self, 1.3f, color, 0, 0x21, 0.0f, -1, 90.0f, 4);
    }
    if (st->t4C != 0 && func_00282948(&st->t4C))
        func_L00_002AF7D0();
    if (self[0x42] == self[0x43] && (self[0x60] & 2))
        func_002A75E0(self, 1, 0, 2, 0);
    ready = 1;
    if (HERO->i[0x2294 / 4] == 0x1D) {
        if (func_00282948(&HERO->i[0x2534 / 4]) == 0)
            ready = 0;
    } else {
        HERO->i[0x2534 / 4] = 0x28;
    }
    if (self[0x20] == 1 && HERO->b[0x22BC] == 0 && st->timer == 0.0f && HERO->i[0x1240 / 4] >= 0x17 && ready) {
        if ((((Hero *)D_00138180)->i[0x1A0 / 4] & HERO->i[0x1230 / 4]) && func_L00_002D3F30(-1, 1)) {
            if (HERO->ptr[0x2290 / 4][0x43] == ((WeaponEntry *)((u8 *)D_L00_00262570 + D_001395AC * 0xE0))->id || HERO->i[0x229C / 4] != 0 || HERO->h[0x24EC / 2] != 0) {
                st->t40 = 1;
                st->t6 = D_L00_001B01E8;
            } else {
                st->t40 = 0;
                st->t6 = 2;
            }
            func_L00_002AF568();
            st->handle = func_L00_002D6998(D_L00_00296120);
            func_002A75E0(self, 2, 0, 2, 0);
            st->t4C = D_L00_001B0238;
            self[0x20] = 2;
            st->fC = func_002A7940();
            st->t8 = D_L00_001B01EC;
            st->f20 = 1.0f / func_00283CE0(st->t8);
            st->tA = D_L00_001B0214;
            st->t8 += 2;
            st->f24 = 1.0f / func_00283CE0(st->tA);
            st->t28 = D_L00_001B020C;
            st->f2C = 1.0f / func_00283CE0(st->t28);
            st->t44 = D_L00_001B021C;
            st->f48 = 1.0f / func_00283CE0(st->t44);
            st->t44 += 2;
        } else if (((Hero *)D_00138180)->i[0x1A4 / 4] & HERO->i[0x1230 / 4]) {
            func_002E5CF8(5, 0, self);
        }
        if (!(((Hero *)D_00138180)->i[0x1A0 / 4] & HERO->i[0x1230 / 4]) || !func_L00_002D4040(-1) || HERO->b[0x22B8] == 0) {
            if (st->handle >= 0) {
                func_L00_002D6B70(st->handle);
                st->handle = -1;
            }
        }
    }
    if (st->t6 == 0) {
        func_00282978(&st->tA);
        func_00282978(&st->t8);
        func_00282948(&st->t28);
        func_00282948(&st->t44);
        if (st->t8 != 0 || st->tA != 0 || st->t28 != 0 || st->t44 != 0)
            func_L00_002E6EF8(func_L00_003D2ED0, self);
        func_L00_003D3388(self);
    }
    if (self[0x20] == 2 || self[0x20] == 3) {
        if (func_00282978(&st->t6)) {
            if (self[0x20] == 2) {
                float f;
                self[0x20] = 3;
                qcopy(st->q30, D_0018A580);
                a[0] = D_L00_001B0220;
                a[1] = D_L00_001B0224 - 0.25f;
                a[2] = D_L00_001B0228;
                a[3] = 1.0f;
                func_00283098(b, a, self + 0xC0);
                func_00282CC0(b, b, self + 0x10);
                {
                    u8 *q = func_L00_0033EC48(b, 7, 0.4f, 8.0f, 0x80FFFFFF, 2, 0, D_L00_001A8F20, 0, 0, 6, 0);
                    if (q)
                        *(TI128 *)(q + 0x10) = *(TI128 *)(b);
                }
                {
                    u8 *q = func_L00_0033EC48(b, 4, 0.5f, 12.0f, 0x3CFF1010, 2, 0, D_L00_001A8F20, 3, 0, 6, 0);
                    if (q)
                        *(TI128 *)(q + 0x10) = *(TI128 *)(b);
                }
                {
                    u8 *q = func_L00_0033EC48(b, 4, 0.5f, 4.0f, 0x80FFFFFF, 2, 0, D_L00_001A8F20, 3, 0, 6, 0);
                    if (q)
                        *(TI128 *)(q + 0x10) = *(TI128 *)(b);
                }
                a[2] = -a[2];
                func_00283098(b, a, self + 0xC0);
                func_00282CC0(b, b, self + 0x10);
                {
                    u8 *q = func_L00_0033EC48(b, 7, 0.4f, 8.0f, 0x80FFFFFF, 2, 0, D_L00_001A8F20, 0, 0, 6, 0);
                    if (q)
                        *(TI128 *)(q + 0x10) = *(TI128 *)(b);
                }
                {
                    u8 *q = func_L00_0033EC48(b, 4, 0.5f, 12.0f, 0x3CFF1010, 2, 0, D_L00_001A8F20, 3, 0, 6, 0);
                    if (q)
                        *(TI128 *)(q + 0x10) = *(TI128 *)(b);
                }
                {
                    u8 *q = func_L00_0033EC48(b, 4, 0.5f, 4.0f, 0x80FFFFFF, 2, 0, D_L00_001A8F20, 3, 0, 6, 0);
                    if (q)
                        *(TI128 *)(q + 0x10) = *(TI128 *)(b);
                }
                a[2] = 0.0f;
                a[1] = D_L00_001B0224;
                func_00283098(b, a, self + 0xC0);
                func_00282CC0(st->v10, b, self + 0x10);
                func_L00_003D2C00(self, st->v10, 0);
                func_L00_002E6EF8(func_L00_003D2ED0, self);
                func_002E5CF8(0, 0, self);
                f = 0.06f;
                if (st->t40)
                    f = 0.12f;
                D_L00_001B8C80.f160 = f;
                D_L00_001B8C80.i168 = 30;
                D_L00_001B8C80.f170 = f;
                D_L00_001B8C80.i178 = 30;
                D_L00_001B8C80.i16C = 0;
            } else {
                Hit hit;
                Vec4 up;
                Vec4 side;
                Vec4 fwd;
                Mat3 basis;
                Mat3 inv;
                Mat4 mtx;
                Vec4 origin;
                Vec4 offs;
                u8 *list[20];
                int saved[20];
                Vec4 rot;
                Vec4 dir;
                Vec4 from;
                Vec4 to;
                int count, i, n, h, k, r;
                float angle, spread;

                self[0x20] = 6;
                st->t4 = 0x1C;
                hit.flags = 0x10000;
                hit.count = 1;
                hit.b18 = 3;
                hit.b19 = 2;
                hit.oclass = *(u16 *)(self + 0xAA);
                hit.damage = ((WeaponEntry *)((u8 *)D_L00_00262570 + D_00139568[0x1A] * 0xE0))->damage;
                hit.source = self;
                func_00282D30(a, self + 0xD0, -1.35f);
                func_00282CC0(a, a, self + 0x10);
                func_00282D30(b, self + 0xC0, 0.275f);
                func_00282CC0(a, a, b);
                n = func_00277F48(1.5f, a, 1, HERO->ptr[0x2290 / 4], 0);
                for (h = 0; h < n; h++) {
                    if (D_L00_001C3280[h] != HERO->ptr[0x2290 / 4]) {
                        func_00282D30(hit.pos, self + 0xD0, -1.5f);
                        hit.pos[3] = 5627.925f;
                        func_002A8E20(D_L00_001C3280[h], &hit);
                        func_0032D758(D_L00_001C3280[h], 0x44, self);
                    }
                }
                func_00283410(mtx, D_L00_001B0190);
                func_00283678(inv, mtx);
                func_0029FCC0(self, 0, origin);
                if (HERO->h[0x24EC / 2] == 1) {
                    func_00282D30(up, self + 0xD0, -1.0f);
                    func_00282D30(side, self + 0xC0, -1.0f);
                    func_00282D30(fwd, self + 0xE0, 0.1f);
                    func_00283738(basis, self + 0xC0, inv);
                } else {
                    qcopy(up, HERO->b + 0x730);
                    qcopy(side, HERO->b + 0x740);
                    func_00282D30(fwd, HERO->b + 0x750, -0.1f);
                    func_00283738(basis, HERO->b + 0x730, inv);
                }
                qcopy(st->q30, up);
                spread = 1.0471977f;
                count = 0;
                angle = 0.0f;
                for (k = 0; k < 20; k++) {
                    list[k] = 0;
                    saved[k] = 0;
                }
                for (i = 0; i < 20; i++) {
                    func_002AB668(rot, side, func_002A7878(0.01f, 0.52359885f));
                    func_002ACDE8(dir, up, rot);
                    func_002ACDE8(offs, fwd, rot);
                    angle = func_00283B98(func_002A7878(spread * 0.5f, spread * 1.5f), angle);
                    func_002AB668(rot, up, angle);
                    func_002ACDE8(dir, dir, rot);
                    func_002ACDE8(offs, offs, rot);
                    func_00282D30(dir, dir, 38.0f);
                    func_00282CC0(from, origin, offs);
                    func_00282CC0(to, from, dir);
                    p = func_L00_003D2A00(self, from, to, &hit);
                    if (p) {
                        saved[count] = *(int *)(p + 0x98);
                        list[count] = p;
                        *(int *)(p + 0x98) = 0;
                        count++;
                    }
                }
                for (r = 0; r < count; r++)
                    *(int *)(list[r] + 0x98) = saved[r];
                {
                    WeaponEntry *w = (WeaponEntry *)((u8 *)D_L00_00262570 + D_00139568[0x1A] * 0xE0);
                    st->timer = 1.0f / w->rate;
                }
            }
        }
    }
}
