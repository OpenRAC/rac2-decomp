#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
extern void func_002A7750(char *, int, int);
extern float func_002A7878(float,float);
extern char *func_0035CBA0(char *,int,int);
extern void func_00282D30(void *,void *,float);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00283098(void *,void *,void *);
extern void func_00350388(char *);
extern void func_L00_0033E220(void *,void *,unsigned int,int,int,int,int,int,float,float);
extern void func_L00_0032A258(void *,void *,void *,void *,int,int,int,int,int,int,int);
extern void func_L00_00326110(char *,int,float);
extern void func_L01_0031A278(char *,void *,float,float,float);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void func_L00_003263D0(char *,void *,int,float,int,void *,float,unsigned int,float,float,int);
extern char D_L06_001B1C08[] SDATA(D_L06_001B1C08);
extern char D_L06_001B1C00[] SDATA(D_L06_001B1C00);
extern char D_L06_001B1C10[] SDATA(D_L06_001B1C10);
extern char D_L06_001A8F20[] MACRO_ADDR;
extern int D_L06_001B1C30 __attribute__((sda));

void func_L06_004621C8(char *obj)
{
    float pos[4], a[4], b[4], c[4];
    char *stateData = *(char **)(obj + 0x68);
    char *hit;
    int state = *(unsigned char *)(obj + 0x20);
    int i;

    *(Quad *)a = 0;
    a[2] = *(float *)(obj + 0x2C) * 21.5f;
    *(Quad *)pos = *(Quad *)a;
    switch (state) {
    case 0:
        func_L00_0033E220(pos, obj, 0x50801420, -1, 0, -1, 0, 96, 430500.0f, 0.0f);
        func_L00_0033E220(pos, obj, 0x40801420, -1, 1, -1, 0, 96, 73500.0f, 0.75f);
        func_002A7750(obj, 1, -1);
        break;
    case 1:
        hit = func_0035CBA0(obj, 0x4010000, 0);
        if (hit && !*(int *)stateData) {
            *(Quad *)a = 0;
            a[1] = a[0] = 3.0f;
            *(float *)(hit + 0x18) = 0.75f;
            FastVecScale(b, hit + 0x10, func_002A7878(6.0f, 8.0f));
            qcopy(c, b);
            FastVecSub(b, b, a);
            FastVecAdd(c, c, a);
            func_L00_0032A258(obj, b, D_L06_001B1C08, D_L06_001B1C00,
                             65535, -1, D_L06_001B1C30, 9, state, 255, 0);
            func_002A7750(obj, 2, -1);
        }
        ((unsigned char *)obj)[0xA8] = 255;
        break;
    case 2:
        func_L00_0032A258(obj, D_L06_001B1C10, D_L06_001B1C08, D_L06_001B1C00,
                         65535, 0, D_L06_001B1C30, 7, 62, 255, 0);
        func_L00_00326110(obj, 1, pos[2] * 0.33333334f);
        func_L01_0031A278(obj, a, pos[0], pos[1], pos[2]);
        SpawnExplosionEffects(obj, D_L06_001A8F20, a, 0, 0, 8, 3, 3, 0, 0, 9, 0.35f,
                      -1, 0, 0, 0, -1, 0, 0x810001);
        for (i = 0; i < 4; i++) {
            b[0] = (i / 2 * 2 - 1) * 0.0166666675f;
            b[1] = (i % 2 * 2 - 1) * 0.0166666675f;
            b[2] = 0.1166666746f;
            matrix_mul_vec3(b, b, obj + 0xC0);
            SpawnTintedEffects(obj, a, 3, 0, 1, b, 5, 0x7FFF8080, 0.45f, 0.6f, 0);
        }
        func_00350388(obj);
        break;
    }
}
