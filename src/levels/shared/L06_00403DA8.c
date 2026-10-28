#include "common.h"
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern void *func_002BFB38(void *, void *, int, int);
extern void func_002A7A00(float *, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void *func_L00_00338AE0(char *, char *, int, float, float);
extern int func_00283CF0(float);
extern float D_L06_001B2FC8 MACRO_ADDR;
extern char D_L06_001A8F20[] MACRO_ADDR;

void func_L06_00403DA8(void *unused, void *position)
{
    float vector[4];
    float angle, radius;
    int life, kind;
    char *effect;
    int i;
    float *data = &D_L06_001B2FC8;
    for (i = 15; i >= 0; --i) {
        angle = func_002A7940();
        radius = func_002A7878(0.0f, 0.050000004f);
        vector[0] = func_00283180(angle) * radius;
        vector[1] = func_00283198(angle) * radius;
        vector[2] = func_002A7878(0.050000004f, 0.10833334f);
        life = func_002A7820(90, 120);
        kind = func_002A77E0(2);
        func_002BFB38(position, vector, kind, life);
    }
    for (i = 0; i < 16; ++i) {
        func_002A7A00(vector, 1.0f, 1.0f);
        func_00282CC0(vector, vector, position);
        vector[2] = D_L06_001B2FC8 + 0.05f;
        effect = func_L00_00338AE0((char *)vector, D_L06_001A8F20, (int)data, func_002A7878(0.7f, 1.0f), i == 0 ? 2.0f : -2.0f);
        if (effect != 0)
            *(short *)(effect + 10) = func_00283CF0(func_002A7878(30.0f, 60.0f));
    }
}
