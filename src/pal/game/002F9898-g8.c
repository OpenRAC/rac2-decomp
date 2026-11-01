#include "include_asm.h"
extern void func_002F93B0(void);

void func_PAL_002FA6F8(void)
{
    func_002F93B0();
}

#include "common.h"
#include "common.h"
typedef unsigned int Quad_002F9198 __attribute__((mode(TI), aligned(16)));
typedef struct { Quad_002F9198 a, b, c; } Three_002F9198;
typedef struct { int words[5]; } Five_002F9198;
typedef struct { int state; char pad4[0x24]; char *moby; char pad2C[0x24]; int mode; char pad54[0xC]; int restore; char pad64[0x7C]; Quad_002F9198 saved; } Shop_002F9198;
typedef struct { char *moby; char pad4[0x14]; int a; char pad1C[0x14]; int b; } HeroMenu_002F9198;
extern Shop_002F9198 D_0021F240;
extern char D_001B5350[];
extern Three_002F9198 D_001B2250 MACRO_ADDR;
extern float D_001AD234 __attribute__((sda));
extern float D_001AD238 __attribute__((sda));
extern int D_001B2284, D_001B2288, D_001B228C, D_001B2290, D_001B2294, D_001B2298;
extern int D_001AD230 __attribute__((sda));
extern int D_001AD1B8 __attribute__((sda));
extern unsigned short D_001AD1BC __attribute__((sda)), D_001AD1C0 __attribute__((sda));
typedef struct { char pad0[0x20]; short level; char pad22[0x1E]; } Settings_002F9198;
extern Settings_002F9198 D_001A79F8 MACRO_ADDR;
extern Five_002F9198 D_001AD308;
extern HeroMenu_002F9198 D_00152C00;
extern int D_001A7AF0;
extern unsigned short D_001A7AF2;
extern void func_002FC138(void);
extern int func_002E5CF8(int, int, void *);
extern void func_PAL_00292CD0(int);
extern int func_00288FB8(int);
extern void func_PAL_0029D630(int, int);
extern void func_PAL_00292F00(int);
extern void func_PAL_00292FC8(int);
extern void func_002E6178(int);

void func_PAL_002FA118(void)
{
    Shop_002F9198 *s = &D_0021F240;
    Five_002F9198 table;
    func_002FC138();
    func_002E5CF8(5, 17, s->moby);
    if (s->restore) {
        qcopy(D_001B5350, &s->saved);
        { Quad_002F9198 *dst = (Quad_002F9198 *)(D_001B5350 + 0x220);
          Three_002F9198 *src = &D_001B2250;
          dst[0] = src->a; dst[1] = src->b; dst[2] = src->c; }
    }
    *(unsigned short *)(s->moby + 0x34) |= 0x100;
    D_0021F240.state = 2;
    D_001AD234 = 1.0f;
    D_001AD238 = 1.1f;
    D_001AD230 = 0;
    D_001B2290 = 0; D_001B2294 = 0; D_001B2298 = 0;
    D_001B2284 = 96;
    D_001B2288 = 96;
    D_001B228C = 85;
    if (D_0021F240.mode == 3) {
        if (D_001AD1B8) D_001A79F8.level = D_001AD1BC; else D_001A79F8.level = D_001AD1C0;
        func_PAL_00292CD0(D_001A79F8.level);
        table = D_001AD308;
        if (D_001AD1B8) func_PAL_0029D630(func_00288FB8(table.words[D_001A79F8.level]), -1);
    }
    if (D_0021F240.mode == 2) {
        if (D_00152C00.a != D_001A7AF0) {
            char *m;
            func_PAL_00292F00(D_001A7AF0 & 3);
            m = D_00152C00.moby;
            if (m && *(int *)(m + 0x98)) *(int *)(m + 0x98) = *(int *)(*(char **)(m + 0x24) + 0x10);
        }
        if (D_00152C00.b != (D_001A7AF2 & 31)) func_PAL_00292FC8(D_001A7AF2 & 31);
        func_002E6178(0);
    }
}
