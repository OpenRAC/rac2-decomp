#include "include_asm.h"
#include "names.h"

typedef int Quad __attribute__((mode(TI)));
extern void euler_to_matrix(void *, void *);
extern void copy_matrix_rotation(void *, void *);
extern void multiply_matrix(void *, void *, void *);
extern void copy_matrix3x4(void *, void *);
extern void transform_vector(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
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
    euler_to_matrix(matrices+4, (*(char **)(context+0x20))+0xF0);
    copy_matrix_rotation(matrices+8,parent+0xC0);
    multiply_matrix(matrices,matrices+8,matrices+4);
    copy_matrix3x4((*(char **)(context+0x20))+0xC0,matrices);
    transform_vector(&result,&offset,matrices);
    FastVecAdd((*(char **)(context+0x20))+0x10,&result,parent+0x10);
    func_002A10E8(*(char **)(context+0x20));
}


#include "common.h"
typedef struct { int color[6]; } EffectPalette;
extern EffectPalette D_L00_001AF0F8, D_L00_001AF110;
extern char g_camera_l00_position[];
extern float D_L00_001B19CC MACRO_ADDR;
extern void *func_PAL_002BD400(void *, int, int, float, float, float, float, float);
extern void FastVecSub(void *, void *, void *), vec_clear_128(Quad *);
extern float FastVecLength(void *), math_random_float_range(float, float);
extern int FloatToInt(float), math_random_int_below(s32), math_random_int_range(s32, s32);
extern void *part_spawn_firework_spark(void *, void *, int, int, int, int, int, int, float, float);
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
    FastVecSub(delta, g_camera_l00_position, actor + 0x10);
    vec_clear_128((Quad *)velocity);
    distance = FastVecLength(delta);
    if (distance < 8.0f) count = FloatToInt(distance) + 2;
    else count = 10;
    nearPenalty = 0;
    if (distance < 7.0f) nearPenalty = 7.0f - distance;
    for (i = 0; i < count; i++) {
        speed = math_random_float_range(8.0f, 10.0f) * 0.020000001f;
        speed -= nearPenalty * 0.020000001f;
        first = D_L00_001AF0F8;
        second = D_L00_001AF110;
        firstColor = first.color + math_random_int_below(6);
        lastColor = second.color + math_random_int_below(6);
        startLife = math_random_int_range(12, 17);
        endLife = math_random_int_range(21, 25);
        part_spawn_firework_spark(actor + 0x10, velocity, *firstColor, *lastColor, startLife, endLife, 0, 0,
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



