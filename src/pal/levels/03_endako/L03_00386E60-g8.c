#include "include_asm.h"

#include "common.h"
extern void func_002A7750(void *, int, int);
extern char *func_002A9640(void *, int, int);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_00283180(float), func_00283198(float);
extern void func_PAL_00303578(void *, void *, void *, int, int, int);
extern int D_L03_001AEC30 __attribute__((sda));
extern char D_L03_001AEC10[8] __attribute__((sda)), D_L03_001AEC08[8] __attribute__((sda)), D_L03_001AEC00[8] __attribute__((sda));
extern void func_PAL_L00_0032C328(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern void func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void func_0029F338(void *);
extern int func_002B3868(void *);
extern void func_L02_002DCEA0(int, float);
extern float D_L03_001B2460;
extern char *func_0029EFD0(int);
extern char D_L03_001B9980[];
extern int D_L03_001A8FB4, D_L03_001A8FB0;

void func_PAL_L03_00386E60(char *m)
{
    float pos[4], vel[4];
    int i;
    char *p;
    switch (*(unsigned char *)(m + 0x20)) {
    case 0:
        *(unsigned short *)(m + 0x34) |= 0x1000;
        func_002A7750(m, 1, -1);
        break;
    case 1: {
        char *hit;
        hit = func_002A9640(m, 0x4010000, 0);
        if (hit) {
            hit = *(char **)(hit + 0x20);
            if (hit && *(short *)(hit + 0xAA) == 0x825)
                func_002A7750(m, 3, -1);
            else func_002A7750(m, 2, -1);
        }
        *(unsigned char *)(m + 0xA8) = 0xFF;
        break;
    }
    case 2: {
        char *position = m + 0x10;
        if (!D_L03_001AEC30) {
            D_L03_001AEC30 = 1;
            qcopy(pos, position);
            pos[2] += 0.5f;
            i = 9;
            do {
                float angle, speed;
                i--;
                angle = func_002A7940();
                speed = func_002A7878(0, 1) * (0.020000001f);
                vel[0] = func_00283180(angle) * speed;
                vel[1] = func_00283198(angle) * speed;
                vel[2] = 0;
                vel[2] = func_002A7878(5, 10) * (0.020000001f);
                func_PAL_00303578(m, pos, vel, 0, 100, 0);
            } while (i >= 0);
        }
        func_PAL_L00_0032C328(m, D_L03_001AEC10, D_L03_001AEC08, D_L03_001AEC00, 65535, 0, -1, 6, 65535, 255, 0);
        func_PAL_L00_003FB330(position, 0, 25, 20, 20, 20, 45, 1, 1, 1, 0, 0, 0.5f, 20);
        func_0029F338(m);
        break;
    }
    case 3:
        if (func_002B3868(m)) func_L02_002DCEA0(1, 15);
        if (D_L03_001B2460 >= 1) {
            p = func_0029EFD0(0x1335);
            if (p) {
                qcopy(p + 0x10, D_L03_001B9980);
                *(unsigned char *)(p + 0x30) = 255;
            }
            D_L03_001A8FB4 = 2;
            D_L03_001A8FB0 = 12;
            func_002A7750(m, 1, -1);
        } else {
            unsigned int count = *(unsigned short *)(m + 0x96);
            unsigned int old = count++;
            *(unsigned short *)(m + 0x96) = count;
            if (old >= 51) func_002A7750(m, 1, -1);
        }
        break;
    }
}
