#include "include_asm.h"

#include "common.h"
extern int D_001A79F0 MACRO_ADDR;
extern int D_001A79F0_gp SDATA(D_001A79F0);
extern u8 D_0019B278[];
extern float D_L05_001B1738 __attribute__((sda));
extern float D_L05_001B173C __attribute__((sda));
extern float D_L05_001B1740 __attribute__((sda));
extern float D_L05_001B1748 __attribute__((sda));
extern float D_L05_001B174C __attribute__((sda));
extern float D_L05_001B1750 __attribute__((sda));
extern float D_L05_001B1754 __attribute__((sda));
extern int D_L05_001B1778 __attribute__((sda));
extern int D_L05_001B177C __attribute__((sda));
extern u8 *D_L05_001B1780 __attribute__((sda));
extern int D_L05_001B2170 __attribute__((sda));
extern int D_L05_001B1F68 __attribute__((sda));
extern int D_L05_001B2264[] __attribute__((sda));
extern u8 D_00189EA0[];
extern u8 D_00189E20[];
extern float func_002A7940(void);
extern void func_PAL_L01_0039AD60(void *);
extern float func_00283198(float);
extern float func_00283B98(float, float);
extern void func_PAL_L01_0039AE48(void *);
extern int func_002A77E0(int);
extern void func_PAL_L01_0041C560(void *);
extern float func_00282E48(void *, void *);
extern void func_PAL_002B1588(int, int);
extern int func_0029B3E0(int, int);
extern int func_002E5CF8(int, int, void *);
extern void func_0029F338(void *);
extern void func_L01_00397C98(void *);
extern void func_PAL_L01_0039AC80(void *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_PAL_L00_002D2668(int, int, float);
extern int func_00282948(void *);
extern void func_PAL_L00_002B9CD8(void *, void *, int, int);
extern void func_003355A8(int);
typedef union { float f[0x40]; int i[0x40]; s16 h[0x80]; u16 uh[0x80]; } Fields;

void func_PAL_L05_004319A8(u8 *actor)
{
    u8 *state = *(u8 **)(actor + 0x68);
    int i;
    u8 *hero;
    switch (actor[0x20]) {
    case 0:
        if (((Fields *)state)->i[0] == -1 || D_0019B278[((Fields *)state)->i[0] + (D_001A79F0_gp << 2)] != 0) {
            func_0029F338(actor);
            return;
        }
        qcopy(state + 0x10, actor + 0x10);
        ((Fields *)state)->f[0x1C / 4] = ((Fields *)actor)->f[0xF8 / 4];
        ((Fields *)actor)->f[0xF0 / 4] = func_002A7940();
        ((Fields *)actor)->f[0xF4 / 4] = func_002A7940();
        ((Fields *)actor)->f[0xF8 / 4] = func_002A7940();
        ((Fields *)actor)->f[0xFC / 4] = func_002A7940();
        ((Fields *)state)->f[0x68 / 4] = D_L05_001B1748 * 0.0003490659f;
        ((Fields *)state)->f[0x64 / 4] = D_L05_001B174C * 0.0003490659f;
        ((Fields *)state)->f[0x60 / 4] = D_L05_001B1750 * 0.0003490659f;
        if (((Fields *)actor)->h[0x32 / 2] < 64)
            ((Fields *)actor)->h[0x32 / 2] = 64;
        actor[0x20] = 1;
        func_PAL_L01_0039AD60(actor);
        return;
    case 1:
        ((Fields *)actor)->f[0x2C / 4] = *(float *)(*(char **)(actor + 0x24) + 0x24) * D_L05_001B1738;
        ((Fields *)actor)->f[0x18 / 4] = ((Fields *)state)->f[0x18 / 4] + D_L05_001B173C +
                                  D_L05_001B1740 * func_00283198(((Fields *)actor)->f[0xFC / 4]);
        ((Fields *)actor)->f[0xF0 / 4] = func_00283B98(((Fields *)actor)->f[0xF0 / 4], D_L05_001B1748 * 0.0003490659f);
        ((Fields *)actor)->f[0xF4 / 4] = func_00283B98(((Fields *)actor)->f[0xF4 / 4], D_L05_001B174C * 0.0003490659f);
        ((Fields *)actor)->f[0xF8 / 4] = func_00283B98(((Fields *)actor)->f[0xF8 / 4], D_L05_001B1750 * 0.0003490659f);
        ((Fields *)actor)->f[0xFC / 4] = func_00283B98(((Fields *)actor)->f[0xFC / 4], D_L05_001B1754 * 0.0003490659f);
        func_PAL_L01_0039AE48(actor);
        if (func_002A77E0(D_L05_001B1778) == 0)
            func_PAL_L01_0041C560(actor);
        if (func_00282E48(D_L05_001B1780 + 0x10, actor + 0x10) < 1.5f) {
            D_L05_001B2170 = 150;
            func_PAL_002B1588(0x124B, -1);
            D_0019B278[((Fields *)state)->i[0] + (D_001A79F0 << 2)] = 1;
            D_L05_001B177C++;
            func_0029B3E0(0, -1);
            func_002E5CF8(1, 0, actor);
            func_0029F338(actor);
        }
        return;
    case 2:
        D_L05_001B2264[1] = 1;
        func_L01_00397C98(actor);
        qcopy(actor + 0x10, D_00189EA0);
        qcopy(actor + 0xF0, D_00189EA0 + 0x10);
        if (actor[0x42] == 1) {
            func_PAL_L01_0039AC80(actor);
            if (func_002A77E0(10) == 0)
                func_PAL_L01_0041C560(actor);
            if (actor[0x60] & 2) {
                if (actor[0x43] != 0)
                    func_PAL_002A7E68(actor, 0, 0, 0);
                actor[0x31] = 0;
                ((Fields *)actor)->uh[0x34 / 2] |= 1;
                for (i = 3; i >= 0; i--)
                    func_PAL_L01_0041C560(actor);
            }
        }
        hero = D_00189E20;
        if (*(int *)(hero + 0xC28) & 2)
            func_PAL_L00_002D2668(0, 0, 25.0f);
        if (actor[0x42] == 0 && func_00282948(state + 0x6C) != 0) {
            D_L05_001B2170 = 150;
            func_PAL_002B1588(0x1234, -1);
            D_0019B278[((Fields *)state)->i[0] + (D_001A79F0 << 2)] = 1;
            D_L05_001B177C++;
            D_L05_001B1F68 = 0;
            func_PAL_L00_002B9CD8(hero + 0x80, hero + 0x90, 0, 0);
            func_003355A8(0);
            func_0029B3E0(0, -1);
            func_0029F338(actor);
        }
        break;
    }
}
