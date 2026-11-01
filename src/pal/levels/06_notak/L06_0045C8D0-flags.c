#include "include_asm.h"

#include "common.h"
extern void func_00282CC0(void *, void *, void *);
extern float func_00282C48(float);
extern float func_002A7878(float, float);
extern float D_L06_001B234C __attribute__((sda));
extern float D_001B2350 __attribute__((sda));
extern int func_002E5CF8(int, int, char *);
extern void func_0029F338(char *);
extern void func_00283098(void *, void *, void *);
extern double func_001234F0(float);
extern void func_0026FEB8(char *, ...);
extern char D_L06_001B18E0[];
extern void func_PAL_L00_00328480(char *, void *, int, float, int, void *, float, unsigned int, float, float, int);

void func_PAL_L06_0045D258(char *a0) {
    float pos[4], vel[4];
    int count = 13, i;
    if (D_L06_001B234C < 0.9f && D_001B2350 < 0.9f) count = 40;
    for (i = 0; i < count; i++) {
        pos[0] = func_002A7878(-8.045f, 8.045f);
        pos[1] = func_00282C48(pos[0] * 0.1243008077f) * 1.745f;
        pos[2] = func_002A7878(0.0f, 3.99f);
        vel[0] = pos[0] * 0.0049720327f;
        vel[1] = -0.16000001f;
        vel[2] = func_002A7878(3.0f, 7.0f) * 0.020000001f;
        func_00283098(pos, pos, a0 + 0xC0);
        func_00282CC0(pos, pos, a0 + 0x10);
        func_00283098(vel, vel, a0 + 0xC0);
        func_0026FEB8(D_L06_001B18E0, func_001234F0(pos[0]), func_001234F0(pos[1]), func_001234F0(pos[2]), func_001234F0(vel[0]), func_001234F0(vel[1]), func_001234F0(vel[2]));
        func_PAL_L00_00328480(a0, pos, 1, 0.0f, 1, vel, 3.0f, 0x50808040, 1.0f, 5.5f, 0);
        func_002E5CF8(0, 0, a0);
    }
    func_0029F338(a0);
}
