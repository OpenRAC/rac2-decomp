#include "common.h"

typedef int V4_325AE8 __attribute__((mode(TI)));

extern int func_0027C878(int);
extern void func_00282CF0(char *, char *, char *);
extern void func_00282F20(float, char *, char *);
extern void func_00282DD8(char *, char *, char *);
extern void func_00282D30(char *, char *, float);
extern void func_00282CC0(char *, char *, char *);
extern void func_002830C0(char *, char *, char *);
extern void func_00280B90(char *, char *, int);
extern char D_001B8DC0[];
extern float D_001AA310[16] SDATA(D_001AA310);

/* Draws a single camera-facing quad of the given color near a position. */
void func_L00_00325AE8(char *source, int color, float alpha, float distance)
{
    char work[0x90];
    float up[4];
    char basis[0x30];
    char position[16];
    char scaled[16];
    char *table;
    char *p;
    int i;

    *(V4_325AE8 *)up = 0;
    up[2] = 1.0f;
    up[3] = 1.0f;
    *(long long *)(work + 0x78) = GetEffectTextureDescriptor(0xB);
    *(long long *)(work + 0x88) = 0x0000008000000048LL;
    *(long long *)(work + 0x80) = 0x0000FF9000000260LL;
    *(long long *)(work + 0x70) = 5;
    *(int *)(work + 0x50) = 0;
    *(int *)(work + 0x54) = 0;
    *(int *)(work + 0x58) = 0;
    *(float *)(work + 0x5C) = 1.0f;
    *(float *)(work + 0x60) = 1.0f;
    *(int *)(work + 0x64) = 0;
    *(float *)(work + 0x68) = 1.0f;
    *(float *)(work + 0x6C) = 1.0f;
    qcopy(position, source);
    FastVecSub(basis, D_001B8DC0, position);
    vec_scale_to_length(1.0f, basis, basis);
    FastVecCross(basis + 0x10, basis, (char *)up);
    vec_scale_to_length(1.0f, basis + 0x10, basis + 0x10);
    FastVecCross(basis + 0x20, basis + 0x10, basis);
    FastVecScale(scaled, basis, distance);
    FastVecAdd(position, position, scaled);
    *(int *)(work + 0x4C) = color;
    *(int *)(work + 0x48) = color;
    *(int *)(work + 0x44) = color;
    *(int *)(work + 0x40) = color;
    table = (char *)D_001AA310;
    p = work;
    for (i = 3; i >= 0; i--) {
        FastVecScale(p, table, alpha);
        table += 0x10;
        transform_vector(p, p, basis);
        p += 0x10;
    }
    draw_world_quad(work, 0, 0);
}
