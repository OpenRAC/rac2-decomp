#include "common.h"
extern float func_00283180(float), func_00283198(float);
extern float func_00283B98(float, float), func_00283BE0(float, float);
extern void func_00282CC0(void *, void *, void *), func_00282C88(void *);
extern void func_0027D330(int), func_L01_002B35E8(int), func_L00_002B9D60(void *, void *, int, int), func_002E5CF8(int, int, void *);
extern void func_00335438(void *, void *, int, int, int), func_00335370(void *), func_003353C8(void *);
extern void func_002A7470(void *, int, int, int), func_L00_002D2168(int, int, float);

extern unsigned char D_001A7A45;
extern int D_L01_001B1FA8;
typedef struct {
    char pad[0x80];
    float pos[4];
    float rot[4];
    char pad2[0x2214];
    unsigned char state;
    char pad3[10];
    unsigned char flag;
} TransitionPlayerState;
extern TransitionPlayerState D_00189E20;
void func_L01_00397110(unsigned char *m) {
    float a[4], b[4], c[4], d[4];
    char *p = *(char **)(m + 0x68);
    a[0] = func_00283180(*(float *)(p + 0x1C))*2.5f;
    a[1] = func_00283198(*(float *)(p + 0x1C))*2.5f;
    a[2] = 0;
    FastVecAdd(a, a, p + 0x10);
    func_00282C88(b);
    b[2] = FastAddRotations(*(float *)(p + 0x1C), 3.1415929794311523f);
    FadeToBlack(10);
    if (D_00189E20.state == 3) func_L01_002B35E8(0);
    func_L00_002B9D60(a, b, 0x6F, 0);
    PlayMobySound(0, 0, m);
    c[0] = func_00283180(*(float *)(p + 0x1C))*1.25f;
    c[1] = func_00283198(*(float *)(p + 0x1C))*1.25f;
    c[2] = 0;
    c[0] += func_00283180(FastAddRotations(*(float *)(p + 0x1C), 1.5707964897155762f))*4.0f;
    c[1] += func_00283198(FastAddRotations(*(float *)(p + 0x1C), 1.5707964897155762f))*4.0f;
    FastVecAdd(c, c, p + 0x10);
    c[2] += 1;
    func_00282C88(d);
    d[2] = fast_subtract_rotations(*(float *)(p + 0x1C), 1.5707964897155762f);
    SetCamera5Pose(c, d, 1, 0, 0);
    func_00335370(c);
    func_003353C8(d);
    qcopy_nc(m + 0x10, D_00189E20.pos);
    qcopy_nc(m + 0xF0, D_00189E20.rot);
    if (m[0x43] != 1) func_002A7470(m, 1, 0, 0);
    set_hero_animation(0x7B, 0, 0.0f);
    if (D_001A7A45) *(unsigned short *)(m + 0x34) |= 0x8000;
    D_00189E20.flag = 1;
    D_L01_001B1FA8 = 1;
    m[0x20] = 2;
    *(int *)(p + 0x6C) = 60;
}
