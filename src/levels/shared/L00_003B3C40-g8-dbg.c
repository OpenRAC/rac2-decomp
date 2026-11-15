#include "include_asm.h"
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002ACEC0(void *, void *, void *, float);
extern float func_002A7940(void);
extern int func_002A77E0(int);
extern float func_00283CE0(int);
extern char *func_002BDCE8(char *, float, float, float, float, int, char *, int, int);
extern char D_L00_001B8DC0[];
extern char D_L00_001A8F20[] MACRO_ADDR;
extern float D_L00_001AF8FC __attribute__((sda));
extern int D_L00_001AF900 __attribute__((sda));
extern int D_L00_001AF904 __attribute__((sda));
extern float D_L00_001AF908 __attribute__((sda));
extern float D_L00_001AF90C __attribute__((sda));
extern int D_L00_001AF910 __attribute__((sda));
extern int D_L00_001AF914 __attribute__((sda));

/* Throws out a few spark particles away from the camera, plus an occasional puff of smoke, around the object. */
void func_L00_003B3C40(char *object)
{
    union { Quad q; float f[4]; } position;
    float a[4], b[4], c[4], d[4];
    int angle;
    int r;
    float t;
    char *p;
    position.q = 0;
    position.f[2] = D_L00_001AF908;
    FastVecSub(a, gCameraPosition_L00, object + 0x10);
    ApplyAxisRotationToQuaternion(b, &position, a, RandomAngle());
    FastVecAdd(c, object + 0x10, b);
    r = RandomIntBelow(0x10);
    if (RandomIntBelow(2))
        r = -r;
    angle = D_L00_001AF904;
    t = D_L00_001AF908 / IntToFloat(angle);
    vec_scale_to_length(d, b, -t);
    p = SpawnSpinningSparkParticle((char *)c, 0.5f, 1.0f, 0.99f, D_L00_001AF8FC * 210000.0f, r, (char *)d, D_L00_001AF900, 0);
    if (p) {
        char *s = p + 0x20;
        *(short *)(p + 0xA) = angle;
        *(int *)(s + 4) = 3;
        s[0xA] = 0x7F;
        s[0xB] = *(unsigned char *)(p + 0xA);
    }
    if (RandomIntBelow(3) == 0) {
        vec_scale_to_length(a, a, -0.5f);
        FastVecAdd(c, object + 0x10, a);
        p = SpawnSpinningSparkParticle((char *)c, 0.1f, 1.0f, 0.8f, D_L00_001AF90C * 210000.0f, r, D_L00_001A8F20, (D_L00_001AF910 & 0xFFFFFF) | (D_L00_001AF914 << 24), 0);
        if (p) {
            char *s = p + 0x20;
            *(short *)(p + 0xA) = 0x3C;
            p[3] = 0x44;
            *(int *)(s + 4) = 3;
            s[0xA] = *(unsigned char *)&D_L00_001AF914;
            s[0xB] = *(unsigned char *)(p + 0xA);
        }
    }
}
