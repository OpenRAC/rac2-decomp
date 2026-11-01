#include "include_asm.h"

typedef int Quad __attribute__((mode(TI)));
extern void func_00283410(void *, void *);
extern void func_00283658(void *, void *);
extern void func_00283788(void *, void *, void *);
extern void func_00283678(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A10E8(void *);

void func_PAL_L00_003944E8(char *parent, char *context)
{
    Quad matrices[12];
    union { Quad quad; float f[4]; } offset;
    Quad result;
    char *child;
    float *height;
    if (*(char **)(context+0x20)==0) return;
    offset.quad=0;
    offset.f[1]=0.11f;
    child=*(char **)(context+0x20);
    height=(float *)(*(char **)(child+0x68)+0xC);
    if (*height>0.45f) *height=*height-0.060000002f;
    else if (*height<0.45f) *height=*height+0.060000002f;
    child=*(char **)(context+0x20);
    *(float *)(child+0xF8)=-1.8849558f;
    func_00283410(matrices+4, (*(char **)(context+0x20))+0xF0);
    func_00283658(matrices+8,parent+0xC0);
    func_00283788(matrices,matrices+8,matrices+4);
    func_00283678((*(char **)(context+0x20))+0xC0,matrices);
    func_002830C0(&result,&offset,matrices);
    func_00282CC0((*(char **)(context+0x20))+0x10,&result,parent+0x10);
    func_002A10E8(*(char **)(context+0x20));
}


#include "common.h"
typedef struct { int color[6]; } EffectPalette;
extern EffectPalette D_L00_001AF0F8, D_L00_001AF110;
extern char D_L00_001B8DC0[];
extern float D_L00_001B19CC MACRO_ADDR;
extern void *func_PAL_002BD400(void *, int, int, float, float, float, float, float);
extern void func_00282CF0(void *, void *, void *), func_00282C88(Quad *);
extern float func_00282DF0(void *), func_002A7878(float, float);
extern int func_00283CF0(float), func_002A77E0(s32), func_002A7820(s32, s32);
extern void *func_002BBCB0(void *, void *, int, int, int, int, int, int, float, float);
extern char *func_PAL_003096D0(void *, void *, void *, int, int, int, int, int, float);

/* Emits the tether's impact smoke, distance-weighted sparks and colored fragments. */
void func_PAL_L00_00394630(char *actor, int fragments) {
    float point[4] __attribute__((aligned(16)));
    float delta[4], velocity[4];
    EffectPalette first, second;
    int i, k, count, startLife, endLife;
    int *firstColor, *lastColor;
    float distance, nearPenalty, speed;
    qcopy(point, actor + 0x10);
    point[2] += 0.3f;
    func_PAL_002BD400(point, 1, 0x40808080, 0.3f, 1.01f, 1.075f, 0.05f, 50000.0f);
    for (k = 0; k < 5; k++)
        func_PAL_002BD400(point, 1, 0x40808080, 0.3f, 1.01f, 1.07f, 0.05f, 50000.0f);
    if (!fragments) return;
    func_00282CF0(delta, D_L00_001B8DC0, actor + 0x10);
    func_00282C88((Quad *)velocity);
    distance = func_00282DF0(delta);
    if (distance < 8.0f) count = func_00283CF0(distance) + 2;
    else count = 10;
    nearPenalty = 0;
    if (distance < 7.0f) nearPenalty = 7.0f - distance;
    for (i = 0; i < count; i++) {
        speed = func_002A7878(8.0f, 10.0f) * 0.020000001f;
        speed -= nearPenalty * 0.020000001f;
        first = D_L00_001AF0F8;
        second = D_L00_001AF110;
        firstColor = first.color + func_002A77E0(6);
        lastColor = second.color + func_002A77E0(6);
        startLife = func_002A7820(12, 17);
        endLife = func_002A7820(21, 25);
        func_002BBCB0(actor + 0x10, velocity, *firstColor, *lastColor, startLife, endLife, 0, 0,
                      400000.0f, speed);
    }
    if (D_L00_001B19CC < 0.95f) {
        func_PAL_003096D0(actor, actor + 0x10, velocity, 12, 0x7F, 0x7F, 0x7F, 0x20, 3.0f);
        func_PAL_003096D0(actor, actor + 0x10, velocity, 20, 0x7F, 0x20, 0, 0x20, 2.0f);
    }
    func_PAL_003096D0(actor, actor + 0x10, velocity, 17, 0x7F, 0x40, 0, 0x30, 3.0f);
    func_PAL_003096D0(actor, actor + 0x10, velocity, 22, 0x60, 0x10, 0, 0x40, 2.0f);
    func_PAL_003096D0(actor, actor + 0x10, velocity, 24, 0x20, 0, 0, 0x20, 1.0f);
}



