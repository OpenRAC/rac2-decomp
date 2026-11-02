/* func_L06_0041EF08: near miss, 920/916 bytes, 0 of 1 place (USA v1.01, 2 November 2026).

   Profile: its own unit, `-O2 -G0 -ffunction-sections -frac2-qcopy`.

   Another Notak enemy's update, the same shape as func_L06_00443A38: spawn-time setup, then
   the distance, target and ground checks. Calls and constants follow retail (the float
   literals are exact).
   What differs: the constant 3. Retail stores it for both 0xCE and 0xA8 from one register in
   the setup block and loads a fresh 3 for the later `m[0x43] != 3` test. Here cse, following
   the path around the `m[0x43] != 1` call (cse-skip-blocks), reuses the setup's 3 for that
   test, so it lives across calls in a saved $s2 (one more save, a different frame). Without
   -fcse-skip-blocks the $s2 goes, but retail does keep 20.0f in $f20 across the same skip, so
   retail had that flag; something cuts the path between the setup and the calls that this C
   does not have. Writing `I(0xA8) = 3` before `B(0xCE) = 3` shares the register as retail
   does (this draft); do-while wrappers around the animation sets change nothing. */

#include "common.h"

typedef int Quad __attribute__((mode(TI)));

extern char D_L06_001B0820[];
extern char D_L06_001B9840[];
extern int func_L02_0032E508(void *, int, void *, int);
extern void func_0026FEB8(const char *, ...);
extern float func_002A78D8(float, float);
extern int func_002A7820(int, int);
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern int func_00283CF0(float);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern int func_002B0ED8(void *, void *, int);
extern void func_L06_0041F798(void *);
extern s32 func_002B3BA8(void *, s32, float, float, s32, s32);
extern void func_002A6C58(void *, int, int);
extern void func_002AC728(void *, void *, int, float, float);
extern void func_0029F338(void *);

#define B(o) (*(unsigned char *)(v + (o)))
#define H(o) (*(short *)(v + (o)))
#define I(o) (*(int *)(v + (o)))
#define F(o) (*(float *)(v + (o)))

void func_L06_0041EF08(u8 *m)
{
    u8 *v = *(u8 **)(m + 0x68);
    int hit;

    if (m[0x20] == 0) {
        I(0x480) = func_L02_0032E508(m, I(0x230), v + 0x260, 16);
        func_0026FEB8(D_L06_001B0820, I(0x480));
        qcopy(v + 0x460, m + 0x10);
        I(0xA8) = 3;
        B(0xD4) = 0;
        H(0x26) = 0;
        B(0x72) = 16;
        F(0x46C) = *(float *)(m + 0xF8);
        B(0x76) = 14;
        B(0x77) = 15;
        F(0x7C) = 0.20000002f;
        F(0x80) = 0.125f;
        F(0x84) = 0.00555555569f;
        F(0x88) = 0.00972222257f;
        F(0x94) = 0.5f;
        F(0x9C) = 0.4f;
        B(0xCC) = 7;
        B(0xCD) = 12;
        B(0xCE) = 3;
        B(0xCF) = 5;
        B(0xD2) = 10;
        B(0xD3) = 17;
        F(0x5AC) = (float)B(0x34);
        B(0x29) = 1;
        F(0x30) = 0.75f;
        B(0x70) = 15;
        B(0x71) = 12;
        F(0x90) = 0.5f;
        B(0x28) = 1;
        F(0x8C) = 0.00416666688f;
        F(0x47C) = func_002A78D8(10.0f, 25.0f) * 0.0174532942f;
        I(0x478) = 0;
        H(0x24C) = func_002A7820(0, 0x5F);
        I(0x498) = -1;
        I(0x5A0) = H(0x490);
        *(Quad *)(v + 0x5B0) = 0;
        func_002A7750(m, 1, 0);
        if (m[0x43] != 1)
            func_002A7470(m, 1, 0, 0);
        B(0x48) = func_00283CF0(20.0f);
        B(0x4A) = func_00283CF0(8.0f);
        if (H(0x492) != 0) {
            if (m[0x43] != 3)
                func_002A7470(m, 3, 0, 0);
            B(0x48) = func_00283CF0(20.0f);
            B(0x4A) = func_00283CF0(24.0f);
        }
    }
    if (m[0x31] != 0 && func_00282E48(m + 0x10, D_L06_001B9840) < 24.0f) {
        func_002A93B0(m);
        m[0x6F] = 0x16;
    }
    hit = func_002B0ED8(m, v + 0x60, 0);
    if (hit != 0) {
        if (B(0x37) == 10)
            B(0xD7) = 1;
        if (hit == 5) {
            I(0xF0) = 0;
            F(0xF4) = 0.837758183f;
        }
        func_L06_0041F798(m);
        m[0xA8] = 0xFF;
    }
    I(0x228) = func_002B3BA8(m, I(0x220), F(0x240), 10.0f, 0, 0);
    I(0x22C) = func_002B3BA8(m, I(0x224), F(0x244), 10.0f, 0, 0);
    if (*(float *)(m + 0x18) < 48.0f) {
        func_002A6C58(m, 0, 3);
        func_002AC728(m, m + 0x10, -1, 1.0f, 13.0f);
        func_0029F338(m);
    }
}
