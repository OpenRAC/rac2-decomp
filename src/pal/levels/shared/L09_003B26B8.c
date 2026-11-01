#include "include_asm.h"

extern void func_00282CC0(char *first, char *second, char *third);
extern void func_00282F20(char *dst, char *src, float x);
extern void func_002AB668(void *a, void *b, float f);
extern void func_00282D30(char *a, char *b, float f);
extern void func_002ACDE8(char *a, char *b, char *c);
extern float func_00283BE0(float a, float b);
extern void func_L00_002E6CF0(char *table, char *object);
extern char D_L09_003AEF78[];

/* rebuilds the object's orientation matrix from its stored angles and hands it to the stage */
void func_PAL_L09_003B26B8(char *object)
{
    char *p = *(char **)(object + 0x68);
    float m[4];
    char *q = object + 0x10;
    char *r = p + 0x10;

    func_00282F20((char *)m, p + 0x30, 1.0f);
    func_002AB668(m, m, *(float *)(p + 0x5C));
    func_00282D30(r, p, *(float *)(p + 0x50));
    func_002ACDE8(r, r, (char *)m);
    *(float *)(p + 0x20) = -*(float *)(p + 0x10);
    *(float *)(p + 0x24) = -*(float *)(p + 0x14);
    *(float *)(p + 0x28) = -*(float *)(p + 0x18);
    func_00282CC0(r, q, r);
    func_00282CC0(p + 0x20, q, p + 0x20);
    *(float *)(p + 0x5C) = func_00283BE0(*(float *)(p + 0x5C), 0.37699118f);
    func_L00_002E6CF0(D_L09_003AEF78, object);
}

