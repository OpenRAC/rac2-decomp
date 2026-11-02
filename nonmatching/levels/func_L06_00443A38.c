/* func_L06_00443A38: near miss, 936/936 bytes, 0 of 1 place (USA v1.01, 2 November 2026).

   Profile: its own unit, `-O2 -G8 -ffunction-sections -frac2-qcopy`.

   A Notak enemy's update: the spawn-time setup (both warnings when the count is over, the
   position copy, about thirty tuning fields, the speed and animation), then the shared
   distance, target and ground checks. Calls, constants and branches follow retail.
   What mattered: both prints sit inside the count test, and `I(0x98) = 3` comes before
   `B(0x28) = 3`, so cse gives the byte store the int constant's register as retail does.
   What differs (46 rows, one region): the order of the tuning stores and which FP register
   holds 0.333 and 0.4 ($f3/$f0 swapped). Moving the 0.333, 0.6, 0.4 and 0.5 stores to every
   position in the block moves it by at most two rows. */

#include "common.h"

extern int D_L06_001B2838;
extern char *D_L06_001B2480;
extern float D_L06_001B1090 __attribute__((sda));
extern char D_L06_002E20C8[];
extern char D_L06_002E2128[];
extern char D_L06_001B9840[];
extern void func_0026FEB8(const char *, ...);
extern void func_00282A28(void);
extern int func_00283CF0(float);
extern float func_002A78D8(float, float);
extern float func_002A7940(void);
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern int func_002B0ED8(void *, void *, int);
extern void func_L06_00443E88(void *);
extern void func_L06_00443F30(char *);
extern void func_002A6C58(void *, int, int);
extern void func_002AC728(void *, void *, int, float, float);
extern void func_0029F338(void *);
extern s32 func_002B3BA8(void *, s32, float, float, s32, s32);

#define B(o) (*(unsigned char *)(v + (o)))
#define H(o) (*(short *)(v + (o)))
#define I(o) (*(int *)(v + (o)))
#define F(o) (*(float *)(v + (o)))

void func_L06_00443A38(u8 *m)
{
    u8 *v = *(u8 **)(m + 0x68);
    int hit;

    if (m[0x20] == 0) {
        char *rec;

        if (D_L06_001B2838 < m[0x21]) {
            func_0026FEB8(D_L06_002E20C8);
            func_0026FEB8(D_L06_002E2128);
        }
        func_00282A28();
        m[0x30] = 0x40;
        qcopy(v + 0x2E0, m + 0x10);
        F(0x324) = 1.0f;
        B(0x48) = func_00283CF0(15.0f);
        B(0x4A) = func_00283CF0(4.8f);
        H(0x88) = 0;
        B(0x60) = 8;
        I(0x98) = 3;
        B(0x28) = 3;
        F(0x30) = 0.333f;
        F(0x100) = F(0x324) * 0.6f;
        F(0x10C) = 0.5f;
        I(0x138) |= 0x80;
        F(0x108) = 0.5f;
        F(0x84) = 0.2f;
        F(0x8C) = 0.4f;
        F(0x134) = 0.05f;
        F(0x104) = F(0x324) * 0.5f;
        F(0x110) = 1.57079649f;
        F(0x130) = 0.52359885f;
        F(0x80) = 0.2f;
        F(0x1DC) = func_002A78D8(18.0f, 22.0f) * 0.0174532942f;
        B(0x1E8) = 7;
        B(0x1E9) = 6;
        H(0x1E2) = 120;
        H(0x1E4) = 180;
        F(0x1D4) = 3.0f;
        F(0x1D0) = D_L06_001B1090 * 0.0166666675f;
        rec = D_L06_001B2480 + I(0x210) * 0x30;
        if (*(short *)(rec + 0x30) != 0)
            I(0x13C) = **(int **)(rec + 0x3C);
        F(0x328) = func_002A7940();
        if (I(0x214) != 0) {
            *(int *)(m + 0x98) = 0;
            *(unsigned short *)(m + 0x34) = (*(unsigned short *)(m + 0x34) | 0x41) & 0xEFFF;
            func_002A7750(m, 9, 4);
            if (m[0x43] != 10)
                func_002A7470(m, 10, 0, 0);
        } else {
            func_002A7750(m, 1, 0);
            if (m[0x43] != 0)
                func_002A7470(m, 0, 0, 0);
        }
    }
    if (m[0x31] != 0 && func_00282E48(m + 0x10, D_L06_001B9840) < 24.0f) {
        func_002A93B0(m);
        m[0x6F] = 0x16;
    }
    hit = func_002B0ED8(m, v + 0x50, 0);
    if (hit != 0) {
        func_L06_00443E88(m);
        if (hit >= 4)
            func_L06_00443F30((char *)m);
    }
    if (*(float *)(m + 0x18) < 48.0f) {
        func_002A6C58(m, 0, 3);
        func_002AC728(m, m + 0x10, -1, 1.0f, 13.0f);
        func_0029F338(m);
    } else if (m[0x95] != 3 && m[0x95] != 4) {
        H(0x314) = func_002B3BA8(m, I(0x210), 16.0f, 0.0f, 0, 0);
    }
}
