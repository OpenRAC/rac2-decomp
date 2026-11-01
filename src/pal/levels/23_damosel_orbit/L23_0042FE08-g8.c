#include "include_asm.h"

#include "common.h"
typedef struct Edge_0042A8C0 {
    s16 a;
    s16 b;
    s16 c;
    s16 d;
} Edge_0042A8C0;
extern u8 *D_L23_001B1484 MACRO_ADDR;
extern float D_L23_001B1470 MACRO_ADDR;
extern float D_L23_001B39D0 MACRO_ADDR;
extern s32 D_L23_001B1694 MACRO_ADDR;
extern s32 D_L23_001B3934 MACRO_ADDR;
extern s32 D_L23_001B3980[] MACRO_ADDR;
extern s32 D_L23_0025E9D0[];
extern Edge_0042A8C0 D_L23_002A7A70[];
extern float D_L23_002A6390[][4];
extern float D_L23_0025EC40[][4];
extern float D_L23_001B1C60 __attribute__((sda));
extern s16 D_L23_001B1B96 __attribute__((sda));
extern s32 D_L23_001B1B98 __attribute__((sda));
extern s32 D_L23_001B1B98_2 __asm__("D_L23_001B1B98") __attribute__((sda));
extern float D_L23_001B1C4C __attribute__((sda));
extern float D_L23_001B1C50 __attribute__((sda));
extern float D_L23_001B1C54 __attribute__((sda));
extern float D_L23_001B1C0C __attribute__((sda));
extern float D_L23_001B1C34 __attribute__((sda));
extern s32 D_L23_001B1C44 __attribute__((sda));
extern s32 D_L23_001B1C48 __attribute__((sda));
extern s32 D_L23_001B1C40 __attribute__((sda));
extern u8 D_L23_001B1C58 __attribute__((sda));
extern u8 D_L23_001B1C5C __attribute__((sda));
extern s16 D_L23_001B1C38 __attribute__((sda));
extern s16 D_L23_001B1C3C __attribute__((sda));
extern void func_00291450(s32);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7878(float, float);
extern s32 func_L00_002FCF18(void *, float, float, float, float, float);
extern s32 func_L23_0041C0B0(void);
extern void func_L03_002EFB60(void *, void *, float);
extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void *func_L23_004256F0(void *, u8 *, void *, u8, u8, s16, s16, float, float, float, float, s32, s32, s32,
                               s32, s32);

/* Refreshes the sound handle, builds a rotation from the state's matrix rows and the roll angle, picks the next slot of the 15-entry ring, rewrites the slot's
   two edge vectors from the edge table and starts the effect object with them. */
void func_PAL_L23_0042FE08(u8 *moby) {
    u8 *vars;
    float m[16] __attribute__((aligned(16)));
    float v60[4] __attribute__((aligned(16)));
    float v70[4] __attribute__((aligned(16)));
    float m80[12] __attribute__((aligned(16)));
    float vB0[4] __attribute__((aligned(16)));
    float vC0[4] __attribute__((aligned(16)));
    float f20;
    float f21;
    float f22;
    float r1;
    float r2;
    float r3;
    s32 flag;
    float *rot;
    s32 e;
    u8 *hero;

    if (D_L23_001B1484 != 0) {
        D_L23_001B39D0 = D_L23_001B1470 * D_L23_001B1C60;
        if (D_L23_001B1B96 != -1) {
            func_00291450(D_L23_001B1B96);
        }
        func_00282D30(v60, D_L23_001B1484 + 0xE0, 5.0f);
        func_00282CC0(v60, v60, D_L23_001B1484 + 0x10);
        r1 = func_002A7878(0.0f, 1.3f) + 1.3f;
        r2 = func_002A7878(0.0f, 1.3f) + 1.3f;
        r3 = func_002A7878(0.0f, 1.35f) + 1.6f;
        D_L23_001B1B96 = func_L00_002FCF18(v60, 10.0f, 0.0f, r1, r2, r3);
        if (func_L23_0041C0B0() == 0) {
            flag = 0;
            f21 = D_L23_001B1C4C - D_L23_001B1C4C * 0.5f;
            f20 = D_L23_001B1C50 - D_L23_001B1C50 * 0.5f;
            f22 = D_L23_001B1C54 * 0.5f;
        } else {
            flag = 1;
            f21 = D_L23_001B1C4C;
            f22 = D_L23_001B1C54 * 1.6f;
            f20 = D_L23_001B1C50;
        }
        vars = *(u8 **)(moby + 0x68);
        hero = D_L23_001B1484;
        qcopy_nc(m, hero + 0xC0);
        qcopy_nc(m + 4, hero + 0xD0);
        qcopy_nc(m + 8, hero + 0xE0);
        qzero_nc(m + 12);
        func_L03_002EFB60(m, m, D_L23_001B1C0C);
        qcopy(m + 12, D_L23_001B1484 + 0x10);
        m[15] = 1.0f;
        rot = m;
        qzero_nc(v70);
        v70[2] = *(float *)vars;
        func_002833F0(m80, v70);
        func_00283738(rot, rot, m80);
        D_L23_001B1B98 = D_L23_001B1B98 + 1;
        D_L23_001B1B98_2 = D_L23_001B1B98 % 15;
        if (D_L23_001B1694 < 0) {
            if (D_L23_001B1694 >= -0x39) {
                D_L23_001B3980[D_L23_001B1B98_2] = D_L23_001B3980[D_L23_001B1B98_2] + 1;
            }
        }
        D_L23_001B3980[D_L23_001B1B98_2] = D_L23_001B3980[D_L23_001B1B98_2] % D_L23_001B3934;
        e = D_L23_0025E9D0[D_L23_001B3980[D_L23_001B1B98_2]];
        func_002830C0(vB0, D_L23_002A6390[D_L23_002A7A70[e].a], m);
        func_002830C0(vC0, D_L23_002A6390[D_L23_002A7A70[e].b], m);
        qcopy_nc(D_L23_0025EC40[D_L23_001B1B98_2 * 2], vB0);
        qcopy_nc(D_L23_0025EC40[D_L23_001B1B98_2 * 2 + 1], vC0);
        func_L23_004256F0(D_L23_0025EC40[D_L23_001B1B98_2 * 2], moby, D_L23_0025EC40[D_L23_001B1B98_2 * 2 + 1],
                          D_L23_001B1C58, D_L23_001B1C5C, D_L23_001B1C38, D_L23_001B1C3C, f21, f20, f22,
                          D_L23_001B1C34, D_L23_001B1C40, D_L23_001B1C44, flag, D_L23_001B1C48, 0);
    }
}
